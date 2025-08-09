#ifndef _SEARCH_FUNC_H_
#define _SEARCH_FUNC_H_

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
extern void set_global_name_function_current(Function* function);
extern void set_name_function_to_node(Node* node, Function* function);
extern void set_name_function_to_argument_or_variable(ArgumentOrVariable* argument_or_variable, Token* token);

#endif
