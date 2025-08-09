#ifndef _PARSA_H_
#define _PARSA_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsa.h"

#define COUNT_CODE_MAX 100
#define COUNT_BLOCK_MAX 100
#define COUNT_FUNCTION_DECLARATION_MAX 10
#define BYTESIZE_VARIABLE 8

/*型宣言*/
/*************************************************************************************************/
typedef enum {
    NODE_FUNCTION_DECLARATION,    // 関数の定義
    NODE_FUNCTION_CALL,           // 関数
    NODE_BLOCK,                   // 「{}」
    NODE_ARGUMENT_OR_VARIABLE,    // 関数の引数

    NODE_NUMBER,                  // 整数

    NODE_ADD,                     // +
    NODE_SUBTRACT,                // -
    NODE_MULTIPLICATION,          // *
    NODE_DIVISION,                // /
    NODE_ASSIGN,                  // =
    NODE_EQUAL,                   // ==
    NODE_NOT_EQUAL,               // !=
    NODE_LESS_THAN,               // <
    NODE_LESS_THAN_OR_EQUAL,      // <=
    NODE_ADDRESS,                 // &
    NODE_DEREFERENCE,             // *

    NODE_RETURN,                  //「return」
    NODE_IF,                      //「if」
    NODE_BRANCH_IF,               // if文の分岐
    NODE_ELSE,                    //「else」
    NODE_WHILE,                   //「while」
    NODE_FOR,                     //「for」
    NODE_BRANCH_FOR,              // for文の終了分岐
    NODE_FOREXECUTE,              // for文の処理部分

} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
    NodeKind kind;                          // ノードの型
    Node* left_hand_side;                   // 左辺
    Node* right_hand_side;                  // 右辺
    Node* block[COUNT_BLOCK_MAX];           // {}の中の文章
    Node* arguments[4];
    int count_arguments;
    int value_number;                       // kindがND_NUMの場合のみ使う
    char name_function[64];                 //関数を定義、呼び出す用の関数の名前
    int offset_argument_or_local_variable;  //関数の引数、ローカル変数を呼ぶためのベースポインタからのオフセット
};

typedef struct ArgumentOrVariable ArgumentOrVariable;

// 関数の引数の型
struct ArgumentOrVariable {
    ArgumentOrVariable* next;
    char name[64]; // 変数の名前
    int length;    // 名前の長さ
    int offset;    // RBPからのオフセット
};

typedef struct Function Function;

//関数の型
struct Function {
    char name[64];                                          // 関数の名前
    int length_name;                                        // 名前の長さ

    int stack_flame;

    Function* next;                                         // 次の関数かNULL
    
    Node* node_arguments[4];                                //定義するときに引数はノードを持たなければいけないので、その確保
    int count_arguments;                                    //引数の数

    ArgumentOrVariable* list_arguments_or_local_variables;  //引数とローカル変数を分けずに管理

    Node* code[COUNT_CODE_MAX];
};

/*extern宣言*/
/*************************************************************************************************/
extern Function* global_list_functions;
extern Node* global_function_declaration[COUNT_FUNCTION_DECLARATION_MAX];
extern char global_name_function_current[64];

extern void program(void);
extern Node* function_declaration(void);
extern Node* stmt(void);
extern Node* expr(void);
extern Node* assign(void);
extern Node* equality(void);
extern Node* relational(void);
extern Node* add(void);
extern Node* mul(void);
extern Node* unary(void);
extern Node* primary(void);
extern Node* node_else(void);
extern Node* tf(void);
extern Node* forbranch(void);
extern Node* forexecute(void);

#endif
