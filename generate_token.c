/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "generate_token.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "tokenize.h"

// 新しいトークンを作成してリストに繋げる
Token* generate_token(TokenKind kind, Token* token_current, char* string_token_current, int length_token_current) {
    Token* token_new = calloc(1, sizeof(Token));
    
    token_new->kind = kind;
    token_new->string = string_token_current;
    token_new->length = length_token_current;
    
    token_current->next = token_new;

    return token_new;
}