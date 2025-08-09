/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "generate_function.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"

/*���J�֐��F*/
/*****************************************************************************************/
Function* generate_function(Token* token)
{
    Function* function = calloc(1, sizeof(Function));

    if (function == NULL)
    {
        error("�̈���m�ۂł��܂���ł���");
    }
    else
    {
        strncpy_s(function->name, sizeof(token->string), token->string, token->length);
        function->length_name = (int)strlen(function->name);
        function->count_arguments = 0;
    }
    return function;
}