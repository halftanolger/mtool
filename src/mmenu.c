#include <ncurses.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mmenu.h"


Mmenu * mmenu_new (Mapp *app, const char *name, const char trigger, 
		char *items[]) {

	assert (name != NULL);
	assert (trigger != 0);
	assert (app != NULL);

	const char *signatur = "mmenu_new(Mapp*,const char,const char)";
	mlog_log (app->mlog, MLOG_INFO, 
			signatur,
		        __FILE__, __LINE__, 	
			"Enter function");

	char buffer[256];
	sprintf(buffer,"name = %s, trigger= %c",name,trigger);
	mlog_log (app->mlog, MLOG_INFO, 
			signatur,
		       __FILE__, __LINE__, 	
			(char*)buffer);

	Mmenu *mmenu = (Mmenu*)malloc(sizeof(Mmenu));

	if (mmenu == NULL) {
		sprintf (buffer, 
				"Error, can't malloc. %s\n",
				strerror (errno));

		mlog_log (app->mlog, MLOG_ERROR, 
			signatur,
		       __FILE__, __LINE__, 	
			(char*)buffer);

		return NULL;
	}

	mmenu->app = app;
	mmenu->name = strdup(name);
	mmenu->trigger = trigger;
	mmenu->selected_item = -1;

	int MAX_ITEMS = MMENU_MAX_ITEMS;

	mmenu->number_of_items = 0;
	for (int i = 0; i < MAX_ITEMS; i++) {
		char *c = items[i];
		if (c == NULL)
			break;
		mmenu->items[i] = strdup(c);
		mmenu->number_of_items++;
	}

	if (mmenu->number_of_items == MAX_ITEMS) {
		mlog_log (app->mlog, 
				MLOG_ERROR, 
				signatur,
				__FILE__,__LINE__, 
				"mmenu->number_of_items == MAX_ITEMS");
		return NULL;
	}

	for (int i = 0; i < mmenu->number_of_items; i++) {
		sprintf(buffer,"Item nr %d is '%s'",i,mmenu->items[i]);
		mlog_log (app->mlog, MLOG_INFO, 
				signatur,
			       __FILE__, __LINE__,	
				buffer);
	}

	mlog_log (app->mlog, MLOG_INFO, 
			signatur,
		       __FILE__, __LINE__,	
			"Exit function");
	return mmenu;

}


void mmenu_select_next_item (Mmenu *menu) {

	assert (menu != NULL);

	Mlog *mlog = menu->app->mlog;
	const char *signatur = "mmenu_select_next_item(Mmenu*)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	if (menu->selected_item < menu->number_of_items - 1)
		menu->selected_item++;

	char buffer[256];
	sprintf(buffer,"selected_item = %d", menu->selected_item);
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			buffer);

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");
}


void mmenu_select_previous_item (Mmenu *menu) {

	assert (menu != NULL);

	Mlog *mlog = menu->app->mlog;
	const char *signatur = "mmenu_previous__item(Mmenu*)";
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Enter function");

	if (menu->selected_item > 0)
		menu->selected_item--;

	char buffer[256];
	sprintf(buffer,"selected_item = %d", menu->selected_item);
	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__, 
			buffer);

	mlog_log (mlog, MLOG_INFO, 
			signatur, 
			__FILE__, __LINE__,
			"Exit function");
}


void mmenu_delete (Mmenu **mmenu) {
	
	assert ((*mmenu) != NULL);

	free ((*mmenu)->name);
	free (*mmenu);

}
