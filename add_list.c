/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "add_list.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "parsa.h"

/*公開関数：*/
/*****************************************************************************************/
void add_function_to_list(Function* function)
{
    function->next = global_list_functions;
    global_list_functions = function;
}

void add_argument_or_variable_to_list(ArgumentOrVariable* argument_or_variable, Function* function)
{
    argument_or_variable->next = function->list_arguments_or_local_variables;
    function->list_arguments_or_local_variables = argument_or_variable;
}