/*****************************************************************************
 * File name:   tree_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daniel 
 * Date:        2019-03-17 15:44:24
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /*     cout, cerr    	*/
#include <cstdlib>      /*    EXIT_SUCCESS   	*/

#include "tree.h"       /* Forward declarations */


using namespace ilrd;
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
    
  	std::shared_ptr<Entry> entry;
  	std::shared_ptr<Entry> find;

    entry = Directory::Create("ws1");

    entry->Display();

    std::cout << "\n\n";
    //(entry->Find("fol1"))->Display();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
