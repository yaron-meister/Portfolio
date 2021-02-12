/*****************************************************************************
 * File name:   game.cpp
 * Developer:   Yaron Meister
 * Date:        2021-02-05
 * Description: Source file for class CGame
 *****************************************************************************/

#include <iostream>
#include <conio.h>

#include "game.h"

// Namespaces
using namespace std;

// Macros
static const int KEY_UP(72);
static const int KEY_DOWN(80);
static const int KEY_LEFT(75);
static const int KEY_RIGHT(77);

static const CTimeout::DurationInMilli FREQ_20HZ(CTimeout::DurationInMilli(50));
static const CTimeout::DurationInMilli FREQ_50HZ(CTimeout::DurationInMilli(90));

// Global variables


/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CGame::CGame() : m_keyBoardInput(KB_NONE)
{}

/////////////////////////////////////////////////////////////////////////////
CGame::~CGame()
{
  m_thread.join();
}

/////////////////////////////////////////////////////////////////////////////
void CGame::start()
{
  m_board.generateFood();
}

/////////////////////////////////////////////////////////////////////////////
CGame::EGameState CGame::update()
{
  EGameState gameState(GAME_PLAY);

  getInput();

  if (m_freqTimer.hasExpired())
  {
    CDirection snakeDirectionReq(m_snake.getHead().direction);

    switch (m_keyBoardInput)
    {
    case KB_UP:
      snakeDirectionReq = CDirection::UP;
      break;
    case KB_DOWN:
      snakeDirectionReq = CDirection::DOWN;
      break;
    case KB_RIGHT:
      snakeDirectionReq = CDirection::RIGHT;
      break;
    case KB_LEFT:
      snakeDirectionReq = CDirection::LEFT;
      break;
    case KB_QUIT:
      gameState = GAME_STOP;
      break;
    default:
      break;
    }

    if (CSnake::CRUSH == m_snake.move(snakeDirectionReq) || CSnake::CRUSH == m_board.update(m_snake))
    {
      gameState = GAME_STOP;

      cout << "***** SNAKE CRUSH!!! *****" << endl;
      cout << "*****   GAME OVER    *****" << endl;
    }
    else if (m_board.isFoodEaten())
    {
      m_snake.grow();
      m_board.generateFood();
    }

    m_freqTimer.startNow(CTimeout::DurationInMilli(200));
  }

  return (gameState);
}

/////////////////////////////////////////////////////////////////////////////
const CBoard& CGame::getUpdatedBoard()
{
  return (const_cast<const CBoard&>(m_board));
}

/////////////////////////////////////////////////////////////////////////////
const CSnake& CGame::getUpdatedSnake()
{
  return (const_cast<const CSnake&>(m_snake));
}

/////////////////////////////////////////////////////////////////////////////
void CGame::getInput()
{
  if (_kbhit())
  {
    switch (_getch())
    {
    case 'A':
    case 'a':
      m_keyBoardInput = KB_LEFT;
      break;

    case 'D':
    case 'd':
      m_keyBoardInput = KB_RIGHT;
      break;

    case 'W':
    case 'w':
      m_keyBoardInput = KB_UP;
      break;

    case 'S':
    case 's':
      m_keyBoardInput = KB_DOWN;
      break;

    case 'Q':
    case 'q':
      m_keyBoardInput = KB_QUIT;
      break;

    default:
      m_keyBoardInput = KB_NONE;
      break;
    }
  }
}


