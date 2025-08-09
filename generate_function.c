/*自ファイルのヘッダ*/
/*****************************************************************************************/
#include "generate_function.h"

/*利用ファイルのヘッダ*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "tokenize.h"

/*公開関数：*/
/*****************************************************************************************/
Function* generate_function(Token* token)
{
    Function* function = calloc(1, sizeof(Function));

    if (function == NULL)
    {
        error("領域を確保できませんでした");
    }
    else
    {
        strncpy_s(function->name, sizeof(token->string), token->string, token->length);
        function->length_name = (int)strlen(function->name);
        function->count_arguments = 0;
    }
    return function;
}