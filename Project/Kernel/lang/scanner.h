#ifndef _SCANNER_H
#define _SCANNER_H	1

#define MAX_STR_CONST	1024
extern int	  lex_iconst;
extern double  lex_dconst;
extern int	   lex_lineno;
extern char    lex_sconst[MAX_STR_CONST];
#include <stdio.h>

#endif

