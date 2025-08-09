/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "identify.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"

/*公開関数：*/
/*****************************************************************************************/
Function* identify_function_from_token(Token* token)
{
    for (Function* function = global_list_functions; function; function = function->next)
    {
        if (function->length_name == token->length && !memcmp(token->string, function->name, function->length_name))
        {
            return function;
        }
    }
    return NULL;
}

Function* identify_function_from_string(char* string)
{
    for (Function* function = global_list_functions; function; function = function->next)
    {
        if (function->length_name == strlen(string) && !memcmp(string, function->name, function->length_name))
        {
            return function;
        }
    }
    return NULL;
}

ArgumentOrVariable* identify_argument_or_variable_from_token(Function* function, Token* token)
{
    ArgumentOrVariable* argument_or_variable;
    for (argument_or_variable = function->list_arguments_or_local_variables;
        argument_or_variable; argument_or_variable = argument_or_variable->next)
    {
        if (argument_or_variable->length == token->length
            && !memcmp(token->string, argument_or_variable->name, argument_or_variable->length))
        {
            return argument_or_variable;
        }
    }
    return NULL;
}