/*****************************************************************************
 * File name:   game.h
 * Developer:   Yaron Meister
 * Date:        2020-01-29
 * Description: Header file for the Game
 *****************************************************************************/
#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

class CGame
{
public:
	enum EGameState
	{
		GAME_STOP,
		GAME_PLAY
	};

	EGameState update();
	const CBoard& getUpdatedBoard();

private:

};




#endif // __GAME_H__