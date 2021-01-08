/*****************************************************************************
 * File name:   handleton_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-04 13:29:14
 * Test Flow: 
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
 
#include "handleton.h"         /* Forward declarations */

using namespace ilrd;
/************************** Forward declarations ******************************/
struct yaron
{
    int num;
};

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{   
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
	  yaron* handle1 = Handleton<yaron>::GetInstance();
    yaron* handle2 = Handleton<yaron>::GetInstance();
    yaron* handle3 = Handleton<yaron>::GetInstance();


    (*handle1).num = 5;
    printf("Before assignment of handle2:\n");
    printf("handle1: %p ---> %d\n\n", (void*)&handle1->num, *(int*)&handle1->num);
    printf("handle3: %p ---> %d\n\n", (void*)&handle3->num, *(int*)&handle3->num);

    (*handle2).num = 6;
    printf("After assignment of handle2:\n");
    printf("handle1: %p ---> %d\n", (void*)&handle1->num, *(int*)&handle1->num);
    printf("handle2: %p ---> %d\n", (void*)&handle2->num, *(int*)&handle2->num);
    printf("handle3: %p ---> %d\n\n", (void*)&handle3->num, *(int*)&handle3->num);


	printf("\n************** SUMMARY OF UNIT-TEST *************************\n");
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/







/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
