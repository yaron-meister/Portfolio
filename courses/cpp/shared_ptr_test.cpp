/*****************************************************************************
 * File name:   shared_ptr_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2019-03-10 14:43:34
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <iostream>     	/* 		cout, cerr		*/
#include <cstdlib>      	/*     EXIT_SUCCESS 	*/
#include <cstdio>			/*		  printf 		*/

#include "shared_ptr.h"     /* Forward declarations */


/********************************** Structs ***********************************/ 
class Person
{
	public:  
		Person(int age) : m_age(age){};
		
		void ChangAge()
		{
			m_age = 40;
		}

		int GetAge() const
		{
			return (m_age);
		}
		
	private:
		int m_age;
};

class Derived : public Person
{
public:
	Derived() : Person(50){}
};



using namespace ilrd;
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);

void CopyFuncsTest(void);
void DeReferenceTest(void);
void DerivedTest(void);

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
    
  	CopyFuncsTest();
  	DeReferenceTest();
  	DerivedTest();

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
void CopyFuncsTest(void)
{
	printf("\n***************** Copy-Funcs TEST ***************************\n");

	SharedPtr<int> sp1(new int(5124));
	SharedPtr<int> sp2(sp1);
	SharedPtr<int> sp3(new int(15));
	EqualityTest<int>(*(sp2.GetPtr()), 5124, 1);
	sp3 = sp2;
	EqualityTest<int>(*(sp3.GetPtr()), 5124, 2);
	sp2 = sp2;
	EqualityTest<int>(*(sp2.GetPtr()), 5124, 3);
}

/******************************************************************************/
void DeReferenceTest(void)
{
	printf("\n**************** De-Reference TEST **************************\n");

	SharedPtr<Person> sp(new Person(30));
	*sp = 20;
	EqualityTest<int>(sp->GetAge(), 20, 4);
	sp->ChangAge();
	EqualityTest<int>(sp->GetAge(), 40, 5);
}

/******************************************************************************/
void DerivedTest(void)
{
	printf("\n******************* Derived TEST ****************************\n");

	SharedPtr<Person> bp(new Person(30));
	SharedPtr<Derived> dp(new Derived);

	EqualityTest<int>(bp->GetAge(), 30, 6);
	bp = dp;	// Replace (dp = bp) to get a compilation error
	EqualityTest<int>(bp->GetAge(), 50, 7);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
