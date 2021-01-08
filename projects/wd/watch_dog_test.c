/*****************************************************************************
 * File name:   watch_dog_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2019-02-07 13:04:07
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>      /* 	  	  printf  		*/
#include <stdlib.h>   	/*     EXIT_SUCCESS		*/
#include <unistd.h>		/*		  sleep			*/

#include "watch_dog.h"  /* Forward declarations */


/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(int argc, char *argv[], char *env[])
{   
	int ret_pid = 0;
	int counter = 0;

	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
	ret_pid = WDKeepMeAlive(argc, argv, env, 5);

	while (counter < 60)
	{
		sleep(1);
		++counter;
	}

	WDLetMeDie(ret_pid);
    
    return (EXIT_SUCCESS);
}






/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    

