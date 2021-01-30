/*****************************************************************************
 * File name:   display.cpp
 * Developer:   Yaron Meister
 * Date:        2020-01-25
 * Description: Source file for class CDisplay
 *****************************************************************************/

#include <iostream>
#include <string>

#include "display.h"

// Namespaces
using namespace std;

// Macros
static const unsigned short SCREEN_ROW_NUM(100);
// Global variables

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
void CDisplay::clearScreen()
{
	cout << string(SCREEN_ROW_NUM, '\n');
}

/////////////////////////////////////////////////////////////////////////////