/*****************************************************************************
 * File name:   display.h
 * Developer:   Yaron Meister
 * Date:        2020-01-23 
 * Description: Header file for the displayer
 *****************************************************************************/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "board.h"

class CDisplay
{
public:
	void welcomeGame();
	void updateScreen(const CBoard& updatedBoard);
	void clearScreen();
};




#endif