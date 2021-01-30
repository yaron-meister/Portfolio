/*****************************************************************************
 * File name:   sanke.cpp
 * Developer:   Yaron Meister
 * Date:        2020-01-29
 * Description: Source file for class CSnake
 *****************************************************************************/

#include <iostream>

#include "snake.h"

// Namespaces
using namespace std;

// Macros

// Global variables


/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
CSnake::CSnake(CPos startPos, CDirection startDir,	char headSymbol, char bodySymbol) :
	m_head(startDir, startPos), m_headSymbol(headSymbol), m_bodySymbol(bodySymbol)
{
	addLink(m_head.position, startDir);
}

/////////////////////////////////////////////////////////////////////////////
void CSnake::grow()
{
	m_grow = true;
}

/////////////////////////////////////////////////////////////////////////////
CSnake::ECrashStatus CSnake::move(CDirection reqDirection)
{
	ECrashStatus crashStatus(NO_CRASH);

	if (!m_body.empty())
	{
		CDirection direction(reqDirection);

		if (m_head.direction.isOppositeDir(direction))
		{
			direction = m_head.direction;
		}

		m_body.push_front(m_head.position);
		m_head.position = addLink(m_head.position, m_head.direction.getOppositeDirection(), false);

		if (m_grow)
		{
			m_grow = false;
		}
		else
		{
			m_body.pop_back();
		}

		for (std::list<CPos>::iterator it = m_body.begin(); 
					it != m_body.end() && CRASH != crashStatus;
					++it)
		{
			if (it->operator==(m_head.position))
			{
				crashStatus = CRASH;
			}
		}
	}
	else
	{
		cerr << "Body is empty of links" << endl;
		crashStatus = CRASH;
	}

	return (crashStatus);
}

/////////////////////////////////////////////////////////////////////////////
CSnake::SHead& CSnake::getHead() const
{
	return (const_cast<SHead&>(m_head));
}

/////////////////////////////////////////////////////////////////////////////
std::list<CPos>& CSnake::getBody() const
{
	return (const_cast<std::list<CPos>&>(m_body));
}

/////////////////////////////////////////////////////////////////////////////
CPos CSnake::addLink(CPos where, CDirection direction, bool isBody)
{
	CPos newPos;

	switch (direction.getDirection())
	{
	case CDirection::UP:
		newPos.setX(where.getX());
		newPos.setY(where.getY() + 1);
		break;
	case CDirection::DOWN:
		newPos.setX(where.getX());
		newPos.setY(where.getY() - 1);
		break;
	case CDirection::LEFT:
		newPos.setX(where.getX() + 1);
		newPos.setY(where.getY());
		break;
	case CDirection::RIGHT:
	default:
		newPos.setX(where.getX() - 1);
		newPos.setY(where.getY());
		break;
	}

	if (isBody)
	{
		m_body.push_front(newPos);
	}

	return (newPos);
}


