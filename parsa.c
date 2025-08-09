/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "parsa.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "tokenize.h"
#include "check_token.h"
#include "set_string.h"
#include "generate_node.h"
#include "generate_function.h"
#include "add_list.h"
#include "assign.h"

/*変数*/
/*****************************************************************************************/
Node* global_function_declaration[COUNT_FUNCTION_DECLARATION_MAX];
Function* global_list_functions;
char global_name_function_current[64];

/*プロトタイプ宣言*/
/*****************************************************************************************/

/*公開関数*/
/*****************************************************************************************/
void program() 
{
    for (int i = 0; !at_eof(); i++)
    {
        if (i > COUNT_FUNCTION_DECLARATION_MAX - 2)
        {
            error("関数をこれ以上宣言できません");
        }
        global_function_declaration[i] = function_declaration();
        global_function_declaration[i+1] = NULL;
    }
}

Node* function_declaration(void)
{
    Token* token_function_declaration = consume_identifier();

    //ノードに関数の名前を追加
    Node* node = generate_node_function_declaration(token_function_declaration);
    
    //functions生成
    Function* function = generate_function(token_function_declaration);

    //このタイミングでグローバル変数のfuncname_refに関数名を登録しないと、ローカル変数を関数名で検索できない
    set_global_name_function_current(function);

    expect("(");
    if (!consume_symbols(")"))
    {
        Token* token_argument = consume_identifier();
        assign_argument_to_function(token_argument, function);
        
        while (!consume_symbols(")"))
        {
            expect(",");
            token_argument = consume_identifier();
            assign_argument_to_function(token_argument, function);
        }
    }

    add_function_to_list(function);

    expect("{");
    for (int i = 0; !consume_symbols("}"); i++)
    {
        if (i > COUNT_CODE_MAX - 2)
        {
            error("関数内に記述できる文の数を超過しました");
        }
        global_list_functions->code[i] = stmt();
        global_list_functions->code[i+1] = NULL;
    }

    return node;
}

Node* stmt() {
    Node* node;
    
    if (consume_symbols("{"))
    {
        node = generate_node(NODE_BLOCK, NULL, NULL);
        node->block[0] = NULL;

        for (int i = 0; !consume_symbols("}"); i++)
        {
            if (i > COUNT_BLOCK_MAX - 2)
            {
                error("ブロック文に含むことのできる文の数を超過しました");
            }
            node->block[i] = stmt();
            node->block[i + 1] = NULL;
        }
    }
 
    else if (consume_keywords("return"))
    {
        node = generate_node(NODE_RETURN, expr(), NULL);
        expect(";");
    }
    else if (consume_keywords("if"))
    {
        expect("(");
        node = generate_node(NODE_IF, expr(), NULL);
        expect(")");
        node->right_hand_side = tf();
    }
    else if (consume_keywords("while"))
    {
        expect("(");
        node = generate_node(NODE_WHILE, expr(), NULL);
        expect(")");
        node->right_hand_side = stmt();
    }
    else if (consume_keywords("for"))
    {
        expect("(");
        node = generate_node(NODE_FOR, NULL, NULL);
        if (!consume_symbols(";"))
        {
            node->left_hand_side = expr();
            expect(";");
        }
        node->right_hand_side = forbranch();
    }
    else
    {
        node = expr();
        expect(";");
    }
    return node;
}

Node* expr() {
    return assign();
}

Node* assign() {
    Node* node = equality();
 
    if (consume_symbols("="))
    {
        node = generate_node(NODE_ASSIGN, node, assign());
    }
    
    return node;
}

Node* equality() {
    Node* node = relational();

    while(1)
    {
        if (consume_symbols("=="))
        {
            node = generate_node(NODE_EQUAL, node, relational());
        }
        else if (consume_symbols("!="))
        {
            node = generate_node(NODE_NOT_EQUAL, node, relational());
        }
        else
        {
            return node;
        }
    }
}

Node* relational() {
    Node* node = add();

    for (;;) {
        if (consume_symbols("<")) {
            node = generate_node(NODE_LESS_THAN, node, add());
        }
        else if (consume_symbols("<=")) {
            node = generate_node(NODE_LESS_THAN_OR_EQUAL, node, add());
        }
        else if (consume_symbols(">")) {
            node = generate_node(NODE_LESS_THAN, add(), node);
        }
        else if (consume_symbols(">=")) {
            node = generate_node(NODE_LESS_THAN_OR_EQUAL, add(), node);
        }
        else {
            return node;
        }
    }
}

Node* add() {
    Node* node = mul();

    for (;;) {
        if (consume_symbols("+"))
        {
            node = generate_node(NODE_ADD, node, mul());
        }
        else if (consume_symbols("-"))
        {
            node = generate_node(NODE_SUBTRACT, node, mul());
        }
        else
        {
            return node;
        }
    }
}

Node* mul() {
    Node* node = unary();

    for (;;) {
        if (consume_symbols("*"))
        {
            node = generate_node(NODE_MULTIPLICATION, node, unary());
        }
        else if (consume_symbols("/"))
        {
            node = generate_node(NODE_DIVISION, node, unary());
        }
        else
        {
            return node;
        }
    }
}

Node* unary() {
    if (consume_symbols("&"))
    {
        return generate_node(NODE_ADDRESS, unary(), NULL);
    }
    else if (consume_symbols("*"))
    {
        return generate_node(NODE_DEREFERENCE, unary(), NULL);
    }
    else if (consume_symbols("+"))
    {
        return primary();
    }
    else if (consume_symbols("-"))
    {
        return generate_node(NODE_SUBTRACT, generate_node_number(0), primary());
    }
    else
    {
        return primary();
    }
}

Node* primary() {
    Node* node;
    Token* token;

    if (consume_symbols("(")) {
        node = expr();
        expect(")");
        return node;
    }

    token = consume_identifier();

    if (token && consume_symbols("("))
    {
        return generate_node_function_call(token);
    }

    if (token) //tokenは変数名
    {
        return generate_node_argument_or_local_variable(token);
    }

    return generate_node_number(expect_number());
}

Node* node_else()
{
    Node* node = generate_node(NODE_ELSE, stmt(), NULL);
    return node;
}

Node* tf(void)
{
    Node* node = generate_node(NODE_BRANCH_IF, stmt(), NULL);
    if (consume_keywords("else"))
    {
        node->right_hand_side = node_else();
    }
    return node;
}

Node* forbranch(void)
{
    Node* node = generate_node(NODE_BRANCH_FOR, NULL, NULL);
    if (!consume_symbols(";"))
    {
        node->left_hand_side = expr();
        expect(";");
    }
    node->right_hand_side = forexecute();
    return node;
}

Node* forexecute()
{
    Node* node = generate_node(NODE_FOREXECUTE, NULL, NULL);
    if (!consume_symbols(")"))
    {
        node->left_hand_side = expr();
        expect(")");
    }
    node->right_hand_side = stmt();
    return node;
}