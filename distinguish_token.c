/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "distinguish_token.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "tokenize.h"

/*�ϐ�*/
/*****************************************************************************************/
static char* keywords[] = { "return","if","else","while","for" };
static char* symbols[] = { "==","!=",">=","<=", "+","-", "*","/", "(",")", ">","<", "=",";","{","}" ,"&","*", ","};

/*���J�֐��F*/
/*****************************************************************************************/
int iskeywords(char* string_token_current, int* length_token_current)
{
    for (int i = 0; keywords[i]; i++)
    {
        if (!strncmp(string_token_current, keywords[i], strlen(keywords[i])) 
            && !isalnum(string_token_current[strlen(keywords[i])]))
        {
            *length_token_current = (int)strlen(keywords[i]);
            return 1;
        }
    }
    return 0;
}

int issymbols(char* string_token_current, int* length_token_current)
{
    for (int i = 0; symbols[i]; i++)
    {
        if (!strncmp(string_token_current, symbols[i], strlen(symbols[i])))
        {
            *length_token_current = (int)strlen(symbols[i]);
            return 1;
        }
    }
    return 0;
}

int isidentifiers(char *string_token_current, int *length_token_current)
{
    if (isalpha(*string_token_current) || (*string_token_current == '_'))
    {
        char* string_identifier = string_token_current;
        int length_identifier = 0;
        do
        {
            string_identifier++;
            length_identifier++;
        } while (isalnum(*string_identifier) || (*string_identifier == '_'));

        if (*length_token_current > 64)
        {
            error("63�����ȏ�͕ϐ��Ƃ��Ċi�[�ł��܂���(C����)");
        }
        *length_token_current = length_identifier;
        return 1;
    }
    return 0;
}

int isnumber(char* string_token_current, int* length_token_current)
{
    if (isdigit(*string_token_current))
    {
        int length_number = 0;
        char* string_number = string_token_current;
        do
        {
            string_number++;
            length_number ++;
        } while (isdigit(*string_number));
        *length_token_current = length_number;
        return 1;
    }
    return 0;
}