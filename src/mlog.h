#ifndef _MLOG_H_
#define _MLOG_H_

#include "mconfig.h"

enum mlog_types_enum {MLOG_INFO, MLOG_ERROR};

typedef enum mlog_types_enum mlog_type;

typedef struct mlog_st {

	int active;
	mlog_type level;
	char signature[256];
	char *filename;
	FILE *fp;

} Mlog;

Mlog * mlog_new (Mconfig *);

void mlog_delete (Mlog **);

void mlog_log (Mlog *, mlog_type, const char*, const char*, int, const char*);

#endif // _MLOG_H_
