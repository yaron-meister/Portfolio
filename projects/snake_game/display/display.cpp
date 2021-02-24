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

// Forward declarations
void callback(CComposite* supergroup);

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
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
  CPos frameCenterPoint(400, 300);

  CRectangle frame1(frameColor, frameCenterPoint, 410, 610, false);
  CRectangle frame2(frameColor, frameCenterPoint, 412, 612, false);
  CRectangle frame3(frameColor, frameCenterPoint, 414, 614, false);
  CRectangle frame4(frameColor, frameCenterPoint, 416, 616, false);
  CRectangle frame5(frameColor, frameCenterPoint, 418, 618, false);

  CGroup group;
  CGraphicalApp app;

  group.addMember(&frame1);
  group.addMember(&frame2);
  group.addMember(&frame3);
  group.addMember(&frame4);
  group.addMember(&frame5);

  group.addMember(&m_food);
  group.addMember(&m_snakeHead);

  app.endlessLoop(&group, CDisplay::isRunGraphicalApp);
}

/////////////////////////////////////////////////////////////////////////////
void callback(CComposite* supergroup)
{
  
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::stopGraphicalApp()
{
  m_stopGraphicalApp = true;
}

/////////////////////////////////////////////////////////////////////////////
bool CDisplay::isRunGraphicalApp(CComposite* composite)
{
  static_cast<void>(composite);

  m_mutex.lock();
  m_food.setCenter(CPos(400 - 305 + (m_foodPos.getX() * 5), 300 - 205 + (m_foodPos.getY() * 5)));
  m_snakeHead.setCenter(CPos(95 + (m_snake.getHead().position.getX() * 5), 95 + (m_snake.getHead().position.getY() * 5)));
  m_mutex.unlock();

  return (!m_stopGraphicalApp);
}

