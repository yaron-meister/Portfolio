/*****************************************************************************
 * File name:   game.h
 * Developer:   Yaron Meister
 * Date:        2021-01-29
 * Description: Header file for the Game
 *****************************************************************************/

#ifndef __GAME_H__
#define __GAME_H__

#include <mutex>
#include <thread>

#include "board.h"
#include "snake.h"
#include "timeout.h"
#include "logger.h"

class CGame
{
public:
	enum EGameState
	{
		GAME_STOP,
		GAME_PLAY
	};

	enum EKeyBoardInput
	{
		KB_NONE,
		KB_UP,
		KB_DOWN,
		KB_RIGHT,
		KB_LEFT,
		KB_QUIT
	};

	// CTor
	CGame();

	// DTor
	~CGame();

	void start();
	EGameState update();
	const CBoard& getUpdatedBoard();
	const CSnake& getUpdatedSnake();

private:
	void getInput();

	CSnake m_snake;
	CBoard m_board;
	EKeyBoardInput m_keyBoardInput;
	CTimeout m_freqTimer;

	Logger* m_logger;
	
	std::thread m_thread;
	std::mutex m_mutex;
};




#endif // __GAME_H__