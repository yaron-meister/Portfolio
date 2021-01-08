/*****************************************************************************
 * File name:   complex.h
 * Developer:   HRD7	
 * Date:        2019-02-20 23:52:53
 * Description: Complex operators header
 *****************************************************************************/

#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <iostream>

namespace ilrd
{
    class Complex
    {
    public:
        Complex(double real = 0, double img = 0): m_real(real) , m_img(img) {}		// Non explicit for a case of '3 + complex' when we want 3 to cast to a complex

        Complex& operator+=(const Complex& rhs);
        Complex& operator-=(const Complex& rhs);
        Complex& operator*=(const Complex& rhs);
        Complex& operator/=(const Complex& rhs);

        double GetReal(void) const;
        double GetImg(void) const;
        void SetReal(double new_real);
        void SetImg(double new_img);

    private:
        double m_real;
        double m_img;
    };

    std::istream& operator>>(std::istream& is, Complex& cpx); 
    std::ostream& operator<<(std::ostream& os, const Complex& cpx);  

    const Complex operator+(const Complex& lhs, const Complex& rhs);
    const Complex operator-(const Complex& lhs, const Complex& rhs);
    const Complex operator*(const Complex& lhs, const Complex& rhs);
    const Complex operator/(const Complex& lhs, const Complex& rhs);

    bool operator==(const Complex& lhs, const Complex& rhs);
    bool operator!=(const Complex& lhs, const Complex& rhs);


/***************************** Global variables *******************************/
static const double g_epsilon = 0.1;

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex;

	new_complex += lhs;
	new_complex += rhs;

	return (new_complex);
}

/******************************************************************************/ 
inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex;

	new_complex += lhs;
	new_complex -= rhs;

	return (new_complex);
}

/******************************************************************************/
inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex(lhs);

	new_complex *= rhs;

	return (new_complex);
}

/******************************************************************************/
inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex new_complex(lhs);

	new_complex /= rhs;

	return (new_complex);
}

/******************************************************************************/
inline bool operator==(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.GetReal() - rhs.GetReal()) < g_epsilon && (lhs.GetReal() - 
													 rhs.GetReal()) > -g_epsilon
		 	&& (lhs.GetImg() - rhs.GetImg()) < g_epsilon && (lhs.GetImg() -
		 											rhs.GetImg()) > -g_epsilon);
}

/******************************************************************************/
inline bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.GetReal() - rhs.GetReal()) > g_epsilon || (lhs.GetReal() -
													 rhs.GetReal()) < -g_epsilon
			|| (lhs.GetImg() - rhs.GetImg()) > g_epsilon || (lhs.GetImg() -
													rhs.GetImg()) < -g_epsilon);
}

/******************************************************************************/
inline Complex& Complex::operator+=(const Complex& rhs)
{
	m_real = m_real + rhs.m_real;
	m_img = m_img + rhs.m_img;

	return (*this);
}

/******************************************************************************/
inline Complex& Complex::operator-=(const Complex& rhs)
{
	m_real = m_real - rhs.m_real;
	m_img = m_img - rhs.m_img;

	return (*this);
}

/******************************************************************************/
inline Complex& Complex::operator*=(const Complex& rhs)
{
	double temp = m_real;

	m_real = m_real * rhs.m_real - m_img * rhs.m_img;
	m_img = temp * rhs.m_img  + m_img * rhs.m_real;

	return (*this);
}

/******************************************************************************/
inline Complex& Complex::operator/=(const Complex& rhs)
{
	Complex rhs_conj(rhs.m_real, -rhs.m_img);
	Complex numerator 	= *this * rhs_conj;
	Complex denominator = rhs * rhs_conj;

	m_real = numerator.m_real / denominator.m_real;
	m_img  = numerator.m_img  / denominator.m_real;

	return (*this);
} 

/******************************************************************************/
inline double Complex::GetReal(void) const
{
	return (m_real);
}

/******************************************************************************/
inline double Complex::GetImg(void) const
{
	return (m_img);
}

/******************************************************************************/
inline void Complex::SetReal(double new_real)
{
	m_real = new_real;
}        

/******************************************************************************/
inline void Complex::SetImg(double new_img)
{
	m_img = new_img;
} 

/******************************************************************************/
inline std::ostream& operator<<(std::ostream& os, const Complex& cpx)
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
inline std::istream& operator>>(std::istream& is, Complex& cpx)
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

} // ILRD

 
#endif     /* __COMPLEX_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
