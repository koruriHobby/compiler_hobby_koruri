#ifndef _DISTINGUISH_TOKEN_H_
#define _DISTINGUISH_TOKEN_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*externéŒ¾*/
/*****************************************************************************************/
extern int iskeywords(char* string_token_current, int* length_token_current);
extern int issymbols(char* string_token_current, int* length_token_current);
extern int isidentifiers(char* string_token_current, int* length_token_current);
extern int isnumber(char* string_token_current, int* length_token_current);

#endif

