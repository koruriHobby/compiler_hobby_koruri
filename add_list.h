#ifndef _ADD_LIST_H_
#define _ADD_LIST_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsa.h"

/*externêÈåæ*/
/*************************************************************************************************/
extern void add_function_to_list(Function* function);
extern void add_argument_or_variable_to_list(ArgumentOrVariable* argument_or_variable, Function* function);

#endif
