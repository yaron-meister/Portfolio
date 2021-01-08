/*****************************************************************************
 * File name:   heap.c
 * Developer:   Yaron Meister
 * Reviewer: 	Rachel
 * Date:        2019-01-07 09:17:04
 * Description: Heap data structure implementation
 *****************************************************************************/
 
#include <stdio.h>      /* 		fprintf()      */
#include <stdlib.h>     /*        malloc        */
#include <assert.h>		/*		  assert		*/

#include "utils.h"		/*		   DBG			*/
#include "dv.h"			/*	  Dynamic vector	*/   
#include "heap.h"       /* Forward declarations */


/********************************* Macros *************************************/
#define TOP_OF_HEAP (0)		/* An index to the top of the heap */

typedef enum status
{
	NOT_FOUND,
	FOUND
} status_t;

typedef enum swap
{
	NOT_SWAPPED,
	SWAPPED
} swap_t;
 
/************************** Forward Declarations ******************************/
struct heap
{
	dv_t *dv;
	int(*is_before)(const void *element1, const void *element2, void *param);
	void *param;
};

static void HeapifyUp(heap_t *heap, ssize_t index);
static void HeapifyDown(heap_t *heap, size_t index);
static void SwapFamilyMember(void **parent, void **child);
static ssize_t FindMyParent(ssize_t index);
static ssize_t FindMyLeft(ssize_t index);

/* A function that finds if 'arg' exists and returns his index */
static ssize_t FindIndex(heap_t *heap,
		   int (*is_match)(const void *data, const void *arg), const void *arg);	   
static void PrintFunc(void *element);

/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
heap_t *HeapCreate(size_t capacity, 
       int(*is_before)(const void *element1, const void *element2, void *param),
																   void *param)
{
	heap_t *heap = NULL;
	
	if (NULL != is_before && capacity > 0)
	{
		heap = (heap_t*)malloc(sizeof(heap_t));															   
		if (NULL != heap)
		{
			heap->is_before = is_before;
			heap->param		= param;
			heap->dv 		= DVCreate(capacity, sizeof(void*));
			if (NULL == heap->dv)
			{
				DBG(fprintf(stderr, "dv creation failed!!!\n"));
				HeapDestroy(heap);
				heap = NULL;
			}
		}
	}
	
	return (heap);
}
		
/******************************************************************************/ 
void HeapDestroy(heap_t *heap)
{
	assert(heap);
	
	if (NULL != heap->dv)
	{
		DVDestroy(heap->dv);
		heap->dv = NULL;
	}
	
	heap->is_before = NULL;
	heap->param		= NULL;
	
	free(heap);
	heap = NULL;
}

/******************************************************************************/
size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return ((NULL != heap->dv) ? DVSize(heap->dv) : 0);
}
	
/******************************************************************************/	
int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return (0 == HeapSize(heap));
}
	
/******************************************************************************/	
void *HeapPeek(const heap_t *heap)
{
	void *peek = NULL;
	
	assert(heap);
	
	/* TOP_OF_HEAP is an index to the top of the heap (0) */
	if (! HeapIsEmpty(heap))
	{
		peek = (*(void**)DVItemAddress(heap->dv, TOP_OF_HEAP));
	}
	
	return (peek);
}
	
/******************************************************************************/	
int HeapPush(heap_t *heap, void *data)
{
	/*
	 * 1. Push 'data' to the back of the 'dv'
	 * 2. Heapify up by comparing with (inserted index)/2 which is the parent 
	*/
	
	ssize_t index = -1;
	
	assert(heap);
	assert(data);
	
	if (NULL != heap->dv)
	{
		index = DVPushBack(heap->dv, &data);
		HeapifyUp(heap, index);
	}
	
	return (! (0 <= index));
}
	
/*********															***********/
/* A function that push up a value according to Heap policy if necessary */
static void HeapifyUp(heap_t *heap, ssize_t index)
{	
	assert(heap);
	
	while (index > 0)
	{
		if (! heap->is_before(*(void**)DVItemAddress(heap->dv,
														   FindMyParent(index)), 
						  *(void**)DVItemAddress(heap->dv, index), heap->param))
        {
        	SwapFamilyMember(DVItemAddress(heap->dv, FindMyParent(index)),
        					 DVItemAddress(heap->dv, index));
    	}
    	
    	index = FindMyParent(index);	/* index = index's parent */		
	}	
}

/*********															***********/
/* A function that push down a value according to Heap policy if necessary */
static void HeapifyDown(heap_t *heap, size_t index)
{
	size_t left_index  	= FindMyLeft(index);
	size_t right_index 	= left_index + 1;
	size_t max_value_index = index;
	
	assert(heap);
	
	/* While 'index' has at least one child */
	while (left_index < HeapSize(heap))
	{
		/* If there is a left child and he is before */ 
		if (heap->is_before(*(void**)DVItemAddress(heap->dv, left_index), 
			 		      *(void**)DVItemAddress(heap->dv, index), heap->param))
		{
			max_value_index = left_index;
		}
	
		/* If there is a right child and he is before 'max_value_index' */ 
		if (right_index < HeapSize(heap) &&
			heap->is_before(*(void**)DVItemAddress(heap->dv, right_index), 
			    *(void**)DVItemAddress(heap->dv, max_value_index), heap->param))
		{
			max_value_index = right_index;
		}
	
		/* If swapping is necessary */ 
		if (max_value_index != index)
		{
			SwapFamilyMember(DVItemAddress(heap->dv, max_value_index),
							 DVItemAddress(heap->dv, index));
		}
		/* If swapping is NOT necessary, return */
		else
		{
			break;
		}
	
		index 		= max_value_index;
		left_index  = FindMyLeft(index);
		right_index = left_index + 1;
	}
}

/*********															***********/
static ssize_t FindMyParent(ssize_t index)
{
	return ((index - 1) / 2);
}

/*********															***********/
static ssize_t FindMyLeft(ssize_t index)
{
	return ((index + 1) * 2 - 1);
}

/*********															***********/
static void SwapFamilyMember(void **parent, void **child)
{
	void *temp = *parent;
	*parent	   = *child;
	*child	   = temp;
}

/******************************************************************************/
void HeapPop(heap_t *heap)
{
	/*
	 * 1. Swap between top data and last inserted data
	 * 2. PopBack from dv
	 * 3. HeapifyDown
	*/
	size_t last_of_heap = HeapSize(heap) - 1;
	
	assert(heap);
	
	if (!HeapIsEmpty(heap))
	{
		if (HeapSize(heap) > 1)
		{
			SwapFamilyMember(DVItemAddress(heap->dv, TOP_OF_HEAP),
							 DVItemAddress(heap->dv, last_of_heap));
		}
		
		DVPopBack(heap->dv);
		HeapifyDown(heap, TOP_OF_HEAP);
	}
}

/******************************************************************************/
void HeapRemove(heap_t *heap,int (*is_match)(const void *data, const void *arg),
																const void *arg)
{
	/*
	 * 1. Find if arg is exist at the heap
	 * 2. If he is, Swap between him and last inserted data
	 * 3. PopBack from dv
	 * 4. HeapifyUp
 	 * 5. HeapifyDown
	*/
	
	ssize_t index       = -1;
	size_t last_of_heap = HeapSize(heap) - 1;
	swap_t swaping_flag = NOT_SWAPPED;
	
	assert(heap);
	assert(is_match);
	assert(arg);
	
	index = FindIndex(heap, is_match, arg);

	if (index >= 0)
	{
		if (HeapSize(heap) > 1 && (size_t)index != last_of_heap)
		{
			SwapFamilyMember(DVItemAddress(heap->dv, index),
							 DVItemAddress(heap->dv, last_of_heap));
			swaping_flag = SWAPPED;
		}
		
		DVPopBack(heap->dv);
		
		if (SWAPPED == swaping_flag)
		{
			HeapifyUp(heap, index);
			HeapifyDown(heap, index);
		}
	}
}
		
/*********															***********/
/* A function that finds if 'arg' exists and returns his index */
static ssize_t FindIndex(heap_t *heap,
			int (*is_match)(const void *data, const void *arg), const void *arg)
{
	ssize_t index     = -1;
	status_t status	  = NOT_FOUND;
	size_t i	      = 0;
	
	if (NULL != heap->dv && (!HeapIsEmpty(heap)))
	{
		for (; i < HeapSize(heap) && NOT_FOUND == status; ++i)
		{
			status = is_match(*(void**)DVItemAddress(heap->dv, i), arg);
		}
		
		if (FOUND == status)
		{
			index = i - 1;
		}
	}
	
	return (index);
}
	
/******************************************************************************/
void HeapPrint(const heap_t *heap)
{
	assert(heap);
	
	printf("\n");	
	DVPrint(heap->dv, &PrintFunc);
	printf("\n");

}
	
/*********															***********/
static void PrintFunc(void *element)
{
	assert(element);
	
	printf("%d ", **(int**)element);
}	
	
	


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
