/*****************************************************************************
 * File name:   knights_tour_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Shiran
 * Date:        2019-01-13 14:25:40
 * Test Flow: 	One case and array cell's check
 *****************************************************************************/
 
#include <stdio.h>     			/*        printf 	    */
#include <stdlib.h>    			/*     EXIT_SUCCESS 	*/
#include <time.h>	   		    /*	     clock	        */

#include "knights_tour.h"       /* Forward declarations */


/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{   
    unsigned int out_solution_array[64] = {0};
	int test_array[64] 					= {0};
	int i								= 0;
	int flag							= 0;
	clock_t time   						= 0;
	
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
    time = clock();
    KnightsTour(2, 0, out_solution_array);
	time = clock() - time;    
    
	for (; i < 64; ++i)
	{
		test_array[(out_solution_array[i])] = 1;
	}
	
	for (i = 0; i < 64 && 1 != flag ; ++i)
	{
		if (1 != test_array[i])
		{
			flag = 1;
		}
	}
	
	if (0 != flag)
    {
    	printf("*************************************************************");
  		printf("\n"); 
        printf("                   Test \033[1;31mFAILED\033[0m\n");
        printf("*************************************************************");
  		printf("\n"); 
        printf("\n");       
    }
    else
    {
    	printf("*************************************************************");
  		printf("\n"); 
        printf("                   Test \033[1;32mSUCCEEDED\033[0m\n");
        printf("*************************************************************");
  		printf("\n");
  		printf("Solution found in %f seconds\n", ((double)time)/CLOCKS_PER_SEC); 
        printf("\n");
    }
    
    return (EXIT_SUCCESS);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/

