/*****************************************************************************
 * File name:   cbuf_test.c
 * Developer:   xyz
 * Reviewer: 
 * Date:        2018-11-13 14:50:48
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "cbuf.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
void Test(void);

/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{
    Test();
 
    return (EXIT_SUCCESS);
}

/******************************************************************************/      
void Test(void)
{
    const char str[] = "Hello";
    size_t capacity = 10;
    ssize_t written = 0;
    char dest[] = "world";
    cbuf_t *cbuf = CBCreate(capacity);
    
    printf("The capacity of the buffer is %lu bytes\n", CBCapacity(cbuf));
    
    if (CBIsEmpty(cbuf))
    {
        printf("Buffer is empty...\n");
    }
    else
    {
        printf("Buffer is NOT empty...\n"); 
    }
    
    written = CBWrite(cbuf, str, 15);
    printf("%lu bytes were written\n", written);
    CBRead(cbuf, dest, 4);
    CBPrint(cbuf);
    
    CBDestroy(cbuf);
}    
    














