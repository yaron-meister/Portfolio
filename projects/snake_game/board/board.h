/*****************************************************************************
 * File name:   board.h
 * Developer:   Yaron Meister
 * Date:        2021-01-23
 * Description: Header file for the class 'CBoard'
 *****************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.hpp"
#include "snake.h"
#include "logger.h"
#include "utils.h"

class CBoard
{
public:
	static const unsigned int NUM_OF_ROWS = 20;
	static const unsigned int NUM_OF_COLUMNS = 100;

	// CTor
	CBoard();

	CSnake::ECrushStatus update(const CSnake& snake);
	void generateFood();
	bool isFood(CPos position) const;
	CCell getCell(CPos position) const;
	size_t getNumOfColumns() const;
	size_t getNumOfRows() const;

private:
	EStatus updateCell(CPos updatedPosition, CCell::EContent updatedContent);
	bool isPositionValid(CPos position) const;

	CCell m_cells[NUM_OF_ROWS][NUM_OF_COLUMNS];
	CPos m_snakePrevLastLink;
	Logger* m_logger;
};

#endif // __BOARD_H__