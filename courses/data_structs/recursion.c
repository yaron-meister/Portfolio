/*****************************************************************************
 * File name:   recursion.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-12-26 14:02:34
 * Description: 
 *****************************************************************************/

#include <string.h>			 /*		 strncmp		 */
#include <assert.h>			 /* 	 assert			 */
 
#include "recursion.h"       /* Forward declarations */


/*************************** Forward Declarations *****************************/
static void StackPushRec(stack_t *stack, int data);


/************************ Functions's implementations *************************/
size_t Fibonacci(size_t num)
{
	size_t arr[] = {1, 1};
	size_t i = 2;
	
	while (i < num)
	{
		arr[i % 2] = arr[0] + arr[1];
		++i;
	}
	
	return (arr[!(i % 2)]);
}	  

/******************************************************************************/
size_t FibonacciRec(size_t num)
{
	if (num < 2)
	{
		return (num);
	}
	
	return (FibonacciRec(num - 1) + FibonacciRec(num - 2));
}

/******************************************************************************/
size_t StrlenRec(const char *str)
{
	assert(str);
	
	if ('\0' == *str)
	{
		return (0);
	}

	/* First '1' is for progressing <str> and the second '1' is for counting */	
	return ((StrlenRec(str + 1) + 1));
}

/******************************************************************************/
int StrcmpRec(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	
	if ('\0' == *str1 || *str1 != *str2)
	{
		return (*str1 - *str2);
	}
	
	return (StrcmpRec(str1 + 1, str2 + 1));
}

/******************************************************************************/
char *StrcpyRec(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	if ('\0' == *src)
	{
		*dest = *src;
		
		return (dest);
	}
	
	*dest = *src;
		
	StrcpyRec(dest + 1, src + 1);
	
	return (dest);
}

/******************************************************************************/
char *StrcatRec(char *dest, const char *src)
{
	assert(dest);
	assert(src);

	if ('\0' == *dest)
	{
		return (StrcpyRec(dest, src));
	}

	return (StrcatRec(dest + 1, src));
}

/******************************************************************************/
char *StrstrRec(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);
	
	if ('\0' == *haystack)
	{
		return (NULL);
	}
	
	if (*haystack == *needle &&
				0 == strncmp(haystack, needle, StrlenRec(needle)))
	{
		return ((char*)haystack);
	}

	return (StrstrRec (haystack + 1, needle));
}	
	
/******************************************************************************/        
sl_node_t *SLFlipIter(sl_node_t *head)
{
    sl_node_t *temp1 = head;
    sl_node_t *temp2 = NULL;
    sl_node_t *temp3 = NULL;

    assert(head);
    
    temp2 = temp1->next;
    
    if (NULL != temp2)
    {
    	temp3 = temp2->next;
	}
	
    while (NULL != temp3)
    {
        temp2->next = temp1;
        temp1 = temp2;
        temp2 = temp3;
        temp3 = temp3->next;
    }
    
    temp2->next = temp1;
    head->next = NULL;

    return (temp2);
}

/******************************************************************************/
sl_node_t *SLFlipRec(sl_node_t *head)
{
	sl_node_t *new_head = NULL;
	sl_node_t *temp 	= NULL;
	
	assert(head);
	
	temp = head->next;
	
	if (NULL == temp)
	{
		return (head);
	}
	
	new_head = SLFlipRec(temp);
	temp->next = head;
	head->next = NULL;

	return (new_head);
}
	
/******************************************************************************/
void SortStackRec(stack_t *stack)
{
	int temp = 0;

	assert(stack);
		
	if (2 > StackSize(stack))
	{
		return;
	}
	
	temp = *(int*)StackPeek(stack);
	StackPop(stack);
	SortStackRec(stack);
	StackPushRec(stack, temp);
}

/******************************************************************************/
static void StackPushRec(stack_t *stack, int data)
{
	int temp = 0;
	
	if (0 == StackSize(stack))
	{
		StackPush(stack, &data);
		return;
	}
	
	temp = *(int*)StackPeek(stack);
	
	if (data >= temp)
	{
		StackPush(stack, &data);
		return;
	}
	
	StackPop(stack);
	StackPushRec(stack, data);
	StackPush(stack, &temp);
}

/**************************** End OF FILE *************************************/

