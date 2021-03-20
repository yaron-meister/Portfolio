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
CCircle CDisplay::m_food(CColor(90, 0, 0), CPos(0, 0), 4);
CPos CDisplay::m_foodPos(0, 0);
CSquare CDisplay::m_snakeHead(CColor(0, 90, 0), CPos(0,0), 7);
CPos CDisplay::m_snakeHeadPos(0, 0);
CPos CDisplay::m_prevSnakeHeadPos(0, 0);
CSnake CDisplay::m_snake;
CDisplay::SFrame CDisplay::m_frame;
CGroup CDisplay::m_snakeBodyGroup;
size_t CDisplay::m_prevSnakeBodySize(0);

// Forward declarations

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CDisplay::CDisplay()
{
  m_frame.center = CPos((CRenderer::SCREEN_WIDTH / 2), (CRenderer::SCREEN_HEIGHT / 2));
  m_frame.width = (CBoard::NUM_OF_COLUMNS + 1) * POS_TO_PIXEL; // The contour is one line offset outside
  m_frame.height = (CBoard::NUM_OF_ROWS + 1) * POS_TO_PIXEL; // The contour is one line offset outside
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
void CDisplay::runGraphicalApp()
{
  CColor frameColor(90, 90, 90);
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
  superGroup.addGroup(&m_snakeBodyGroup);

  CGraphicalApp app;
  app.endlessLoop(&superGroup, CDisplay::updateGraphicalApp);
}

/////////////////////////////////////////////////////////////////////////////
void CDisplay::stopGraphicalApp()
{
  m_stopGraphicalApp = true;
}

/////////////////////////////////////////////////////////////////////////////
bool CDisplay::updateGraphicalApp(CSuperGroup* composite)
{
  static_cast<void>(composite);

  CPos foodUpdatedCenter;
  CPos snakeHeadUpdatedCenter;
  size_t snakeBodySize;
  
  m_mutex.lock();

  snakeBodySize = m_snake.getBody().size();
  // The start position of the board is the start of the frame + offset of one position
  foodUpdatedCenter = 
    CPos(m_frame.start.getX() + POS_TO_PIXEL + (m_foodPos.getX() * POS_TO_PIXEL), m_frame.start.getY() + POS_TO_PIXEL + (m_foodPos.getY() * POS_TO_PIXEL));
  snakeHeadUpdatedCenter =
    CPos(m_frame.start.getX() + POS_TO_PIXEL + (m_snake.getHead().position.getX() * POS_TO_PIXEL), 
      m_frame.start.getY() + POS_TO_PIXEL + (m_snake.getHead().position.getY() * POS_TO_PIXEL));

  m_mutex.unlock();

  if (snakeHeadUpdatedCenter != m_prevSnakeHeadPos)
  {
    CSquare* snakeNewBodyLink(new CSquare(m_snakeHead));

    snakeNewBodyLink->setColor(CColor(0, 0, 90));

    m_snakeBodyGroup.addMember(snakeNewBodyLink);
    if (snakeBodySize <= m_prevSnakeBodySize)
    {
      m_snakeBodyGroup.removeOldestMember();
    }

    m_prevSnakeBodySize = snakeBodySize;
    m_prevSnakeHeadPos = snakeHeadUpdatedCenter;
  }

  m_food.setCenter(foodUpdatedCenter);
  m_snakeHead.setCenter(snakeHeadUpdatedCenter);

  return (!m_stopGraphicalApp);
}

