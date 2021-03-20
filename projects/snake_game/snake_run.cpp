/*****************************************************************************
 * File name:   snake_run.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-23 
 * Description: Source file for running the 'main' of the game SNAKE
 *****************************************************************************/

#include <iostream>
#include <new>

#include "game.h"
#include "display.h"
#include "timeout.h"
#include "utils.h"

/* Namespaces */
using namespace std;

/* Forward Declarations    */
class CSnakeGame
{
public:
  // CTor
  CSnakeGame();

  //DTor
  ~CSnakeGame();

  EStatus run();

private:
  void runGraphics();

  CGame* m_gameModule;
  CDisplay* m_displayModule;
  thread m_thread;
};

/*  Global/Static variables  */

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  CSnakeGame snakeGame;

  return (snakeGame.run());
}

/******************************************************************************/
void CSnakeGame::runGraphics()
{
  if (nullptr != m_displayModule)
  {
    m_displayModule->runGraphicalApp();
  }
  else
  {
    cerr << "Thread func Failed - Module = NULL" << endl;
  }
}

/******************************************************************************/
CSnakeGame::CSnakeGame() : m_gameModule(new (nothrow) CGame()), m_displayModule(new (nothrow) CDisplay())
{}

/******************************************************************************/
CSnakeGame::~CSnakeGame()
{
  m_thread.join();

  delete(m_gameModule);
  m_gameModule = nullptr;
  delete(m_displayModule);
  m_displayModule = nullptr;
}

/******************************************************************************/
EStatus CSnakeGame::run()
{
  EStatus retVal(SUCCESS);
  CTimeout displayFreqTimer;

  if (nullptr != m_gameModule && nullptr != m_displayModule)
  {
    m_thread = thread (&CSnakeGame::runGraphics, this);

    m_displayModule->welcomeGame();
    m_gameModule->start();

    while (CGame::GAME_PLAY == m_gameModule->update())
    {
      if (displayFreqTimer.hasExpired())
      {
        m_displayModule->updateScreen(m_gameModule->getUpdatedBoard(), m_gameModule->getUpdatedSnake());

        displayFreqTimer.startNow(CTimeout::DurationInMilli(100));
      }
    }

    m_displayModule->stopGraphicalApp();
    m_displayModule->gameOver();
  }
  else
  {
    cerr << "Initiation Failed - Module = NULL" << endl;
    retVal = FAILURE;
  }

  return (retVal);
}