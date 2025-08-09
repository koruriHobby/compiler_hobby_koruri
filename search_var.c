/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "search_var.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "tokenize.h"
#include "parsa.h"
#include "generate_node.h"

/*�ϐ�*/
/*****************************************************************************************/

/*���J�֐�*/
/*****************************************************************************************/
Node* search_var(Token* token)
{
    Node* node = generate_node(NODE_ARGUMENT_OR_VARIABLE, NULL, NULL);
    Function* func_cur;
    ArgumentOrVariable* var;

    /*********************************************************
    * funcname_ref�Ɠ������O�̊֐��ɃA�N�Z�X
    * var_list���������āA�ϐ������݂���Ȃ�֐����ƃI�t�Z�b�g��o�^���ă��^�[��
    *********************************************************/
    for (func_cur = global_list_functions; func_cur; func_cur = func_cur->next)
    {
        if (func_cur->length_name == strlen(global_name_function_current) && !memcmp(global_name_function_current, func_cur->name, func_cur->length_name))
        {
            break;
        }
    }

    for (var = func_cur->list_arguments_or_local_variables; var; var = var->next)
    {
        if (var->length == token->length && !memcmp(token->string, var->name, var->length))
        {
            strncpy_s(node->name_function, 64, func_cur->name, sizeof(func_cur->name) / sizeof(char));
            node->offset_argument_or_local_variable = var->offset;
            return node;
        }
    }

    /*********************************************************
    * var_list�ɂ��Ȃ��ϐ��̓��[�J���ϐ��Ƃ��ēo�^
    * �m�[�h�F�֐����ƃI�t�Z�b�g(var_list��NULL�̂Ƃ���VAR_SIZE�A����ȊO�́{VAR_SIZE)
    * var_list�F���O�A���O�̒����A�I�t�Z�b�g
    *********************************************************/
    //���[�J���ϐ���funcname_ref�œo�^
    if (node->name_function == NULL)
    {
        strncpy_s(node->name_function, 64, global_name_function_current, sizeof(global_name_function_current) / sizeof(char));
    }

    if (func_cur->list_arguments_or_local_variables == NULL)
    {
        node->offset_argument_or_local_variable = BYTESIZE_VARIABLE;
    }
    else
    {
        node->offset_argument_or_local_variable = func_cur->list_arguments_or_local_variables->offset + BYTESIZE_VARIABLE;
    }

    var = calloc(1, sizeof(ArgumentOrVariable));
    strncpy_s(var->name, strlen(token->string), token->string, token->length);
    var->length = token->length;
    var->offset = node->offset_argument_or_local_variable;
    var->next = func_cur->list_arguments_or_local_variables;
    func_cur->list_arguments_or_local_variables = var;

    return node;
}



