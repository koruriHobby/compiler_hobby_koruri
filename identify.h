#ifndef _IDENTIFY_H_
#define _IDENTIFY_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "parsa.h"

/*externêÈåæ*/
/*************************************************************************************************/
extern Function* identify_function_from_token(Token* token);
extern Function* identify_function_from_string(char* string);
extern ArgumentOrVariable* identify_argument_or_variable_from_token(Function* function, Token* token);

#endif
