/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "check_token.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "tokenize.h"

/*���J�֐�*/
/*****************************************************************************************/
// ���̃g�[�N�������҂��Ă���L���̂Ƃ��ɂ́A�g�[�N����1�ǂݐi�߂�
// �^��Ԃ��B����ȊO�̏ꍇ�ɂ͋U��Ԃ��B
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

// ���̃g�[�N�������҂��Ă���L���̂Ƃ��ɂ́A�g�[�N����1�ǂݐi�߂�B
// ����ȊO�̏ꍇ�ɂ̓G���[��񍐂���B
void expect(char* string_expected) {
    if (global_list_token->kind != TOKEN_SYMBOLS 
        || (int)strlen(string_expected) != global_list_token->length
        || memcmp(global_list_token->string, string_expected, global_list_token->length))
    {
        error_at(global_list_token->string, "'%s'�ł͂���܂���", string_expected);
    }
    global_list_token = global_list_token->next;
}

// ���̃g�[�N�������l�̏ꍇ�A�g�[�N����1�ǂݐi�߂Ă��̐��l��Ԃ��B
// ����ȊO�̏ꍇ�ɂ̓G���[��񍐂���B
int expect_number(void) {
    if (global_list_token->kind != TOKEN_NUMBER)
    {
        error_at(global_list_token->string, "���ł͂���܂���");
    }
    int value_number = global_list_token->value_number;
    global_list_token = global_list_token->next;
    return value_number;
}

bool at_eof() {
    return global_list_token->kind == TOKEN_EOF;
}