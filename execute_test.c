/*ファイル名：execute_test.c*/
/*責務：コンパイル結果が正しいかテスト* /

/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "execute_test.h"
#include<sys/>

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"

/*変数*/
/*****************************************************************************************/


/*公開関数*/
/*****************************************************************************************/
void execute_test(void)
{
	//tmpファイルポインタ
	FILE* tmpfile;

	char* path="./";

	//出力結果の行数
	char line[FILESIZE];

	//tmpファイル名
	char* name_tmpfile = "cmd.tmp";


	/*gcc -o a a.s & a & echo %errorlevel% */

	//命令
	char command[FILESIZE] = "gcc -o abc test.s & abc & echo %errorlevel%";

	//命令をtmpファイルに出力して、コマンドプロンプトで実行
	sprintf_s(command, FILESIZE, "%s %s > %s", command, path, name_tmpfile);
	int res = system(command);

	//添付ファイル読み込み
	errno_t flag_open = fopen_s(&tmpfile, name_tmpfile, "r");
	if (flag_open == 0)
	{
		for(int i=0 ;fgets(line, FILESIZE, tmpfile) != NULL ; i++)
		{
			printf("テスト番号：%d　結果：%s", i, line);
		}
		fclose(tmpfile);
	}
	else {
		error("テストファイルを読み込めませんでした");
	}
	//tmpファイルの削除
	remove(name_tmpfile);
}

