/*****************************************************************************
 * File name:   plug_and_play_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daria
 * Date:        2019-04-22 11:33:22
 * Test Flow:   Tests cases
 *****************************************************************************/
 
#include <iostream>             // cout, cerr
#include <cstdlib>              // EXIT_SUCCESS
#include <unistd.h>             // sleep
#include <chrono>               // std::chrono

#include "plug_and_play.h"      // Forward declarations 
#include "factory.h"            // Factory::CreateShared
#include "handleton.h"          // Handleton::GetInstance
#include "base.h"               // class Base



using namespace ilrd;
/********************************* Macros *************************************/ 
 
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);


/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approved by valgrind     */

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
    
	static DirMonitor dir_monitor("/home/shiran/git/yaron-meister/projects/monitor");
    static DllLoader dll_loader(dir_monitor.GetPublisher());
    
    Factory<Base,std::string,int>* factory =
                        Handleton<Factory<Base,std::string,int>>::GetInstance();

    
    std::this_thread::sleep_for (std::chrono::seconds(5));

    std::shared_ptr<Base> task = factory->CreateShared("Task1", 15);
    EqualityTest<int>(task->GetNum(), 15, 1);

	printf("\n************** SUMARY OF UNIT-TEST **************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
