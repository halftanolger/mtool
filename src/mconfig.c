#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "mconfig.h"

static void print_regerror(int, regex_t*);
static void print_config_error(const char * filename, int line_count, const char * data);
static int check_line(char *line, char *key, char *value, regex_t *regex);
static int store_config(Mconfig *mconfig, char * key, char * value);

Mconfig * mconfig_new (const char * filename) {

	assert (filename != NULL);
	assert (strlen(filename) > 1);

	Mconfig * _mconfig = (Mconfig*)malloc(sizeof(Mconfig));

	if (_mconfig == NULL) {
		fprintf (stderr, "Error: can't malloc. %s\n", strerror (errno));
		return NULL;
	}

	_mconfig->filename = strdup (filename);
	_mconfig->parse_error = 0;
	_mconfig->application_name = NULL;
	_mconfig->application_version_minor = 0;
	_mconfig->application_version_major = 0;
	_mconfig->application_min_number_of_lines = 0;
	_mconfig->application_min_number_of_columns = 0;
	_mconfig->log_console = NULL;
	_mconfig->log_filename = NULL;
	_mconfig->log_level = NULL;

	if (_mconfig->filename == NULL) {
		fprintf (stderr, "Error: can't strdup. %s\n", strerror (errno));
		return NULL;
	}

	/* Make som regex to help parse the config file */

	regex_t regex_key_value;
	int r = regcomp (&regex_key_value, 
			"^([a-z'_']+) = ([a-zA-Z0-9'.''~''/']+)", 
			REG_EXTENDED);

	if (r != 0) 
	{
		print_regerror (r, &regex_key_value);
		regfree (&regex_key_value);
		return NULL;
	}

	regex_t regex_comment;
	r = regcomp (&regex_comment, 
			"^[' ']*['#']+", 
			REG_EXTENDED);

	if (r != 0) 
	{
		print_regerror (r, &regex_comment);
		regfree (&regex_key_value);
		regfree (&regex_comment);
		return NULL;
	}

	regex_t regex_empty_line;
	r = regcomp (&regex_empty_line, 
			"^[' ']+", 
			REG_EXTENDED);

	if (r != 0) 
	{
		print_regerror (r, &regex_empty_line);
		regfree (&regex_key_value);
		regfree (&regex_comment);
		regfree (&regex_empty_line);
		return NULL;
	}

	regex_t regex_new_line;
	r = regcomp (&regex_new_line, 
			"^['\n']+", 
			REG_EXTENDED|REG_NEWLINE);

	if (r != 0) 
	{
		print_regerror (r, &regex_new_line);
		regfree (&regex_key_value);
		regfree (&regex_comment);
		regfree (&regex_empty_line);
		regfree (&regex_new_line);
		return NULL;
	}



	/* Read and parse the config-file */

	FILE *fp = fopen (_mconfig->filename, "r");

	if (fp == NULL) {
		fprintf (stderr, "Error: can't fopen. %s\n", strerror (errno));
		return NULL;
	}

	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;

	line_size = getline (&line_buf, &line_buf_size, fp);

	char key[256];
	char value[256];

	while (line_size >= 0) {

		line_count++;

		if (line_size == 0)
			continue;

		//printf("line[%03d]: chars=%03zd, buf size=%03zu,contents: %s", 
		//		line_count, line_size,line_buf_size, line_buf);

		strcpy(key,"nop");
		strcpy(value,"nop");

		char *d = line_buf;

		r = check_line (d,
			(char*)&key,
			(char*)&value,
			&regex_key_value);

		if (r == 0) {

			//printf("key=%s value=%s\n",key,value);
			int rs = store_config(_mconfig,(char*)&key,(char*)&value);

			if ( rs > 0) {

				char buff[256];
				sprintf(buff,"Unknown input: key=%s value=%s",key,value);			
                             	print_config_error(filename, 
						line_count, (char*)buff);

				_mconfig->parse_error = 1;

			}

		} else {

			r = check_line (d,
				(char*)&key,
				(char*)&value,
				&regex_comment);

			if (r == 0) {

				/* Ok, this i a comment-line,
				 * starting with # */

				//printf("a comment line\n");

			} else {

				r = check_line (d,
					(char*)&key,
					(char*)&value,
					&regex_empty_line);

				if (r == 0) {

					/* Ok, this is a blanck/empty 
					 * line containing spaces */

					//printf("empty line\n");

				} else {

					r = check_line (d,
						(char*)&key,
						(char*)&value,
						&regex_new_line);

					if (r == 0) {

						/* Ok, this is a line 
						 * containing just a newline
						 */
						//printf ("new line\n");

					} else {
						
						/* This is not an ok line. */

						_mconfig->parse_error = 1;

						int a = strlen(d)-1;
						if (d[a] == '\n') d[a] = '\0';

                             			print_config_error(filename, 
								line_count, d);
					
					}
				}
			}
		}
	
		line_size = getline(&line_buf, &line_buf_size, fp);

	}

	free (line_buf);
	line_buf = NULL;

	fclose (fp);

	regfree (&regex_key_value);
	regfree (&regex_comment);
	regfree (&regex_empty_line);
	regfree (&regex_new_line);

	if (_mconfig->parse_error == 1) {
		mconfig_delete(&_mconfig);
		_mconfig = NULL;
	}

	return _mconfig;

}

void mconfig_delete (Mconfig ** mconfig) {

	assert (*mconfig != NULL);

	if ((*mconfig)->filename != NULL)
		free ((*mconfig)->filename);

	if ((*mconfig)->application_name != NULL)
		free ((*mconfig)->application_name);

	if ((*mconfig)->log_console != NULL)
		free ((*mconfig)->log_console);

	if ((*mconfig)->log_filename != NULL)
		free ((*mconfig)->log_filename);

	if ((*mconfig)->log_level != NULL)
		free ((*mconfig)->log_level);

	free (*mconfig);

	return;
}

/* These are some private helper-functions */

static int check_line(char *line, char *key, char *value, regex_t *regex) {

	int nsub = (int)regex->re_nsub + 1;
	size_t nmatch = nsub;
	regmatch_t pmatch[nsub];

	if (regexec (regex, line, nmatch, pmatch, 0) != 0)
		return 1;

	if (nsub == 1 )
		return 0;

	strncpy (key, &line[pmatch[1].rm_so], 
			pmatch[1].rm_eo - pmatch[1].rm_so);

	strncpy (value, &line[pmatch[2].rm_so], 
			pmatch[2].rm_eo - pmatch[2].rm_so);

	int l =  (int)(pmatch[1].rm_eo - pmatch[1].rm_so);
	key[l]=0;

	l =  (int)(pmatch[2].rm_eo - pmatch[2].rm_so);
	value[l]=0;

	return 0;
}



static int store_config(Mconfig *mconfig, char * key, char * value) {

	assert (key != NULL);
	assert (value != NULL);
	assert (strlen(key) > 0);
	assert (strlen(value) > 0);

	if (strcmp(key,"mtool_application_name") == 0) {
		mconfig->application_name = strdup(value);
	} else  

	if (strcmp(key,"mtool_application_version_minor") == 0) {
		mconfig->application_version_minor = atoi(value);
	} else  

	if (strcmp(key,"mtool_application_version_major") == 0) {
		mconfig->application_version_major = atoi(value);
	} else  
		
	if (strcmp(key,"mtool_application_min_number_of_lines") == 0) {
		mconfig->application_min_number_of_lines = atoi(value);
	} else  
		
	if (strcmp(key,"mtool_application_min_number_of_columns") == 0) {
		mconfig->application_min_number_of_columns = atoi(value);
	} else  
		
	if (strcmp(key,"mtool_log_console") == 0) {
		mconfig->log_console = strdup(value);
	} else  
	
	if (strcmp(key,"mtool_log_filename") == 0) {
		mconfig->log_filename = strdup(value);
	} else  

	if (strcmp(key,"mtool_log_level") == 0) {
		mconfig->log_level = strdup(value);
	} else {
		return 1;
	}

	return 0;
}

static void print_regerror(int errorcode, regex_t *regex) {

	size_t ERR_BUFF_SIZE = 256;
	char errbuff[ERR_BUFF_SIZE];

	regerror (errorcode, regex, (char*)&errbuff, ERR_BUFF_SIZE);

	fprintf (stderr, "Error: regerror = %s\n", errbuff);

	return;
}

static void print_config_error(const char * filename, int line_count, const char * data) {

	fprintf (stderr, "\n-------------------------------------\n");
	fprintf (stderr, "===>>>  unknown stuff in config <<===\n");
        fprintf (stderr, "-------------------------------------\n");
	fprintf (stderr, "configfile: %s\n", filename); 
	fprintf (stderr, "linenr    : %d\n",line_count);
	fprintf (stderr, "data      : %s\n",data);
        fprintf (stderr, "-------------------------------------\n\n");

}

