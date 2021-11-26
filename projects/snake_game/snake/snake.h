/*****************************************************************************
 * File name:   snake.h
 * Developer:   Yaron Meister
 * Date:        2021-01-29
 * Description: Header file for the class 'CSnake'
 *****************************************************************************/

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <list>

#include "direction.h"
#include "position.hpp"
#include "logger.h"
#include "singleton.hpp"
#include "params.h"

class SnakeParams : public ParamsBase
{
public:

	// CTor
	SnakeParams(CPos startPos = (1, 1), CDirection startDirection = CDirection::RIGHT) : m_startPos(startPos), m_startDirection(startDirection){}

	CPos				m_startPos;
	CDirection	m_startDirection;
};

class CSnake
{
public:
	friend class Singleton<CSnake>;

	enum ECrushStatus
	{
		NO_CRUSH,
		CRUSH
	};

	struct SHead
	{
		// CTor
		SHead(CDirection startDirection, CPos startPos) :
					direction(startDirection), position(startPos) {}

		CDirection direction;
		CPos position;
	};

	void grow();
	ECrushStatus move(CDirection reqDirection);
	SHead& getHead() const;
	std::list<CPos>& getBody() const;

private:
	// CTor
	CSnake();

	CPos addLink(CPos where, CDirection direction, bool isBody = true);

	SHead m_head;
	std::list<CPos> m_body;
	bool m_grow;

	Logger* m_logger;
};


#endif // __SNAKE_H__