/*****************************************************************************
 * File name:   sortlist.h
 * Developer:   Yaron Meister
 * Reviewer:    Eran    
 * Date:        2018-11-22 08:43:32
 * Description: 
 *****************************************************************************/

#ifndef __SORLTIST_H__
#define __SORLTIST_H__

#include <stddef.h>      /* size_t */

typedef struct sorted_list sortlist_t;
typedef void* sortlist_iter_t;

/*
 * User is responsible for managing the lifetime of the data stored in the list
 * User provides a comparison function, is_before, that checks whether its first
 * argument should go before the second argument in the sorted list
 *
 * BadIter is an iterator that does not point after the end of the list [End()]
 * but IsBadIter(iter) on it is true
 */

/*
 * Create an empty Sorted List
 * Returns NULL on malloc() failure
 * 
 * is_before is a boolean function, thus returns either truthy or zero
 * If is_before is NULL, list creation fails
 * param is volunatry, may be NULL
 *
 * Complexity: O(1)
 */
sortlist_t *SortListCreate(int (*is_before)(const void *left, const void *right,
        const void *param), const void *param);

/*
 * Destroy a list
 * Doesn't free user data
 * Complexity: O(n)
 */
void SortListDestroy(sortlist_t *list);

/*
 * Count list elements
 * Complexity: O(n)
 */
size_t SortListSize(const sortlist_t *list);

/*
 * Whether the list is empty
 * Returns truthy if the list is empty
 * Complexity: O(1)
 */
int SortListIsEmpty(const sortlist_t *iter);

/*
 * End() returns an iterator pointing to a pseudo-element after the last real one
 * Complexity: O(1)
 */
sortlist_iter_t SortListEnd(sortlist_t *list);

/*
 * Returns an iterator to the first element
 * If the list is empty, returns End()
 * Complexity: O(1)
 */
sortlist_iter_t SortListBegin(sortlist_t *list);

/*
 * Returns an iterator pointing to the element after the given one
 * Returns End() if the given element is the last one
 *
 * Calling on End() is undefined
 * Complexity: O(1)
 */
sortlist_iter_t SortListNext(sortlist_iter_t iter);

/*
 * Returns an iterator pointing to the element before the given one
 *
 * Calling on Begin() is undefined
 * Complexity: O(1)
 */
sortlist_iter_t SortListPrev(sortlist_iter_t iter);
 
/*
 * Check whether the two iterators are equal (point to the same element
 * within the same list)
 * Calling on BadIter is well-defined (must be able to handle)
 * 
 * Complexity: O(1)
 */
int SortListIsSameIter(sortlist_iter_t iter1, sortlist_iter_t iter2);

/*
 * Check whether the iterator is BadIter or points to the pseudo-element after
 * the end of the list [End()]
 * Returns boolean: iter is BadIter or iter is End()
 */
int SortListIsBadIter(sortlist_iter_t iter);

/*
 * Get the user data from the list element pointed to by the iterator
 * 
 * Calling on End() returns NULL
 * Calling on BadIter is undefined
 * Complexity: O(1)
 */
void *SortListGetData(sortlist_iter_t iter);

/*
 * Insert a new element containing data into the list
 * The list remains sorted
 * May fail (allocation failure), in such case returns BadIter
 * 
 * Returns an iterator pointing to the newly inserted element
 * Complexity: O(n)
 */
sortlist_iter_t SortListInsert(sortlist_t *list, void *data);

/*
 * Remove an element from the list
 * Calling on End() is undefined
 * Calling on BadIter is undefined
 * 
 * Returns iterator to following iter from the erased
 * Stores data contained in the removed element inside 'data'
 * Complexity: O(1)
 */
sortlist_iter_t SortListErase(sortlist_iter_t iter, void **data);

/*
 * Remove an element from the beginning (end) of the list
 * Calling on empty list returns NULL
 * 
 * Returns data contained in the removed element
 * Complexity: O(1)
 */
void *SortListPopFront(sortlist_t *list);
void *SortListPopBack(sortlist_t *list);

/*
 * Traverse the range [from; to) calling action_func on each element or until
 * the action_func returns failure
 * <param> is passed to action_func unchanged on each call
 * The <to> element is excluded from range
 * Calling on from = to results in returning <to>
 * Calling on action_func = NULL is undefined
 * Calling on <from> pointing to a list different from the one <to> points to
 * results in undefined behavior
 * Calling on <from> pointing to the element after <to> is undefined
 *
 * action_func returns status, i.e. 0 is success/continue, non-zero is failure
 *
 * Returns the iterator <to> when every call to action_func succeeded or returns
 * an iterator to the element that caused action_func to fail
 * Complexity: O(n)
 */
sortlist_iter_t SortListForEach(sortlist_iter_t from, sortlist_iter_t to,
    int (*action_func)(void *data, void *param), void *param);

/*
 * Traverse the range [from; to) and run compare_func for each element until it
 * returns equality
 * <param> is passed to compare_func unchanged on each call
 * The <to> element is excluded from range
 * Calling on from = to results in returning <to>
 * Calling on compare_func = NULL is undefined
 * Calling on <from> pointing to a list different from the one <to> points to
 * results in undefined behavior
 * Calling on <from> pointing to the element after <to> is undefined
 *
 * compare_func returns comparison result, i.e. 0 means equality, non-zero means
 * inequaility
 *
 * Returns the iterator <to> when none of the elements matched or an iterator
 * to the first element that matched
 * Complexity: O(n)
 */
sortlist_iter_t SortListFind(sortlist_iter_t from, sortlist_iter_t to,
    int (*compare_func)(const void *data, const void *param), const void *param);

/*
 * Move all the elements of <source> to <dest> keeping the sorted order
 * <source> is left empty (not destroyed)
 * <dest>'s is_before is expected to be able to handle <source>'s elements
 * Calling on empty <source> is well-defined
 * Complexity: O(n + m)
 */
void SortListMerge(sortlist_t *dest, sortlist_t *source);

#endif     /* __SORLTIST_H__ */

