#ifndef _GENERATE_NODE_H_
#define _GENERATE_NODE_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsa.h"
#include "tokenize.h"

/*externêÈåæ*/
/*************************************************************************************************/
extern Node* generate_node(NodeKind kind, Node* left_hand_side, Node* right_hand_side);
extern Node* generate_node_number(int value_number);
extern Node* generate_node_function_declaration(Token* token);
extern Node* generate_node_function_call(Token* token);
extern Node* generate_node_argument_or_local_variable(Token* token);

#endif
