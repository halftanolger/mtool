
#include <ncurses.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mmenubar.h"


Mmenubar * mmenubar_new (Mapp *app, WINDOW *win, Mmenu **menus) {

	assert (app != NULL);
	assert (win != NULL);
	assert ((*menus) != NULL);

	const char *signatur = "mmenubar_new(Mapp*,WINDOW*,Mmenu**)";
	mlog_log (app->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	Mmenubar *menubar = (Mmenubar*)malloc(sizeof(Mmenubar));

	if (menubar == NULL) {

		char buffer[256];
		sprintf (buffer, "Error, can't malloc. %s\n",
				strerror (errno));

		mlog_log (app->mlog, MLOG_ERROR, 
				signatur, 
				__FILE__, __LINE__,
				(char*)buffer);

		return NULL;
	}

	menubar->app = app;
	menubar->win = win;
	menubar->menus = menus;
	menubar->selected_index = -1;


	int index = 0;
	Mmenu *c;
	while (1) {
		c = (Mmenu*) (menus[index]);
		if (c != NULL) {
			index++;
		} else {
			break;
		}
		if (index == 100)
			break;
	}
	
	char buffer[256];
	sprintf(buffer,"There are %d menus on the bar",index);
	mlog_log (app->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			buffer);

	if (index == 100) {

		sprintf (buffer, "Error: The input argument Mmenu** must be \
				terminated with a null -element. This is \
				probably not the case here.");

		mlog_log (app->mlog, MLOG_ERROR, 
				signatur, 
				__FILE__, __LINE__,
				buffer);

		return NULL;
	}


	
	menubar->number_of_menus = index;

	int current_pos = 2;

	for (int i = 0; i < menubar->number_of_menus; i++) {

		Mmenu *m = (Mmenu*) (menus[i]);		
		m->start_x = current_pos;
		current_pos += strlen(m->name) + 1;

		sprintf(buffer,"Menu %s starts at x=%d",m->name,m->start_x);
		mlog_log (app->mlog, MLOG_INFO, 
				signatur, 
				__FILE__, __LINE__,
				buffer);

	}


	//todo: calculate the size using the item-name-length ..

	int yMax, xMax, yBeg, xBeg;
	getmaxyx(menubar->win, yMax, xMax);
	getbegyx(menubar->win, yBeg, xBeg);

	menubar->menuwin = newwin(yMax - 2, xMax - 2, yBeg + 1, xBeg + 1);
	keypad (menubar->menuwin, true);
	wrefresh (menubar->menuwin);

	mlog_log (app->mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");

	return menubar;

}


void mmenubar_reset (Mmenubar *menubar) {

	assert (menubar !=  NULL);
	assert (menubar->app != NULL);
	assert (menubar->app->mlog != NULL);

	Mlog *mlog = menubar->app->mlog;
	const char *signatur = "mmenubar_reset(Mmenubar*)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	for (int i = 0; i < menubar->number_of_menus; i++) {
		Mmenu *m = (Mmenu*) (menubar->menus[i]);
		mvwprintw (menubar->win, 0, m->start_x, m->name); 
	}

	wrefresh (menubar->win);

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");	
}

void mmenubar_draw (Mmenubar *menubar) {

	assert (menubar !=  NULL);
	assert (menubar->app != NULL);
	assert (menubar->app->mlog != NULL);

	Mlog *mlog = menubar->app->mlog;
	const char *signatur = "mmenubar_draw(Mmenubar*)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	for (int i = 0; i < menubar->number_of_menus; i++) {
		
		Mmenu *m = (Mmenu*) (menubar->menus[i]);
		char is_selected = (menubar->selected_index == i);
		mmenubar_draw_menu (menubar, m, is_selected);

	}

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");	
}


void mmenubar_draw_menu (Mmenubar *menubar, Mmenu *menu, char is_selected) {

	assert (menubar !=  NULL);
	assert (menubar->app != NULL);
	assert (menubar->app->mlog != NULL);

	Mlog *mlog = menubar->app->mlog;
	const char *signatur = "mmenubar_draw_menu(Mmenubar*,char)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	if (is_selected == 1)
		wattron (menubar->win, A_STANDOUT);

	mvwprintw (menubar->win, 0, menu->start_x, menu->name); 

	if (is_selected == 1)
		wattroff (menubar->win, A_STANDOUT);

	wrefresh(menubar->win);

	char buffer[256];
	sprintf (buffer,"name = %s, is_selected = %d", menu->name, is_selected);
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			buffer);
	
	if (is_selected != 1) {
		return;
	}


	int ch;

	mmenubar_draw_menu_items (menubar, menu);
	wrefresh (menubar->menuwin);

	while (is_selected == 1 && (ch = wgetch (menubar->menuwin))) {

		switch (ch) {

		case KEY_DOWN:
			mmenu_select_next_item (menu);
			break;

		case KEY_UP:
			mmenu_select_previous_item (menu);
			break;

		default:
			is_selected = -1;

		}

		mmenubar_draw_menu_items (menubar, menu);

	}

	werase (menubar->menuwin);
	wrefresh (menubar->menuwin);	
	mmenubar_reset (menubar);

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");
}


void mmenubar_draw_menu_items (Mmenubar *menubar, Mmenu *menu) {
	
	int yMax, xMax;
	getmaxyx (menubar->menuwin, yMax, xMax);

	for (int i=0; i<menu->number_of_items; i++) {

		mvwprintw (menubar->menuwin, i, 0, menu->items[i]);

		if ( i == menu->selected_item ) {

			mvwchgat (menubar->menuwin,i,0,xMax,A_NORMAL,1,NULL);

		} else {

			mvwchgat (menubar->menuwin,i,0,xMax,A_STANDOUT,0,NULL);

		}

	}
}


void mmenubar_handle_trigger (Mmenubar *menubar, const char trigger) {

	assert (menubar !=  NULL);
	assert (menubar->app != NULL);
	assert (menubar->app->mlog != NULL);

	Mlog *mlog = menubar->app->mlog;
	const char *signatur = "mmenubar_handle_trigger(Mmenubar*,const char)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	char buffer[256];
	sprintf(buffer,"trigger = %c", trigger);
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			buffer);

	menubar->selected_index = -1;

	for (int i = 0; i < menubar->number_of_menus; i++) {

		Mmenu *m = (Mmenu*) (menubar->menus[i]);
		if (m->trigger == trigger)
		       menubar->selected_index = i;

	}

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");	

}


void mmenubar_delete (Mmenubar **menubar) {
	
	assert ((*menubar) != NULL);

	//TODO: ...


}
