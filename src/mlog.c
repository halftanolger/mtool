
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "mlog.h"


mlog * mlog_new (mconfig * _myconfig) {

	assert (_myconfig != NULL);

	mlog * _mlog = (mlog*)malloc(sizeof(mlog));

	if (_mlog == NULL) {
		fprintf (stderr, "Error: can't malloc. %s\n", strerror (errno));		return NULL;
	}

	//TODO: get these from the config-file ...
	
	_mlog->active = 1;
	
	strcpy (_mlog->signature, "nop");

	return _mlog;

}

void mlog_delete (mlog **_mlog) {

	if (*_mlog == NULL)
		return;

	free (*_mlog);

}

void mlog_log (mlog * _mlog, mlog_type type, 
		const char* signatur , const char* message) {

	assert (_mlog != NULL);
	assert (signatur != NULL);
	assert (message != NULL);
	assert (strlen(signatur) < 80);

	if (_mlog->active == 0) 
		return;

	time_t rawtime;
	struct tm * timeinfo;
	char text[128];
	char *type_text;
	char *type_text_inf = "INF";
	char *type_text_err = "ERR";

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	if (type == INFO) {
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

