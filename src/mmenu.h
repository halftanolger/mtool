#ifndef _MMENU_H_
#define _MMENU_H_

#include "mapp.h"

#define MMENU_MAX_ITEMS 50;

typedef struct mmenu_st {

		Mapp *app;
		int start_x;
		char *name;
		char trigger;
		int selected_item;
		int number_of_items;
		char *items[];

} Mmenu;

/**
 * Functionname: mmenu_new
 * Parameters  : Mapp*         - pointer to the Mapp-objekt.
 *               const char*   - the name of the menu-bar-menu.
 *               const char    - the short-cut character for the menu-bar-menu.
 *               char *items[] - the menu-bar-menu-items (todo: this ought to
 *                               be action-objects.)
 * Returns     : a Mmenu object or NULL.
 */
Mmenu * mmenu_new (Mapp*, const char *, const char, char *items[]);

void mmenu_select_next_item (Mmenu *);

void mmenu_select_previous_item (Mmenu *);

void mmenu_delete (Mmenu **);


#endif // _MMENU_H_
