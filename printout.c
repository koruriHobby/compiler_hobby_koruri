/*ファイル名：printout.c*/
/*責務：入力文字列を受け取ってコンパイル結果を出力する。* /

/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "printout.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "main.h"
#include "generate_code.h"
#include "compile.h"

/*変数*/
/*****************************************************************************************/

/*公開関数*/
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