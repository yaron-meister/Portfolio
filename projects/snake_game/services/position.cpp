/*****************************************************************************
 * File name:   position.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-29
 * Description: Source file for class 'CPos'
 *****************************************************************************/

#include <iostream>
#include <stdexcept>

#include "position.hpp"

// Namespaces
using namespace std;

// Macros

// Global variables

 /////////////////////////////////////////////////////////////////////////////
 //                        Functions's implementations
 /////////////////////////////////////////////////////////////////////////////
CPos::CPos(int x, int y) : m_x(x), m_y(y)
{}

/////////////////////////////////////////////////////////////////////////////
bool CPos::operator==(const CPos& other)
{
	return (m_x == other.m_x && m_y == other.m_y);
}

/////////////////////////////////////////////////////////////////////////////
bool CPos::operator!=(const CPos& other)
{
	return (!operator==(other));
}

/////////////////////////////////////////////////////////////////////////////
const CPos CPos::operator+(const CPos& rhs)
{
  CPos sum(m_x, m_y); // Initialize 'sum' as 'this'

  sum += rhs;

  return (sum);
}

/////////////////////////////////////////////////////////////////////////////
const CPos CPos::operator-(const CPos& rhs)
{
  CPos diff(m_x, m_y); // Initialize 'diff' as 'this'

  diff -= rhs;

  return (diff);
}

/////////////////////////////////////////////////////////////////////////////
CPos& CPos::operator+=(const CPos& pos)
{
  m_x += pos.getX();
  m_y += pos.getY();

  return (*this);
}

/////////////////////////////////////////////////////////////////////////////
CPos& CPos::operator-=(const CPos& pos)
{
  m_x -= pos.getX();
  m_y -= pos.getY();

  return (*this);
}

/////////////////////////////////////////////////////////////////////////////
CPos& CPos::operator*=(int multiplier)
{
  m_x *= multiplier;
  m_y *= multiplier;

  return (*this);
}

/////////////////////////////////////////////////////////////////////////////
CPos& CPos::operator/=(int multiplier)
{
  try 
  {
    m_x /= multiplier;
    m_y /= multiplier;
  }
  catch (runtime_error& e) 
  {
    cout << "Division by ZERO" << endl << e.what();
  }

  return (*this);
}
