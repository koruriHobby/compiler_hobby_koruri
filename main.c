/*�t�@�C�����Fmain.c*/
/*�Ӗ��F���͕�������󂯎���ăR���p�C�����ʂ��o�͂���B* /

/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "main.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "tokenize.h"
#include "parsa.h"
#include "compile.h"

/*�ϐ�*/
/*****************************************************************************************/
//char* user_input = "hoge(c){return (c+3);} foo(b){return hoge(b+2);} main(){a = 1; return foo(a);}";
//char* global_user_input = "main(){return 2;}";
char* global_user_input = "hoge(m){return (m-3);} foo(x){y =4; return hoge(x * y);} main(){a = 2; b = 2; c= a+b; return foo(c);}";
//char* global_user_input = "foo(n){if(n==0){return 0;}if(n==1){return 1;}else{return (foo(-1 + n)+foo(-2 + n));}} main(){a =8; return foo(a);}";

FILE* global_filepointer_output;
char* global_file_output = "b.s";

/*���J�֐�*/
/*****************************************************************************************/
int main(void) {

    tokenize();

    program();

    if (fopen_s(&global_filepointer_output, global_file_output, "w") != 0)
    {
        error("�o�͗p�t�@�C�����J���܂���ł���");
    }
    else
    {
        compile();
        fclose(global_filepointer_output);
    }

    return 0;
}