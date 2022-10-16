//---------------------------------------------------------------------------//
//                                                                           //
//  mytool                                                                   //
//                                                                           //
//---------------------------------------------------------------------------//

#include <iostream>

#include "mtool.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Boot mytool .." << endl;

	mtool m;
	m.init(argc,argv);
	int r = m.run();

	return r;
}

