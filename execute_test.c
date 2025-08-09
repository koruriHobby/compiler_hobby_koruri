/*�t�@�C�����Fexecute_test.c*/
/*�Ӗ��F�R���p�C�����ʂ����������e�X�g* /

/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "execute_test.h"
#include<sys/>

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"

/*�ϐ�*/
/*****************************************************************************************/


/*���J�֐�*/
/*****************************************************************************************/
void execute_test(void)
{
	//tmp�t�@�C���|�C���^
	FILE* tmpfile;

	char* path="./";

	//�o�͌��ʂ̍s��
	char line[FILESIZE];

	//tmp�t�@�C����
	char* name_tmpfile = "cmd.tmp";


	/*gcc -o a a.s & a & echo %errorlevel% */

	//����
	char command[FILESIZE] = "gcc -o abc test.s & abc & echo %errorlevel%";

	//���߂�tmp�t�@�C���ɏo�͂��āA�R�}���h�v�����v�g�Ŏ��s
	sprintf_s(command, FILESIZE, "%s %s > %s", command, path, name_tmpfile);
	int res = system(command);

	//�Y�t�t�@�C���ǂݍ���
	errno_t flag_open = fopen_s(&tmpfile, name_tmpfile, "r");
	if (flag_open == 0)
	{
		for(int i=0 ;fgets(line, FILESIZE, tmpfile) != NULL ; i++)
		{
			printf("�e�X�g�ԍ��F%d�@���ʁF%s", i, line);
		}
		fclose(tmpfile);
	}
	else {
		error("�e�X�g�t�@�C����ǂݍ��߂܂���ł���");
	}
	//tmp�t�@�C���̍폜
	remove(name_tmpfile);
}

