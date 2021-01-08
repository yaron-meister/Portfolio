/*****************************************************************************
 * File name:   dlist.h
 * Developer:   Yaron
 * Reviewer: 
 * Date:        2018-11-20 11:04:53
 * Description: 
 *****************************************************************************/

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>      /* size_t */ 

struct dlist_node;
typedef struct dlist dlist_t;
typedef struct dlist_node* dlist_iter_t; 

/* 
 * Create empty list
 * Return NULL if malloc failed
 */
dlist_t *DListCreate(void); 									

void DListDestroy(dlist_t *dlist);								

/* Complexity O(n) */
size_t DListCount(const dlist_t *dlist);					

/*
 * Return value: 0 - not empty, !0 - empty
 * Complexity O(1)
 */
int DListIsEmpty(const dlist_t *dlist);

/* When dlist is empty - returns End, complexity O(1) */
dlist_iter_t DListBegin(const dlist_t *dlist);

/* Returns iterator to (stub) element after the last one, complexity O(1) */
dlist_iter_t DListEnd(const dlist_t *dlist);

/* Undefined behavior when iter = End, complexity O(1) */
dlist_iter_t DListNext(dlist_iter_t iter);

/* Undefined behavior when iter = Begin, complexity O(1) */
dlist_iter_t DListPrev(dlist_iter_t iter);

/* Return NULL when iter = End, complexity O(1) */
void *DListGetData(const dlist_iter_t iter);

/*
 * Return value: truthy - same, 0 - else
 * Complexity O(1)
 */
int DListIsSameIter(dlist_iter_t iter1, dlist_iter_t iter2);

/*
 * Return value: truthy - iter = End, 0 - else
 * check iter validality(not assert) -> not for user
 * Complexity O(1)
 */
int DListIsBadIter(dlist_iter_t iter);

/*
 * Insert data before where
 * Return value: iter inserted = success, NULL = failure
 * Complexity O(1) 
 */
dlist_iter_t DListInsert(dlist_iter_t where, void *data);

/* Returns iterator to following iter from the erased
 * Data will be point to the data of the erased - if isn't NULL
 * Complexity O(1)              
 */
dlist_iter_t DListErase(dlist_iter_t where, void **data);

/*
 * Push data before Begin
 * return value: 0 = success, !0 = failure
 * Complexity O(1) 
 */
int DListPushFront(dlist_t *dlist, void *data);

/*
 * Push data before End
 * Return value: 0 = success, !0 = failure
 * Complexity O(1) 
 */
int DListPushBack(dlist_t *dlist, void *data);

/*
 * Pop the Begin and return data 
 * Return NULL if dlist is empty
 * Complexity O(1)  
 */
void *DListPopFront(dlist_t *dlist);

/*
 * Pop the element before End and return data 
 * Return NULL if dlist is empty
 * Complexity O(1) 
 */
void *DListPopBack(dlist_t *dlist);

/*
 * Elements between begin (including) to end (excluding) are cut-paste
 * src list remain valid
 * Complexity O(1)
 */
void DListSpliceBefore(dlist_iter_t dest, 
                       dlist_iter_t src_begin, dlist_iter_t src_end);
                       
/* Return iterator to the one which made the action_func fail
 * Return 'to' if havn't fail ('to' isn't included)
 */
dlist_iter_t DListForEach(dlist_iter_t from, dlist_iter_t to,
				 int (*action_func)(void *data, void *param),
			  	 void *param);
			  	 
/* Return iterator to the one who found,
 * Return 'to' if havn't found ('to' isn't included)
 */
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
                int (*compare_func)(const void *data, const void *param), 
                                                      const void *param);

#endif     /* __DLIST_H__ */

