/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "tokenize.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "main.h"
#include "error.h"
#include "distinguish_token.h"
#include "generate_token.h"

/*変数*/
/*****************************************************************************************/
Token* global_list_token;

/*公開関数*/
/*****************************************************************************************/
// 入力文字列pをトークナイズしてそれを返す
void tokenize(void) {
    Token token_head;
    token_head.next = NULL;
    Token* token_current = &token_head;
    char* string_token_current = global_user_input;
    int length_token_current = 0;

    while (*string_token_current) 
    {
        // 空白文字をスキップ
        if (isspace(*string_token_current)) {
            string_token_current++;
            continue;
        }

        // 行コメントをスキップ
        if (strncmp(string_token_current, "//", 2) == 0) {
            string_token_current += 2;
            while (*string_token_current != '\n')
            {
                string_token_current++;
            }
            string_token_current++;
            continue;
        }

        // ブロックコメントをスキップ
        if (strncmp(string_token_current, "/*", 2) == 0) {
            char* q = strstr(string_token_current + 2, "*/");
            if (!q)
            {
                error_at(string_token_current, "コメントが閉じられていません");
            }
            string_token_current = q + 2;
            continue;
        }

        if (iskeywords(string_token_current,&length_token_current))
        {
            token_current = generate_token(TOKEN_KEYWORDS, token_current, string_token_current,length_token_current);
            string_token_current += length_token_current;
            continue;
        }

        if (issymbols(string_token_current, &length_token_current))
        {
            token_current = generate_token(TOKEN_SYMBOLS, token_current, string_token_current, length_token_current);
            string_token_current += length_token_current;
            continue;
        }

        if (isidentifiers(string_token_current, &length_token_current))
        {
            token_current = generate_token(TOKEN_IDENTIFIER, token_current, string_token_current, length_token_current);
            string_token_current += length_token_current;
            continue;
        }

        if (isnumber(string_token_current, &length_token_current))
        {
            token_current = generate_token(TOKEN_NUMBER, token_current, string_token_current, length_token_current);
            token_current->value_number = strtol(string_token_current, &string_token_current, 10);
            continue;
        }

        error("トークナイズできません");
    }
    generate_token(TOKEN_EOF, token_current, string_token_current, 0);
    global_list_token = token_head.next;
}