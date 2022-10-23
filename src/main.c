#include <stdio.h>
#include <string.h>
#include "mapp.h"

static int show_usage();

int main(int argc, char* argv[])
{
	if (argc != 3)
       		return show_usage(argv[0]);
	
	if (strcmp("-config",argv[1]) != 0)
		return show_usage(argv[0]);

	Mapp *mapp = mapp_new (argv[2]);

	if (mapp == NULL)
		return 1;

	int rcode = mapp_init (mapp);

	if (rcode != 0)
		return rcode;

	rcode = mapp_run (mapp);

	mapp_delete (&mapp);

	return 0;	
}

int show_usage(const char* name) {
	fprintf (stderr, "usage: %s -config <filename>\n", name);
	return 1;
}	

