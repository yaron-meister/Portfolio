/*****************************************************************************
 * File name:   slist.h
 * Developer:   Yaron Meister
 * Reviewer:    Majd
 * Date:        2018-11-15
 * Description: 
 *****************************************************************************/

#ifndef __SLIST_H__
#define __SLIST_H__

#include <unistd.h>      /* ssize_t, size_t */ 

typedef struct sl_node 
{
    void *data;
    struct sl_node *next;
} sl_node_t;

/*   User responsibility for data safety   */
sl_node_t *SLCreateNode(sl_node_t *next, void *data);

void SLFreeNode(sl_node_t *node);
void SLFreeAll(sl_node_t *head);

/* 
 * Return a pointer to the inserted node
 */
sl_node_t *SLInsertAfter(sl_node_t *where, sl_node_t *new_node);
sl_node_t *SLInsertBefore(sl_node_t *where, sl_node_t *new_node);

/* 
 * Return a pointer to the removed node or NULL if 'node' is the last one
 * NOTE: There is no option to remove the last 'node'
 */
sl_node_t *SLRemoveAfter(sl_node_t *node);
sl_node_t *SLRemove(sl_node_t *node);

/*  Counts all nodes  */
size_t SLCount(const sl_node_t *head);

/*  Stops if user function fails.
*   Returns status of *action_func (0 if succeeded, !0 if failed).
*   If failed_node provided by user is not NULL:
*   *failed_node gets NULL if "SUCCESS" and a pointer to failed node if "FAILURE"
*   
*/
int SLForEach(sl_node_t *head, 
              int (*action_func)(void *data, void *param), void *param, 
              sl_node_t **failed_node);

/*  Returns a pointer to a node with matched data or NULL if not found.  */
sl_node_t *SLFind(sl_node_t *head, 
                int (*compare_func)(const void *data, const void *param), 
                                                      const void *param);

/*  Flips a list.
*   Returns pointer to head of the new list.
*/
sl_node_t *SLFlip(sl_node_t *head);

/*  
*  Returns 0 if there is no loop and 1 if there is a loop.     
*/
int SLHasLoop(const sl_node_t *head);

/*  Returns a pointer to intersection is found,
*   Returns NULL if intersection is not found.
*/
sl_node_t *SLFindIntersection(const sl_node_t *head1, const sl_node_t *head2);
 
#endif     /* __SLIST_H__ */


