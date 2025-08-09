/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "compile.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "parsa.h"
#include "generate_code.h"
#include "printout.h"

/*公開関数*/
/*****************************************************************************************/
void compile(void)
{
    printout(".intel_syntax noprefix");
    printout_list_function();

    // 先頭の式から順にコード生成
    for (int i = 0; global_function_declaration[i]; i++) 
    {
        compile_code(global_function_declaration[i]);
    }

}