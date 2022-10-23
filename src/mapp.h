#ifndef _MAPP_H_
#define _MAPP_H_

#include "mlog.h"
#include "mconfig.h"

typedef struct mapp_st {

	Mconfig * mconfig;
	Mlog * mlog;

} Mapp;

Mapp * mapp_new (const char*);

int mapp_init (Mapp *);

int mapp_run (Mapp *);

void mapp_delete (Mapp **);

#endif // _MAPP_H_
