/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "generate_argument_or_variable.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"
#include "set_string.h"
#include "add_list.h"

/*���J�֐��F*/
/*****************************************************************************************/
void generate_argument(Function* function,Token* token)
{
    ArgumentOrVariable* argument = calloc(1, sizeof(ArgumentOrVariable));

    set_name_function_to_argument_or_variable(argument, token);

    argument->length = token->length;

    argument->offset = function->count_arguments * BYTESIZE_VARIABLE;

    add_argument_or_variable_to_list(argument, function);
}

void generate_local_variable(Node* node, Function* function, Token* token)
{
    //���������[�J���ϐ������݂��Ă��Ȃ��Ȃ猻�݂̎��ʎq��1�ڂɓo�^
    if (function->list_arguments_or_local_variables == NULL)
    {
        node->offset_argument_or_local_variable = BYTESIZE_VARIABLE;
    }
    //list�ɂ��Ȃ��Ȃ�O�̃I�t�Z�b�g������Z�����I�t�Z�b�g��o�^
    else
    {
        node->offset_argument_or_local_variable = function->list_arguments_or_local_variables->offset + BYTESIZE_VARIABLE;
    }

    ArgumentOrVariable* local_variable = calloc(1, sizeof(ArgumentOrVariable));

    set_name_function_to_argument_or_variable(local_variable, token);
    
    local_variable->length = token->length;

    local_variable->offset = node->offset_argument_or_local_variable;

    add_argument_or_variable_to_list(local_variable, function);
}