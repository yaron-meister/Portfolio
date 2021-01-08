/*****************************************************************************
 * File name:   complex.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Yael
 * Date:        2019-02-20 23:52:53
 * Description: Complex operators implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*       	       	    */

#include "complex.h"    /* Forward declarations */
 

using namespace ilrd;
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
const Complex ilrd::operator+(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex;

	new_complex.m_real = lhs.m_real + rhs.m_real;
	new_complex.m_img  = lhs.m_img  + rhs.m_img;

	return (new_complex);
}

/******************************************************************************/ 
const Complex ilrd::operator-(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex;

	new_complex.m_real = lhs.m_real - rhs.m_real;
	new_complex.m_img  = lhs.m_img  - rhs.m_img;

	return (new_complex);
}

/******************************************************************************/
const Complex ilrd::operator*(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex;

	new_complex.m_real = lhs.m_real * rhs.m_real - lhs.m_img * rhs.m_img;
	new_complex.m_img  = lhs.m_real * rhs.m_img  + lhs.m_img * rhs.m_real;

	return (new_complex);
}

/******************************************************************************/
const Complex ilrd::operator/(const Complex& lhs, const Complex& rhs)
{
	Complex rhs_conj(rhs.m_real, -rhs.m_img);
	Complex numerator 	= lhs * rhs_conj;
	Complex denominator = rhs * rhs_conj;
	Complex new_complex;

	new_complex.m_real = numerator.m_real / denominator.m_real;
	new_complex.m_img  = numerator.m_img  / denominator.m_real;

	return (new_complex);
}

/******************************************************************************/
bool ilrd::operator==(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.m_real - rhs.m_real) < 0.1 && (lhs.m_real - rhs.m_real) > -0.1
		 	&& (lhs.m_img - rhs.m_img) < 0.1 && (lhs.m_img - rhs.m_img) > -0.1);
}

/******************************************************************************/
bool ilrd::operator!=(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.m_real - rhs.m_real) > 0.1 || (lhs.m_real - rhs.m_real) < -0.1
			|| (lhs.m_img - rhs.m_img) > 0.1 || (lhs.m_img - rhs.m_img) < -0.1);
}

/******************************************************************************/
Complex& Complex::operator+=(const Complex& rhs)
{
	*this = *this + rhs;

	return (*this);
}

/******************************************************************************/
Complex& Complex::operator-=(const Complex& rhs)
{
	*this = *this - rhs;

	return (*this);
}

/******************************************************************************/
Complex& Complex::operator*=(const Complex& rhs)
{
	*this = *this * rhs;

	return (*this);
}

/******************************************************************************/
Complex& Complex::operator/=(const Complex& rhs)
{
	*this = *this / rhs;

	return (*this);
} 

/******************************************************************************/
double Complex::GetReal(void) const
{
	return (m_real);
}

/******************************************************************************/
double Complex::GetImg(void) const
{
	return (m_img);
}

/******************************************************************************/
void Complex::SetReal(double new_real)
{
	m_real = new_real;
}        

/******************************************************************************/
void Complex::SetImg(double new_img)
{
	m_img = new_img;
} 

/******************************************************************************/
std::ostream& ilrd::operator<<(std::ostream& os, const Complex& cpx)
{
	double img_mem = cpx.GetImg();

	if (img_mem < 0)
	{
		return (os << cpx.GetReal() << " - " << -img_mem << "*i");
	}
	else
	{
		return (os << cpx.GetReal() << " + " << img_mem << "*i");
	}
}

/******************************************************************************/
std::istream& ilrd::operator>>(std::istream& is, Complex& cpx)
{
	double temp = 0;

	std::cout << "Please insert the REAL member" << std::endl;
	is >> temp;
	cpx.SetReal(temp);
	std::cout << "Please insert the IMG member" << std::endl;
	is >> temp;
	cpx.SetImg(temp);

	return (is);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
