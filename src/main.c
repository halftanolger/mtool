//---------------------------------------------------------------------------//
//                                                                           //
//  mtool                                                                    //
//                                                                           //
//---------------------------------------------------------------------------//

#include <stdio.h>
#include <string.h>

#include "mconfig.h"
#include "mlog.h"

/* These are global variabels */

const char * mtool_infostring = "mtool ver. 0.0";

mlog * _mlog;
mconfig * _mconfig;

static int show_usage();

/* The main */ 

int main(int argc, char* argv[])
{

	/* We demand a config-file as argument. */

	if (argc != 3)
       		return show_usage(argv[0]);
	
	if (strcmp("-config",argv[1]) != 0)
		return show_usage(argv[0]);

	/* Initialize the config- object/struct with this configfile. */

	_mconfig = mconfig_new (argv[2]);

	if (_mconfig == NULL) 
		return 1;

	/* Make a log -object/struc. It's always nice to have. */

	_mlog = mlog_new (_mconfig);

	if (_mlog == NULL) {
		mconfig_delete (&_mconfig);
		return 1;
	}

	const char * signatur = "main(int,char**)";
	mlog_log (_mlog, INFO, signatur, mtool_infostring); 

	mlog_log (_mlog, INFO, signatur, "TheStart"); 


	/* Ok, start the tool. */

	//todo: 
	mlog_log (_mlog, INFO, signatur, "todo: everything ..."); 

	mlog_log (_mlog, INFO, signatur, "TheEnd"); 

	mlog_delete (&_mlog);
	mconfig_delete (&_mconfig);

	return 0;	
}

int show_usage(const char* name) {
	fprintf (stderr, "usage: %s -config <filename>\n", name);
	return 1;
}	

