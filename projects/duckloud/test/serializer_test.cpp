/*****************************************************************************
 * File name:   serializer_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-08 13:20:48
 * Test Flow: 
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <sstream>      /*     stringstream     */

#include "serializer.h" /* Forward declarations */

using namespace ilrd;
/********************************* Classes ************************************/ 
class Base
{
public:
    static std::unique_ptr<Base> CreateBase(int num);

    Base(int num) : m_base(num){}
    virtual void Serialize(std::ostream& os) const;
    virtual int GetNum() const;

private:
    int m_base;

};

std::ostream& operator<<(std::ostream& os, const Base& base);

/****************************/
class Derived1 : public Base
{
public:
    static std::unique_ptr<Derived1> CreateDerived1(int num, int flo);

    Derived1(int num, int flo) : Base(num), m_derived1(flo){}
    virtual void Serialize(std::ostream& os) const;
    int GetNum() const;

private:
    int m_derived1;

};

std::ostream& operator<<(std::ostream& os, const Derived1& derived1);

/****************************/
class Derived2 : public Base
{
public:
    static std::unique_ptr<Derived2> CreateDerived2(int num, int dbl);

    Derived2(int num, int dbl) : Base(num), m_derived2(dbl){}
    virtual void Serialize(std::ostream& os) const;
    int GetNum() const;

private:
    int m_derived2;
};

std::ostream& operator<<(std::ostream& os, const Derived2& derived2);

/****************************/
class Derived3 : public Base
{
public:
    static std::unique_ptr<Derived3> CreateDerived3(int num, int chr);

    Derived3(int num, int chr) : Base(num), m_derived3(chr){}
    virtual void Serialize(std::ostream& os) const;
    int GetNum() const;

private:
    int m_derived3;

};

std::ostream& operator<<(std::ostream& os, const Derived3& derived3);

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
void SerializeTest();
void DeserializeTest();
void AddAndDeserializeTest();

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
    
    SerializeTest();
    AddAndDeserializeTest();
	
	printf("\n************** SUMARY OF UNIT-TEST **************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                        Class Functions definitions 
*******************************************************************************/ 
/* Class Base */
/******************************************************************************/
static std::unique_ptr<Base> CreateBase(int num)
{
    return (std::unique_ptr<Base> (new Base(num)));
}

/******************************************************************************/
void Base::Serialize(std::ostream& os) const
{
    os << typeid(*this).name() << '\n' << *this << '\n' << '\n' ;
}

/******************************************************************************/
int Base::GetNum() const
{
    return (m_base);
}

/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Base& base)
{
    return (os << base.GetNum());
}

/******************************************************************************/
namespace ilrd
{
template<>
template<>
std::unique_ptr<Base> Serializer<Base>::Creator<Base>(std::istream& is)
{
    int num;

    is >> num;

    return (CreateBase(num));
}
}


/* Class Derived1 */
/******************************************************************************/
static std::unique_ptr<Derived1> CreateDerived1(int num, int flo)
{
    return (std::unique_ptr<Derived1> (new Derived1(num, flo)));
}

/******************************************************************************/
void Derived1::Serialize(std::ostream& os) const
{
    os << typeid(*this).name() << '\n' << *this << '\n' << '\n' ;
}

/******************************************************************************/
int Derived1::GetNum() const
{
    return (m_derived1);
}

/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Derived1& derived1)
{
    return (os << derived1.GetNum());
}

/******************************************************************************/
namespace ilrd
{
template<>
template<>
std::unique_ptr<Base> Serializer<Base>::Creator<Derived1>(std::istream& is)
{
    int flo;

    is >> flo;

    return (CreateDerived1(10, flo));
}
}


/* Class Derived2 */
/******************************************************************************/
static std::unique_ptr<Derived2> CreateDerived2(int num, int dbl)
{
    return (std::unique_ptr<Derived2> (new Derived2(num, dbl)));
}

/******************************************************************************/
void Derived2::Serialize(std::ostream& os) const
{
    os << typeid(*this).name() << '\n' << *this << '\n' << '\n' ;
}

/******************************************************************************/
int Derived2::GetNum() const
{
    return (m_derived2);
}

/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Derived2& derived2)
{
    return (os << derived2.GetNum());
}

/******************************************************************************/
namespace ilrd
{
template<>
template<>
std::unique_ptr<Base> Serializer<Base>::Creator<Derived2>(std::istream& is)
{
    int dbl;

    is >> dbl;

    return (CreateDerived2(20, dbl));
}
}


/* Class Derived3 */
/******************************************************************************/
static std::unique_ptr<Derived3> CreateDerived3(int num, int chr)
{
    return (std::unique_ptr<Derived3> (new Derived3(num, chr)));
}

/******************************************************************************/
void Derived3::Serialize(std::ostream& os) const
{
    os << typeid(*this).name() << '\n' << *this << '\n' << '\n' ;
}

/******************************************************************************/
int Derived3::GetNum() const
{
    return (m_derived3);
}

/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Derived3& derived3)
{
    return (os << derived3.GetNum());
}

/******************************************************************************/
namespace ilrd
{
template<>
template<>
std::unique_ptr<Base> Serializer<Base>::Creator<Derived3>(std::istream& is)
{
    int chr;

    is >> chr;

    return (CreateDerived3(30, chr));
}
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
void SerializeTest()
{
    printf("\n");
    printf("***************** Serialize - Test ******************************");
    printf("\n");

    Serializer<Base> serializer;

    Base base(5);
    serializer.Serialize(std::cout, base);

    Derived1 derived1(1, 10);
    serializer.Serialize(std::cout, derived1);

    Derived2 derived2(2,20);
    serializer.Serialize(std::cout, derived2);

    Derived3 derived3(3, 30);
    serializer.Serialize(std::cout, derived3);

    // Simple simple(50);
    // serializer.Serialize(std::cout, simple);
}

/******************************************************************************/
void AddAndDeserializeTest()
{
    printf("\n");
    printf("************** Add & Deserialize - Test *************************");
    printf("\n");

    Serializer<Base> serializer;
    std::stringstream base_stream;
    std::stringstream derived1_stream;
    std::stringstream derived2_stream;
    std::stringstream derived3_stream;

    serializer.Add<Base>();
    serializer.Add<Derived1>();
    serializer.Add<Derived2>();
    //serializer.Add<Derived2>();

    Base base_before(5);
    Derived1 derived1_before(1, 10);
    Derived2 derived2_before(2, 20);
    Derived3 derived3_before(3, 30);

    serializer.Serialize(base_stream, base_before);
    std::unique_ptr<Base> base_after = serializer.Deserialize(base_stream);
    EqualityTest<int>(base_after->GetNum(), 5, 1);
    
    serializer.Serialize(derived1_stream, derived1_before);
    std::unique_ptr<Base> derived1_after =
                                        serializer.Deserialize(derived1_stream);
    EqualityTest<int>(derived1_after->GetNum(), 10, 2);

    serializer.Serialize(derived2_stream, derived2_before);
    std::unique_ptr<Base> derived2_after =
                                        serializer.Deserialize(derived2_stream);
    EqualityTest<int>(derived2_after->GetNum(), 20, 3);

    // serializer.Serialize(derived3_stream, derived3_before);
    // std::unique_ptr<Base> derived3_after = 
                                      //serializer.Deserialize(derived3_stream);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
