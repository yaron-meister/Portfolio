/*****************************************************************************
 * File name:   cbuf.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-13
 * Description: 
 *****************************************************************************/

#ifndef __CBUF_H__
#define __CBUF_H__

#include <unistd.h>      /* ssize_t, size_t */ 

typedef struct circular_buffer cbuf_t;

/*
 * Capacity is the total number of bytes.
 * NULL is returned upon allocation failure & if capacity == 0.
 */
cbuf_t *CBCreate(size_t capacity);

void CBDestroy(cbuf_t *cbuf);

/* 
 * success - num of written bytes;
 * if overflows : + sets errno to EOVERFLOW;
 */
ssize_t CBWrite(cbuf_t *cbuf, const void *src, size_t count);

/* 
 * success - num of read bytes;
 * if empty : + sets errno to ENODATA;
 */
ssize_t CBRead(cbuf_t *cbuf, void *dest, size_t count);



/* number of bytes available to write */
size_t CBSizeWrite(const cbuf_t *cbuf);

/* number of bytes available to read */
size_t CBSizeRead(const cbuf_t *cbuf);

/* maximum capacity */
size_t CBCapacity(const cbuf_t *cbuf);

/*
 * bool - 
 * !0 = is empty
 * 0 = not empty
 */
int CBIsEmpty(const cbuf_t *cbuf);

void CBPrint(cbuf_t *cbuf);

 
#endif     /* __CBUF_H__ */


  
