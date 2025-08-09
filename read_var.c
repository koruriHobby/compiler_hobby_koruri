/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "read_var.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"
#include "check_token.h"
#include "generate_node.h"
#include "add_list.h"

#include "set_string.h"

#include "generate_argument_or_variable.h"

/*公開関数：*/
/*****************************************************************************************/
void assign_argument_or_variable_to_function(Token* token, Function* function)
{
    Node* node = generate_node(NODE_ARGUMENT_OR_VARIABLE, NULL, NULL);

    set_name_function_to_node(node, function);

    node->offset_argument_or_local_variable = (function->count_arguments + 1) * BYTESIZE_VARIABLE;
    function->node_arguments[function->count_arguments] = node;
    function->count_arguments++;

    generate_argument_or_variable(function, token);
}