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
bool CDisplay::m_stopGraphicalApp(false);
mutex CDisplay::m_mutex;
CCircle CDisplay::m_food(CColor(90, 0, 0), CPos(0, 0), 3);
CPos CDisplay::m_foodPos(0, 0);
CSquare CDisplay::m_snakeHead(CColor(0, 90, 0), CPos(0,0), 5);
CPos CDisplay::m_snakeHeadPos(0, 0);
CSnake CDisplay::m_snake;
CDisplay::SFrame CDisplay::m_frame;

// Forward declarations

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CDisplay::CDisplay()
{
  m_frame.center = CPos((CRenderer::SCREEN_WIDTH / 2), (CRenderer::SCREEN_HEIGHT / 2));
  m_frame.width = (CBoard::NUM_OF_COLUMNS + 2) * POS_TO_PIXEL; // The 2 because the contour is one line offset outside
  m_frame.height = (CBoard::NUM_OF_ROWS + 2) * POS_TO_PIXEL; // The 2 because the contour is one line offset outside
  m_frame.start = 
    CPos(m_frame.center.getX() - (m_frame.width / 2), m_frame.center.getY() - (m_frame.height / 2));
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

  Sleep(ONE_SECOND);
  clearScreen();

  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                ||||||       ||                    ||||            ||          ||                  **\n");
  printf("**                ||    |||    ||                   ||  ||            ||        ||                   **\n");
  printf("**                ||      ||   ||                  ||    ||            ||      ||                    **\n");
  printf("**                ||      ||   ||                 ||      ||            ||    ||                     **\n");
  printf("**                ||      ||   ||                ||        ||            ||  ||                      **\n");
  printf("**                ||    |||    ||               ||          ||            ||||                       **\n");
  printf("**                ||||||       ||              ||||||||||||||||            ||                        **\n");
  printf("**                ||           ||             ||              ||           ||                        **\n");
  printf("**                ||           ||            ||                ||          ||                        **\n");
  printf("**                ||           ||           ||                  ||         ||                        **\n");
  printf("**                ||           ||||||||||  ||                    ||        ||                        **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
}



/////////////////////////////////////////////////////////////////////////////
void CDisplay::gameOver()
{
  clearScreen();

  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
  printf("**                                                                                                   **\n");
  printf("**                     ||||           |||       ||            ||  |||||||||                          **\n");
  printf("**                   ||    ||        || ||      ||||        ||||  ||                                 **\n");
  printf("**                  ||      ||      ||   ||     || ||      || ||  ||                                 **\n");
  printf("**                 ||              ||     ||    ||  ||    ||  ||  |||||||                            **\n");
  printf("**                 ||   |||||     |||||||||||   ||   ||  ||   ||  ||                                 **\n");
  printf("**                  ||     ||    ||         ||  ||    ||||    ||  ||                                 **\n");
  printf("**                    |||||     ||           || ||     ||     ||  |||||||||                          **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("**                       ||||       ||           ||   |||||||||   ||||||                             **\n");
  printf("**                     ||    ||      ||         ||    ||          ||   ||                            **\n");
  printf("**                    ||      ||      ||       ||     ||          ||    ||                           **\n");
  printf("**                  ||          ||     ||     ||      |||||||     ||   ||                            **\n");
  printf("**                    ||      ||         ||  ||       ||          |||||                              **\n");
  printf("**                     ||    ||           ||||        ||          ||   ||                            **\n");
  printf("**                       ||||              ||         |||||||||   ||    ||                           **\n");
  printf("**                                                                                                   **\n");
  printf("**                                                                                                   **\n");
  printf("*******************************************************************************************************\n");
  printf("*******************************************************************************************************\n");
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::updateScreen(const CBoard& updatedBoard, const CSnake& updatedSnake)
{
  m_mutex.lock();
  m_foodPos = updatedBoard.getFoodPos();
  m_snake = updatedSnake;
  m_mutex.unlock();
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::clearScreen()
{
	cout << string(SCREEN_ROW_NUM, '\n');
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::updateGraphicalApp()
{
  CColor frameColor(0, 90, 0);
  CPos frameCenterPoint((CRenderer::SCREEN_WIDTH / 2), (CRenderer::SCREEN_HEIGHT / 2));

  CRectangle frame1(frameColor, frameCenterPoint, m_frame.height, m_frame.width, false);
  CRectangle frame2(frameColor, frameCenterPoint, m_frame.height + 2, m_frame.width + 2, false);
  CRectangle frame3(frameColor, frameCenterPoint, m_frame.height + 4, m_frame.width + 4, false);
  CRectangle frame4(frameColor, frameCenterPoint, m_frame.height + 6, m_frame.width + 6, false);
  CRectangle frame5(frameColor, frameCenterPoint, m_frame.height + 8, m_frame.width + 8, false);

  CGroup frameGroup;
  frameGroup.addMember(&frame1);
  frameGroup.addMember(&frame2);
  frameGroup.addMember(&frame3);
  frameGroup.addMember(&frame4);
  frameGroup.addMember(&frame5);

  CGroup foodGroup;
  foodGroup.addMember(&m_food);
  
  CGroup snakeHeadGroup;
  snakeHeadGroup.addMember(&m_snakeHead);
  
  CSuperGroup superGroup;
  superGroup.addGroup(&frameGroup);
  superGroup.addGroup(&foodGroup);
  superGroup.addGroup(&snakeHeadGroup);

  CGraphicalApp app;
  app.endlessLoop(&superGroup, CDisplay::isRunGraphicalApp);
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::stopGraphicalApp()
{
  m_stopGraphicalApp = true;
}

/////////////////////////////////////////////////////////////////////////////
bool CDisplay::isRunGraphicalApp(CSuperGroup* composite)
{
  static_cast<void>(composite);

  CPos foodUpdatedCenter = 
    CPos(m_frame.start.getX() + (m_foodPos.getX() * POS_TO_PIXEL), m_frame.start.getY() + (m_foodPos.getY() * POS_TO_PIXEL));
  CPos snakeHeadUpdatedCenter =
    CPos(m_frame.start.getX() + (m_snake.getHead().position.getX() * POS_TO_PIXEL), 
      m_frame.start.getY() + (m_snake.getHead().position.getY() * POS_TO_PIXEL));

  m_mutex.lock();
  m_food.setCenter(foodUpdatedCenter);
  m_snakeHead.setCenter(snakeHeadUpdatedCenter);
  m_mutex.unlock();

  return (!m_stopGraphicalApp);
}

