/*****************************************************************************
 * File name:   snake_run.cpp
 * Developer:   Yaron Meister
 * Date:        2021-01-23 
 * Description: Source file for running the 'main' of the game SNAKE
 *****************************************************************************/

#include <iostream>

#include "game.h"
#include "display.h"
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

  CGame* gameModule = new (nothrow) CGame();
  CDisplay* displayModule = new (nothrow) CDisplay();

  if (nullptr != gameModule && nullptr != displayModule)
  {
    displayModule->welcomeGame();
    gameModule->start();

    if (CGame::GAME_PLAY == gameModule->update())
    {
      displayModule->updateScreen(gameModule->getUpdatedBoard(), gameModule->getUpdatedSnake());
      displayModule->displayScreen();
    }
  }
  else
  {
    cerr << "Initiation Failed - Module = NULL" << endl;
    retVal = FAILURE;
  }

  return (retVal);
}