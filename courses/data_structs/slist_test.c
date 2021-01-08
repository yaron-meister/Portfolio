/*****************************************************************************
 * File name:   slist_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Majd
 * Date:        2018-11-15 12:45:35
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>    /* memcpy       */
 
#include "slist.h"       /*              */

/* Macros                  */
 
/* Forward Declarations    */
void SLCreateAndDestroyNode_test(void *data1, void *data2);
int SLInsertAfter_test(void);
int SLInsertBefore_test(void);
int SLRemoveAfter_test(void);
int SLRemove_test(void);
int SLCount_test(void);
int SLForEach_test(void);
int SLFind_test(void);
int SLFlip_test(void);
int SLFindIntersection_test(void);
int SLHasLoop_test(void);
int Action(void *data, void *param);
int CompareData(const void *data, const void *param);
void SLInterview_test(void);
/*void TEST(void);*/

typedef struct person
{
    char name[10];
    int age;
    int height;
} person_t;

 
/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/   
int main(void)
{
                        /* count is the number of tests that succeeded */
    int count = 3;      /* Create, Free and FreeAll approaved by valgrind */
    int tests = 30;
 
    count += SLInsertAfter_test();
    count += SLInsertBefore_test();
    count += SLRemoveAfter_test();
    count += SLRemove_test();
    count += SLCount_test();
    count += SLForEach_test();
    count += SLFind_test();
    count += SLFlip_test();
    count += SLHasLoop_test();
    count += SLFindIntersection_test();
    SLInterview_test();
   
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count, tests - count); 
    printf("\n");
  
    return (EXIT_SUCCESS);
}

/******************************************************************************/
int SLInsertAfter_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertAfter(head, end_node);
    SLInsertAfter(head, node);

    printf("\n******************* InsertAfter - TEST **********************\n");

    if ('Y' != *((char*)head->data))
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++status;
    }
    
    if (28 != *((int*)(head->next)->data))
    {
        printf("Test No. 2 failed\n");
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++status;
    }

    if (183 != *((int*)(node->next)->data))
    {
        printf("Test No. 3 failed\n");
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++status;
    }

    SLFreeAll(head);

    return (status);
}

/******************************************************************************/
int SLInsertBefore_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertBefore(head, node);
    SLInsertBefore(node, end_node);

    printf("\n******************* InsertBefore - TEST *********************\n");

    if (28 != *((int*)head->data))
    {
        printf("Test No. 4 failed\n");
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++status;
    }
    
    if (183 != *((int*)(head->next)->data))
    {
        printf("Test No. 5 failed\n");
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++status;
    }

    if ('Y' != *((char*)(node->next)->data))
    {
        printf("Test No. 6 failed\n");
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++status;
    }

    SLFreeAll(head);

    return (status);
}

/******************************************************************************/
int SLRemoveAfter_test(void)   
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertAfter(head, end_node);
    SLInsertAfter(head, node);
    SLRemoveAfter(node);
    SLFreeNode(end_node);

    printf("\n******************* RemoveAfter - TEST **********************\n");

    if (head->next != node)
    {
        printf("Test No. 7 failed\n");
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++status;
    }
    
    if (NULL != node->next)
    {
        printf("Test No. 8 failed\n");
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++status;
    }

    SLRemoveAfter(head);
    SLFreeNode(node);

    if (NULL != head->next)
    {
        printf("Test No. 9 failed\n");
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++status;
    }

    SLFreeAll(head);

    return (status);
}  

/******************************************************************************/
int SLRemove_test(void)   
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertAfter(head, end_node);
    SLInsertAfter(head, node);
    SLRemove(node);
    SLFreeNode(end_node);

    printf("\n******************* Remove - TEST ***************************\n");

    if (NULL != node->next)
    {
        printf("Test No. 10 failed\n");
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++status;
    }
    
    if (183 != *(int*)node->data)
    {
        printf("Test No. 11 failed\n");
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++status;
    }

    SLRemove(head);
    SLFreeNode(node);

    if (NULL != head->next)
    {
        printf("Test No. 12 failed\n");
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++status;
    }

    if (183 != *(int*)head->data)
    {
        printf("Test No. 13 failed\n");
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++status;
    }

    SLFreeAll(head);

    return (status);
}  

/******************************************************************************/
int SLCount_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    int count = SLCount(head);

    printf("\n******************* Count - TEST ****************************\n");

    if (1 != count)
    {
        printf("Test No. 14 failed\n");
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++status;
    }

    SLInsertAfter(head, node);
    count = SLCount(head);

    if (2 != count)
    {
        printf("Test No. 15 failed\n");
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++status;
    }
    
    SLRemove(head);
    SLFreeNode(node);
    count = SLCount(head);

    if (1 != count)
    {
        printf("Test No. 16 failed\n");
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++status;
    }

    SLFreeAll(head);

    return (status);
}  

/******************************************************************************/
int SLForEach_test(void)
{
    int (*action_func)(void *data, void *param) = Action;
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    int a = 0; 
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertAfter(head, end_node);
    SLInsertAfter(head, node);

    printf("\n******************* ForEach - TEST **************************\n"); 

    if (0 != SLForEach(node, action_func, &a, NULL))
    {
        printf("Test No. 17 failed\n");
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++status;
    }
    
    SLFreeAll(head);

    return (status);
}  

/******************************************************************************/
int SLFind_test(void)
{
    int (*compare_func)(const void *data, const void *param) = CompareData;
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    int a = 183;
    int b = 83; 
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node = SLCreateNode(NULL, &person.age);
    sl_node_t *end_node = SLCreateNode(NULL, &person.height);
    SLInsertAfter(head, end_node);
    SLInsertAfter(head, node);

    printf("\n******************* Find - TEST *****************************\n"); 

    if (SLFind(node, compare_func, &a) != end_node)
    {
        printf("Test No. 18 failed\n");
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++status;
    }

    if (NULL != SLFind(node, compare_func, &b))
    {
        printf("Test No. 19 failed\n");
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++status;
    }
    
    SLFreeAll(head);

    return (status);
}          

/******************************************************************************/
int SLFlip_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node1 = SLCreateNode(NULL, &person.age);
    sl_node_t *node2 = SLCreateNode(NULL, &person.height);
    sl_node_t *node3 = SLCreateNode(NULL, &person.name);    
    SLInsertAfter(head, node3);
    SLInsertAfter(head, node2);
    SLInsertAfter(head, node1);
    SLFlip(head);

    printf("\n******************* Flip - TEST *****************************\n"); 

    if (183 != (*(int*)((node3->next)->data)))
    {
        printf("Test No. 20 failed\n");
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++status;
    }

    if (28 != (*(int*)((node2->next)->data)))
    {
        printf("Test No. 21 failed\n");
    }
    else
    {
        printf("Test No. 21 succeded\n");
        ++status;
    }

    if ('Y' != (*(char*)((node1->next)->data)))
    {
        printf("Test No. 22 failed\n");
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++status;
    }

    if (NULL != head->next)
    {
        printf("Test No. 23 failed\n");
    }
    else
    {
        printf("Test No. 23 succeded\n");
        ++status;
    }
    
    SLFreeNode(head);
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);

    return (status);
}          

/******************************************************************************/
int SLHasLoop_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};
    sl_node_t *head = SLCreateNode(NULL, &person.name);
    sl_node_t *node1 = SLCreateNode(NULL, &person.age);
    sl_node_t *node2 = SLCreateNode(NULL, &person.height);
    sl_node_t *node3 = SLCreateNode(NULL, &person.name);    
    SLInsertAfter(head, node3);
    SLInsertAfter(head, node2);
    SLInsertAfter(head, node1);
    node3->next = node1;

    printf("\n******************* LOOP - TEST *****************************\n"); 

    if (!SLHasLoop(head))
    {
        printf("Test No. 24 failed\n");
    }
    else
    {
        printf("Test No. 24 succeded\n");
        ++status;
    }

    node3->next = NULL;

    if (SLHasLoop(head))
    {
        printf("Test No. 25 failed\n");
    }
    else
    {
        printf("Test No. 25 succeded\n");
        ++status;
    }

    SLFreeNode(head);
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);

    return (status);
}          

/******************************************************************************/
int SLFindIntersection_test(void)
{
    int status = 0;
    person_t person = {"Yaron", 28, 183};

    sl_node_t *node7 = SLCreateNode(NULL, &person.name);     
    sl_node_t *node6 = SLCreateNode(node7, &person.height);
    
    sl_node_t *node3 = SLCreateNode(node6, &person.name);
    sl_node_t *node2 = SLCreateNode(node3, &person.height);
    sl_node_t *node1 = SLCreateNode(node2, &person.age);
    sl_node_t *head1 = SLCreateNode(node1, &person.name);
    
    
     
    sl_node_t *node5 = SLCreateNode(node6, &person.height);
    sl_node_t *node4 = SLCreateNode(node5, &person.age);
    sl_node_t *head2 = SLCreateNode(node4, &person.name);
        
    printf("\n******************* Intersection - TEST *********************\n"); 

    if (SLFindIntersection(head1, head2) != node6)
    {
        printf("Test No. 26 failed\n");
    }
    else
    {
        printf("Test No. 26 succeded\n");
        ++status;
    }

    node5->next = NULL;

    if (NULL != SLFindIntersection(head1, head2))
    {
        printf("Test No. 27 failed\n");
    }
    else
    {
        printf("Test No. 27 succeded\n");
        ++status;
    }

    SLFreeNode(head1);
    SLFreeNode(head2);
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);
    SLFreeNode(node4);
    SLFreeNode(node5);
    SLFreeNode(node6);
    SLFreeNode(node7);

    return (status);
}          
    
/******************************************************************************/
int Action(void *data, void *param)
{
    int status = 1;

    memcpy(param, data, sizeof(int));
    
    if (*(int*)data == *(int*)param)
    {
        status = 0;
    }
 
    return (status);
}
                                                      
/******************************************************************************/
int CompareData(const void *data, const void *param)
{
    int status = 1;

    if (*(int*)data == *(int*)param)
    {
        status = 0;
    }

    return (status);
}

/******************************************************************************/
void SLInterview_test(void)
{
    person_t person = {"Yaron", 28, 183};
    sl_node_t *temp = NULL;

    sl_node_t *node5 = SLCreateNode(NULL, &person.name);     
    sl_node_t *node4 = SLCreateNode(node5, &person.height);    
    sl_node_t *node3 = SLCreateNode(node4, &person.name);
    sl_node_t *node2 = SLCreateNode(node3, &person.height);
    sl_node_t *node1 = SLCreateNode(node2, &person.age);
    temp = node1;
             
    printf("\n******************* INTERVIEW - TEST ************************\n"); 

    while (NULL != temp && NULL != temp->next)
    {
        temp = temp->next->next;
    }
    
    
    
    printf((NULL == temp) ? "There is an even number of nodes\n" : "There is an odd number of nodes\n");
    
    /*if (NULL == temp)
    {
        printf("There is an even number of nodes\n");
    }
    else 
    {
        printf("There is an odd number of nodes\n");
    }*/
        
    SLFreeNode(node1);
    SLFreeNode(node2);
    SLFreeNode(node3);
    SLFreeNode(node4);
    SLFreeNode(node5);
}      
