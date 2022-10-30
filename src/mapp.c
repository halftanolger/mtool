#include <ncurses.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapp.h"
#include "mutil.h"
#include "mmenu.h"
#include "mmenubar.h"

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
	mlog_log (mapp->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	mutil_info_print_all_config (mapp);

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	if (!has_colors()) {
		mlog_log (mapp->mlog, MLOG_ERROR, 
				signatur, 
				__FILE__, __LINE__,
				"Terminal does not support color!");
		return 1;
	}

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	mlog_log (mapp->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");
	return 0;
}

int mapp_run (Mapp *mapp) {

	assert (mapp != NULL);

	const char * signatur = "mapp_run(Mapp*)";
	mlog_log (mapp->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");


	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//WINDOW *win = newwin (yMax / 2, xMax / 2, yMax / 4, xMax / 4);
	WINDOW *win = newwin (yMax , xMax , 0, 0);
	//box(win, 0,0);

	char *items_file[]={"Site a", "Site b", "Exit", NULL};
	char *items_edit[]={"Edit one", "Edit two", "Edit tree", NULL};
	char *items_options[]={"Opt one", "Opt two", "Opt tree", NULL};
	char *items_help[]={"Help", "About", NULL};

	Mmenu *menu_file = mmenu_new(mapp,"File",'f', items_file);

	if (menu_file == NULL) {
		mlog_log (mapp->mlog, MLOG_ERROR, 
				signatur, 
				__FILE__, __LINE__,
				"mmenu_new() == null, I'm out of here!");
		return 1;
	}

	Mmenu *menu_edit = mmenu_new(mapp,"Edit", 'e', items_edit);

	if (menu_edit == NULL) {
		mlog_log (mapp->mlog, MLOG_ERROR, 
				signatur, 
				__FILE__,__LINE__,
				"mmenu_new() == null, I'm out of here!");
		return 1;
	}

	Mmenu *menu_options = mmenu_new(mapp, "Options", 'o', items_options);

	if (menu_options == NULL) {
		mlog_log (mapp->mlog, MLOG_ERROR, 
				signatur,
			       __FILE__,__LINE__,	
				"mmenu_new() == null, I'm out of here!");
		return 1;
	}

	Mmenu *menu_help = mmenu_new(mapp, "Help", 'h', items_help);

	if (menu_help == NULL) {
		mlog_log (mapp->mlog, MLOG_ERROR, 
				signatur,
			       __FILE__,__LINE__,	
				"mmenu_new() == null, I'm out of here!");
		return 1;
	}

	Mmenu *menus[] = {
		menu_file, 
		menu_edit, 
		menu_options,
		menu_help,
		NULL
	};

	Mmenubar *menubar = mmenubar_new (mapp, win, menus);
	mmenubar_draw (menubar);

	char ch;
	while (1) {
		ch = wgetch (menubar->win);	
		mmenubar_handle_trigger (menubar, ch);
		mmenubar_draw (menubar);
	}



	/*
	refresh();
	wrefresh(win);

	keypad(win,true);
	
	char *choices[3] = {"Walk", "Jog", "Run"};
	int choice;
	int highlight = 2;


	while (1) {

		for (int i=0; i<3; i++) {
			if (i == highlight) {
				wattron (menuwin, A_REVERSE);		
			}
			mvwprintw (menuwin, i+1, 1, choices[i]);
			wattroff (menuwin, A_REVERSE);
		}
		choice = wgetch (menuwin);

		switch (choice) {
			case KEY_UP:
				highlight==0?highlight=0:highlight--;
				break;
			case KEY_DOWN:
				highlight==2?highlight=2:highlight++;
				break;
			default:
				break;	
			
		}
		if (choice == 10) {
			break;
		}

	}

	refresh();
	getch();
*/
	mlog_log (mapp->mlog, MLOG_INFO, 
			signatur,
		       __FILE__, __LINE__,	
			"Exit function");
	return 0;
}

void mapp_delete (Mapp **mapp) {

	assert ((*mapp) != NULL);

	const char * signatur = "mapp_delete(Mapp*)";
	mlog_log ((*mapp)->mlog, MLOG_INFO, 
			signatur,
		       __FILE__, __LINE__,	
			"Enter function");

	endwin();

}
