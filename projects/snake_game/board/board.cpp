/*****************************************************************************
* File name:   board.cpp
* Developer:   Yaron
* Date:        2020-01-29 11:04:53
* Description: Source file for class 'CBoard'
*****************************************************************************/

#include <iostream>

#include "board.h"

// Namespaces
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CBoard::CBoard()
{
	for (unsigned row(0); row < NUM_OF_ROWS; ++row)
	{
		for (unsigned column(0); column < NUM_OF_COLUMNS; ++column)
		{
			m_board[row][column].setPosition((row, column));
			m_board[row][column].setContent(CCell::NONE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void CBoard::update(const CSnake& snake)
{
	for (std::list<CPos>::iterator it = snake.getBody().begin();
		it != snake.getBody().end();
		++it)
	{
		int xPos = it->getX();
		int yPos = it->getY();

		if (xPos < NUM_OF_ROWS && yPos < NUM_OF_COLUMNS)
		{
			if (CCell::NONE == m_board[xPos][yPos].getContent())
			{
				m_board[xPos][yPos].setContent(CCell::SNAKE_LINK);
			}
		}
		else
		{
			cerr << "CBoard: Position (" << xPos << "," << yPos << ") is not exist" << endl;
		}
	}


}
