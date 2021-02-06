/*****************************************************************************
 * File name:   display.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-25
 * Description: Source file for class CDisplay
 *****************************************************************************/

#include <windows.h>
#include <iostream>
#include <string>

#include "display.h"

// Namespaces
using namespace std;

// Macros
static const unsigned short SCREEN_ROW_NUM(100);
static const unsigned int ONE_SECOND(1000);

// Global variables

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CDisplay::CDisplay()
{
  unsigned row(0);
  unsigned column(0);

  for (; row < 2; ++row)
  {
    for (column = 0; column < (NUM_OF_COLUMNS - 1); ++column)
    {
      m_dispMatrix[row][column] = '#';
    }

    m_dispMatrix[row][column] = '\n';
  }

  for (; row < (NUM_OF_ROWS - 2); ++row)
  {
    m_dispMatrix[row][0] = '#';
    m_dispMatrix[row][1] = '#';

    for (column = 2; column < (NUM_OF_COLUMNS - 3); ++column)
    {
      m_dispMatrix[row][column] = ' ';
    }

    m_dispMatrix[row][NUM_OF_COLUMNS - 3] = '#';
    m_dispMatrix[row][NUM_OF_COLUMNS - 2] = '#';
    m_dispMatrix[row][NUM_OF_COLUMNS - 1] = '\n';
  }

  for (; row < NUM_OF_ROWS; ++row)
  {
    for (column = 0; column < (NUM_OF_COLUMNS - 1); ++column)
    {
      m_dispMatrix[row][column] = '#';
    }

    m_dispMatrix[row][column] = '\n';
  }
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::welcomeGame()
{
  clearScreen();

  printf("****************************************************************************************************\n");
  printf("****************************************************************************************************\n");
  printf("**                                                                                                **\n");
  printf("**                                                                                                **\n");
  printf("**                                                                                                **\n");
  printf("**               |||       ||          ||            ||           ||    ||  ||||||||||||          **\n");
  printf("**             ||   ||     ||||        ||           ||||          ||   ||   ||                    **\n");
  printf("**            ||     ||    || ||       ||          ||  ||         ||  ||    ||                    **\n");
  printf("**            ||           ||  ||      ||         ||    ||        || ||     ||                    **\n");
  printf("**             ||          ||   ||     ||        ||      ||       ||||      ||                    **\n");
  printf("**              ||         ||    ||    ||       ||        ||      ||||      ||||||||||            **\n");
  printf("**               ||        ||     ||   ||      ||||||||||||||     || ||     ||                    **\n");
  printf("**                ||       ||      ||  ||     ||            ||    ||  ||    ||                    **\n");
  printf("**            ||    ||     ||       || ||    ||              ||   ||   ||   ||                    **\n");
  printf("**             ||   ||     ||        ||||   ||                ||  ||    ||  ||                    **\n");
  printf("**               |||       ||          ||  ||                  || ||     || ||||||||||||          **\n");
  printf("**                                                                                                **\n");
  printf("**                                                                                                **\n");
  printf("****************************************************************************************************\n");
  printf("****************************************************************************************************\n");

  Sleep(ONE_SECOND);
  clearScreen();

  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                               ||||                                                **\n");
  printf("**                                             ||| |||                                               **\n");
  printf("**                                            |||   |||                                              **\n");
  printf("**                                           ||      ||                                              **\n");
  printf("**                                                  |||                                              **\n");
  printf("**                                                 |||                                               **\n");
  printf("**                                             ||||||                                                **\n");
  printf("**                                                 |||                                               **\n");
  printf("**                                                  |||                                              **\n");
  printf("**                                           ||      ||                                              **\n");
  printf("**                                            |||   |||                                              **\n");
  printf("**                                             ||| |||                                               **\n");
  printf("**                                               ||||                                                **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");

  Sleep(ONE_SECOND);
  clearScreen();

  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                               ||||                                                **\n");
  printf("**                                             ||| |||                                               **\n");
  printf("**                                            |||   |||                                              **\n");
  printf("**                                           ||      ||                                              **\n");
  printf("**                                                  |||                                              **\n");
  printf("**                                                 |||                                               **\n");
  printf("**                                                |||                                                **\n");
  printf("**                                               |||                                                 **\n");
  printf("**                                              |||                                                  **\n");
  printf("**                                             |||                                                   **\n");
  printf("**                                            |||                                                    **\n");
  printf("**                                           |||||||||||                                             **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");

  Sleep(ONE_SECOND);
  clearScreen();

  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                |||                                                **\n");
  printf("**                                               ||||                                                **\n");
  printf("**                                              || ||                                                **\n");
  printf("**                                             ||  ||                                                **\n"); 
  printf("**                                            ||   ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                 ||                                                **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::updateScreen(const CBoard& updatedBoard, const CSnake& updatedSnake)
{
  size_t boardRowsNum(updatedBoard.getNumOfRows());
  size_t boardColumnsNum(updatedBoard.getNumOfColumns());
  char snakeHeadSymbol(updatedSnake.getHeadSymbol());
  char snakeBodySymbol(updatedSnake.getBodySymbol());
  char symbol;
  size_t rowsOffset((NUM_OF_ROWS - boardRowsNum) / 2);
  size_t columnsOffset((NUM_OF_COLUMNS - boardColumnsNum) / 2);

  if (boardRowsNum <= NUM_OF_ROWS && boardColumnsNum <= NUM_OF_COLUMNS)
  {
    for (unsigned row(0); row < boardRowsNum; ++row)
    {
      for (unsigned column(0); column < boardColumnsNum; ++column)
      {
        CCell currentCell(updatedBoard.getCell(CPos(column, row)));

        switch (currentCell.getContent())
        {
        case CCell::NONE:
          symbol = ' ';
          break;
        case CCell::SNAKE_HEAD:
          symbol = snakeHeadSymbol;
          break;
        case CCell::SNAKE_LINK:
          symbol = snakeBodySymbol;
          break;
        case CCell::FOOD:
          symbol = '*';
          break;
        default:
          break;
        }

        m_dispMatrix[row + rowsOffset][column + columnsOffset] = symbol;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::displayScreen()
{
  for (unsigned row(0); row < NUM_OF_ROWS; ++row)
  {
    for (unsigned column(0); column < NUM_OF_COLUMNS; ++column)
    {
      cout << m_dispMatrix[row][column];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::clearScreen()
{
	cout << string(SCREEN_ROW_NUM, '\n');
}

/////////////////////////////////////////////////////////////////////////////


