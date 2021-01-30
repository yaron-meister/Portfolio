/*****************************************************************************
 * File name:   position.cpp
 * Developer:   Yaron Meister
 * Date:        2020-01-29
 * Description: Source file for class 'CPos'
 *****************************************************************************/

#include "position.hpp"

 // Namespaces

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
