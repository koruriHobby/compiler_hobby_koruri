/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "check_token.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "tokenize.h"

/*公開関数*/
/*****************************************************************************************/
// 次のトークンが期待している記号のときには、トークンを1つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
bool consume_symbols(char* string_expected) {
    if (global_list_token->kind != TOKEN_SYMBOLS 
        || (int)strlen(string_expected) != global_list_token->length
        || memcmp(global_list_token->string, string_expected, global_list_token->length))
    {
        return false;
    }
    global_list_token = global_list_token->next;
    return true;
}

bool consume_keywords(char *string_expected) {
    if (global_list_token->kind != TOKEN_KEYWORDS 
        || (int)strlen(string_expected) != global_list_token->length
        || memcmp(global_list_token->string, string_expected, global_list_token->length))
    {
        return false;
    }
    global_list_token = global_list_token->next;
    return true;
}

Token* consume_identifier(void)
{
    Token* token_current = global_list_token;
    if (global_list_token->kind != TOKEN_IDENTIFIER)
    {
        return NULL;
    }
    global_list_token = global_list_token -> next;
    return token_current;
}

// 次のトークンが期待している記号のときには、トークンを1つ読み進める。
// それ以外の場合にはエラーを報告する。
void expect(char* string_expected) {
    if (global_list_token->kind != TOKEN_SYMBOLS 
        || (int)strlen(string_expected) != global_list_token->length
        || memcmp(global_list_token->string, string_expected, global_list_token->length))
    {
        error_at(global_list_token->string, "'%s'ではありません", string_expected);
    }
    global_list_token = global_list_token->next;
}

// 次のトークンが数値の場合、トークンを1つ読み進めてその数値を返す。
// それ以外の場合にはエラーを報告する。
int expect_number(void) {
    if (global_list_token->kind != TOKEN_NUMBER)
    {
        error_at(global_list_token->string, "数ではありません");
    }
    int value_number = global_list_token->value_number;
    global_list_token = global_list_token->next;
    return value_number;
}

bool at_eof() {
    return global_list_token->kind == TOKEN_EOF;
}