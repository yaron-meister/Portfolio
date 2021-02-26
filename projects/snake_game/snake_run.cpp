/*****************************************************************************
 * File name:   snake_run.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-23 
 * Description: Source file for running the 'main' of the game SNAKE
 *****************************************************************************/

#include <iostream>

#include "game.h"
#include "display.h"
#include "timeout.h"
#include "utils.h"

/* Namespaces */
using namespace std;

/* Forward Declarations    */
int runSnake();
void threadFunc();

/*  Global/Static variables  */
CGame* gameModule(nullptr);
CDisplay* displayModule(nullptr);

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  int retVal(SUCCESS);
  CTimeout displayFreqTimer;

  gameModule = new (nothrow) CGame();
  displayModule = new (nothrow) CDisplay();

  if (nullptr != gameModule && nullptr != displayModule)
  {
    thread displayThread(threadFunc);

    displayModule->welcomeGame();
    gameModule->start();

    while (CGame::GAME_PLAY == gameModule->update())
    {
      if (displayFreqTimer.hasExpired())
      {
        displayModule->updateScreen(gameModule->getUpdatedBoard(), gameModule->getUpdatedSnake());

        displayFreqTimer.startNow(CTimeout::DurationInMilli(200));
      }
    }

    displayModule->stopGraphicalApp();
    displayModule->gameOver();
  }
  else
  {
    cerr << "Initiation Failed - Module = NULL" << endl;
    retVal = FAILURE;
  }

  delete(gameModule);
  gameModule = nullptr;
  delete(displayModule);
  displayModule = nullptr;

  return (retVal);
}

/******************************************************************************/
void threadFunc()
{
  if (nullptr != displayModule)
  {
    displayModule->updateGraphicalApp();
  }
  else
  {
    cerr << "Thread func Failed - Module = NULL" << endl;
  }
}

/******************************************************************************/