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
  m_thread = thread(&CGame::getInput, this);
  m_board.generateFood();
}

/////////////////////////////////////////////////////////////////////////////
CGame::EGameState CGame::update()
{
  EGameState gameState(GAME_PLAY);
  CDirection snakeDirectionReq(m_snake.getHead().direction);

  m_mutex.lock();
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
  m_mutex.unlock();

  if (CSnake::CRUSH == m_snake.move(snakeDirectionReq) || CSnake::CRUSH == m_board.update(m_snake))
  {
    gameState = GAME_STOP;

    cout << "***** SNAKE CRUSH!!! *****" << endl;
    cout << "*****   GAME OVER    *****" << endl;
  }
  else if (m_board.isFood(m_snake.getHead().position))
  {
    m_snake.grow();
    m_board.generateFood();
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
  int input(0);
  bool quit(false);

    while (!quit)
    {
      input = 0;

      m_mutex.lock();
      switch (input = _getch())
      {
      case KEY_UP:
        m_keyBoardInput = KB_UP;
        break;
      case KEY_DOWN:
        m_keyBoardInput = KB_DOWN;
        break;
      case KEY_LEFT:
        m_keyBoardInput = KB_LEFT;
        break;
      case KEY_RIGHT:
        m_keyBoardInput = KB_RIGHT;
        break;
      case 'Q':
      case 'q':
        m_keyBoardInput = KB_QUIT;
        quit = true;
        break;
      default:
        break;
      }
      m_mutex.unlock();
    }
}


