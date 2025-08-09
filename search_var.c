/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "search_var.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "tokenize.h"
#include "parsa.h"
#include "generate_node.h"

/*変数*/
/*****************************************************************************************/

/*公開関数*/
/*****************************************************************************************/
Node* search_var(Token* token)
{
    Node* node = generate_node(NODE_ARGUMENT_OR_VARIABLE, NULL, NULL);
    Function* func_cur;
    ArgumentOrVariable* var;

    /*********************************************************
    * funcname_refと同じ名前の関数にアクセス
    * var_listを検索して、変数が存在するなら関数名とオフセットを登録してリターン
    *********************************************************/
    for (func_cur = global_list_functions; func_cur; func_cur = func_cur->next)
    {
        if (func_cur->length_name == strlen(global_name_function_current) && !memcmp(global_name_function_current, func_cur->name, func_cur->length_name))
        {
            break;
        }
    }

    for (var = func_cur->list_arguments_or_local_variables; var; var = var->next)
    {
        if (var->length == token->length && !memcmp(token->string, var->name, var->length))
        {
            strncpy_s(node->name_function, 64, func_cur->name, sizeof(func_cur->name) / sizeof(char));
            node->offset_argument_or_local_variable = var->offset;
            return node;
        }
    }

    /*********************************************************
    * var_listにいない変数はローカル変数として登録
    * ノード：関数名とオフセット(var_listがNULLのときはVAR_SIZE、それ以外は＋VAR_SIZE)
    * var_list：名前、名前の長さ、オフセット
    *********************************************************/
    //ローカル変数はfuncname_refで登録
    if (node->name_function == NULL)
    {
        strncpy_s(node->name_function, 64, global_name_function_current, sizeof(global_name_function_current) / sizeof(char));
    }

    if (func_cur->list_arguments_or_local_variables == NULL)
    {
        node->offset_argument_or_local_variable = BYTESIZE_VARIABLE;
    }
    else
    {
        node->offset_argument_or_local_variable = func_cur->list_arguments_or_local_variables->offset + BYTESIZE_VARIABLE;
    }

    var = calloc(1, sizeof(ArgumentOrVariable));
    strncpy_s(var->name, strlen(token->string), token->string, token->length);
    var->length = token->length;
    var->offset = node->offset_argument_or_local_variable;
    var->next = func_cur->list_arguments_or_local_variables;
    func_cur->list_arguments_or_local_variables = var;

    return node;
}



