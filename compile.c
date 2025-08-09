/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "compile.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "parsa.h"
#include "generate_code.h"
#include "printout.h"

/*���J�֐�*/
/*****************************************************************************************/
void compile(void)
{
    printout(".intel_syntax noprefix");
    printout_list_function();

    // �擪�̎����珇�ɃR�[�h����
    for (int i = 0; global_function_declaration[i]; i++) 
    {
        compile_code(global_function_declaration[i]);
    }

}