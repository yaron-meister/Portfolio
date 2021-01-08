/*****************************************************************************
 * File name:   stack_test.c
 * Developer:   Yaron
 * Reviewer: 
 * Date:        2018-11-07 13:44:48
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "stack.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
void Stack_test(void);
void UserPrint(void *element);

/* Global variables        */
 
 
int main(void)
{
    Stack_test();

 
    return (EXIT_SUCCESS);
}






/******************************************************************************/
void Stack_test(void)
{
    size_t capacity = 4;
    size_t element_size = sizeof(int);
    int push_a = 5;
    int push_b = 3;
    int push_c = 7;
    int *p_a = &push_a;
    int *p_b = &push_b;
    int *p_c = &push_c;
    const int *peek_p = NULL;
    void (*print_func1)(void *element);
      
    stack_t *stack = StackCreate(capacity, element_size);
    print_func1 = UserPrint;
        
    printf("The address of STACK is: %p\n", (void*)stack);
    StackPush(stack, p_a);
    StackPush(stack, p_b);
    StackPush(stack, p_c);
    peek_p = StackPeek(stack);
    printf("The value of the PEEK return is: %d\n", *peek_p);
    printf("The STACK SIZE is: %lu\n", StackSize(stack));
    StackPrint(stack, print_func1);
    printf("\n");
    StackPrint(stack, NULL);
    printf("\n");
    StackPop(stack);
    StackPop(stack);
 
    StackDestroy(stack);
}

/******************************************************************************/
void UserPrint(void *element)
{
    printf("%d ",*(int *)element);
}
    
