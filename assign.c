/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "assign.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"
#include "identify.h"
#include "check_token.h"
#include "add_list.h"
#include "set_string.h"
#include "generate_function.h"
#include "generate_node.h"
#include "generate_argument_or_variable.h"

/*公開関数：*/
/*****************************************************************************************/
void assign_function_to_node(Node* node, Token* token)
{
    Function* function = identify_function_from_token(token);

    //関数がリストに存在するならその情報をノードに反映
    if (function != NULL)
    {
        set_name_function_to_node(node, function);
    }
    //いない場合は、外部ファイルの可能性もあるので、functionsにも追加する。
    else
    {
        function = generate_function(token);
        set_name_function_to_node(node, function);
        add_function_to_list(function);
    }
}

Node* assign_arguments_to_node(Node* node)
{
    if (consume_symbols(")"))
    {
        return node;
    }

    int count_arguments = 0;
    node->arguments[count_arguments] = expr();
    count_arguments++;

    while (!consume_symbols(")"))
    {
        if (count_arguments > 4)
        {
            error("このコンパイラでサポートする引数は4個までです");
        }
        expect(",");
        node->arguments[count_arguments] = expr();
        count_arguments++;
    }

    node->count_arguments = count_arguments;

    return node;
}

void assign_argument_to_function(Token* token, Function* function)
{
    Node* node = generate_node(NODE_ARGUMENT_OR_VARIABLE, NULL, NULL);

    set_name_function_to_node(node, function);

    node->offset_argument_or_local_variable = (function->count_arguments + 1) * BYTESIZE_VARIABLE;
    function->node_arguments[function->count_arguments] = node;
    function->count_arguments++;

    generate_argument(function, token);
}
