/*****************************************************************************
* File name:   dlist.h
* Developer:   Yaron
* Date:        2018-11-20 11:04:53
* Description: Header file for Doubly Linked List
*****************************************************************************/

#ifndef __TESTS_H__
#define __TESTS_H__

#include"utils.h"

#include <iostream>
#include <cstdlib>

using namespace std;

class Test
{
public:
  Test() : m_testsNum(0), m_passedNum(0) {}
  
  template<typename T>
  void equalityTest(T first, T second);

  virtual void printResults();

private:
  unsigned short m_testsNum;
  unsigned short m_passedNum;
};

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template<typename T>
void Test::equalityTest(T first, T second)
{
	++m_testsNum;
	cout << YELLOW_COLOUR << "Test number: " << m_testsNum << "\n";

	if (first == second)
	{
		++m_passedNum;
		cout << GREEN_COLOUR << "\t\tPASSED\n";
	}
	else
	{
		cout << RED_COLOUR << "\t\tFAILED\n";
	}

	cout << RESET_COLOUR;
}

#endif     /* __TESTS_H__ */

