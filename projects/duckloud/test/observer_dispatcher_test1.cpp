/*****************************************************************************
 * File name:   observer_dispatcher_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-19 15:07:13
 * Test Flow: 
 *****************************************************************************/
 
#include <iostream>                     /* 		cout, cerr		*/
#include <cstdlib>                      /*     EXIT_SUCCESS 	*/
 
#include "observer_dispatcher.h"        /* Forward declarations */

using namespace ilrd;
/**************************** Forward Declarations ****************************/
template <class TYPE>
static void EqualityTest(TYPE actual_value, TYPE expected_value,
												 int num_of_test);

class MSG;

void ActionFunc(const MSG& msg);
void StopFunc();

/********************************** Classes ***********************************/ 
class MSG
{
public:
    explicit MSG(int temperature) : m_temperature(temperature){}

    int GetTemp() const
    {
        return (m_temperature);
    }

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

private:
    int m_temperature;
};

/********************/
class Thermometer
{
public:
    explicit Thermometer(int temperature) : m_temperature(temperature){}

    int GetTemp() const
    {
        return (m_temperature);
    }

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

private:
    int m_temperature;
    Publisher<MSG> m_publisher; 
};

/********************/
class Fire
{
public:
    explicit Fire(int temperature) : m_temperature(temperature),
                                     m_subscriber(ActionFunc, StopFunc)
    {}

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

private:
    int m_temperature;
    Subscriber<MSG> m_subscriber;
};

/********************/
class AC
{
public:
    explicit AC(int temperature) : m_temperature(temperature),
                                   m_subscriber(ActionFunc, StopFunc)
    {}

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

private:
    int m_temperature;
    Subscriber<MSG> m_subscriber;
};

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /*  Create and Destroy approved by valgrind    */

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
void ActionFunc(const MSG& msg)
{
    std::cout << "Temp rise up\n";

    if (msg.GetTemp() > 5)
    {
        std::cout << "Warning!!! Too worm\n";
    }
} 

/******************************************************************************/
void StopFunc()
{
    std::cout << "Stopping\n";
} 




/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
