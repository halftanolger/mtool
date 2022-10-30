
#ifndef _MMENUBAR_H_
#define _MMENUBAR_H_

#include <ncurses.h>

#include "mmenu.h"
#include "mapp.h"

typedef struct mmenubar_st {

		Mapp *app;
		WINDOW *win;
		WINDOW *menuwin;
		Mmenu **menus;		
		int number_of_menus;
		int selected_index;

} Mmenubar;

Mmenubar * mmenubar_new (Mapp*, WINDOW*, Mmenu**);

void mmenubar_draw (Mmenubar *);

void mmenubar_draw_menu (Mmenubar *, Mmenu *, char);

void mmenubar_draw_menu_items (Mmenubar *, Mmenu *);

void mmenubar_reset (Mmenubar *);

void mmenubar_handle_trigger (Mmenubar *, const char);

void mmenubar_delete (Mmenubar **);


#endif // _MMENUBAR_H_
