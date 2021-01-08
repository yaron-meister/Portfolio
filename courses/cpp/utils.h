/*******************************************************************************
 * File name:   utils.h
 * Developer:   Yaron Meister
 * Description: All kind of usefull macros 
 ******************************************************************************/

#include <stddef.h>      /* size_t */

#ifndef __UTILS_H__
#define __UTILS_H__

/* Debug mode */
#ifndef NDEBUG  /* if in DEBUG mode -> define DBG macro to print out x        */
#define DBG(x) x
#else
#define DBG(x)  /* if not in DEBUG mode -> define DBG macro not to print out x*/
#endif

/* Unused variable */ 
#define UNUSED_VAR(x) (void) x

/* Unit test mode */ 
#ifdef UNIT_TEST  /* if in UNIT_TEST mode -> define UT macro to print out x   */
#define UT(x) x
#else
#define UT(x) /*if not in UNIT_TEST mode -> define UT macro not to print out x*/
#endif

/* Word size */
#define WORD_SIZE (sizeof(size_t)) 
#define BITS_IN_BYTE (8)
#define BITS_IN_WORD_SIZE (WORD_SIZE * BITS_IN_BYTE)

/* Array size */
#define ARRAY_SIZE(A)	(sizeof(A)/sizeof((A)[0]))

/* Size of variable or type witput using 'sizeof()'*/
#define SIZE_OF_VAR(var) ((size_t)(&var+1) - (size_t)&var)

#define SIZE_OF_TYPE(type) (size_t)(1 + (type *)0 )

/* Max and Min */
#define MAX(A,B)		((A) > (B) ? (A) : (B))
#define MIN(A,B)		((A) < (B) ? (A) : (B))

/* Running to address */
#define RUN_TO_ADDRESS(RUNNER, ELEMENT_SIZE, INDEX)\
					         ((char*)RUNNER + (INDEX) * (ELEMENT_SIZE))

/* Colours */
#define RED_COLOUR     "\033[1;31m"
#define GREEN_COLOUR   "\033[1;32m"
#define YELLOW_COLOUR  "\033[1;33m"
#define BLUE_COLOUR    "\033[1;34m"
#define MAGENTA_COLOUR "\033[1;35m"
#define CYAN_COLOUR    "\033[1;36m"
#define RESET_COLOUR   "\033[0m"



#endif     /* __UTILS_H__ */







