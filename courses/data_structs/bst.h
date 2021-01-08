/*****************************************************************************
 * File name:   bst.h
 * Developer:   HRD7
 * Version:		5 
 * Date:        2018-12-18 14:56:01
 * Description: BST header file including API
 *****************************************************************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>      /* size_t */


typedef struct bst bst_t;
typedef struct bst_node* iter_t;


/*
 * <is_before> is provided by the user and will return !0 if <element1> 
 	is before <element2>, else 0  
 * Returns NULL if <is_before> is NULL or on Create failure
 * <param> is possible to be NULL
 * Complexity = O(1)
 */
bst_t *BSTCreate(int(*is_before)(void *element1, void *element2, void *param),
																   void *param);

/*
 * Desrtroy function does not free user data
 * Complexity = O(nlog(n))
 */
void BSTDestroy(bst_t *bst);

/*
 * Return number of elements in BST  
 * Complexity = O(nlog(n))
 */
size_t BSTCount(const bst_t *bst);

/*
 * Return boolean value is empty   
 * Complexity = O(1)
 */
int BSTIsEmpty(const bst_t *bst);

/*
 * Return an iterator to the smallest element in BST
 * Return END if BST is empty  
 * Complexity = O(log(n))
 */
iter_t BSTBegin(const bst_t *bst);

/*
 * Return an iterator to the last (dummy) element in BST  
 * Complexity = O(1)
 */
iter_t BSTEnd(const bst_t *bst);

/*
 * Return an iterator to the previous element in BST
 * Prev on Begin will result in undefined behaviour  
 * Complexity = O(log(n))
 */
iter_t BSTPrev(iter_t iter);

/*
 * Return an iterator to the next element in BST
 * Next on End will result in undefined behaviour  
 * Complexity = O(log(n))
 */
iter_t BSTNext(iter_t iter);

/*
 * Return data to the element in BST
 * GetData on End will result in undefined behaviour 
 * Complexity = O(1)
 */
void *BSTGetData(iter_t iter);

/*
 * Return an iterator to the inserted element in BST or NULL on failure
 * User <is_before> function should handle with <data>
 * Complexity = O(log(n))
 */
iter_t BSTInsert(bst_t *bst, void *data);

/*
 * Function Removes iter from BST
 * Removing END results undefined beavior
 * Function does not free user data
 * Complexity = O(log(n))
 */
void BSTRemove(iter_t iter);

/*
 * ForEach function applying <action_func> on element between <from> (including)
 	 to <to> (excluding).
 * Function return value -> status of <action_func> - 0 - success, !0 - failure  
 * Function will stop running if <action_func> returns failure
 * 
 * Undefined behaviour if <action_func> is NULL
 * <param> is optional and may be NULL
 * <from> must be smaller than <to> and belong to the same BST, undefined
 	 behaviour else 
 * <failed_iter> is a pointer for the iter that made <action_func> fail
 	and is optional (may be NULL)
 * Changing the sorting key results undefined behavior
 * Complexity = O(nlog(n))
 */
int BSTForEach(iter_t from, iter_t to,
									 int(*action_func)(void *data, void *param),
					       		       		  void *param, iter_t *failed_iter);

/*
 * Find function checks if <bst> includes <data>
 * Returns an iterator to the one fits <data> and END if doesn't find 
 * if <data> == NULL, the function returns END (dummy)
 * Complexity = O(log(n))
 */
iter_t BSTFind(const bst_t *bst, void *data);

/*
 * Return boolean value is-same-iterator   
 * Complexity = O(1)
 */
int BSTIsSameIter(iter_t iter1, iter_t iter2);



#endif     /* __BST_H__ */
 

