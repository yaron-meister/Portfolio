/*****************************************************************************
 * File name:   cbuf.c
 * Developer:   Yaron Meister
 * Reviewer:    Daria Shilo
 * Date:        2018-11-13 14:50:48
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* malloc       */
#include <stddef.h>    /* offset       */
#include <assert.h>    /* assert       */
#include <errno.h>     /* errno        */
#include <string.h>    /* memcpy       */

#include "cbuf.h"       /*              */


/* Macros                  */
 
 
/* Forward Declarations    */
struct circular_buffer 
        {   
            void *read;
            void *write;
            size_t capacity;
            char data[8];
        }; 
 
/* Global variables        */
 
 
/******************************************************************************/      
cbuf_t *CBCreate(size_t capacity)
{
    if (capacity > 0)
    {
        cbuf_t *cbuf = (cbuf_t*)malloc(offsetof(cbuf_t, data) + capacity + 1);
        
        if (NULL == cbuf)               /* Malloc check */
        {
            fprintf(stderr, "Malloc faild!!!");
            return (NULL);
        }
        
        cbuf->read = cbuf->data;
        cbuf->write = cbuf->data;
        cbuf->capacity = capacity;
               
        return (cbuf);
    }
    
    return (NULL);
}

/******************************************************************************/
void CBDestroy(cbuf_t *cbuf)
{
    free(cbuf);
    cbuf = NULL;
}

/******************************************************************************/
ssize_t CBWrite(cbuf_t *cbuf, const void *src, size_t count)
{
    ssize_t written = 0;                /* counting variable */
    const void *runner = src;
    
    assert(cbuf);
    assert(src);
    
    if (count > CBSizeWrite(cbuf))      /* if overflows */
    {
        errno = EOVERFLOW;
        count = CBSizeWrite(cbuf);
    }
    
    while (written < (ssize_t)count)
    {
        *(char*)cbuf->write = *(char*)runner;
        ++written;
        runner = (char*)runner + 1;
        
       /* Checking if cbuf->write is at the end of the buffer */
        if (cbuf->write == ((char*)cbuf->data + cbuf->capacity))
        {
            cbuf->write = cbuf->data;
        }
        else
        {
            cbuf->write = (char*)cbuf->write + 1;
        }
    }
    
    return (written);
}    

/******************************************************************************/
ssize_t CBRead(cbuf_t *cbuf, void *dest, size_t count)
{
    ssize_t read_already = 0;           /* counting variable */               
    void *runner = dest;
    
    assert(cbuf);
    assert(dest);
    
    if (count > CBSizeRead(cbuf))       /* if empty */
    {
        errno = ENODATA;
        count = CBSizeRead(cbuf);
    }
    
    while (read_already < (ssize_t)count)
    {
        *(char*)runner = *(char*)cbuf->read;
        ++read_already;
        runner = (char*)runner + 1;

       /* Checking if cbuf->read is at the end of the buffer */        
        if (cbuf->read == ((char*)cbuf->data + cbuf->capacity))
        {
            cbuf->read = cbuf->data;
        }
        else
        {
            cbuf->read = (char*)cbuf->read + 1;
        }
    }
    
    return (read_already);
}    

/******************************************************************************/    
size_t CBSizeWrite(const cbuf_t *cbuf)
{
    assert(cbuf);
    
    return (cbuf->capacity - CBSizeRead(cbuf));
}   
    
/******************************************************************************/
size_t CBSizeRead(const cbuf_t *cbuf)
{
    size_t ret = 0;
    
    assert(cbuf);
    
    if (cbuf->read <= cbuf->write)
    {
        ret = ((char*)cbuf->write - (char*)cbuf->read);
    }
    else            /* if write crossed the start again */
    {
        ret = cbuf->capacity - ((char*)cbuf->read - (char*)cbuf->write - 1);
    }
    
    return (ret);
}
        
/******************************************************************************/
size_t CBCapacity(const cbuf_t *cbuf)
{
    assert(cbuf);
    
    return (cbuf->capacity);
}    
    
/******************************************************************************/
int CBIsEmpty(const cbuf_t *cbuf)
{
    assert(cbuf);
   
    return (0 == CBSizeRead(cbuf));     
}

/******************************************************************************/
void CBPrint(cbuf_t *cbuf)
{
    int count = 100;
    int i = 0;
    void *runner = NULL;
    
    assert(cbuf);
    
    runner = cbuf->read;    
    printf("The available cells to read are:\n\n");
    
    while (i < count && runner != cbuf->write)
    {
        printf("%c ",*((char*)runner));
        ++i;
        
        if (runner == ((char*)cbuf->data + cbuf->capacity))
        {
            runner = cbuf->data;
        }
        else
        {
            runner = (char*)runner + 1;
        } 
    }
    
    printf("\n\n");
}
    




       
