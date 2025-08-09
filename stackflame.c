/*�t�@�C�����Fstackflame.c*/
/*�Ӗ��F���͕�������󂯎���ăR���p�C�����ʂ��o�͂���B* /

/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "stackflame.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"
#include "generate_code.h"
#include "compile.h"
#include "printout.h"
#include "identify.h"

#define BYTESIZE_BUFFER 256
/*�ϐ�*/
/*****************************************************************************************/

/*���J�֐�*/
/*****************************************************************************************/
void push(char* string)
{
	char buffer[BYTESIZE_BUFFER];
	sprintf_s(buffer, BYTESIZE_BUFFER, "  push %s\n",string);
	fprintf_s(global_filepointer_output, buffer);
	global_bytesize_push_or_pop += 8;
}

void pop(char* string)
{
	char buffer[BYTESIZE_BUFFER];
	sprintf_s(buffer, BYTESIZE_BUFFER, "  pop %s\n", string);
	fprintf_s(global_filepointer_output, buffer);
	global_bytesize_push_or_pop -= 8;
}

void push_rbp(void)
{
	fprintf_s(global_filepointer_output, "  push rbp\n");
}
void pop_rbp(void)
{
	fprintf_s(global_filepointer_output, "  pop rbp\n");
}

void ret(void)
{
	fprintf_s(global_filepointer_output, "  ret\n");
}