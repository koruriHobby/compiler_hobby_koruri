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

/*�^�錾*/
/*************************************************************************************************/
typedef enum {
    NODE_FUNCTION_DECLARATION,    // �֐��̒�`
    NODE_FUNCTION_CALL,           // �֐�
    NODE_BLOCK,                   // �u{}�v
    NODE_ARGUMENT_OR_VARIABLE,    // �֐��̈���

    NODE_NUMBER,                  // ����

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

    NODE_RETURN,                  //�ureturn�v
    NODE_IF,                      //�uif�v
    NODE_BRANCH_IF,               // if���̕���
    NODE_ELSE,                    //�uelse�v
    NODE_WHILE,                   //�uwhile�v
    NODE_FOR,                     //�ufor�v
    NODE_BRANCH_FOR,              // for���̏I������
    NODE_FOREXECUTE,              // for���̏�������

} NodeKind;

typedef struct Node Node;

// ���ۍ\���؂̃m�[�h�̌^
struct Node {
    NodeKind kind;                          // �m�[�h�̌^
    Node* left_hand_side;                   // ����
    Node* right_hand_side;                  // �E��
    Node* block[COUNT_BLOCK_MAX];           // {}�̒��̕���
    Node* arguments[4];
    int count_arguments;
    int value_number;                       // kind��ND_NUM�̏ꍇ�̂ݎg��
    char name_function[64];                 //�֐����`�A�Ăяo���p�̊֐��̖��O
    int offset_argument_or_local_variable;  //�֐��̈����A���[�J���ϐ����ĂԂ��߂̃x�[�X�|�C���^����̃I�t�Z�b�g
};

typedef struct ArgumentOrVariable ArgumentOrVariable;

// �֐��̈����̌^
struct ArgumentOrVariable {
    ArgumentOrVariable* next;
    char name[64]; // �ϐ��̖��O
    int length;    // ���O�̒���
    int offset;    // RBP����̃I�t�Z�b�g
};

typedef struct Function Function;

//�֐��̌^
struct Function {
    char name[64];                                          // �֐��̖��O
    int length_name;                                        // ���O�̒���

    int stack_flame;

    Function* next;                                         // ���̊֐���NULL
    
    Node* node_arguments[4];                                //��`����Ƃ��Ɉ����̓m�[�h�������Ȃ���΂����Ȃ��̂ŁA���̊m��
    int count_arguments;                                    //�����̐�

    ArgumentOrVariable* list_arguments_or_local_variables;  //�����ƃ��[�J���ϐ��𕪂����ɊǗ�

    Node* code[COUNT_CODE_MAX];
};

/*extern�錾*/
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
