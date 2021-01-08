/*****************************************************************************
 * File name:   cqueue.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-01-24 11:57:27
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>      /* 		 fprintf  	    */
#include <assert.h>		/*		 assert			*/
#include <stdlib.h>		/*		 malloc			*/

#include "utils.h"		/*		   DBG			*/
#include "q.h"			/*		   q.c			*/
#include "cqueue.h"     /* Forward declarations */

/* Forward Declarations    */
struct cqueue
{
    queue_t *que;
};

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
cq_t *CQCreate(void)
{
    cq_t *cque = (cq_t*)malloc(sizeof(cq_t));
    if (NULL != cque)
    {
       cque->que = QCreate();
       if (NULL == cque->que)
    	{
        	fprintf(stderr, "Malloc failed!!!");
        	
        	free(cque);
        	cque = NULL;
    	} 
    }

    return (cque);
}

/******************************************************************************/
void CQDestroy(cq_t *cque)
{
    assert(cque);

    QDestroy(cque->que);
    cque->que = NULL;
   
    free(cque);
    cque = NULL;	
}  

/******************************************************************************/
size_t CQSize(const cq_t *cque)
{    
    assert(cque);
    
    return (QSize(cque->que));
}

/******************************************************************************/
int CQIsEmpty(const cq_t *cque)
{
    assert(cque);
    
    return (QIsEmpty(cque->que));
}  

/******************************************************************************/
int CQEnqueue(cq_t *cque, int data)
{
	int temp = data;
	
    assert(cque);
    
    return (QEnqueue(cque->que, &temp));
}

/******************************************************************************/
void *CQDequeue(cq_t *cque)
{
	assert(cque);
	
	return (QDequeue(cque->que));
}

/******************************************************************************/
int CQPeek(const cq_t *cque)
{
	assert(cque);
	
	return (*(int*)QPeek(cque->que));
}












/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
