/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "tokenize.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"
#include "error.h"
#include "distinguish_token.h"
#include "generate_token.h"

/*�ϐ�*/
/*****************************************************************************************/
Token* global_list_token;

/*���J�֐�*/
/*****************************************************************************************/
// ���͕�����p���g�[�N�i�C�Y���Ă����Ԃ�
void tokenize(void) {
    Token token_head;
    token_head.next = NULL;
    Token* token_current = &token_head;
    char* string_token_current = global_user_input;
    int length_token_current = 0;

    while (*string_token_current) 
    {
        // �󔒕������X�L�b�v
        if (isspace(*string_token_current)) {
            string_token_current++;
            continue;
        }

        // �s�R�����g���X�L�b�v
        if (strncmp(string_token_current, "//", 2) == 0) {
            string_token_current += 2;
            while (*string_token_current != '\n')
            {
                string_token_current++;
            }
            string_token_current++;
            continue;
        }

        // �u���b�N�R�����g���X�L�b�v
        if (strncmp(string_token_current, "/*", 2) == 0) {
            char* q = strstr(string_token_current + 2, "*/");
            if (!q)
            {
                error_at(string_token_current, "�R�����g�������Ă��܂���");
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

        error("�g�[�N�i�C�Y�ł��܂���");
    }
    generate_token(TOKEN_EOF, token_current, string_token_current, 0);
    global_list_token = token_head.next;
}