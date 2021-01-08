/*****************************************************************************
 * File name:   stack_unit_test.c
 * Developer:   Yaron
 * Reviewer: 
 * Date:        2018-11-08 13:00:48
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <assert.h>    /* assert       */
 
#include "stack.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
int StackPush_test(void);
int StackPop_test(void);
int StackPeek_test(void);
int StackSize_test(void);
void StackPrint_test(void);
void PrintInt(void *element);

/* Global variables        */
 
 
int main(void)
{
                             /* count is the number of tests that succeeded */
    int count = 2;           /* create and destroy approaved by valgrind    */
    int tests = 6;
    count += StackPush_test();
    count += StackPop_test();
    count += StackPeek_test();
    count += StackSize_test();

    printf("%d tests succeed, %d tests faild\n", count, tests - count);
    StackPrint_test();
        

    printf("%d tests succeed, %d tests faild\n", count, tests - count); 
    StackPrint_test();

    
    return (EXIT_SUCCESS);
}

/******************************************************************************/
int StackPush_test(void)
{
    size_t capacity = 4;
    stack_t *stack = StackCreate(capacity, sizeof(char));
    
    char push_a = 'a';
    char push_b = 'b';
    char push_c = 'c';
    char push_d = 'd';
    char push_e = 'e';
    int status = 0;
    const char *peek_p = NULL;
    
    StackPush(stack, &push_a);
    StackPush(stack, &push_b);
    StackPush(stack, &push_c);
    StackPush(stack, &push_d);
    StackPush(stack, &push_e);
    peek_p = StackPeek(stack);
    status = StackPush(stack, &push_e);
    
    if (1 == status && 'd' == *peek_p)
    {
        StackDestroy(stack);
        
        return (1);
    }
    
    StackDestroy(stack);
    
    return (0);
}    

/******************************************************************************/
int StackPop_test(void)
{
    size_t capacity = 4;
    stack_t *stack = StackCreate(capacity, sizeof(unsigned long));

    unsigned long push_a = 2;
    unsigned long push_b = 4;
    unsigned long *p_a = &push_a;
    unsigned long *p_b = &push_b;
    int status = 0;

    StackPush(stack, p_a);
    StackPush(stack, p_b);
    
    StackPop(stack);
    StackPop(stack);
    status = StackPop(stack);
    
    if (1 == status)
    {
        StackDestroy(stack);
        
        return (1);
    }
    
    StackDestroy(stack);
    
    return (0);
}
    
/******************************************************************************/
int StackPeek_test(void)
{
    size_t capacity = 1;
    int a = 5;
    stack_t *stack = StackCreate(capacity, sizeof(int));
    
    const int *p1 = NULL;
    const int *p2 = NULL;
    const int *p3 = NULL;
    p1 = StackPeek(stack);
    StackPush(stack, &a);
    p2 = StackPeek(stack);
    StackPush(stack, &a);
    p3 = StackPeek(stack);
            
    if (5 == *p2 && NULL == p1 && 5 == *p3)
    {
        StackDestroy(stack);
        return (1);
    }

    StackDestroy(stack);    
    return (0);
} 

/******************************************************************************/
int StackSize_test(void)
{
    size_t capacity = 1;
    int a = 5;
    size_t size1 = 0;
    size_t size2 = 0;
    size_t size3 = 0; 
    stack_t *stack = StackCreate(capacity, sizeof(int));
        
    size1 = StackSize(stack);    
    StackPush(stack, &a);
    size2 = StackSize(stack);
    StackPush(stack, &a);
    size3 = StackSize(stack);
    
    if (0 == size1 && 1 == size2 && 1 == size3)
    {
        StackDestroy(stack);
        return (1);
    }
            
    StackDestroy(stack);
    return (0);
}

/******************************************************************************/
void StackPrint_test(void)
{
    int      i       = 0;
    size_t   size    = 5;
    stack_t *stack   = StackCreate(size, sizeof(int));     
    
    StackPrint(stack, NULL);
    StackPrint(stack, PrintInt);
    
    while ((size_t)i < size)
    {
        ++i;
        StackPush(stack, &i);
        StackPrint(stack, NULL);
        StackPrint(stack, PrintInt);
    }

    StackDestroy(stack);;
}

/******************************************************************************/
void PrintInt(void *element)
{
    assert(element);
    
    printf("%d ",*(int*)element);
}



