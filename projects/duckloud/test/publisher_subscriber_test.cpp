/*****************************************************************************
 * File name:   observer_dispatcher_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daria
 * Date:        2019-04-19 15:07:13
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>                     /* 		cout, cerr		*/
#include <cstdlib>                      /*     EXIT_SUCCESS 	*/
 
#include "publisher_subscriber.h"       /* Forward declarations */

using namespace ilrd;
/********************************** Classes ***********************************/ 
class Thermometer
{
public:
    explicit Thermometer(int temperature) : m_temperature(temperature){}

    int GetTemp() const
    {
        return (m_temperature);
    }

    void SetTemp()
    {
        ++m_temperature;
        m_publisher.Publish(m_temperature);
    }

    Publisher<int>* GetPublisher()
    {
        return (&m_publisher);
    }

private:
    int m_temperature;
    Publisher<int> m_publisher; 
};

/********************/
class Fire
{
public:
    Fire(int temperature, Publisher<int>* publisher) : 
            m_temperature(temperature),
            m_subscriber(publisher, &Fire::ActionFunc, &Fire::StopFunc, *this)
    {}

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

    void ActionFunc(const int& temp)
    {
        std::cout << "Fire: Temp rise up\n";

        if (temp > 25)
        {
            std::cout << "Fire: Warning!!! Too worm\n";
        }
    } 

    void StopFunc()
    {
        std::cout << "Fire: Stopping\n";
    } 

    private:
        int m_temperature;
        Subscriber<int, Fire> m_subscriber;
    };

/********************/
class AC
{
public:
    AC(int temperature, Publisher<int>* publisher) : 
            m_temperature(temperature),
            m_subscriber(publisher, &AC::ActionFunc, &AC::StopFunc, *this)
    {}

    void SetTemp(int temperature)
    {
        m_temperature = temperature;
    }

    void ActionFunc(const int& temp)
    {
        std::cout << "AC: Temp rise up\n";

        if (temp > 23)
        {
            std::cout << "AC: Warning!!! Too worm\n";
        }
    } 

    void StopFunc()
    {
        std::cout << "AC: Stopping\n";
    }

private:
    int m_temperature;
    Subscriber<int, AC> m_subscriber;
};

/**************************** Forward Declarations ****************************/
void TrivialTest();
void UnSubscribeAndDtorTest();
void PublishDeathTest();

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
    
    TrivialTest();
    UnSubscribeAndDtorTest();
    PublishDeathTest();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void TrivialTest()
{
    printf("\n");
    printf("****************** Trivial - Test *******************************");
    printf("\n");

    Thermometer thermo(20);

    // After 5 sets warn about heat
    Fire fire(thermo.GetTemp(), thermo.GetPublisher());
    // After 3 sets warn about heat
    AC ac(thermo.GetTemp(), thermo.GetPublisher());

    for (size_t i = 0; i < 6; ++i)
    {
        thermo.SetTemp();
    }
}

/******************************************************************************/
void UnSubscribeAndDtorTest()
{
    printf("\n");
    printf("************* UnSubscribe & Dtor - Test *************************");
    printf("\n");

    Thermometer thermo(20);
   
    Fire fire(thermo.GetTemp(), thermo.GetPublisher());
    
    {
        AC ac(thermo.GetTemp(), thermo.GetPublisher());
    }

    // Fire should print about Temp rise-up
    // AC isn't
    thermo.SetTemp();
}

/******************************************************************************/
void PublishDeathTest()
{
    printf("\n");
    printf("**************** PublishDeath - Test ****************************");
    printf("\n");

    Thermometer thermo(20);
    Fire fire(thermo.GetTemp(), thermo.GetPublisher());
    
    // Fire should print about Temp rise-up
    thermo.SetTemp();

    // StopFunc of Fire should be called
    (thermo.GetPublisher())->PublishDeath();

    // Nothing should happen
    thermo.SetTemp();
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 