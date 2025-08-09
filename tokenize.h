#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*�^�錾*/
/*****************************************************************************************/
typedef enum {
    TOKEN_SYMBOLS,  // �L��  
    TOKEN_IDENTIFIER,    // ���ʎq
    TOKEN_NUMBER,      // �����g�[�N��
    TOKEN_KEYWORDS, // �\���
    TOKEN_EOF,      // ���͂̏I����\���g�[�N��
} TokenKind;

typedef struct Token Token;

// �g�[�N���^
struct Token {
    TokenKind kind; // �g�[�N���̌^
    Token* next;    // ���̓��̓g�[�N��
    int value_number;        // kind��TK_NUM�̏ꍇ�A���̐��l
    char* string;      // �g�[�N��������
    int length;        //�g�[�N���̒���
};

/*extern�錾*/
/*****************************************************************************************/
extern Token* global_list_token;

extern void tokenize(void);

#endif

