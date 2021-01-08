/*****************************************************************************
 * File name:   recursion.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-12-26 14:02:34
 * Description: Forward declaration of recursion.c
 *****************************************************************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>      /* size_t */
#include "slist.h"
#include "stack.h"

/* Iterative Fibonacci */
size_t Fibonacci(size_t num);

/* Recursive Fibonacci */
size_t FibonacciRec(size_t num); 

/* Recursive Strlen */
size_t StrlenRec(const char *str); 

/* Recursive Strcmp */
int StrcmpRec(const char *str1, const char *str2); 

/* Recursive Strcpy */
char *StrcpyRec(char *dest, const char *src); 

/* Recursive Strcat */
char *StrcatRec(char *dest, const char *src); 

/* Recursive Strstr */
char *StrstrRec(const char *haystack, const char *needle); 

/* Iterative SLFlip */
sl_node_t *SLFlipIter(sl_node_t *head);

/* Recursive SLFlip */
sl_node_t *SLFlipRec(sl_node_t *head);

/* Recursive SortStack */
void SortStackRec(stack_t *stack);
  
#endif     /* __RECURSION_H__ */
