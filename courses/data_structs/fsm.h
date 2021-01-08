/*****************************************************************************
 * File name:   fsm.h
 * Developer:   Yaron Meister
 * Reviewer:    Sandra
 * Date:        2018-12-04 14:44:05
 *
 * Description: - This product is a Fixed Size Memory allocation managing unit.
 *              - It gets a block of memory from the user and NOT responsible 
 *                of a lack of space or a gap between the request of the user
 *                and the actual size of memory.
 *              - It allocates and frees blocks of data in complexity of o(1).
 *              - It's making sure that an allocated block will be aligned with
 *                a machine-word.
 *              - It's making sure that more than one proccess will be able to
 *                use it simultaneously. 
 *****************************************************************************/

#ifndef __FSM_H__
#define __FSM_H__

#include <stddef.h>      /* size_t */

typedef struct fsm fsm_t;
			
/*
 * Calc memory size of bytes for # of blocks of size 'block_size' that are 
 * aligned, with an addition of the metadata 
 */
size_t FsmSuggestSize(size_t blocks, size_t block_size);

/*
 * initialize the memory segment structure, complexity = O(n)
 * if blocks==0 or block_size==0 ---> undefined behavior
 */
fsm_t *FsmInit(void *segment, size_t blocks, size_t block_size);

/* alloc 1 block from the segment, complexity = O(1)
 * return NULL when there is no available block 
 */
void *FsmAlloc(fsm_t *segment);

/* Free adds another block, complexity = O(1) */							
void FsmFree(void *block);

/* Count free blocks. complexity = O(n) */
size_t FsmCountFree(const fsm_t *segment);


#endif     /* __FSM_H__ */

