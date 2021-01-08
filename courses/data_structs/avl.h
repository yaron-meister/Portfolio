/*****************************************************************************
 * File name:   avl.h
 * Developer:   HRD07
 * Version: 	2
 * Date:        2018-12-27 15:55:28
 * Description: A header file including API
 *****************************************************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>      /* size_t */

typedef struct avl avl_t;

/*
 * <cmp_func> is provided by the user.
 * return positive number if <left> is bigger than <right>,
 *  0 for equal, and negative number if right bigger than left.  
 * Complexity = O(1)
 */
avl_t *AVLCreate(int(*cmp_func)(const void *left, const void *right));

/* 
 * Destroy the AVL.
 * Destroy function does not free user data.
 * Complexity = O(n)
 */
void AVLDestroy(avl_t *avl);

/*      
 * Return number of elements in the AVL.  
 * Complexity = O(n)
 */
size_t AVLSize(const avl_t *avl);

/*
 * Return boolean value if AVL is empty or not.  
 * Complexity = O(1)
 */
int AVLIsEmpty(const avl_t *avl);

/*
 * Insert element to the AVL.
 * 0 on success (-1) on failure.
 * Complexity = O(log(n))
 */
int AVLInsert(avl_t *avl, void *data);

/*
 * return the height of the AVL.
 * return 0 for empty AVL.
 * Complexity = O(log(n))
 */
size_t AVLHeight(avl_t *avl);

/*
 * Function Removes node with the same data from AVL.
 * Function does not free user data.
 * Complexity = O(log(n))
 */
void AVLRemove(avl_t *avl, void *data);

/*       
 * ForEach function applying <action_func> on the AVL.
 * Function return value -> status of <action_func> - 0 - success, -1 - failure  
 * Function will stop running if <action_func> returns failure
 * 
 * if <action_func> is NULL, segmentation fault.
 * <param> is optional and may be NULL.
 * Changing the sorting key results undefined behavior.
 * Complexity = O(n)
 */
int AVLForEach(avl_t *avl, int(*action_func)(void *data, void *param)
	                                                   ,void *param);
/*
 * Find function checks if <avl> includes <data>
 * Returns pointer to the data if found, NULL else.
 * if <data> == NULL, return NULL.
 * Complexity = O(log(n))
 */
void *AVLFind(const avl_t *avl, void *data);




void AVLPrint(const avl_t *avl);



#endif     /* __AVL_H__ */


