#ifndef _GENERATE_FUNCTION_H_
#define _GENERATE_FUNCTION_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "parsa.h"

/*å^êÈåæ*/
/*************************************************************************************************/

/*externêÈåæ*/
/*************************************************************************************************/
extern Function* generate_function(Token* token_func_def);

#endif
