/*****************************************************************************
 * File name:   item7.c
 * Developer:   Yaron Meister
 * Date:        2019-02-13 08:46:58
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */


/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
 	float *f1 = new float[15];
 	f1[0] = 4; f1[1] = 5;  

 	for (int i = 0; i < 15; ++i)
 	{
 		printf("%f\n", f1[i]);	
 	}
 	
 	delete[] f1;

 	/*int *ptr = (int*)malloc(1000 * sizeof(int));
 	
 	delete (ptr);

 	int *ptr2 = new int[1000];
 	free(ptr2);*/

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
