/*****************************************************************************
 * File name:   complex_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Yael
 * Date:        2019-02-20 23:52:53
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <stdlib.h>     /*     EXIT_SUCCESS 	*/
#include <stdio.h>		/*		  printf 		*/

#include "complex.h"    /* Forward declarations */

 
/**************************** Forward Declarations ****************************/
static void DoubleEqualityTest(double actual_value, 
                                        double expected_value, int num_of_test);
static void ComplexEqualityTest(ilrd::Complex actual_value,
                                 ilrd::Complex expected_value, int num_of_test);
static void PlusTest(void);
static void MinusTest(void);
static void MultiTest(void);
static void DivideTest(void);
static void AsignTest(void);
static void GetAndSetTest(void);
static void StreamsTest(void);


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
    
    PlusTest();
    MinusTest();
    MultiTest();
    DivideTest();
    AsignTest();
    GetAndSetTest();
    StreamsTest();

	printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static void DoubleEqualityTest(double actual_value, 
                                         double expected_value, int num_of_test)
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
static void ComplexEqualityTest(ilrd::Complex actual_value,
                                  ilrd::Complex expected_value, int num_of_test)
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
static void PlusTest(void)
{
    ilrd::Complex cpx(2, 1);
    
    ilrd::Complex cpx1(3, 4);
    ilrd::Complex cpx1_ex(5, 5);

    ilrd::Complex cpx2(-2, -1);
    ilrd::Complex cpx2_ex(0, 0);

    ilrd::Complex cpx3(5, 0);
    ilrd::Complex cpx3_ex(7, 1);

    printf("\n");
    printf("********************* Plus - Test *****************************\n");
    printf("\n");

    ComplexEqualityTest(cpx + cpx1, cpx1_ex, 1);
    ComplexEqualityTest(cpx + cpx2, cpx2_ex, 2);
    ComplexEqualityTest(cpx + cpx3, cpx3_ex, 3);
}

/******************************************************************************/
static void MinusTest(void)
{
    ilrd::Complex cpx(2, 1);
    
    ilrd::Complex cpx1(3, 4);
    ilrd::Complex cpx1_ex(-1, -3);

    ilrd::Complex cpx2(-2, -1);
    ilrd::Complex cpx2_ex(4, 2);

    ilrd::Complex cpx3(5, 0);
    ilrd::Complex cpx3_ex(-3, 1);

    printf("\n");
    printf("******************** Minus - Test *****************************\n");
    printf("\n");

    ComplexEqualityTest(cpx - cpx1, cpx1_ex, 4);
    ComplexEqualityTest(cpx - cpx2, cpx2_ex, 5);
    ComplexEqualityTest(cpx - cpx3, cpx3_ex, 6);
}

/******************************************************************************/
static void MultiTest(void)
{
    ilrd::Complex cpx(2, 1);
    
    ilrd::Complex cpx1(3, 4);
    ilrd::Complex cpx1_ex(2, 11);

    ilrd::Complex cpx2(-2, -1);
    ilrd::Complex cpx2_ex(-3, -4);

    ilrd::Complex cpx3(5, 0);
    ilrd::Complex cpx3_ex(10, 5);

    printf("\n");
    printf("******************* Multiple - Test ***************************\n");
    printf("\n");

    ComplexEqualityTest(cpx * cpx1, cpx1_ex, 7);
    ComplexEqualityTest(cpx * cpx2, cpx2_ex, 8);
    ComplexEqualityTest(cpx * cpx3, cpx3_ex, 9);
}

/******************************************************************************/
static void DivideTest(void)
{
    ilrd::Complex cpx(2, 1);
    
    ilrd::Complex cpx1(3, 4);
    ilrd::Complex cpx1_ex(0.4, -0.2);

    ilrd::Complex cpx2(-2, -1);
    ilrd::Complex cpx2_ex(-1, 0);

    ilrd::Complex cpx3(5, 0);
    ilrd::Complex cpx3_ex(0.4, 0.2);

    printf("\n");
    printf("******************** Divide - Test ****************************\n");
    printf("\n");

    ComplexEqualityTest(cpx / cpx1, cpx1_ex, 10);
    ComplexEqualityTest(cpx / cpx2, cpx2_ex, 11);
    ComplexEqualityTest(cpx / cpx3, cpx3_ex, 12);
}

/******************************************************************************/
static void AsignTest(void)
{
    ilrd::Complex cpx_plus(2, 1);
    ilrd::Complex cpx_minus(2, 1);
    ilrd::Complex cpx_multi(2, 1);
    ilrd::Complex cpx_divide(2, 1);

    ilrd::Complex cpx1(3, 4);
    ilrd::Complex cpx1_ex(5, 5);
    cpx_plus += cpx1;

    ilrd::Complex cpx2(3, 4);
    ilrd::Complex cpx2_ex(-1, -3);
    cpx_minus -= cpx2;

    ilrd::Complex cpx3(3, 4);
    ilrd::Complex cpx3_ex(2, 11);
    cpx_multi *= cpx3;

    ilrd::Complex cpx4(3, 4);
    ilrd::Complex cpx4_ex(0.4, -0.2);
    cpx_divide /= cpx4;

    printf("\n");
    printf("******************** Asign - Test *****************************\n");
    printf("\n");

    ComplexEqualityTest(cpx_plus, cpx1_ex, 13);
    ComplexEqualityTest(cpx_minus, cpx2_ex, 14);
    ComplexEqualityTest(cpx_multi, cpx3_ex, 15);
    ComplexEqualityTest(cpx_divide, cpx4_ex, 16);
}

/******************************************************************************/
static void GetAndSetTest(void)
{
    ilrd::Complex cpx(2, 1);
    
    printf("\n");
    printf("****************** Get and Set - Test *************************\n");
    printf("\n");

    DoubleEqualityTest(cpx.GetReal(), 2, 17);
    DoubleEqualityTest(cpx.GetImg(), 1, 18);

    cpx.SetReal(-2);
    cpx.SetImg(-1);

    DoubleEqualityTest(cpx.GetReal(), -2, 19);
    DoubleEqualityTest(cpx.GetImg(), -1, 20);

    cpx.SetReal(0);
    cpx.SetImg(0);

    DoubleEqualityTest(cpx.GetReal(), 0, 21);
    DoubleEqualityTest(cpx.GetImg(), 0, 22);
}

/******************************************************************************/
static void StreamsTest(void)
{
    ilrd::Complex cpx1(2, 1);
    ilrd::Complex cpx2(-2, -1);

    printf("\n");
    printf("******************** Streams - Test ***************************\n");
    printf("\n");

    std::cout << "OStream test for cpx1(2, 1): "   <<  cpx1 << std::endl;
    std::cout << "OStream test for cpx2(-2, -1): " <<  cpx2 << std::endl;

    std::cout << "First test for IStream: " << std::endl;
    printf("\n");
    std::cout << "Please insert the complex (2, 1)" << std::endl;
    std::cin >> cpx1;
    std::cout << "If 2 = " << cpx1.GetReal() << " and 1 = " << cpx1.GetImg() 
                                            << " ---> TEST PASSED" << std::endl;
    printf("\n");
    std::cout << "Please insert the complex (-2, -1)" << std::endl;
    std::cin >> cpx1;
    std::cout << "If -2 = " << cpx1.GetReal() << " and -1 = " << cpx1.GetImg()
                                            << " ---> TEST PASSED" << std::endl;
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
