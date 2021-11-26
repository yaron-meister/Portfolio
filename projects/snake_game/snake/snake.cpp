/*****************************************************************************
 * File name:   sanke.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-29
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
CSnake::CSnake() :
	m_head(CDirection::RIGHT, (1, 1)), m_grow(false)
	, m_logger(Singleton<Logger>::GetInstance())
{
	addLink(m_head.position, m_head.direction);

	m_logger->write("CSnake: Snake was initiated");
}

/////////////////////////////////////////////////////////////////////////////
void CSnake::grow()
{
	m_grow = true;
}

/////////////////////////////////////////////////////////////////////////////
CSnake::ECrushStatus CSnake::move(CDirection reqDirection)
{
	ECrushStatus crashStatus(NO_CRUSH);

	if (!m_body.empty())
	{
		CDirection direction(reqDirection);

		if (m_head.direction.isOppositeDir(direction))
		{
			direction = m_head.direction;
		}

		m_body.push_front(m_head.position);
		m_head.direction = direction;
		m_head.position = addLink(m_head.position, direction.getOppositeDirection(), false);

		if (m_grow)
		{
			m_grow = false;

			m_logger->write("CSnake: Snake grew");
		}
		else
		{
			m_body.pop_back();
		}

		for (std::list<CPos>::iterator it = m_body.begin(); 
					it != m_body.end() && CRUSH != crashStatus;
					++it)
		{
			if (it->operator==(m_head.position))
			{
				crashStatus = CRUSH;
			}
		}
	}
	else
	{
		cerr << "Body is empty of links" << endl;
		crashStatus = CRUSH;
	}

	m_logger->write("CSnake: Snake moved");

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


