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

class CSnake
{
public:
	enum ECrushStatus
	{
		NO_CRUSH,
		CRUSH
	};

	struct SHead
	{
		// CTor
		SHead(CDirection startDirection = CDirection::RIGHT, CPos startPos = (1, 1)) :
					direction(startDirection), position(startPos) {}

		CDirection direction;
		CPos position;
	};

	// CTor
	CSnake(CPos startPos = (1,1), 
				CDirection startDir = CDirection::RIGHT,
				char headSymbol = '0', 
				char bodySymbol = '=');

	void grow();
	ECrushStatus move(CDirection reqDirection);
	SHead& getHead() const;
	std::list<CPos>& getBody() const;
	char getHeadSymbol() const;
	char getBodySymbol() const;

private:
	CPos addLink(CPos where, CDirection direction, bool isBody = true);

	SHead m_head;
	std::list<CPos> m_body;
	char m_headSymbol;
	char m_bodySymbol;
	bool m_grow;
};


#endif // __SNAKE_H__