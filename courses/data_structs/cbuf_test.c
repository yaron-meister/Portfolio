/*****************************************************************************
 * File name:   cbuf_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Daria Shilo
 * Date:        2018-11-13 14:50:48
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "cbuf.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
int CBWrite_test(void);
int CBRead_test(void);
int CBSizeWrite_test(void);
int CBSizeRead_test(void);
int CBCapacity_test(void);
int CBIsEmpty_test(void);
 
/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{
                        /* count is the number of tests that succeeded */
    int count = 2;      /* create and destroy approaved by valgrind    */
    int tests = 8; 
    count += CBWrite_test();
    count += CBRead_test();    
    count += CBSizeWrite_test();       
    count += CBSizeRead_test();       
    count += CBCapacity_test();
    count += CBIsEmpty_test();              
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d faild\n", count, tests - count); 
    printf("\n");
    
    
    return (EXIT_SUCCESS);
}

/******************************************************************************/      
int CBWrite_test(void)
{
    size_t capacity = 5;
    cbuf_t *cbuf = CBCreate(capacity);
    const char arr1[] = "Hello";        /* arr1 is writing to cbuf->write */
    const char arr2[] = "Beautiful";    /* arr2 is writing to cbuf->write */
    const char arr3[] = "World";        /* arr3 is writing to cbuf->write */
    char dest[20] = {0};
    ssize_t written = 0;                /* A counting variable */
    int status = 0;                     /* A flag variable for checking */ 

    printf("\n\n****************** WRITE-TEST ***************************\n\n");
    
    written = CBWrite(cbuf, arr1, 3);
    CBPrint(cbuf);
    
    if (3 != written)
    {
        ++status;
    }
    
    written = CBWrite(cbuf, arr2, 3);
    perror("ERROR");
    printf("\n");
    CBPrint(cbuf);
    
    if (2 != written)
    {
        ++status;
    }
    
    CBRead(cbuf, dest, 4);
    
    written = CBWrite(cbuf, arr3, 4);
    CBPrint(cbuf);
    
    if (4 != written)
    {
        ++status;
    }

    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}

/******************************************************************************/
int CBRead_test(void)
{
    size_t capacity = 5;
    cbuf_t *cbuf = CBCreate(capacity);
    const char arr1[] = "Yaron";        /* arr1 is writing to cbuf->write */
    char dest[] = "Meister-Meister";    /* CBRead is writing to dest */
    ssize_t read_already = 0;           /* A counting variable */
    int status = 0;                     /* A flag variable for checking */ 
    
    printf("\n\n****************** READ-TEST ****************************\n\n");
        
    read_already = CBRead(cbuf, dest, 4);
    perror("ERROR");
    
    if (0 != read_already)
    {
        ++status;
    }
    
    CBWrite(cbuf, arr1, 3);
    CBPrint(cbuf);
    
    read_already = CBRead(cbuf, dest, 2);
    
    if (2 != read_already)
    {
        ++status;
    }
    
    printf("%s\n", dest);
    
    read_already = CBRead(cbuf, dest, 2);
    perror("ERROR");
    
    if (1 != read_already)
    {
        ++status;
    }
    
    printf("%s\n", dest);
       
    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}


/******************************************************************************/
int CBSizeWrite_test(void)
{
    size_t capacity = 5;
    cbuf_t *cbuf = CBCreate(capacity);
    const char arr1[] = "Yaron";        /* arr1 is writing to cbuf->write */
    ssize_t size_to_write = 0;
    int status = 0;                     /* A flag variable for checking */ 
            
    size_to_write = CBSizeWrite(cbuf);
    
    if (5 != size_to_write)
    {
        ++status;
    }
    
    CBWrite(cbuf, arr1, 3);
    size_to_write = CBSizeWrite(cbuf);
    
    if (2 != size_to_write)
    {
        ++status;
    }
    
    CBWrite(cbuf, arr1, 3);
    size_to_write = CBSizeWrite(cbuf);
    
    if (0 != size_to_write)
    {
        ++status;
    }
       
    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}
    
/******************************************************************************/
int CBSizeRead_test(void)
{
    size_t capacity = 5;
    cbuf_t *cbuf = CBCreate(capacity);
    const char arr1[] = "Yaron";        /* arr1 is writing to cbuf->write */   
    char dest[] = "Meister-Meister";    /* CBRead is writing to dest */
    ssize_t size_to_read = 0;
    int status = 0;                     /* A flag variable for checking */ 
            
    size_to_read = CBSizeRead(cbuf);

    if (0 != size_to_read)
    {
        ++status;
    }
    
    CBWrite(cbuf, arr1, 3);
    size_to_read = CBSizeRead(cbuf);

    if (3 != size_to_read)
    {
        ++status;
    }
    
    CBWrite(cbuf, arr1, 3);
    size_to_read = CBSizeRead(cbuf);

    if (5 != size_to_read)
    {
        ++status;
    }
    
    CBRead(cbuf, dest, 5);
    size_to_read = CBSizeRead(cbuf);

    if (0 != size_to_read)
    {
        ++status;
    }
       
    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}    

/******************************************************************************/    
int CBCapacity_test(void)
{
    size_t init_capacity = 5;
    cbuf_t *cbuf = CBCreate(init_capacity);
    size_t current_capacity = 0;  
    int status = 0;                          /* A flag variable for checking */   
    current_capacity = CBCapacity(cbuf);
    
    
    if (5 != current_capacity)
    {
        ++status;
    }
    
    CBDestroy(cbuf);
    
    init_capacity = 20;
    cbuf = CBCreate(init_capacity);   
    current_capacity = CBCapacity(cbuf);
    
    if (20 != current_capacity)
    {
        ++status;
    } 

    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}    

/******************************************************************************/    
int CBIsEmpty_test(void)  
{
    size_t capacity = 5;
    cbuf_t *cbuf = CBCreate(capacity);
    const char arr1[] = "Yaron";
    char dest[] = "Meister-Meister";        /* CBRead is writing to dest */
    int status = 0;                         /* A flag variable for checking */ 
    
    if (!CBIsEmpty(cbuf))
    {
        ++status;
    } 
      
    CBWrite(cbuf, arr1, 3);
    
    if (CBIsEmpty(cbuf))
    {
        ++status;
    } 
    
    CBRead(cbuf, dest, 2);
    
    if (CBIsEmpty(cbuf))
    {
        ++status;
    } 
    
    CBRead(cbuf, dest, 1);
    
    if (!CBIsEmpty(cbuf))
    {
        ++status;
    } 
    
    CBDestroy(cbuf);
    
    if (0 == status)
    {
        return (1);
    }
    
    return (0);    
}    
    
    
    
    
    
    
    
    
    
    
