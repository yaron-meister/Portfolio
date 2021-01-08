/*****************************************************************************
 * File name:   string_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Alon
 * Date:        2019-02-24 10:32:31
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <stdio.h>		/*		  printf 		*/
#include <cstring>		/*	 string Functions 	*/

#include "string.h"     /* Forward declarations */

using namespace ilrd; 
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);

static void CtorAsignAndToStringTest();
static void BracketsAndEqualsTest();
static void ConcateTest();
static void LengthTest();
static void CCtorBigSmallTest();
static void OstreamTest();
static void IstreamTest();

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main()
{   
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
  	CtorAsignAndToStringTest();
	BracketsAndEqualsTest();
	ConcateTest();
	LengthTest();
	CCtorBigSmallTest();
	OstreamTest();
	IstreamTest();

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
static void CtorAsignAndToStringTest()
{
	printf("\n");
    printf("************* Ctor, '=' and ToString - Test *******************\n");
	printf("\n");

	String Str1("Hello");
	String Str2("World");

	Str1 = Str2;

	EqualityTest<int>(strcmp(Str1.ToString(), Str2.ToString()), 0, 1);
}

/******************************************************************************/
static void BracketsAndEqualsTest()
{
	printf("\n");
    printf("************** Brackets and Equals - Test *********************\n");
	printf("\n");

	String Str("Hello");

	EqualityTest<char>(Str[1] == 'e', true,  2);
	EqualityTest<char>('H' != Str[0], false,  3);
	EqualityTest<char>('a' != Str[0], true, 4);
	EqualityTest<char>(Str[3] == 'm', false, 5);
}

/******************************************************************************/
static void ConcateTest()
{
	printf("\n");
    printf("******************** '+=' - Test ******************************\n");
	printf("\n");

	String Str1("Hello");
	String Str2(" world");
	char concatenated_str[] = "Hello world";

	Str1 += Str2;

	EqualityTest<int>(strcmp(Str1.ToString(), concatenated_str), 0, 6);
}

/******************************************************************************/
static void LengthTest()
{
	printf("\n");
    printf("******************* Length - Test *****************************\n");
	printf("\n");

	String Str = String();
	EqualityTest<std::size_t>(Str.Length(), 0, 7);
	
	Str = "Hello";
	EqualityTest<std::size_t>(Str.Length(), 5, 8);

	Str = "Hi";
	EqualityTest<std::size_t>(Str.Length(), 2, 9);

}

/******************************************************************************/
static void CCtorBigSmallTest()
{
	printf("\n");
    printf("************** CCtor, Big and samll - Test ********************\n");
	printf("\n");

	String Str("Yaron");
	String Str1(Str);
	String Str2(Str1);

	Str2[0] = 'y';

	EqualityTest<bool>((Str2 > Str1), true, 10);
	EqualityTest<bool>((Str1 < Str2), true, 11);
}

/******************************************************************************/
static void OstreamTest()
{
	printf("\n");
    printf("******************** OStream - Test ***************************\n");
	printf("\n");

	String Str("I am COUT and I am working!!!");
	std::cout << Str << std::endl;
}

/******************************************************************************/
static void IstreamTest()
{
	printf("\n");
    printf("******************** IStream - Test ***************************\n");
	printf("\n");

	String Str = String();
	std::cout << "Please insert the string 'Hello':" << std::endl;
	std::cin >> Str;
	std::cout << "Str keeps the string: " << Str << std::endl;
}
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
