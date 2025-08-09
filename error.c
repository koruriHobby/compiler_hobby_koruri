/*ファイル名：error.c*/
/*責務：各工程でエラーが出た際にエラーを表示する* /

/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "main.h"

/*公開関数*/
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
    fprintf(stderr, "%*s", pos, " "); // pos個の空白を出力
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

/*非公開関数：*/
/*****************************************************************************************/
//なし