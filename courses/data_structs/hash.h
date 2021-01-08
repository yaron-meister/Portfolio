/*******************************************************************************
 * File name:   hash.h
 * Developer:   HRD-7
 * Version:     2
 * Date:        2019-01-02 16:46:28
 * Description: Declaretion of all functions provided by Hash table
 ******************************************************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>      /* size_t */

typedef struct hash hash_t;

/*
 * Create Function return a pointer to an Hash table NULL in case of memory
 * allocation failure.
 * <cmp_func> is provided by the user and returns a positive number if <left>
 * is bigger than <right>, 0 for equality and negative number if right bigger
 * than left.
 * <hash_func> returns the appropriate <bucket> for <data>
 * <param> is optional and may be NULL.
 * <buckets_num> is the total number of <bucket>.
 * Complexity = O(1)
 */
hash_t *HashCreate(size_t buckets_num, void *param,
                           size_t (*hash_func)(const void *data, void *param),
                           int(*cmp_func)(const void *left, const void *right));
/* 
 * Destroy the Hash table.
 * Destroy function does not free user data.
 * Complexity = O(n)
 */
void HashDestroy(hash_t *hash);

/*      
 * Return number of elements in the HASH.  
 * Complexity = O(n)
 */
size_t HashSize(const hash_t *hash);

/*
 * Return boolean value if HASH is empty or not.  
 * Complexity = O(1)
 */
int HashIsEmpty(const hash_t *hash);

/*
 * Insert element to the HASH.
 * Returns 0 on success, (-1) on failure.
 * <hash_func> and <cmp_func> should be able to handle with <data>
 * Complexity = O(1)
 */
int HashInsert(hash_t *hash, void *data);

/*
 * Function Removes node with the same data from HASH.
 * Function does not free user data.
 * Complexity = O(1)
 */
void HashRemove(hash_t *hash, void *data);

/*       
 * ForEach function applying <action_func> on the HASH.
 * Function return value -> status of <action_func> - 0 - success, (-1)- failure  
 * Function will stop running if <action_func> returns failure
 * 
 * if <action_func> is NULL, segmentation fault.
 * <act_param> is optional and may be NULL.
 * Complexity = O(n)
 */
int HashForEach(hash_t *hash, int(*action_func)(void *data, void *act_param)
	                                                   ,void *act_param);

/*
 * Find function checks if <hash> includes <data>
 * Returns pointer to the data if found, NULL else.
 * if <data> == NULL, return NULL.
 * Complexity = O(1)
 */
void *HashFind(const hash_t *hash, void *data);

#endif     /* __HASH_H__ */


