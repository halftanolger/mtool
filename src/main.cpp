//---------------------------------------------------------------------------//
//                                                                           //
//  mytool                                                                   //
//                                                                           //
//---------------------------------------------------------------------------//

#include <signal.h>
#include <iostream>
#include <ncurses.h>

#include "mtool.h"

using namespace std;

void resize(int);

int main(int argc, char* argv[])
{
	cout << "Boot mytool .." << endl;

	void (*resizeHandler)(int);
	resizeHandler = resize;
	signal(SIGWINCH, resizeHandler);

	mtool m;
	m.init(argc,argv);
	int r = m.run();

	return r;
}

void resize(int sig)

	// make a singleton of mtool, get it, and redraw ...{
	cout << "rsize?" << endl;
}
