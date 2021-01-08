/*****************************************************************************
 * File name:   heap.h
 * Developer:   HRD7
 * Version:		1
 * Date:        2018-01-06 14:56:01
 * Description: HEAP header file including API
 *****************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>      /* size_t */


typedef struct heap heap_t;

/*
 * <is_before> is provided by the user and will return 1 if <element1>
 * is before <element2>, else 0
 * Returns NULL if <is_before> is NULL or on Create failure
 * <is_before> return 1 when parent and 0 for child.
 * <param> is possible to be NULL
 * Complexity = O(1)
 */
heap_t *HeapCreate(size_t capacity,
                   int(*is_before)(const void *element1,
                     const void *element2, void *param),void *param);


/*
 * Desrtroy function does not free user data
 * Complexity = O(1)
 */
void HeapDestroy(heap_t *heap);

/*
 * Return number of elements in Heap
 * Complexity = O(1)
 */
size_t HeapSize(const heap_t *heap);

/*
 * Return boolean value is empty
 * Complexity = O(1)
 */
int HeapIsEmpty(const heap_t *heap);

/*
 * Return pointer to the element on top of the Heap
 * return NULL when Heap is empty
 * Complexity = O(1)
 */
void *HeapPeek(const heap_t *heap);

/*
 * Return 0 for success and otherwise for failure
 * User <is_before> function should handle with <data>
 * Complexity = O(log(n))
 */
int HeapPush(heap_t *heap, void *data);

/*  args mandatory and holds the matching criteria
 * Function Removes element with the data from Heap
 * Function does not free user data
 * Complexity = O(n)
 */
void HeapRemove(heap_t *heap,int (*is_match)(const void *data, const void *arg),
															   const void *arg);


/*
 * remove the element that on top of the Heap
 * Complexity = O(logn)
 */
void HeapPop(heap_t *heap);







void HeapPrint(const heap_t *heap);





#endif     /* __HEAP_H__ */



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
