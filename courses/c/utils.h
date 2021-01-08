/*******************************************************************************
 * File name:   utils.h
 * Developer:   Yaron Meister
 * Description: All kind of usefull macros 
 ******************************************************************************/

#include <stddef.h>      /* size_t */

#ifndef NDEBUG  /* if in DEBUG mode -> define DBG macro to print out x        */
#define DBG(x) x
#else
#define DBG(x)  /* if not in DEBUG mode -> define DBG macro not to print out x*/
#endif
 
#define UNUSED_VAR(x) (void) x
 

/*size of variable or type witput using 'sizeof()'*/
#define SIZE_OF_VAR(var) ((size_t)(&var+1) - (size_t)&var)

#define SIZE_OF_TYPE(type) (size_t)(1 + (type *)0 )
