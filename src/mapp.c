#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapp.h"
#include "mutil.h"

Mapp * mapp_new (const char * filename) {

	Mapp *mapp = (Mapp*)malloc(sizeof(Mapp));

	if (mapp == NULL) {
		fprintf (stderr, "Error, can't malloc. %s\n", 
				strerror (errno));
		return NULL;
	}

	mapp->mconfig = mconfig_new (filename);
	if (mapp->mconfig == NULL)
		return NULL;

	mapp->mlog = mlog_new (mapp->mconfig);
	if (mapp->mlog == NULL)
		return NULL;

	return mapp;
}

int mapp_init (Mapp *mapp) {

	assert (mapp != NULL);

	const char * signatur = "mapp_init(Mapp*)";
	mlog_log (mapp->mlog, MLOG_INFO, signatur, "Enter function");

	mutil_info_print_all_config (mapp);

	//TODO:

	mlog_log (mapp->mlog, MLOG_INFO, signatur, "Exit function");
	return 0;
}

int mapp_run (Mapp *mapp) {

	assert (mapp != NULL);

	const char * signatur = "mapp_run(Mapp*)";
	mlog_log (mapp->mlog, MLOG_INFO, signatur, "Enter function");

	//TODO:

	mlog_log (mapp->mlog, MLOG_INFO, signatur, "Exit function");
	return 0;
}

void mapp_delete (Mapp **mapp) {

	assert ((*mapp) != NULL);

	const char * signatur = "mapp_delete(Mapp*)";
	mlog_log ((*mapp)->mlog, MLOG_INFO, signatur, "Enter function");

	//TODO:

}
