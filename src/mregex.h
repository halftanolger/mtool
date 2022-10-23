//---------------------------------------------------------------------------//
//                                                                           //
//   mregex                                                                  //
//                                                                           //
//---------------------------------------------------------------------------//
//                                                                           //
//   mregex er en wrapper rundt standard C POSIX.2 regulære uttrykk-         //
//   funksjonalitet i C.                                                     //
//   Hensikten er vel bare aa samle denne logikken i et objekt, samt         //
//   kanskje tilby litt abstraksjon mot noen funksjoner.                     //
//                                                                           //
//---------------------------------------------------------------------------//

#ifndef _MREGEX_H_
#define _MREGEX_H_

#include <sys/types.h>
#include <regex.h>

typedef struct mregex_st {

	char * pattern;
	regex_t *preg;

} Mregex;

Mregex * mregex_new(const char *);

void mregex_delete(Mregex **);



#endif // _MREGEX_H_
