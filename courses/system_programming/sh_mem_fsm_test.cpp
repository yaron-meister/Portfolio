/*****************************************************************************
 * File name:   sh_mem_fsm_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Yael
 * Date:        2019-03-24 15:43:56
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <unistd.h>		/*	   	  fork			*/
#include <sys/types.h>	/*		 waitpid		*/
#include <sys/wait.h>	/*		 waitpid		*/

#include "sh_mem_fsm.h" /* Forward declarations */

using namespace ilrd;
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);
void FsmCreate_test(void);
void FsmAllocAndFree_test(void);
void FsmAttach_test(void);

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

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
    
	FsmCreate_test();
	FsmAllocAndFree_test();
	//FsmAttach_test();

	printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
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

/******************************************************************************/
/******************************************************************************/
void FsmCreate_test(void)
{
   	std::shared_ptr<FSM> fsm = FSM::Create("Yaron", 5, 28); 

    printf("\n****************** Create - TEST ****************************\n");  
    
    void* segment1 = fsm->Alloc();
    EqualityTest<size_t>(*(size_t*)((char*)segment1 + 32), 136, 1);
    void* segment2 = fsm->Alloc();
    EqualityTest<size_t>(*(size_t*)((char*)segment2 + 32), 176, 2);
    fsm->Free(segment1);
    fsm->Free(segment2);
}

/******************************************************************************/
void FsmAllocAndFree_test(void)
{
   	std::shared_ptr<FSM> fsm = FSM::Create("Yaron", 5, 28);
   	void* segment[7] = {nullptr}; 
   	size_t i = 0;

    printf("\n*************** Alloc & Free - TEST *************************\n");  
    
    while (nullptr != (segment[i] = fsm->Alloc()))
    {
    	++i;
    }
    
    EqualityTest<size_t>(i, 5, 3);

    for (i = 0; i < 7; ++i)
    {
    	fsm->Free(segment[i]);
    }
}

/******************************************************************************/
void FsmAttach_test(void)
{
   	
    printf("\n****************** Attach - TEST ****************************\n");  

   	pid_t child_pid = fork();
   	if (0 == child_pid)
   	{
   		sleep(1);
   		std::shared_ptr<FSM> child_fsm = FSM::Attach("Yaron", 5, 28); 		
	    int counter = 0;
	    
	    void* segment1 = child_fsm->Alloc();
	    if (136 == *(size_t*)((char*)segment1 + 32))
	    {
	    	++counter;
	    }

	    void* segment2 = child_fsm->Alloc();
	    if (176 == *(size_t*)((char*)segment2 + 32))
	    {
	    	++counter;
	    } 
	    
	    child_fsm->Free(segment1);
	    child_fsm->Free(segment2);

	    if (2 == counter)
	    {
	    	exit (EXIT_SUCCESS);
	    }

	    exit (EXIT_FAILURE);
   	}
   	else
   	{
   		std::shared_ptr<FSM> fsm = FSM::Create("Yaron", 5, 28); 
   		int ret_status = EXIT_SUCCESS;
   		waitpid(child_pid, &ret_status, 0);
   		EqualityTest<int>(ret_status, EXIT_SUCCESS, 4);
   	}
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
