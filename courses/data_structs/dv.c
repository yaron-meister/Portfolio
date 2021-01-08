/*****************************************************************************
 * File name:   dv.c
 * Developer:   Yaron Meister
 * Reviewer:    Rachel Sagiv
 * Date:        2018-11-11 23:51:00
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert       */
#include <string.h>    /* memcpy       */

#include "dv.h"       /*              */


/* Macros                  */
 
 
/* Forward Declarations    */

struct dynamic_vector
{
    size_t element_size;
    void *array;                    /* pointer to first index */
    size_t capacity;
    size_t num_of_elements;
};
 
/* Global variables        */
 
/******************************************************************************/
dv_t *DVCreate(size_t capacity, size_t element_size)
{
    
    
    /* managing unit - 3 * size_t + 1 pointer = 32 */
    dv_t *manager = (dv_t*)malloc(sizeof(dv_t));
    if (0 == capacity * element_size)
    {
        return (NULL);
    }
    
    if (NULL == manager)
    {
        fprintf(stderr, "Malloc faild!!!");
        return (NULL);
    }  
            
    manager -> element_size = element_size;
    manager -> capacity = capacity;
    manager -> num_of_elements = 0;
    manager -> array = malloc(capacity * element_size);
    if (NULL == (manager -> array))
    {
        free(manager);
        fprintf(stderr, "Malloc faild!!!");
        return (NULL);
    }

    return (manager);
}

/******************************************************************************/
void DVDestroy(dv_t *dv)
{
    assert (dv);
    
    free (dv->array);
    dv->array = NULL;
    free (dv);
    dv = NULL;
}

/******************************************************************************/
void *DVItemAddress(dv_t *dv, size_t index)
{
    assert (dv);
    
    if (index < dv->num_of_elements)
    {
        return ((char*)dv->array + dv->element_size * index);
    }
    
    return (NULL);
}    
  
/******************************************************************************/   
ssize_t DVPushBack(dv_t *dv, const void *element)
{
    void *temp = NULL;
    
    assert (dv);
    
    if (dv->num_of_elements == dv->capacity)
    {
        temp = realloc(dv->array, 2 * dv->capacity
                                                     * dv->element_size);                                           /* מומלץ למחזר את רזרב במקום עוד פעם הקצאה */

/* 
 * temp is for the case that realloc fails. 
 * if it does, dv is the same as before the realloc try...
 */        
        if (NULL == temp)       
        {
           return (-1); 
        }
        
        dv->array = temp;
        dv->capacity *= 2;    
    }
    
    memcpy((char*)dv->array + dv->num_of_elements *
                           dv->element_size, element, dv->element_size);
    ++(dv->num_of_elements);
    
                                             
    return (dv->num_of_elements - 1);
}
    
/******************************************************************************/ 
 
int DVPopBack(dv_t *dv)
{        
    void *temp = NULL;
    
    assert (dv);
    
    if ((dv->num_of_elements) > 0)   /* if there are elements at the vector */                          
    {
    
        if ((dv->num_of_elements - 1) < ((dv->capacity) / 4))    
        {
            temp = realloc(dv->array, (dv->capacity) / 2);                                              /* מומלץ למחזר את רזרב במקום עוד פעם הקצאה */
            
            if (NULL == temp)
            {
                return (1); 
            }
            
            dv->array = temp;
            dv->capacity /= 2;
        }
        
        --(dv->num_of_elements);
        
        return (0);
    }
    
    return (1);
}
  
          
    
/******************************************************************************/    
size_t DVSize(const dv_t *dv)
{
    assert(dv);
    
    return (dv->num_of_elements);
}       
    
/******************************************************************************/    
size_t DVCapacity(const dv_t *dv)
{
    assert(dv);     
    
    return (dv->capacity);
}
    
/******************************************************************************/    
int DVReserve(dv_t *dv, size_t new_capacity)
{
    void *temp = NULL;
    
    assert(dv);
    
    if (dv->num_of_elements < new_capacity) /* secure data */
    {
        temp = realloc(dv->array, dv->element_size * new_capacity);
        
        if (NULL == temp)
        {
            return (1);
        }
        
        dv->array = temp;
        dv->capacity = new_capacity;
        
        return (0);
    }
    
    return (1);
} 
    
/******************************************************************************/    
void DVPrint(dv_t *dv, void (*print_func)(void *element))
{
    size_t i = 0;
    printf("The VECTOR is: ");
    
    if (NULL == print_func)
    {
        for (; i < dv->num_of_elements; ++i)
        {
            printf("0x%x ", *((char*)dv->array +
                                                 (i * dv->element_size)));
        }
    }
    else
    {
        for (; i < dv->num_of_elements; ++i)
        {
            print_func((char*)dv->array + (i * dv->element_size));
        }
    }
    printf("\n");
}       
    
    
    
    
    
    
  
