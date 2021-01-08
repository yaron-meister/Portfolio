/*****************************************************************************
 * File name:   stack.c
 * Developer:   Yaron
 * Reviewer: 
 * Date:        2018-11-07 13:44:48
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /*              */
#include <assert.h>    /* assert       */
#include <string.h>    /* memcpy       */

#include "stack.h"      


/* Macros                  */
 
 
/* Forward Declarations    */
struct stack_s
{
	size_t 	capacity;		/* number of cells		    */
	size_t 	top_index; 		/* first non-occupied cell	*/
	size_t 	element_size;
	char 	data[8];
}; 
 
/* Global variables        */
 
/******************************************************************************/                 
stack_t *StackCreate(size_t capacity, size_t element_size)
{
    if ((capacity * element_size) > 0)
    {
        stack_t *stack_p = (stack_t*)malloc(24 + capacity * element_size);
         
        if (NULL == stack_p)
        {
            fprintf(stderr, "malloc faild!!!");
            return (NULL);
        }
        
        stack_p -> capacity = capacity;
        stack_p -> element_size = element_size;
        stack_p -> top_index = 0;   
    
    return (stack_p);
    }
    
    return (NULL);
} 

/******************************************************************************/                
void StackDestroy(stack_t *stack)
{
    free(stack);
    stack = NULL;
}

/******************************************************************************/
int StackPush(stack_t *stack, const void *element)
{
    assert(stack);
    assert(element);
    
    if ((stack -> top_index) < (stack -> capacity))
    {
        memcpy((stack -> data) + (stack -> top_index) * 
                (stack -> element_size), element, (stack -> element_size));
        ++(stack -> top_index);
        return (0);
    }
    
    return (1);
}

/******************************************************************************/
const void *StackPeek(const stack_t *stack)                                                                 
{
    assert (stack);
    
    if ((stack -> top_index) > 0)
    {
        return ((stack -> data) + (stack -> top_index - 1) * 
                (stack -> element_size));
    }
    
    return (NULL);
}

/******************************************************************************/
int StackPop(stack_t *stack)
{
    assert(stack);
    
    if (0 < (stack -> top_index))
    {
        stack -> data[(stack -> top_index - 1) * stack -> element_size] = 0;                
        --(stack -> top_index);
        
        return (0);
    }
    
    return (1);
}    
    
/******************************************************************************/   
size_t StackSize(const stack_t *stack)                                                      
{
    assert(stack);
    
    return (stack -> top_index);
}
    
/******************************************************************************/
void StackPrint(stack_t *stack, void (*print_func)(void *element))
{
	size_t top = 0;
	size_t floor = 0;
	
    assert(stack);
        
    top = stack -> top_index;
    
    printf("The STACK is: ");
    
    if (NULL == print_func)
    {
        while (floor < top)
        {
            printf("0x%x ",
             stack -> data[floor * stack -> element_size]);
             ++floor;
        }
    }
    else
    {
        while (floor < top)
        {
            print_func((stack -> data) + floor * 
                (stack -> element_size));
            ++floor;
        }
    }
    printf("\n");
}
    
    
    
    
    
    
    
    
    
    
    
    
