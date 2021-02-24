/*****************************************************************************
* File name:   board.cpp
* Developer:   Yaron
* Date:        2021-01-29 11:04:53
* Description: Source file for class 'CBoard'
*****************************************************************************/

#include <iostream>

#include "board.h"
#include "singleton.hpp"

// Namespaces
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CBoard::CBoard() : m_snakePrevLastLink(0, 0), m_isFoodEaten(false), m_logger(Singleton<Logger>::GetInstance())
{
	for (unsigned row(0); row < NUM_OF_ROWS; ++row)
	{
		for (unsigned column(0); column < NUM_OF_COLUMNS; ++column)
		{
			m_cells[row][column].setPosition((column, row));
			m_cells[row][column].setContent(CCell::NONE);
		}
	}

	m_logger->write("CBoard: Board was initiated");
}

/////////////////////////////////////////////////////////////////////////////
CSnake::ECrushStatus CBoard::update(const CSnake& snake)
{
	const CSnake::SHead& snakeHead(snake.getHead());
	bool isWallCrush(false);
	CSnake::ECrushStatus crashStatus(CSnake::NO_CRUSH);

	for (std::list<CPos>::iterator it = snake.getBody().begin();
		it != snake.getBody().end();
		++it)
	{
		isWallCrush |= (FAILURE == updateCell(CPos(it->getX(), it->getY()), CCell::SNAKE_LINK));
	}

	isWallCrush |= (FAILURE == updateCell(snakeHead.position, CCell::SNAKE_HEAD));

	CPos snakeLastLink(snake.getBody().back());
	if (m_snakePrevLastLink != snakeLastLink)
	{
		isWallCrush |= (FAILURE == updateCell(m_snakePrevLastLink, CCell::NONE));
		m_snakePrevLastLink = snakeLastLink;
	}

	if (isWallCrush)
	{
		crashStatus = CSnake::CRUSH;

		m_logger->write("CBoard: Wall crush");
	}

	return (crashStatus);
}

/////////////////////////////////////////////////////////////////////////////
void CBoard::generateFood()
{
	bool foodGenerated(false);
	unsigned int newX;
	unsigned int newY;

	while (!foodGenerated)
	{
		newX = static_cast<unsigned int>(rand() % NUM_OF_COLUMNS);
		newY = static_cast<unsigned int>(rand() % NUM_OF_ROWS);

		if (CCell::NONE == m_cells[newY][newX].getContent())
		{
			m_cells[newY][newX].setContent(CCell::FOOD);
			foodGenerated = true;
			m_isFoodEaten = false;
			m_foodPos.setX(newX);
			m_foodPos.setY(newY);
			m_logger->write("CBoard: Food was generated");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
bool CBoard::isFoodEaten() const
{
	return (m_isFoodEaten);
}

/////////////////////////////////////////////////////////////////////////////
CPos CBoard::getFoodPos() const
{
	return (m_foodPos);
}

/////////////////////////////////////////////////////////////////////////////
CCell CBoard::getCell(CPos position) const
{
	CCell cell(CPos(-1, -1), CCell::INVALID);

	if (isPositionValid(position))
	{
		cell = m_cells[position.getY()][position.getX()];
	}

	return (cell);
}

/////////////////////////////////////////////////////////////////////////////
size_t CBoard::getNumOfRows() const
{
	return (ARRAY_SIZE(m_cells));
}

/////////////////////////////////////////////////////////////////////////////
size_t CBoard::getNumOfColumns() const
{
	return (ARRAY_SIZE(m_cells[0]));
}

/////////////////////////////////////////////////////////////////////////////
EStatus CBoard::updateCell(CPos updatedPosition, CCell::EContent updatedContent)
{
	EStatus status(SUCCESS);
	int xPos(updatedPosition.getX());
	int yPos(updatedPosition.getY());

	if (isPositionValid(updatedPosition))
	{
		CCell::EContent cellContent(m_cells[yPos][xPos].getContent());

		if (CCell::INVALID != cellContent)
		{
			if (CCell::FOOD == cellContent && CCell::SNAKE_HEAD == updatedContent)
			{
				m_isFoodEaten = true;
			}

			m_cells[yPos][xPos].setContent(updatedContent);
		}
	}
	else
	{
		cerr << "CBoard: Position (" << xPos << "," << yPos << ") is a wall" << endl;
		status = FAILURE;
		m_logger->write("CBoard: Crush in a wall");
	}

	return (status);
}

/////////////////////////////////////////////////////////////////////////////
bool CBoard::isPositionValid(CPos position) const
{
	return (position.getX() >= 0 &&
		position.getX() < NUM_OF_COLUMNS &&
		position.getY() >= 0 &&
		position.getY() < NUM_OF_ROWS);
}
