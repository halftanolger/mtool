//---------------------------------------------------------------------------//
//                                                                           //
//  mytool                                                                   //
//                                                                           //
//---------------------------------------------------------------------------//

#include <stdio.h>

#include "myconfig.h"

myconfig * _myconfig;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		fprintf (stderr, "usage: %s -config <filename>\n");
		return 1;
	}

	//_myconfig = myconfig_new(

	return 0;	
}

