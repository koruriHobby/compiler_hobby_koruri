#ifndef _GENERATE_TOKEN_H_
#define _GENERATE_TOKEN_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

/*externêÈåæ*/
/*****************************************************************************************/
extern Token* generate_token(TokenKind kind, Token* token_current, char* string_token_current, int length_token_current);
#endif