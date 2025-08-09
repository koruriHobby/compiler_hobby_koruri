/*�t�@�C�����Ferror.c*/
/*�Ӗ��F�e�H���ŃG���[���o���ۂɃG���[��\������* /

/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"

/*���J�֐�*/
/*****************************************************************************************/
void error(char* fmt, ...) 
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char* loc, char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - global_user_input;
    fprintf(stderr, "%s\n", global_user_input);
    fprintf(stderr, "%*s", pos, " "); // pos�̋󔒂��o��
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

/*����J�֐��F*/
/*****************************************************************************************/
//�Ȃ�