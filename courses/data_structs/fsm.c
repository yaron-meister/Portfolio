/*****************************************************************************
 * File name:   fsm.c
 * Developer:   Yaron Meister
 * Reviewer:    Sandra
 * Date:        2018-12-04 14:44:05
 *
 *****************************************************************************/

#include <assert.h>    /*       assert         */

#include "utils.h"     /*     WORD_SIZE        */ 
#include "fsm.h"       /* Forward declarations */

 
/****************************Forward Declarations******************************/
/* A function that swaps variables */
static void Swap(size_t *x, size_t *y);

/* head is offset(bytes), terminator = 0 */ 
struct fsm
{
	size_t blocks;
	size_t block_size;
	size_t head;	
}; 

/* next is offset(bytes), terminator = 0 */ 
typedef struct fsm_element
{
	size_t next;
} fsm_element_t;
 
/*************************Functions's Definitions******************************/

size_t FsmSuggestSize(size_t num_of_blocks, size_t block_size)
{
    if (0 != (block_size % WORD_SIZE))
    {
        block_size += (WORD_SIZE - (block_size % WORD_SIZE));                           /* במקום התנאי, אפשר להוסיף 7 ולאפס 3 ביטים תחתונים */
    }
    
    return (num_of_blocks * (block_size + sizeof(fsm_element_t))
                                                 + sizeof(fsm_t));    
}

/******************************************************************************/
fsm_t *FsmInit(void *segment, size_t num_of_blocks, size_t block_size)
{
    fsm_t *fsm = segment;
    fsm_element_t *element = NULL;
    /* 'total_size' = total requested size + alignment + metadatas */
    size_t total_size = FsmSuggestSize(num_of_blocks, block_size);
    /* 'total_element_size' = total aligned block size + block's metadata */
    size_t total_element_size = (total_size - sizeof(fsm_t)) / num_of_blocks;
    
    assert(segment);
    
    fsm->blocks = num_of_blocks;
    fsm->block_size = block_size;
    fsm->head = sizeof(fsm_t);
    /* 'element' is the start of the first block after metadata of fsm */
    element = (fsm_element_t *)((char*)segment + fsm->head);
   
    /* Proggresing until the start of the last block */
    while ((char*)element < ((char*)segment + total_size - total_element_size))
    {
        /* Writing the 'next' value inside the metadata of the block */
        element->next = (size_t)((char*)element - (char*)segment)
                                                + total_element_size;
        element = (fsm_element_t *)((char*)element + total_element_size); 
    } 
    
    element->next = 0;
    
    return (segment);
}

/******************************************************************************/
void *FsmAlloc(fsm_t *segment)
{
    void *ret = NULL;
    
    if (0 != FsmCountFree(segment))
    {
  /* Swaping between the values of 'segment->head' and 'segment->head->next' */
        ret = (char*)segment + segment->head + sizeof(fsm_element_t);
        Swap(&segment->head, (size_t*)((char*)segment + segment->head));
    }
    
    return (ret);
}

/******************************************************************************/
void FsmFree(void *block)
{
    if (NULL != block)
    {
/* Swaping between the values of 'segment->head' and 'block's metadata->next' */
        Swap((size_t*)((char*)block - sizeof(fsm_element_t)),
             (size_t*)((char*)block - sizeof(fsm_element_t) - 
             *(size_t*)((char*)block - sizeof(fsm_element_t)) + 2 * WORD_SIZE));                                                                    
    }
}                               
                                    
/******************************************************************************/
size_t FsmCountFree(const fsm_t *segment)
{
    size_t count = 0;
    size_t next = 0;
    
    assert(segment);

    next = segment->head;
    
    while (0 != next)
    {
        ++count;
        next = ((fsm_element_t *)((char*)segment + next))->next;
    }
    
    return (count);
}

/******************************************************************************/
static void Swap(size_t *x, size_t *y)
{
    size_t temp = 0;
    
    assert(x);
    assert(y);
    
    temp = *x;
    *x = *y;
    *y = temp;
}

  
