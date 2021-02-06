/*****************************************************************************
 * File name:   display.h
 * Developer:   Yaron Meister
 * Date:        2021-01-23 
 * Description: Header file for the displayer
 *****************************************************************************/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "board.h"
#include "snake.h"

class CDisplay
{
public:
  static const unsigned short NUM_OF_ROWS = 24;
  static const unsigned short NUM_OF_COLUMNS = 105;

  // CTor
  CDisplay();

	void welcomeGame();
	void updateScreen(const CBoard& updatedBoard, const CSnake& updatedSnake);
  void displayScreen();
	void clearScreen();

private:
  char m_dispMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS];
};




#endif