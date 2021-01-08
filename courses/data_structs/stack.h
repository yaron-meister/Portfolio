/*****************************************************************************
 * File name:   stack.h
 * Developer:   Yaron
 * Reviewer: 	
 * Date:        2018-11-07 14:00:00
 * Description: stack data structure header. 
 *****************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack_s stack_t;

/*
 * Capacity is the total number of cells.
 * NULL is returned upon allocation failure.
 */
stack_t *StackCreate(size_t capacity, size_t element_size);

/* A function that destroys the STACK */
void StackDestroy(stack_t *stack);

/*
 * 0 success 
 * 1 full stack
 */
int StackPush(stack_t *stack, const void *element);

/*
 * Returns NULL if empty.
 * Note: once calling Push() and Pop() functions the pointer returned
 *       by Peek() will not point to the top element anymore.
 *       The user should use the returned pointer only once is sure
 *	`    that the pointer data is valid.
 */
const void *StackPeek(const stack_t *stack);

/*
 * 0 success 
 * 1 stack is empty
 */
int StackPop(stack_t *stack);

/*
 * returns number of elements inserted in stack
 */
size_t StackSize(const stack_t *stack); 

/*
 * User supplies print function per element, or NULL function pointer.
 * If print_func passed by the caller is NULL, data is printed in hex format.
 */
void StackPrint(stack_t *stack, void (*print_func)(void *element));

#endif /* __STACK_H__  */

