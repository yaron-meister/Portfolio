/*****************************************************************************
 * File name:   dv.h
 * Developer:   Yaron Meister
 * Reviewer:    Rachel Sagiv
 * Date:        2018-11-11 17:31:14
 * Description: 
 *****************************************************************************/

#ifndef __DV_H__
#define __DV_H__

#include <stddef.h>      /* size_t     */
#include <sys/types.h>   /* ssize_t    */ 

typedef struct dynamic_vector dv_t;

/*
 * Capacity is the total number of cells.
 * NULL is returned upon allocation failure.
 */
dv_t *DVCreate(size_t capacity, size_t element_size);

void DVDestroy(dv_t *dv);

/**************************************************************************
 * Note: once calling PushBack(), PopBack() and Reserve() functions, the  *  
 *       pointer returned by ItemAddress() will not be valid anymore.     *
 **************************************************************************/
void *DVItemAddress(dv_t *dv, size_t index);

/* 
 * 0 <= success - current index
 * (-1) failure 
 */
ssize_t DVPushBack(dv_t *dv, const void *element);

/*
 * (0) success 
 * (1) empty dv
 */
int DVPopBack(dv_t *dv);

/* number of current elements */
size_t DVSize(const dv_t *dv);

/* number of current maximum capacity */
size_t DVCapacity(const dv_t *dv);

/* 
 *  (0) success
 *  (1) failure: If realloc fails, dv will stay the same as before
 */
int DVReserve(dv_t *dv, size_t new_capacity);

/*
 * User supplies print function per element, or NULL function pointer.
 * If print_func passed by the caller is NULL, data is printed in hex format.
 */
void DVPrint(dv_t *dv, void (*print_func)(void *element));
 
#endif     /* __DV_H__ */


