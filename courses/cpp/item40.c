/*****************************************************************************
 * File name:   item40.c
 * Developer:   Yaron Meister
 * Date:        2019-02-19 13:37:58
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <iostream>
#include <typeinfo>

/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
using namespace std;

struct X
{
	X()
	{
		cerr << "X Ctor" << endl;
		throw bad_cast();
	}

	X(int)
	{
		cerr << "X Ctor (int)" << endl;
	}

	~X()
	{
		cerr << "X Dtor" << endl;
	}
};

struct Y
{
	Y()
	{
		cerr << "Y Ctor" << endl;
	}

	~Y()
	{
		cerr << "Y Dtor" << endl;
	}
};

class L
{
public:
	L(): m_x(2)
	{
		cerr << "L Ctor" << endl;
	}

	~L()
	{
		cerr << "L Dtor" << endl;
	}

private:
	Y m_y;
	X m_x;
};

class M
{
public:
	M()
	{
		cerr << "M Ctor" << endl;
	}
	~M()
	{
		cerr << "M Dtor" << endl;
	}
private:
	X m_x;
	Y m_y;
};

class N
{
public:
	N()
	{
		cerr << "N Ctor" << endl;
	}
	~N()
	{
		cerr << "N Dtor" << endl;
	}
private:
	Y m_y;
	X m_x;
};

class J
{
public:
	J(): m_y(new Y), m_x(new X)
	{
		cerr << "J Ctor" << endl;
	}
	~J()
	{
		cerr << "J Dtor" << endl;
		delete m_x;
		delete m_y;
	}
private:
	Y* m_y;
	X* m_x;
};

class K
{
public:
	K()
	{
		cerr << "K Ctor" << endl;
		m_y = new Y;
		m_x = new X;
	}
	~K()
	{
		cerr << "K Dtor" << endl;
		delete m_x;
		delete m_y;
	}
private:
	Y* m_y;
	X* m_x;
};

/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	try
	{
		K var1;
	}
	catch (exception& e)
	{
		cerr << "exception cout. what:" << e.what() << endl;
	}
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
