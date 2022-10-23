#include <stdio.h>
#include "mutil.h"

void mutil_info_print_all_config (Mapp *mapp) {

	char buff[256];
	const char * signatur = "mutil_info_print_all_config(Mapp*)";

	sprintf (buff,"mtool_application_name = %s", 
			mapp->mconfig->application_name);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_application_version_minor = %d", 
			mapp->mconfig->application_version_minor);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_application_version_major = %d", 
			mapp->mconfig->application_version_major);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_application_min_number_of_lines = %d", 
			mapp->mconfig->application_min_number_of_lines);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_application_min_number_of_columns = %d", 
			mapp->mconfig->application_min_number_of_columns);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_log_console = %s", 
			mapp->mconfig->log_console);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_log_filename = %s", 
			mapp->mconfig->log_filename);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);

	sprintf (buff,"mtool_log_level = %s", 
			mapp->mconfig->log_level);
	mlog_log (mapp->mlog, MLOG_INFO, signatur, (char*)buff);



}
