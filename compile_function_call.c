/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "compile_function_call.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"
#include "error.h"
#include "parsa.h"
#include "compile.h"
#include "generate_code.h"
#include "identify.h"
#include "printout.h"
#include "stackflame.h"

#define BYTESIZE_BUFFER 256

/*�ϐ�*/
/*****************************************************************************************/

/*���J�֐�*/
/*****************************************************************************************/
void compile_function_call(Node* node)
{
    char buffer[BYTESIZE_BUFFER];
    int alignment = 0;

    Function* function_print = identify_function_from_string(node->name_function);

    if (function_print == NULL)
    {
        error("�֐���������܂���");
    }

    if (node->arguments[0] != NULL)
    {
        for (int i = 0; i < node->count_arguments; i++)
        {
            generate_code(node->arguments[i]);
        }
    }

    for (int i = 0; i < node->count_arguments; i++)
    {
        sprintf_s(buffer, BYTESIZE_BUFFER, "%s", register_arguments[node->count_arguments - i - 1]);
        pop(buffer);
    }
   
    if (global_bytesize_push_or_pop % 16 != 0)
    {
        alignment = 16 - (global_bytesize_push_or_pop % 16);
    }

    sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rsp, %d\n  call %s\n  add rsp, %d\n", alignment, node->name_function, alignment);
    fprintf_s(global_filepointer_output, buffer);

    push("rax");
}