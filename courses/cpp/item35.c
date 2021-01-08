/*****************************************************************************
 * File name:   item35.c
 * Developer:   Yaron Meister
 * Date:        2019-02-18 17:56:48
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <iostream>

/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
using namespace std;

struct BadDog: public runtime_error
{
	BadDog(const string& s_="This is a bad dog"): runtime_error(s_)
	{}
};

class X
{
public:
	X()
	{
		std::cout<<"Ctor "<<std::endl;
	}

	~X()
	{
		std::cout<<"Dtor "<<std::endl;
	}
};

void Fifi(){ throw 20; cerr << "Fifi() after throw" << endl; }
void Foo()
{
	X x;
	Fifi(); cerr << "Foo() after Fifi()" << endl;
} 

void Bar(){ Foo(); cerr << "Bar() after Foo()" << endl; }

/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
 	try
 	{
 		Bar();
 	}
 	catch(BadDog& b)
 	{
 		cerr << "Bad dog exception: " << b.what(); exit(3);
 	} 
 
 	catch(bad_alloc)
 	{
 		cerr << "Out of memory! exiting."; exit(2);
 	}
	catch( exception& r )
	{
		cerr << "unknown exception: " << r.what(); exit(4);
	}
	catch(const char* msg)
	{
		std::cerr<<msg<<std::endl;
	}
	catch(...)
	{
		std::cerr<<"default exception"<<std::endl;
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
