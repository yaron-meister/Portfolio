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
#include "graphical.h"
#include "shapes.h"

class CDisplay
{
public:
  static const unsigned short NUM_OF_ROWS = 84;
  static const unsigned short NUM_OF_COLUMNS = 125;

  static const unsigned short POS_TO_PIXEL = 7;

  // CTor
  CDisplay();

	void welcomeGame();
  void gameOver();
	void updateScreen(const CBoard& updatedBoard, const CSnake& updatedSnake);
	void clearScreen();

  void updateGraphicalApp();
  void stopGraphicalApp();
  static bool runGraphicalApp(CSuperGroup* superGroup);

private:
  struct SFrame
  {
    CPos center;
    int width;
    int height;
    CPos start;
  };

  static bool m_stopGraphicalApp;
  static std::mutex m_mutex;
  static size_t m_prevSnakeBodySize;
  static CSnake m_snake;
  static SFrame m_frame;

  // Shapes
  static CCircle m_food;
  static CSquare m_snakeHead;
  static CGroup m_snakeBodyGroup;

  // Shapes positions
  static CPos m_snakeHeadPos;
  static CPos m_foodPos;
  static CPos m_prevSnakeHeadPos;
  

};




#endif