/*****************************************************************************
 * File name:   board.h
 * Developer:   Yaron Meister
 * Date:        2020-01-23
 * Description: Header file for the class 'CBoard'
 *****************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.hpp"
#include "snake.h"

class CBoard
{
public:
	static const unsigned int NUM_OF_ROWS = 100;
	static const unsigned int NUM_OF_COLUMNS = 100;

	// CTor
	CBoard();

	void update(const CSnake& snake);
	void generateFood();
	
private:
	CCell m_board[NUM_OF_ROWS][NUM_OF_COLUMNS];
};

#endif // __BOARD_H__