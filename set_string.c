/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "set_string.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "tokenize.h"
#include "parsa.h"

/*変数*/
/*****************************************************************************************/

/*公開関数*/
/*****************************************************************************************/
void set_global_name_function_current(Function* function)
{
    strncpy_s(global_name_function_current, 64, function->name, function->length_name);
}

void set_name_function_to_node(Node* node, Function* function)
{
    strncpy_s(node->name_function, 64, function->name, function->length_name);
}

void set_name_function_to_argument_or_variable(ArgumentOrVariable* argument_or_variable, Token* token)
{
    strncpy_s(argument_or_variable->name, sizeof(token->string), token->string, token->length);
}
