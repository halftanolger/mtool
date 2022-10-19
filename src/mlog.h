#ifndef _MLOG_H_
#define _MLOG_H_

#include "mconfig.h"

enum mlog_types_enum {INFO, ERROR};

typedef enum mlog_types_enum mlog_type;

typedef struct mlog_st {

	int active;

	char signature[256];

} mlog;

mlog * mlog_new (mconfig *);

void mlog_delete (mlog **);

void mlog_log (mlog *, mlog_type, const char*, const char*);

#endif // _MLOG_H_
