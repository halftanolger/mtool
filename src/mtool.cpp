
#include <cstdio>
#include <ncurses.h>
#include "mtool.h"

mtool::mtool() 
{
	initscr();
}

mtool::~mtool() 
{
	endwin();
}

int mtool::init(int argc, char *argv[])
{
	_minimum_number_of_lines = 24;
	_minimum_number_of_columns = 80;
	_application_name = "mtop";
	_application_version = "0.0";


	return 0;
}

int mtool::run() 
{

	char buffer[255];
   	sprintf(buffer,"%s ver.%s l:%d c:%d",
			_application_name.c_str(),
			_application_version.c_str(),
			LINES,COLS);
	int length = strlen(buffer);
	mvprintw(LINES-1,COLS-length,buffer);

	char c = 0;
	do {

		mvprintw(LINES - 1, 0, " Q -quit  J -down  K -up  nn -select ");


		c = getch();

	} while (c != 'q');

	return 0;
}

