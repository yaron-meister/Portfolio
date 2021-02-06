/*****************************************************************************
 * File name:   cell.h
 * Developer:   Yaron Meister
 * Date:        2021-01-29
 * Description: Header file for the class 'CCell'
 *****************************************************************************/

#ifndef __CELL_H__
#define __CELL_H__

#include "position.hpp"

class CCell
{
public:
	enum EContent
	{
		NONE,
		SNAKE_HEAD,
		SNAKE_LINK,
		FOOD,
		INVALID
	};

	// CTor
	CCell(CPos position = (0,0), EContent content = NONE) : 
		m_position(position), m_content(content){}

	inline CPos getPosition() const;
	inline EContent getContent() const;
	inline void setPosition(CPos position);
	inline void setContent(EContent content);

private:
	CPos m_position;
	EContent m_content;
};

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
inline CPos CCell::getPosition() const
{
	return (m_position);
}

/////////////////////////////////////////////////////////////////////////////
inline CCell::EContent CCell::getContent() const
{
	return (m_content);
}

/////////////////////////////////////////////////////////////////////////////
inline void CCell::setPosition(CPos position)
{
	m_position = position;
}

/////////////////////////////////////////////////////////////////////////////
inline void CCell::setContent(CCell::EContent content)
{
	m_content = content;
}

#endif // __CELL_H__