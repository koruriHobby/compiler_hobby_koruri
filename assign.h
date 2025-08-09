#ifndef _ASSIGN_H_
#define _ASSIGN_H_

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
extern void assign_function_to_node(Node* node, Token* token);
extern Node* assign_arguments_to_node(Node* node);
extern void assign_argument_to_function(Token* token, Function* function);

#endif
