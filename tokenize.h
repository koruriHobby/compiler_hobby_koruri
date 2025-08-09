#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*型宣言*/
/*****************************************************************************************/
typedef enum {
    TOKEN_SYMBOLS,  // 記号  
    TOKEN_IDENTIFIER,    // 識別子
    TOKEN_NUMBER,      // 整数トークン
    TOKEN_KEYWORDS, // 予約語
    TOKEN_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
    TokenKind kind; // トークンの型
    Token* next;    // 次の入力トークン
    int value_number;        // kindがTK_NUMの場合、その数値
    char* string;      // トークン文字列
    int length;        //トークンの長さ
};

/*extern宣言*/
/*****************************************************************************************/
extern Token* global_list_token;

extern void tokenize(void);

#endif

