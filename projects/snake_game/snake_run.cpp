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


/*  Global/Static variables  */


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  int retVal(SUCCESS);
  CTimeout displayFreqTimer;

  CGame* gameModule = new (nothrow) CGame();
  CDisplay* displayModule = new (nothrow) CDisplay();

  if (nullptr != gameModule && nullptr != displayModule)
  {
    displayModule->welcomeGame();
    gameModule->start();

    while (CGame::GAME_PLAY == gameModule->update())
    {
      if (displayFreqTimer.hasExpired())
      {
        displayModule->updateScreen(gameModule->getUpdatedBoard(), gameModule->getUpdatedSnake());
        displayModule->displayScreen();

        displayFreqTimer.startNow(CTimeout::DurationInMilli(200));
      }
    }
  }
  else
  {
    cerr << "Initiation Failed - Module = NULL" << endl;
    retVal = FAILURE;
  }

  return (retVal);
}