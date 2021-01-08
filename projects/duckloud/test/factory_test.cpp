/*****************************************************************************
 * File name:   factory_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daniel
 * Date:        2019-04-07 16:43:32
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>             /* 		cout, cerr		*/
#include <cstdlib>              /*     EXIT_SUCCESS 	*/

#include "utils.h"              /*      UNUSED_VAR      */
#include "factory.h"            /* Forward declarations */

using namespace ilrd;
/********************************* Classes ************************************/ 
class Base
{
public:
    static std::unique_ptr<Base> CreateBase(int num);

    Base(int num = 5) : m_base(num){}
    virtual int GetNum();

private:
    int m_base;

};

/****************************/
class Derived1 : public Base
{
public:
    static std::unique_ptr<Derived1> CreateDerived1(int num);

    Derived1(int num) : m_derived1(num){}
    virtual int GetNum();

private:
    int m_derived1;

};

/****************************/
class Derived2 : public Base
{
public:
    static std::unique_ptr<Derived2> CreateDerived2(int num);

    Derived2(int num) : m_derived2(num){}
    virtual int GetNum();

private:
    int m_derived2;

};

/****************************/
class Simple
{
public:
    static std::unique_ptr<Simple> CreateSimple(int num);

    Simple(int num) : m_simple(num){}

private:
    int m_simple;

};

 
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);

void CreateTest();
void AddTest();

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
    
    AddTest();
    CreateTest();

	printf("\n************** SUMARY OF UNIT-TEST **************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static std::unique_ptr<Base> CreateBase(int num)
{
    return (std::unique_ptr<Base> (new Base(num)));
}

/******************************************************************************/
static std::unique_ptr<Derived1> CreateDerived1(int num)
{
    return (std::unique_ptr<Derived1> (new Derived1(num)));
}

/******************************************************************************/
static std::unique_ptr<Derived2> CreateDerived2(int num)
{
    return (std::unique_ptr<Derived2> (new Derived2(num)));
}

/******************************************************************************/
int Base::GetNum()
{
    return (m_base);
}

/******************************************************************************/
int Derived1::GetNum()
{
    return (m_derived1);
}

/******************************************************************************/
int Derived2::GetNum()
{
    return (m_derived2);
}

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
void AddTest()
{
    printf("\n");
    printf("********************* Add - Test ********************************");
    printf("\n");

    Factory<Base, int, int> factory;

    EqualityTest<bool>(factory.Add(1, CreateBase), true, 1);
    EqualityTest<bool>(factory.Add(2, CreateDerived1), true, 2);
    EqualityTest<bool>(factory.Add(3, CreateDerived2), true, 3);
    // Compiler shouts about line 185 and it should be
    //EqualityTest<bool>(factory.Add(1, CreateSimple), true, 1);
    EqualityTest<bool>(factory.Add(1, CreateBase), false, 4);
    EqualityTest<bool>(factory.Add(2, CreateDerived1), false, 5);
    EqualityTest<bool>(factory.Add(3, CreateDerived2), false, 6);
    EqualityTest<bool>(factory.Add(3.5, CreateDerived2), false, 7);
    
}

/******************************************************************************/
void CreateTest()
{
    printf("\n");
    printf("******************* Create - Test *******************************");
    printf("\n");

    Factory<Base, int, int> factory;

    factory.Add(1, CreateBase);
    factory.Add(2, CreateDerived1);
    factory.Add(3, CreateDerived2);
    factory.Add(6, [](int unused) -> std::unique_ptr<Base>
                               { UNUSED_VAR(unused); throw std::exception(); });

    std::unique_ptr<Base> base = factory.Create(1, 2);
    std::unique_ptr<Base> derived1 = factory.Create(2, 4);
    std::unique_ptr<Base> derived2 = factory.Create(3, 6);

    EqualityTest<int>(base->GetNum(), 2, 8);
    EqualityTest<int>(derived1->GetNum(), 4, 9);
    EqualityTest<int>(derived2->GetNum(), 6, 10);

    try
    {
       std::unique_ptr<Base> derived3 = factory.Create(4, 6); 
    }
    catch(...)
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", 11);
        ++g_count;
    }

    ++g_tests;

    try
    {
        factory.Create(6, 5);
    }
    catch(const Factory<Base, int, int>::BadCreate bc)
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", 12);
        ++g_count;
    }
    
    ++g_tests;
    
}




/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
