#ifndef _MCONFIG_H_
#define _MCONFIG_H_

typedef struct mconfig_st {

	char * filename;

} mconfig;

mconfig * mconfig_new(const char *);

void mconfig_delete(mconfig **);

#endif // _MYCONFIG_H_
