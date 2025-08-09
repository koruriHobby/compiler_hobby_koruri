#ifndef _STACKFLAME_H_
#define _STACKFLAME_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*externêÈåæ*/
/*****************************************************************************************/
extern void ret(void);
extern void push_rbp(void);
extern void pop_rbp(void);
extern void push(char* string);
extern void pop(char* string);

#endif

