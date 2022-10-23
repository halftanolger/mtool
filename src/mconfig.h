#ifndef _MCONFIG_H_
#define _MCONFIG_H_

typedef struct mconfig_st {

	char * filename;
	char parse_error;
	char * application_name;
	int application_version_minor;
	int application_version_major;
	int application_min_number_of_lines;
	int application_min_number_of_columns;
	char * log_console;
	char * log_filename;
	char * log_level;

} Mconfig;

Mconfig * mconfig_new(const char *);

void mconfig_delete(Mconfig **);

#endif // _MYCONFIG_H_
