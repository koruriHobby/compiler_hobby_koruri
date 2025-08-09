#ifndef _GENERATE_ARGUMENT_OR_VARIABLE_H_
#define _GENERATE_ARGUMENT_OR_VARIABLE_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsa.h"
#include "tokenize.h"

/*å^êÈåæ*/
/*************************************************************************************************/

/*externêÈåæ*/
/*************************************************************************************************/
extern void generate_argument(Function* function, Token* token);
extern void generate_local_variable(Node* node, Function* function, Token* token);

#endif
