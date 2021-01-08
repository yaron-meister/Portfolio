/*****************************************************************************
 * File name:   search.h
 * Developer:   HRD7
 * version: 	1
 * Date:        2018-01-10 16:20
 * Description: Searching algorithms Header
 *****************************************************************************/
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stddef.h>      /* size_t */

/*
 * Binary search algorithm
 * Complexity: time - O(log(n))
 * Returns :
 * 		 Data if found,
 *		 NULL if not found.
 * <cmp_func> is provided by user:
 * returns: 
 * 		 > 0 if left > right,
 *		   0 if left == right,
 * 		 < 0 if left < right. 
 */
void *BinarySearchIter(const void *base, size_t nmemb, size_t element_size,
        int (*cmp_func)(const void *left, const void *right), const void *data);

void *BinarySearchRec(const void *base, size_t nmemb, size_t element_size,
        int (*cmp_func)(const void *left, const void *right), const void *data);

/*
 * Jump search algorithm
 * Complexity: time - O(n^0.5)
 * Returns :
 * 		 Data if found,
 *		 NULL if not found.
 * <cmp_func> is provided by user:
 * returns: 
 * 		 > 0 if left > right,
 *		   0 if left == right,
 * 		 < 0 if left < right. 
 */
void *JumpSearch(const void *base, size_t nmemb, size_t element_size,
        int (*cmp_func)(const void *left, const void *right), const void *data);
         
         
#endif     /* __SEARCH_H__ */
