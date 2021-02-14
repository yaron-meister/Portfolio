/*****************************************************************************
* File name:   color.cpp
* Developer:   Yaron
* Date:        2021-02-14 11:04:53
* Description: Source file for class 'CColor'
*****************************************************************************/

#include "color.h"

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CColor::CColor(unsigned char r, unsigned char g, unsigned char b) :
  m_r(r), m_g(g), m_b(b)
{}

/********************                                      ********************/
unsigned char CColor::GetR() const
{
  return (m_r);
}

/********************                                      ********************/
unsigned char CColor::GetG() const
{
  return (m_g);
}

/********************                                      ********************/
unsigned char CColor::GetB() const
{
  return (m_b);
}

/********************                                      ********************/
void CColor::SetR(unsigned char r)
{
  m_r = r;
}

/********************                                      ********************/
void CColor::SetG(unsigned char g)
{
  m_g = g;
}

/********************                                      ********************/
void CColor::SetB(unsigned char b)
{
  m_b = b;
}
