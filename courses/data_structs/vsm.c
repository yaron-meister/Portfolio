/*****************************************************************************
 * File name:   vsm.c
 * Developer:   Yaron Meister
 * Reviewer:    Nir
 * Date:        2018-12-05 16:08:35
 *****************************************************************************/

#include <unistd.h>    /*    ssize_t     */ 
#include <assert.h>    /*    assert      */

#include "utils.h"     /*     DBG()      */
#include "vsm.h"       /*     vsm.c      */


/******************************** Macros **************************************/
#ifndef NDEBUG

#ifdef __i386__
#define MAGIC_VALUE 0x80808080u

#elif __x86_64__
#define MAGIC_VALUE 0x8080808080808080lu

#else
#error I am sorry

#endif /* Platform */

#endif /* NDEBUG */ 
 
/************************* Forward Declarations *******************************/
struct vsm
{
    size_t total_length;
};

typedef struct block_header
{
    ssize_t block_sz;
#ifndef NDEBUG
    size_t magic_field;
#endif
} block_header_t; 

/* A function that merge's free spaces */
static void Merge(vsm_t *segment, block_header_t *header);

/* A function to return the ABSOLUTE number of <size> */ 
static ssize_t Abs(ssize_t size); 
  
/*********************** Functions's definitions ******************************/
 
vsm_t *VSMInit(void *segment, size_t length)
{
    vsm_t *vsm = /* (vsm_t *) */ segment;
    block_header_t *metadata = (block_header_t *)
                               ((char*)segment + sizeof(vsm_t));
    
    assert(segment);
    
    vsm->total_length = length;
    metadata->block_sz = length - sizeof(vsm_t) - sizeof(block_header_t);
    DBG(metadata->magic_field = 0);
        
    return (vsm);
}

/******************************************************************************/
void *VSMAlloc(vsm_t *segment, size_t length)
{
    block_header_t *metadata = (block_header_t *)
                               ((char*)segment + sizeof(vsm_t));
                                   
    assert(segment);

    /* Alignment check */    
    if (0 != (length % WORD_SIZE))
    {
        length += (WORD_SIZE - (length % WORD_SIZE));
    }
    
    /* If we are still running inside the pool */
    while(metadata < (block_header_t *)((char*)segment + segment->total_length))
    {
        /* Progressing until the first place that isn't allocated */ 
        while (metadata->block_sz < 0 && 
          metadata < (block_header_t *)((char*)segment + segment->total_length))
        {
            metadata = (block_header_t *)
                ((char*)metadata - metadata->block_sz + sizeof(block_header_t));
        }
        
        if (metadata < 
                     (block_header_t *)((char*)segment + segment->total_length))
        {
            Merge(segment, metadata);
            
   /* If there is enough room, even wthout the structures of the next block */
            if ((size_t)metadata->block_sz >= length)
            {
                if ((size_t)metadata->block_sz >= 
                                                length + sizeof(block_header_t))
                {
                    ((block_header_t *)((char*)metadata + length + 
                                            sizeof(block_header_t)))->block_sz = 
                           metadata->block_sz - sizeof(block_header_t) - length;
                }
                   
                metadata->block_sz = length * (-1);
                DBG(metadata->magic_field = MAGIC_VALUE);
                
                /* Returning the pointer for the data itself */
                return ((void*)((char*)metadata + sizeof(block_header_t)));
            }
              
            metadata = (block_header_t *)
                ((char*)metadata + metadata->block_sz + sizeof(block_header_t));   
        }
    }

    return (NULL);
}

/******************************************************************************/
static void Merge(vsm_t *segment, block_header_t *header)
{
    block_header_t *runner = (block_header_t *)((char*)header + 
                                     header->block_sz + sizeof(block_header_t));
    ssize_t sum = 0;
    
    /* While we are running over free blocks */
    while (runner < (block_header_t *)((char*)segment + segment->total_length) 
                                                        && runner->block_sz > 0)
    {
        sum += runner->block_sz + sizeof(block_header_t);
        runner = (block_header_t *)((char*)runner + runner->block_sz + 
                                                        sizeof(block_header_t));
    }
    
    header->block_sz += sum;
}

/******************************************************************************/
void VSMFree(void *block)
{
    assert(block);
    
#ifndef NDEBUG    
    if (MAGIC_VALUE != ((block_header_t *)((char*)block - 
                                          sizeof(block_header_t)))->magic_field)    
    {
        return;
    }  
    
   ((block_header_t *)((char*)block - sizeof(block_header_t)))->magic_field = 0;
#endif

    ((block_header_t *)((char*)block - sizeof(block_header_t)))->block_sz 
                                                                        *= (-1);
}

/******************************************************************************/
size_t VSMCountFree(vsm_t *segment)
{
    size_t count = 0;
    block_header_t *runner = (block_header_t *)((char*)segment + sizeof(vsm_t));
    
    assert(segment);

    while (runner < (block_header_t *)((char*)segment + segment->total_length))
    {
        if (runner->block_sz > 0)
        {
            Merge(segment, runner);
            count += (size_t)runner->block_sz;
        }
        
        /* 'runner' = next block */
        runner = (block_header_t *)((char*)runner + Abs(runner->block_sz) + 
                                                        sizeof(block_header_t));
    }
    
    return (count);
}
    
/******************************************************************************/
static ssize_t Abs(ssize_t size)
{
    return ((size < 0) ? (size * (-1)) : size);
}

/******************************************************************************/
size_t VSMLargestBlock(vsm_t *segment)
{
    block_header_t *runner = (block_header_t *)((char*)segment + sizeof(vsm_t));
    size_t largest = 0;
    
    assert(segment);

    while (runner < (block_header_t *)((char*)segment + segment->total_length))
    {
        if (runner->block_sz > 0)
        {
            Merge(segment, runner);
            
            if (largest < (size_t)runner->block_sz)
            {
                largest = (size_t)runner->block_sz;
            }
        }
        
        /* 'runner' = next block */
        runner = (block_header_t *)((char*)runner + Abs(runner->block_sz) + 
                                                        sizeof(block_header_t));
    }
    
    return (largest);
}
    






 
