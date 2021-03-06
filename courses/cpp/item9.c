/*****************************************************************************
 * File name:   item9.c
 * Developer:   Yaron Meister
 * Date:        2019-02-13 10:02:35
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */


/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
void foo(int t, int i = 3, float = 4);
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	foo(3);
	foo(6, 5);
	foo(4, 7, 8.7);
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void foo(int t, int i, float f)
{
	printf("%d\n", t);
	printf("%d\n", i);
	printf("%f\n", f);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
