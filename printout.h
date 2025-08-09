#ifndef _PRINTOUT_H_
#define _PRINTOUT_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*externêÈåæ*/
/*****************************************************************************************/
extern void printout(char* string);
extern void printout_label(char* string , int num); 
extern void printout_jmplabel(char * command, char* label , int num); 
extern void printout_list_function(void);

#endif
