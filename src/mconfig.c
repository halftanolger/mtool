#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mconfig.h"


mconfig * mconfig_new (const char * filename) {

	assert (filename != NULL);
	assert (strlen(filename) > 1);

	mconfig * _mconfig = (mconfig*)malloc(sizeof(mconfig));

	if (_mconfig == NULL) {
		fprintf (stderr, "Error: can't malloc. %s\n", strerror (errno));
		return NULL;
	}

	_mconfig->filename = strdup (filename);

	if (_mconfig->filename == NULL) {
		fprintf (stderr, "Error: can't strdup. %s\n", strerror (errno));		return NULL;
	}

	FILE *f = fopen (_mconfig->filename, "r");

	if (f == NULL) {
		fprintf (stderr, "Error: can't fopen. %s\n", strerror (errno));
		return NULL;
	}

	//TODO: parse file ..
	
	return _mconfig;
}

void mconfig_delete (mconfig ** _mconfig) {

	assert (*_mconfig != NULL);

	free ((*_mconfig)->filename);

	free (*_mconfig);

	return;
}


	
