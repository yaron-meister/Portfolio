/*****************************************************************************
* File name:   direction.h
* Developer:   Yaron
* Date:        2020-01-29 11:04:53
* Description: Header file for class 'CDirection'
*****************************************************************************/

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

class CDirection
{
public:
	enum EDirection
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// CTor
	CDirection(EDirection direction);

	EDirection getDirection();
	EDirection getOppositeDirection();
	bool isOppositeDir(CDirection other);

private:
	EDirection m_direction;
};

#endif // __DIRECTION_H__ 

