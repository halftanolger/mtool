
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "mlog.h"


Mlog * mlog_new (Mconfig * mconfig) {

	assert (mconfig != NULL);

	Mlog * mlog = (Mlog*)malloc(sizeof(Mlog));

	if (mlog == NULL) {
		fprintf (stderr, "Error: can't malloc. %s\n", 
				strerror (errno));		
		return NULL;
	}
	
	mlog->active = strcmp(mconfig->log_console,"on") == 0?1:0;
	mlog->level = strcmp(mconfig->log_level,"info") == 0?MLOG_INFO:MLOG_ERROR;

	strcpy (mlog->signature, "nop");

	return mlog;

}

void mlog_delete (Mlog ** mlog) {

	if ((*mlog) == NULL)
		return;

	free (*mlog);

}

void mlog_log (Mlog * mlog, mlog_type type, 
		const char* signatur , const char* message) {

	assert (mlog != NULL);
	assert (signatur != NULL);
	assert (message != NULL);
	assert (strlen(signatur) < 80);

	if (mlog->active == 0) 
		return;

	if (type == MLOG_INFO && mlog->level == MLOG_ERROR)
	       return;	

	time_t rawtime;
	struct tm * timeinfo;
	char text[128];
	char *type_text;
	char *type_text_inf = "INF";
	char *type_text_err = "ERR";

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	if (type == MLOG_INFO) {
		type_text = type_text_inf;
	} else {
		type_text = type_text_err;
	}

	sprintf (text, "%d:%d:%d %s %s: ", timeinfo->tm_hour,
			timeinfo->tm_min, timeinfo->tm_sec,
			type_text, signatur);

	fprintf (stderr, "%s %s\n", text, message);

	return;

}

