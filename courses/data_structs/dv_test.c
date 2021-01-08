/*****************************************************************************
 * File name:   dv_unit_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Rachel Sagiv
 * Date:        2018-11-11 23:51:00
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "dv.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
void DVCreateAndDestroy_test(void);
void UserPrint(void *element);

/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{
    DVCreateAndDestroy_test();
  
    return (EXIT_SUCCESS);
}




/******************************************************************************/
void DVCreateAndDestroy_test(void)
{
    dv_t *dv = NULL;
    void *item_adress = NULL;
    size_t init_capacity = 2;
    size_t element_size = 4;
    const int a = 5;
    const int b = 3;
    const int c = 7;
    ssize_t status1 = 0;
    int status2 = 0;
    size_t num_of_elements = 0;
    size_t capacity = 0;
    void (*print_func1)(void *element);
    print_func1 = UserPrint;
    
    dv = DVCreate(init_capacity, element_size);
    
 /*   item_adress = DVItemAddress(dv, 3);   
    
    if (NULL == item_adress)
    {
        return;
    }
    
    printf("The item's adress is: %p\n", item_adress);
*/
    status1 = DVPushBack(dv, &a);
    printf("The index is: %lu\n", status1);
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
    capacity = DVCapacity(dv);
    printf("The capacity is: %lu\n", capacity);
    
    status1 = DVPushBack(dv, &b);
    printf("The index is: %lu\n", status1);
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
    capacity = DVCapacity(dv);
    printf("The capacity is: %lu\n", capacity);
    
    status1 = DVPushBack(dv, &c);
    printf("The index is: %lu\n", status1);
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
    capacity = DVCapacity(dv);
    printf("The capacity is: %lu\n", capacity); 
    
    DVPrint(dv, print_func1);
    printf("\n");
    DVPrint(dv, NULL);
    printf("\n");
    
    DVReserve(dv, 100);
    capacity = DVCapacity(dv);
    printf("The capacity is: %lu\n", capacity);
    
    DVReserve(dv, 12);
    capacity = DVCapacity(dv);
    printf("The capacity is: %lu\n", capacity);
    status2 = DVPopBack(dv);
    if (!status2)
    {
        printf("Pop succeeded\n");
    }
    else
    {
        printf("Pop failed!!!");
    }
    
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
  status2 = DVPopBack(dv);
    if (!status2)
    {
        printf("Pop succeeded\n");
    }
    else
    {
        printf("Pop failed!!!");
    }
    status2 = DVPopBack(dv);
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
    if (!status2)
    {
        printf("Pop succeeded\n");
    }
    else
    {
        printf("Pop failed!!!");
    }
    num_of_elements = DVSize(dv);
    printf("Right now, the number of elements is: %lu\n", num_of_elements);
    
    DVDestroy(dv);    
}

/******************************************************************************/
void UserPrint(void *element)
{
    printf("%d ",*(int *)element);
}
    

    






 
