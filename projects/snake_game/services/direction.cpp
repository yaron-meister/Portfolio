/*****************************************************************************
* File name:   direction.cpp
* Developer:   Yaron
* Date:        2021-01-29 11:04:53
* Description: Source file for class 'CDirection'
*****************************************************************************/

#include "direction.h"

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CDirection::CDirection(EDirection direction) : m_direction(direction)
{}

/////////////////////////////////////////////////////////////////////////////
CDirection::EDirection CDirection::getDirection()
{
	return (m_direction);
}

/////////////////////////////////////////////////////////////////////////////
CDirection::EDirection CDirection::getOppositeDirection()
{
	EDirection oppositeDirection(UP);

	switch (m_direction)
	{
	case UP:
		oppositeDirection = DOWN;
		break;
	case RIGHT:
		oppositeDirection = LEFT;
		break;
	case DOWN:
		oppositeDirection = UP;
		break;
	case LEFT:
		oppositeDirection = RIGHT;
		break;
	default:
			break;
	}

	return (oppositeDirection);
}

/////////////////////////////////////////////////////////////////////////////
bool CDirection::isOppositeDir(CDirection other)
{
	return ((UP			== m_direction	&& DOWN		== other.m_direction)		||
					(DOWN		== m_direction	&& UP			== other.m_direction)		||
					(RIGHT	== m_direction	&& LEFT		== other.m_direction)		||
					(LEFT		== m_direction	&& RIGHT	== other.m_direction));
}
