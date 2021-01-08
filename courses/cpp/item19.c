/*****************************************************************************
 * File name:   item19.c
 * Developer:   Yaron Meister
 * Date:        2019-02-16 13:59:52
 *****************************************************************************/
 
#include <iostream>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */


/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
struct X
{
	/* explicit X(); */
	explicit X(int a_, int b_ = 8);
	~X();
	X (const X& other_);
	X& operator = ( const X& other_);

	int m_a;
	int m_b;
};

struct Y
{
	Y();
	X m_x;
	int m_i;
};


/* X::X(): m_a(3), m_b(4)
{
	std::cout<<"this:"<<this<<"	X default Ctor. m_a:" << m_a << " m_b: " << m_b << std::endl;
} */
 
X::X(int a_, int b_): m_a(a_), m_b(b_)
{
	std::cout<< "this:" << this << "	X int int Ctor. m_a:" << m_a << " m_b: " << m_b << std::endl;
}

X::X(const X& other_ ): m_a(other_.m_a), m_b(other_.m_b)
{
	std::cout << "this:" << this << "	X copy Ctor. m_a:" << m_a << " m_b: " << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
	m_a = other_.m_a;
	m_b = other_.m_b;
	std::cout<<"this:"<<this<<"		X assignment operator. m_a:" << m_a << "m_b:" << m_b << std::endl;

	return *this;
}

X::~X()
{
	std::cout<<"this:"<<this<<"		X Dtor. m_a:"<< m_a << "m_b:" << m_b << std::endl;
}

Y::Y(): m_x(3, 4){}

/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	/*X x1; 

	X x2(7);
	std::cout<<"Size of X: "<<sizeof(X)<<std::endl;
	X* px = new X(x2);
	X x3(9, 10);
	X x4(x1);

	x1 = x3;

	X* xp = new X[10];
	delete[] xp; 
	delete px;
	px = 0; */ 

	Y y1; 
	y1.m_x.m_a = 250;
	y1.m_x.m_b = 750;
	Y y2(y1);
	Y y3;

	y3 = y1;  

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
