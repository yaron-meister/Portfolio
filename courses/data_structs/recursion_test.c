/*****************************************************************************
 * File name:   recursion_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Rachel
 * Date:        2018-12-26 14:02:34
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>    		 /*      printf          */
#include <stdlib.h>    		 /*   EXIT_SUCCESS       */
#include <string.h>			 /* 	strcpy           */
 
#include "recursion.h"       /* Forward declarations */
		

/**************************** Forward Declarations ****************************/
void Fibonacci_test(void);
void StrlenRec_test(void);
void StrcmpRec_test(void);
void StrcpyRec_test(void);
void StrcatRec_test(void);
void StrstrRec_test(void);
void SLFlip_test(void);
void SLFlipRec_test(void);
void SortStackRec_test(void);

typedef struct person
{
    char name[10];
    int age;
    int height;
} person_t;

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{   
	printf("\n*********** WELCOME TO YARON's UNIT-TEST ********************\n");
    
	Fibonacci_test();
	StrlenRec_test();
	StrcmpRec_test();
	StrcpyRec_test();
	StrcatRec_test();
	StrstrRec_test(); 
	SLFlip_test();
	SLFlipRec_test();
	SortStackRec_test();
	
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/ 
/******************************************************************************/
void Fibonacci_test(void)
{ 
	printf("\n************* Fibonacci ITER + REC - TEST *******************\n");

	if (1 != Fibonacci(1))
    {
        printf("Test No. 1 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }

	++g_tests;

	if (1 != FibonacciRec(1))
    {
        printf("Test No. 2 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }

	++g_tests;

	if (FibonacciRec(7) != Fibonacci(7))
    {
        printf("Test No. 3 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }

	++g_tests;
}

/******************************************************************************/    
void StrlenRec_test(void)
{
    char str1[] = "Hello";
    char str2[] = "";

	printf("\n******************* StrlenRec - TEST ************************\n");

    if (5 != StrlenRec(str1))
    {
        printf("Test No. 4 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 4 succeded\n");
		++g_count;
    }

	++g_tests;

	if (0 != StrlenRec(str2))
    {
        printf("Test No. 5 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 5 succeded\n");
		++g_count;
    }

	++g_tests;
}
       
/******************************************************************************/    
void StrcmpRec_test(void)
{
    char str1[] = "He2lo";
    char str2[] = "Hello";
    char str3[] = "Hello";
    char str4[] = "";

	printf("\n******************* StrcmpRec - TEST ************************\n");

    if (0 <= StrcmpRec(str1, str2))
    {
        printf("Test No. 6 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 6 succeded\n");
		++g_count;
    }

	++g_tests;

    if (0 != StrcmpRec(str2, str3))
    {
        printf("Test No. 7 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 7 succeded\n");
		++g_count;
    }
 	
	++g_tests; 

	if (0 >= StrcmpRec(str3, str4))
    {
        printf("Test No. 8 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 8 succeded\n");
		++g_count;
    }
 	
	++g_tests;     
}

/******************************************************************************/
void StrcpyRec_test(void)
{
    char src[] = "World";
    char dest[20] = "";
	
	printf("\n******************* StrcpyRec - TEST ************************\n");

	StrcpyRec(dest, src);	

    if (5 != StrlenRec(dest))
    {
        printf("Test No. 9 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 9 succeded\n");
		++g_count;
    }

	++g_tests;

	if ('r' != *(dest + 2))
    {
        printf("Test No. 10 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 10 succeded\n");
		++g_count;
    }

	++g_tests;
	
	if (StrcpyRec(dest, src) != strcpy(dest, src))
    {
        printf("Test No. 11 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 11 succeded\n");
		++g_count;
    }

	++g_tests;      
}

/******************************************************************************/
void StrcatRec_test(void)
{
    char src[] = "world";
    char dest[20] = "Hello ";

	printf("\n******************* StrcatRec - TEST ************************\n");

	StrcatRec(dest, src);	

    if (11 != StrlenRec(dest))
    {
        printf("Test No. 12 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 12 succeded\n");
		++g_count;
    }

	++g_tests;

	if ('w' != *(dest + 6))
    {
        printf("Test No. 13 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 13 succeded\n");
		++g_count;
    }

	++g_tests;
}
       
/******************************************************************************/
void StrstrRec_test(void)
{
    char haystack[] = "Hello, my name is Yaron";
    char needle1[]  = "He";
	char needle2[]  = "ron";
	char needle3[]  = "y n";
	char needle4[]  = "Hello, my name is Yarom";

	printf("\n******************* StrstrRec - TEST ************************\n");
	
    if (NULL == StrstrRec(haystack, needle1))
    {
        printf("Test No. 14 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 14 succeded\n");
		++g_count;
    }

	++g_tests;

	if (NULL == StrstrRec(haystack, needle2))
    {
        printf("Test No. 15 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 15 succeded\n");
		++g_count;
    }

	++g_tests;
	
	if (NULL == StrstrRec(haystack, needle3))
    {
        printf("Test No. 16 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 16 succeded\n");
		++g_count;
    }

	++g_tests;

	if (NULL != StrstrRec(haystack, needle4))
    {
        printf("Test No. 17 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 17 succeded\n");
		++g_count;
    }

	++g_tests;

}

/******************************************************************************/
void SLFlip_test(void)
{
    person_t person  = {"Yaron", 28, 183};
    sl_node_t *head  = SLCreateNode(NULL, &person.name);
    sl_node_t *node1 = SLCreateNode(NULL, &person.age);
    sl_node_t *node2 = SLCreateNode(NULL, &person.height);
    sl_node_t *node3 = SLCreateNode(NULL, &person.name);
        
    SLInsertAfter(head, node3);
    SLInsertAfter(head, node2);
    SLInsertAfter(head, node1);
    SLFlipIter(head);

    printf("\n*************** FlipIter - TEST *****************************\n"); 

    if (183 != (*(int*)((node3->next)->data)))
    {
        printf("Test No. 18 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++g_count;
    }

	++g_tests;

    if (28 != (*(int*)((node2->next)->data)))
    {
        printf("Test No. 19 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++g_count;
    }

	++g_tests;

    if ('Y' != (*(char*)((node1->next)->data)))
    {
        printf("Test No. 20 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++g_count;
    }

	++g_tests;

    if (NULL != head->next)
    {
        printf("Test No. 21 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 21 succeded\n");
        ++g_count;
    }

	++g_tests;
    
    SLFreeNode(head);
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);
}           

/******************************************************************************/
void SLFlipRec_test(void)
{
    person_t person  = {"Yaron", 28, 183};
    sl_node_t *head  = SLCreateNode(NULL, &person.name);
    sl_node_t *node1 = SLCreateNode(NULL, &person.age);
    sl_node_t *node2 = SLCreateNode(NULL, &person.height);
    sl_node_t *node3 = SLCreateNode(NULL, &person.name);    

    SLInsertAfter(head, node3);
    SLInsertAfter(head, node2);
    SLInsertAfter(head, node1);
    SLFlipRec(head);

    printf("\n**************** FlipRec - TEST *****************************\n"); 

    if (183 != (*(int*)((node3->next)->data)))
    {
        printf("Test No. 22 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++g_count;
    }

	++g_tests;

    if (28 != (*(int*)((node2->next)->data)))
    {
        printf("Test No. 23 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 23 succeded\n");
        ++g_count;
    }

	++g_tests;

    if ('Y' != (*(char*)((node1->next)->data)))
    {
        printf("Test No. 24 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 24 succeded\n");
        ++g_count;
    }

	++g_tests;

    if (NULL != head->next)
    {
        printf("Test No. 25 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 25 succeded\n");
        ++g_count;
    }

	++g_tests;
    
    SLFreeNode(head);
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);
}           

/******************************************************************************/    
void SortStackRec_test(void)
{
    stack_t *stack1 = StackCreate(10, sizeof(int));
    stack_t *stack2 = StackCreate(10, sizeof(int));
    stack_t *stack3 = StackCreate(10, sizeof(int));
    stack_t *stack4 = StackCreate(10, sizeof(int));
    int a 	   = 4;
    int b 	   = 2;
    int c 	   = 1;
    int d 	   = 5;
    int e 	   = 3;
    int arr[5] = {0};
    int i	   = 0;
    
    printf("\n************** SortStackRec - TEST **************************\n");
    
 	StackPush(stack1, &a);   
    StackPush(stack1, &b);
    StackPush(stack1, &c);
    StackPush(stack1, &d);
    StackPush(stack1, &e);
        
    SortStackRec(stack1);
    for (i = 0; i < 5; ++i)
    {
    	arr[i] = *(int*)StackPeek(stack1);
    	StackPop(stack1);
	}
	
	if (5 != arr[0] || 4 != arr[1] || 3 != arr[2] || 2 != arr[3] || 1 != arr[4])
    {
    	printf("Test No. 26 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 26 succeded\n");
        ++g_count;
    }

	++g_tests;
	
    StackPush(stack2, &d);
	StackPush(stack2, &a);   
    StackPush(stack2, &e);
    StackPush(stack2, &b);
    StackPush(stack2, &c);

	SortStackRec(stack2);
    for (i = 0; i < 5; ++i)
    {
    	arr[i] = *(int*)StackPeek(stack2);
    	StackPop(stack2);
	}
	
	if (5 != arr[0] || 4 != arr[1] || 3 != arr[2] || 2 != arr[3] || 1 != arr[4])
    {
    	printf("Test No. 27 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 27 succeded\n");
        ++g_count;
    }

	++g_tests;
	
    StackPush(stack3, &c);
    StackPush(stack3, &b);
    StackPush(stack3, &e);
	StackPush(stack3, &a);   
	StackPush(stack3, &d);

	SortStackRec(stack3);
    for (i = 0; i < 5; ++i)
    {
    	arr[i] = *(int*)StackPeek(stack3);
    	StackPop(stack3);
	}
	
	if (5 != arr[0] || 4 != arr[1] || 3 != arr[2] || 2 != arr[3] || 1 != arr[4])
    {
    	printf("Test No. 28 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 28 succeded\n");
        ++g_count;
    }

	++g_tests;
	
	StackPush(stack4, &c);

	SortStackRec(stack4);
    for (i = 0; i < 1; ++i)
    {
    	arr[i] = *(int*)StackPeek(stack4);
    	StackPop(stack4);
	}
	
	if (1 != arr[0]) 
    {
    	printf("Test No. 29 \t\tfailed\n");
    }
    else
    {
        printf("Test No. 29 succeded\n");
        ++g_count;
    }

	++g_tests;
	
    StackDestroy(stack1);
    StackDestroy(stack2);
    StackDestroy(stack3);
    StackDestroy(stack4);
}
         
/******************************* END OF FILE **********************************/

