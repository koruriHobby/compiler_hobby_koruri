#ifndef _CHECK_TOKEN_H_
#define _CHECK_TOKEN_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

/*externêÈåæ*/
/*****************************************************************************************/
extern bool consume_keywords(char* string_expected);
extern bool consume_symbols(char* string_expected);
extern Token* consume_identifier(void);
extern void expect(char* string_expected);
extern int expect_number(void);
extern bool at_eof(void);

#endif


