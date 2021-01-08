/*****************************************************************************
 * File name:   bit_array_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Yael
 * Date:        2019-03-07 10:53:18
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <stdio.h>      /*       printf         */

#include "bit_array.h"  /* Forward declarations */


using namespace ilrd;
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);

void CtorSetAndGetTest(void);
void AndOrXorTest(void);
void CountTrueTest(void);
void BracketsAndEqualityTest(void);
void ShiftTest(void);
void OstreamTest(void);

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
    
    CtorSetAndGetTest();
    AndOrXorTest();
    CountTrueTest();
    BracketsAndEqualityTest();
    ShiftTest();
    OstreamTest();

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
void CtorSetAndGetTest(void)
{
    printf("\n************ Ctor, SetBit and GetBit ************************\n");

    BitArray<100> ba1;
    BitArray<300> ba2;

    ba1[7] = true;
    EqualityTest<bool>(ba1[7], true, 1);
  
    ba1[7] = false;
    EqualityTest<bool>(ba1[7], false, 2);

    ba1[7] = false;
    EqualityTest<bool>(ba1[7], false, 3);
}

/******************************************************************************/
void AndOrXorTest(void)
{
    printf("\n******************* &, | and ^ ******************************\n");

    BitArray<100> ba1;
    BitArray<100> ba2;
    BitArray<100> ba3;

    size_t i = 0;

    for (i = 0; i < 10; ++i)
    {
    	ba1[i] = true;
    }

    for (i = 10; i < 20; ++i)
    {
    	ba2[i] = true;
    }

    ba1 |= ba2;
    EqualityTest<size_t>(ba1.CountTrueBits(), 20, 4);

	  ba1 &= ba3;
    EqualityTest<size_t>(ba1.CountTrueBits(), 0, 5);
 	  std::cout << ba1 << std::endl;

	  ba1[0] = ba1[2] = ba1[4] = ba2[0] = ba2[1] = ba2[2] = true;

	  ba1 ^= ba2;
	  EqualityTest<bool>(ba1[0], false, 6);
	  EqualityTest<bool>(ba1[1], true, 7);
	  EqualityTest<bool>(ba1[2], false, 8);
	  EqualityTest<size_t>(ba1.CountTrueBits(), 12, 9);
}

/******************************************************************************/
void CountTrueTest(void)
{
    printf("\n****************** CountTrue Test ***************************\n");

    BitArray<100> ba;
    size_t i = 0;

    EqualityTest<size_t>(ba.CountTrueBits(), 0, 10);

    for (; i < 20; ++i)
    {
		ba[i] = true;
    }

    EqualityTest<size_t>(ba.CountTrueBits(), 20, 11);

    for (; i < 100; ++i)
    {
		ba[i] = true;
    }

    EqualityTest<size_t>(ba.CountTrueBits(), 100, 12);
}

/******************************************************************************/
void BracketsAndEqualityTest(void)
{
    printf("\n****************** [] and == Test ***************************\n");

    BitArray<100> ba1;
    size_t i = 70;

    for (; i < 80; ++i)
    {
		ba1[i] = true;
    }

    EqualityTest<bool>(true == ba1[74], true, 13);
    EqualityTest<bool>(true == ba1[69], false, 14);
    EqualityTest<bool>(ba1[75] == ba1[78], true, 15);
    EqualityTest<bool>(ba1[85] == ba1[78], false, 16);

    BitArray<100> ba2(ba1);

    EqualityTest<bool>(ba1 == ba2, true, 17);

    ba2[1] = true;
    EqualityTest<bool>(ba1 == ba2, false, 18);
}

/******************************************************************************/
void ShiftTest(void)
{
    printf("\n****************** Shift << Test ****************************\n");

    BitArray<100> ba;
    size_t i = 0;

    for (; i < 3; ++i)
    {
		ba[i] = true;
    }

    for (i = 97; i < 100; ++i)
    {
		ba[i] = true;
    }

    ba <<= 3;
    EqualityTest<bool>(ba[2], false, 19);
    EqualityTest<bool>(ba[3], true, 20);
    EqualityTest<bool>(ba[4], true, 21);
    EqualityTest<bool>(ba[5], true, 22);
    EqualityTest<bool>(ba[97], false, 23);
    EqualityTest<bool>(ba[98], false, 24);
    EqualityTest<bool>(ba[99], false, 25);
    
    for (i = 0; i < 10; ++i)
    {
		ba[i] = true;
    }

    ba <<= 74;
    EqualityTest<bool>(ba[73], false, 26);
    EqualityTest<bool>(ba[74], true, 27);
    EqualityTest<bool>(ba[83], true, 28);
    EqualityTest<bool>(ba[84], false, 29);

    for (i = 0; i < 10; ++i)
    {
		ba[i] = true;
    }

    ba <<= 64;
    EqualityTest<bool>(ba[63], false, 30);
    EqualityTest<bool>(ba[64], true, 31);
    EqualityTest<bool>(ba[73], true, 32);
    EqualityTest<bool>(ba[74], false, 33);
}


/******************************************************************************/
void OstreamTest(void)
{
    printf("\n****************** O-stream Test ****************************\n");

    BitArray<50> ba;

    for (int i = 0; i < 50; i += 10)
    {
		ba[i] = true;
		ba[i + 1] = true;
    }

    std::cout << ba << std::endl;
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
