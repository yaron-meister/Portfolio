/*****************************************************************************
 * File name:   wpq_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Eran
 * Date:        2019-04-11 16:12:40
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		     cout, cerr	          	*/
#include <cstdlib>      /*          EXIT_SUCCESS 	        */
#include <unistd.h>     /*              sleep               */
#include <ctime>        /*       std::time_t, std::time     */
#include <thread>       /*           std::thread            */
#include <chrono>       /*           std::chrono            */

#include "wpq.h"        /*      Forward declarations        */

using namespace ilrd;
/********************************* Macros *************************************/ 
 
 
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);
void SizeAndIsEmptyTest();
void PushAndPopTest();
void WaitTest();
void ThreadFunc1();
void TimedPopTest();
void ThreadFunc2();

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approved by valgrind     */

WPQ<int> g_wpq1;
WPQ<int> g_wpq2;

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
    
    SizeAndIsEmptyTest();
    PushAndPopTest();
    WaitTest();
    TimedPopTest();

	printf("\n************** SUMMARY OF UNIT-TEST *************************\n");
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
void SizeAndIsEmptyTest()
{
    printf("\n"); 
  	printf("***************** Size & IsEmpty - TEST *************************");
  	printf("\n"); 

    WPQ<int> wpq;

    EqualityTest<bool>(wpq.IsEmpty(), true, 1);
    EqualityTest<int>(wpq.Size(), 0, 2);

    wpq.Push(1);
    wpq.Push(3);
    wpq.Push(4);
    wpq.Push(2);

    EqualityTest<bool>(wpq.IsEmpty(), false, 3);
    EqualityTest<int>(wpq.Size(), 4, 4);
}

/******************************************************************************/
void PushAndPopTest()
{
    printf("\n"); 
  	printf("****************** Push & Pop - TEST ****************************");
  	printf("\n"); 

    WPQ<int> wpq;
    int ret;

    wpq.Push(5);
    wpq.Push(7);
    wpq.Push(8);
    wpq.Push(6);

    wpq.Pop(ret);
    EqualityTest<int>(ret, 8, 5);

    wpq.Pop(ret);
    EqualityTest<int>(ret, 7, 6);

    wpq.Pop(ret);
    EqualityTest<int>(ret, 6, 7);

    wpq.Pop(ret);
    EqualityTest<int>(ret, 5, 8);
}

/******************************************************************************/
void WaitTest()
{
    printf("\n"); 
  	printf("******************** Wait - TEST ********************************");
  	printf("\n"); 

    int ret;
    std::thread thread(ThreadFunc1);

    std::time_t time1 = std::time(nullptr);
    g_wpq1.Pop(ret);
    std::time_t time2 = std::time(nullptr);
    g_wpq1.Pop(ret);
    std::time_t time3 = std::time(nullptr);

    EqualityTest<bool>((time2 - time1) < 4, false, 9);
    EqualityTest<bool>((time3 - time2) < 3, false, 10);

    thread.join();
}

/********************                                      ********************/
void ThreadFunc1()
{
    sleep(4);
    g_wpq1.Push(10);

    sleep(3);
    g_wpq1.Push(20);
}

/******************************************************************************/
void TimedPopTest()
{
    printf("\n"); 
  	printf("***************** Timed Pop - TEST ******************************");
  	printf("\n"); 

    int ret_val1 = 0;
    int ret_val2 = 0;
    std::chrono::duration<int> timeout(5);

    std::thread thread(ThreadFunc2);

    std::time_t time1 = std::time(nullptr);
    bool ret1 = g_wpq2.Pop(ret_val1, timeout);
    std::time_t time2 = std::time(nullptr);
    EqualityTest<bool>((time2 - time1) < 5, false, 11);
    EqualityTest<bool>(ret1, false, 12);
    EqualityTest<int>(ret_val1, 0, 13);

    bool ret2 = g_wpq2.Pop(ret_val2, timeout);
    EqualityTest<bool>(ret2, true, 14);
    EqualityTest<int>(ret_val2, 15, 15);

    thread.join();
}

/********************                                      ********************/
void ThreadFunc2()
{
    sleep(7);
    g_wpq2.Push(15);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
