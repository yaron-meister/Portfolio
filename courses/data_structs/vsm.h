/*****************************************************************************
 * File name:   vsm.h
 * Developer:   Yaron Meister
 * Reviewer:    Nir
 * Date:        2018-12-05 16:08:35
 * Version:     1
 * Description: - This product is a Variable Size Memory allocation managing 
 *                unit.
 *              - It gets a block of memory from the user and NOT responsible 
 *                of a lack of space or a gap between the request of the user
 *                and the actual size of memory.
 *              - It allocates blocks of data in complexity of O(n) and frees
 *                in O(1) .
 *              - It's making sure that an allocated block will be aligned with
 *                a machine-word.
 *              - It's making sure that more than one proccess will be able to
 *                use it simultaneously. 
 *****************************************************************************/

#ifndef  __VSM_H__
#define __VSM_H__

#include <stddef.h>         /* size_t */

typedef struct vsm vsm_t;

/*
 * Initialize VSM to manage a memory segment of <length> bytes starting at
 * <segment>
 */
vsm_t *VSMInit(void *segment, size_t length);

/*
 * Returns word-aligned pointer to an allocated block of <length> bytes
 * Returns NULL if there's no space to allocate a segment of given length (this
 * may be due to fragmentation, so smaller sizes may still fit)
 */
void *VSMAlloc(vsm_t *segment, size_t length);

/*
 * Free a <block> that was previously allocated by VSMAlloc
 */
void VSMFree(void *block);

/*
 * Returns the total free memory in <segment> managed by VSM
 *
 * [Impl note: Uri's way means that this func has to merge adjancent empty
 * chunks]
 */
size_t VSMCountFree(vsm_t *segment);

/*
 * Returns the maximal block size that can be allocated in the <segment>
 * managed by VSM without freeing previously allocated chunks
 *
 * [Impl note: Uri's way means that this func has to merge adjancent empty
 * chunks]
 */
size_t VSMLargestBlock(vsm_t *segment);

#endif /* __VSM_H__ */


