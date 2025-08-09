/*�t�@�C�����Fprintout.c*/
/*�Ӗ��F���͕�������󂯎���ăR���p�C�����ʂ��o�͂���B* /

/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "printout.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"
#include "generate_code.h"
#include "compile.h"

/*�ϐ�*/
/*****************************************************************************************/

/*���J�֐�*/
/*****************************************************************************************/
void printout(char * string) 
{
	fprintf_s(global_filepointer_output, "%s\n", string);
}

void printout_label(char* label, int num)
{
	fprintf_s(global_filepointer_output, "%s%d:\n", label, num);
}
void printout_jmplabel(char* command, char* label, int num)
{
	fprintf_s(global_filepointer_output, "  %s %s%d\n",command, label, num);
}

void printout_list_function(void)
{
	fprintf_s(global_filepointer_output,".globl ");
	for (Function* cursol = global_list_functions; cursol; cursol = cursol->next)
	{
		if (cursol->next!= NULL)
		{
			fprintf_s(global_filepointer_output, "%s, ", cursol->name);
		}
		else
		{
			fprintf_s(global_filepointer_output, "%s", cursol->name);
		}
	}
	fprintf_s(global_filepointer_output, "\n" );
}