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
#define BYTE 1

/* Forward Declarations    */
int DVItemAddress_test(void);
int DVPushBack_test(void);
int DVPopBack_test1(void);
int DVPopBack_test2(void);
int DVSize_test(void);  
int DVCapacity_test(void);
int DVReserve_test(void);
void DVPrint_test(void);
void UserPrint(void *element);         

/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{
                        /* count is the number of tests that succeeded */
    int count = 2;      /* create and destroy approaved by valgrind    */
    int tests = 9;
    count += DVItemAddress_test();
    count += DVPushBack_test();
    count += DVPopBack_test1();
    count += DVPopBack_test2();
    count += DVSize_test();
    count += DVCapacity_test();
    count += DVReserve_test(); 
    printf("%d tests succeeded and %d faild\n", count, tests - count); 
    DVPrint_test();   
    
    return (EXIT_SUCCESS);
}




/******************************************************************************/
int DVItemAddress_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 3;
    size_t element_size = 1;
    const char a = 5;
    const char b = 3;
    const char c = 7;
    void *item_adress;
    int status = 0;         /* A flag variable for checking */                  

    dv = DVCreate(init_capacity, element_size);
    DVPushBack(dv, &a);
    DVPushBack(dv, &b);
    DVPushBack(dv, &c);
    
    item_adress = DVItemAddress(dv, 0);
    
    if (NULL == item_adress)                /* Should work */
    {
        ++status;
    }
     
    item_adress = DVItemAddress(dv, 2); 
    
    if (NULL == item_adress)                 /* Should work */
    {
        ++status;
    }
    
    item_adress = DVItemAddress(dv, -1);
    
    if (NULL != item_adress)                 /* Shouldn't work */
    {
        ++status;
    }
    
    item_adress = DVItemAddress(dv, 3); 
    
    if (NULL != item_adress)                /* Shouldn't work */
    {
        ++status;
    }

    DVDestroy(dv);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}
    
/******************************************************************************/    
int DVPushBack_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 1;
    size_t element_size = 4;
    const int a = 5;
    const int b = 3;
    const int c = 7; 
    int status = 0;  
        
    dv = DVCreate(init_capacity, element_size);
    DVPushBack(dv, &a);
    
    if (1 != DVCapacity(dv))
    {
        ++status;
    }
    
    if (1 != DVSize(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &b);
    
    if (2 != DVCapacity(dv))
    {
        ++status;
    }
    
    if (2 != DVSize(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &c);
    
    if (4 != DVCapacity(dv))
    {
        ++status;
    }
   
    /* A check for logical offset accoarding to type */
    if (((char*)DVItemAddress(dv, 0) + (8 * BYTE)) !=
                                                 ((char*)DVItemAddress(dv, 2)))
    {
        ++status;
    }


    DVDestroy(dv);    
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}
    
/******************************************************************************/    
int DVPopBack_test1(void)       /* Test for boundries */
{
    dv_t *dv = NULL;
    size_t init_capacity = 1;
    size_t element_size = 4;
    const int a = 5;
    const int b = 3;    
    int status = 0;
    int pop_status = 0;  
        
    dv = DVCreate(init_capacity, element_size);
    
    DVPushBack(dv, &a);
    DVPushBack(dv, &b);
    
    pop_status = DVPopBack(dv);
    
    if (1 != DVSize(dv) || 0 != pop_status)
    {
        ++status;
    }
    
    pop_status = DVPopBack(dv);
    
    if (0 != DVSize(dv) || 0 != pop_status)
    {
        ++status;
    }
    
    pop_status = DVPopBack(dv);
    
    if (0 != DVSize(dv) || 1 != pop_status)
    {
        ++status;
    }
    
    DVDestroy(dv);
        
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}

/******************************************************************************/    
int DVPopBack_test2(void)       /* Test for (capacity/4) size */
{
    dv_t *dv = NULL;
    size_t init_capacity = 20;
    size_t element_size = 1;
    const int a = 5;
    const int b = 3;    
    int status = 0;
              
    dv = DVCreate(init_capacity, element_size);
    
    DVPushBack(dv, &a);                         
    DVPushBack(dv, &b);
    DVPushBack(dv, &a);                         
    DVPushBack(dv, &b);

    DVPopBack(dv);
    
    if (10 != DVCapacity(dv))
    {
        ++status;
    }
        
    DVDestroy(dv);
        
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}  
    
/******************************************************************************/    
int DVSize_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 1;
    size_t element_size = sizeof(long);
    const long a = 5;
    const long b = 3;
    const long c = 7; 
    int status = 0;  
        
    dv = DVCreate(init_capacity, element_size);
    
    if (0 != DVSize(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &a);
    
    if (1 != DVSize(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &b);
    
    if (2 != DVSize(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &c);
    
    if (3 != DVSize(dv))
    {
        ++status;
    }                  
        
    DVDestroy(dv);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}

/******************************************************************************/
int DVCapacity_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 1;
    size_t element_size = sizeof(long);
    const long a = 5;
    const long b = 3;
    const long c = 7;
    const long d = 9; 
    int status = 0;  
        
    dv = DVCreate(init_capacity, element_size);

    DVPushBack(dv, &a);
    
    if (1 != DVCapacity(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &b);
    
    if (2 != DVCapacity(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &c);
    
    if (4 != DVCapacity(dv))
    {
        ++status;
    }
    
    DVPushBack(dv, &d);
    
    if (4 != DVCapacity(dv))
    {
        ++status;
    }

    DVReserve(dv, 100);
    
    if (100 != DVCapacity(dv))
    {
        ++status;
    }
    
    DVDestroy(dv);
        
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}

/******************************************************************************/
int DVReserve_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 5;
    size_t element_size = sizeof(float);    
    int status = 0;
        
    dv = DVCreate(init_capacity, element_size);     
    DVReserve(dv, 100);             /* Making dv bigger */
    
    if (100 != DVCapacity(dv))  
    {
        ++status;
    }
    
    DVReserve(dv, 50);              /* Making dv smaller */
    
    if (50 != DVCapacity(dv))
    {
        ++status;
    }
    
    DVReserve(dv, 70);              /* Making dv bigger again */
    
    if (70 != DVCapacity(dv))
    {
        ++status;
    }
      
    DVDestroy(dv);
        
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}

/******************************************************************************/
void DVPrint_test(void)
{
    dv_t *dv = NULL;
    size_t init_capacity = 2;
    size_t element_size = 4;
    const int a = 5;
    const int b = 3;
    void (*print_func1)(void *element);
    print_func1 = UserPrint;
 
    dv = DVCreate(init_capacity, element_size);
    
    printf("\n/*********************/\n");
    printf("/******Print test*****/\n");
    printf("/*********************/\n\n");
    
    DVPrint(dv, NULL);                      /* Checking for empty vector */
    DVPrint(dv, print_func1);
    
    DVPushBack(dv, &a);
    DVPushBack(dv, &b);
    
    DVPrint(dv, NULL);                     /* Checking for non-empty vector */
    DVPrint(dv, print_func1);
    
    printf("\n");
    DVDestroy(dv);
}

/******************************************************************************/
void UserPrint(void *element)
{
    printf("%d ",*(int *)element);
}    
    
    
    
    
    
    
    
    
    
    
    
   
