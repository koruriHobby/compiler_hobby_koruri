/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "generate_node.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "parsa.h"
#include "assign.h"
#include "identify.h"
#include "add_list.h"
#include "generate_argument_or_variable.h"
#include "set_string.h"

/*公開関数*/
/*****************************************************************************************/
Node* generate_node(NodeKind kind, Node* left_hand_side, Node* right_hand_side) {
    Node* node = calloc(1, sizeof(Node));
    if (node != NULL)
    {
        node->kind = kind;
        node->left_hand_side = left_hand_side;
        node->right_hand_side = right_hand_side;
        return node;
    }
    return NULL;
}

Node* generate_node_number(int value_number) {
    Node* node = calloc(1, sizeof(Node));
    if (node != NULL)
    {
        node->kind = NODE_NUMBER;
        node->value_number = value_number;
        return node;
    }
    return NULL;
}

Node* generate_node_function_declaration(Token* token) 
{
    Node* node = calloc(1, sizeof(Node));
    if (node != NULL)
    {
        node->kind = NODE_FUNCTION_DECLARATION;
        strncpy_s(node->name_function, sizeof(token->string), token->string, token->length);
        return node;
    }
    return NULL;
}

Node* generate_node_function_call(Token* token)
{
    Node* node = generate_node(NODE_FUNCTION_CALL, NULL, NULL);
    assign_function_to_node(node, token);
    return assign_arguments_to_node(node);
}

Node* generate_node_argument_or_local_variable(Token* token)
{
    Node* node = generate_node(NODE_ARGUMENT_OR_VARIABLE, NULL, NULL);
    Function* function = identify_function_from_string(global_name_function_current);
    set_name_function_to_node(node, function);

    ArgumentOrVariable* argument_or_variable = identify_argument_or_variable_from_token(function, token);

    //listに存在するならオフセットを登録してリターン
    if (argument_or_variable != NULL)
    {
        node->offset_argument_or_local_variable = argument_or_variable->offset;
        return node;
    }
    else 
    {
        generate_local_variable(node, function, token);
        return node;
    }
}