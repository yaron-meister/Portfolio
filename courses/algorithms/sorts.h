/*****************************************************************************
 * File name:   sorts.h
 * Developer:   Yaron Meister
 * Reviewer: 	
 * Date:        2018-12-14 00:38:01
 * Description: SORTING ALGORITHMS
 *****************************************************************************/
#include <stddef.h>         /* size_t */

#ifndef __SORTS_H__
#define __SORTS_H__



/******************************************************************************/
int *BubbleSort(int *base, size_t size);
 
/******************************************************************************/
int *InsertionSort(int *base, size_t size);

/******************************************************************************/
int *SelectionSort(int *base, size_t size);

/******************************************************************************/
int CountingSort(int *base, size_t size, size_t range);

/******************************************************************************/
int RadixSort(unsigned int *base, size_t size);

/******************************************************************************/
/*
 * Merge sort algorthim O(nlog(n)) - time complexity
 * O(n) - space complexity
 * <cmp_func> is provided by the user.
 * return positive number if <left> is bigger than <right>,
 *  0 for equal, and negative number if right bigger than left. 
 */

int MergeSort(void *base, size_t num_of_elements, size_t element_size,
	int(*cmp_func)(const void *left, const void *right));

/******************************************************************************/
/*
 * Heap sort algorithm
 * Complexity: time - O(nlogn) (worst, avg), space - O(1) auxillary
 * <is_before> returns boolean whether its first argument is before the second
 *      in the sorted array
 *
 * Returns status:
 * 0 - success,
 * 1 - failure - memory allocation failure
 */
int HeapSort(void *base, size_t nmemb, size_t element_sz,
        int (*is_before)(const void *left, const void *right, void *param),
        void *param);


/*
 * Quick sort algorithm
 * Complexity: time - O(nlogn) (avg) O(n^2) in the worst case,
 * 				space - O(1) - in place.
 * Returns status:
 * 0 - success,
 * 1 - failure - memory allocation failure
 * <cmp_func> is provided by user:
 * returns: 
 * 		 > 0 if left > right,
 *		   0 if left == right,
 * 		 < 0 if left < right. 
 */
int QuickSort(void *base, size_t nmemb, size_t element_sz,
                  int (*cmp_func)(const void *left, const void *right));



#endif     /* __SORTS_H__ */










/*******************************************************************************
***************************** END OF FILE **************************************
*******************************************************************************/
