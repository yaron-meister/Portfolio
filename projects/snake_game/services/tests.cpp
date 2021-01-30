/*****************************************************************************
* File name:   tests.cpp
* Developer:   Yaron
* Date:        2018-11-20 11:04:53
* Description: Source file for Tests
*****************************************************************************/

#include "tests.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void Test::printResults()
{
	cout << "\n\nTotal number of tests: " << m_testsNum << "\n";
	cout << "Number of PASSED tests: " << m_passedNum << "\n\n";
}