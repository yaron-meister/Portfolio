/*****************************************************************************
 * File name:   dlist_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daniel
 * Date:        2018-11-20 11:04:53
 * Description: This file contains the 'main' function. 
                Program execution begins and ends there.
 * Test Flow:
 *****************************************************************************/

#include <iostream>      
#include <cstdio>       
#include <cstdlib>      
//#include <string.h>     /* Memcpy       */

#include "dlist.h"
#include "tests.h"

using namespace std;
/* Forward Declarations    */

class DlistTest : public Test
{
public:
  void countTest();
  void isEmptyTest();
  void beginTest();
  void endTest();
  void nextTest();
  void prevTest();
  void getDataTest();
  void isBadIterTest();
  void insertTest();
  void eraseTest();
  void pushFrontTest();
  void pushBackTest();
  void popFrontTest();
  void popBackTest();
  void spliceBeforeTest();
  void findTest();
};

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  DlistTest dlistTest;

  dlistTest.countTest();
  dlistTest.isEmptyTest();
  dlistTest.beginTest();
  dlistTest.endTest();
  dlistTest.nextTest();
  dlistTest.prevTest();
  dlistTest.getDataTest();
  dlistTest.isBadIterTest();
  dlistTest.insertTest();
  dlistTest.eraseTest();
  dlistTest.pushFrontTest();
  dlistTest.pushBackTest();
  dlistTest.popFrontTest();
  dlistTest.popBackTest();
  dlistTest.spliceBeforeTest();
  dlistTest.findTest();

  return (EXIT_SUCCESS);
}

/******************************************************************************/
void DlistTest::countTest()
{
  CDlist<int*> dlist;

  cout << "******************* Count - TEST ****************************\n";
  equalityTest<size_t>(dlist.size(), 0);

  int a(5);
  dlist.insert(dlist.end(), &a);
  equalityTest<size_t>(dlist.size(), 1);

  int b(55);
  dlist.insert(dlist.end(), &b);
  equalityTest<size_t>(dlist.size(), 2);
}

/******************************************************************************/
void DlistTest::isEmptyTest()
{
  CDlist<int*> dlist;
  int** pData = new int*;
  CDlist<int*>::Iter iter(nullptr);

  printf("\n******************* IsEmpty - TEST **************************\n");
  equalityTest<bool>(dlist.isEmpty(), true);

  int a = 5;
  iter = dlist.insert(dlist.end(), &a);
  equalityTest<bool>(dlist.isEmpty(), false);

  dlist.erase(iter, pData);
  equalityTest<bool>(dlist.isEmpty(), true);
}

/******************************************************************************/
void DlistTest::beginTest()
{
  CDlist<int*> dlist;

  printf("\n******************* Begin - TEST ****************************\n");

  equalityTest<bool>(dlist.begin() == dlist.end(), true);

  int a(5);
  int b(55);
  dlist.insert(dlist.end(), &a);
  dlist.insert(dlist.end(), &b);

  equalityTest<int>(*dlist.getData(dlist.begin()), 5);
}

/******************************************************************************/
void DlistTest::endTest()
{
  CDlist<int*> dlist;

  printf("\n******************* End - TEST ******************************\n");

  int a(5);
  int b(55);
  dlist.insert(dlist.end(), &a);
  dlist.insert(dlist.end(), &b);

  equalityTest<int>(*dlist.getData(dlist.prev(dlist.end())), 55);
}

/******************************************************************************/
void DlistTest::nextTest()
{
  CDlist<int*> dlist;

  printf("\n******************* Next - TEST *****************************\n");

  int a(5);
  int b(55);
  dlist.insert(dlist.end(), &a);
  dlist.insert(dlist.end(), &b);

  equalityTest<int>(*dlist.getData(dlist.next(dlist.begin())), 55);
}

/******************************************************************************/
void DlistTest::prevTest()
{
  CDlist<int*> dlist;

  printf("\n******************* Prev - TEST *****************************\n");

  int a(5);
  int b(55);
  dlist.insert(dlist.end(), &a);
  dlist.insert(dlist.end(), &b);

  equalityTest<int>(*dlist.getData(dlist.prev(dlist.end())), 55);
}

/******************************************************************************/
void DlistTest::getDataTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(dlist.end());

  printf("\n******************* GetData - TEST **************************\n");

  equalityTest<int*>(dlist.getData(iter), nullptr);

  int a(5);
  iter = dlist.insert(dlist.end(), &a);

  equalityTest<int>(*dlist.getData(iter), 5);
}

/******************************************************************************/
void DlistTest::isBadIterTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
  int a = 5;

  printf("\n******************* IsBadIter - TEST ************************\n");

  equalityTest<bool>(CDlist<int*>::isBadIter(iter), true);

  iter = dlist.insert((dlist.end()), &a);

  equalityTest<bool>(CDlist<int*>::isBadIter(iter), false);

  iter = dlist.end();

  equalityTest<bool>(CDlist<int*>::isBadIter(iter), true);
}

/******************************************************************************/
void DlistTest::insertTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
  
  printf("\n******************* Insert - TEST ***************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.insert(dlist.end(), &b);
  dlist.insert(dlist.prev(dlist.end()), &a);
  dlist.insert(dlist.end(), &c);
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 5);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 55);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 555);
}

/******************************************************************************/
void DlistTest::eraseTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
  
  printf("\n******************* Erase - TEST ****************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.insert(dlist.end(), &b);
  dlist.insert(dlist.prev(dlist.end()), &a);
  dlist.insert(dlist.end(), &c);
  iter = dlist.begin();
  iter = dlist.erase(iter, nullptr);

  equalityTest<int>(*dlist.getData(iter), 55);

  iter = dlist.erase(iter, nullptr);

  equalityTest<int>(*dlist.getData(iter), 555);

  iter = dlist.erase(iter, nullptr);

  equalityTest<CDlist<int*>::Iter>(iter, dlist.end());
}

/******************************************************************************/
void DlistTest::pushFrontTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
  
  printf("\n******************* PushFront - TEST ************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.pushFront(&c);
  dlist.pushFront(&b);
  dlist.pushFront(&a);
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 5);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 55);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 555);
}

/******************************************************************************/
void DlistTest::pushBackTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
  
  printf("\n******************* PushBack - TEST *************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.pushBack(&a);
  dlist.pushBack(&b);
  dlist.pushBack(&c);
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 5);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 55);

  iter = dlist.next(iter);

  equalityTest<int>(*dlist.getData(iter), 555);
}

/******************************************************************************/
void DlistTest::popFrontTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);

  printf("\n******************* PopFront - TEST *************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.pushBack(&a);
  dlist.pushBack(&b);
  dlist.pushBack(&c);
  dlist.popFront();
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 55);

  dlist.popFront();
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 555);

  dlist.popFront();

  equalityTest<int*>(dlist.popFront(), nullptr);
}

/******************************************************************************/
void DlistTest::popBackTest()
{
  CDlist<int*> dlist;
  CDlist<int*>::Iter iter(nullptr);
 
  printf("\n******************* PopBack - TEST **************************\n");

  int a(5);
  int b(55);
  int c(555);
  dlist.pushBack(&a);
  dlist.pushBack(&b);
  dlist.pushBack(&c);
  dlist.popBack();
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 5);

  dlist.popBack();
  iter = dlist.begin();

  equalityTest<int>(*dlist.getData(iter), 5);

  dlist.popBack();

  equalityTest<int*>(dlist.popBack(), nullptr);
}

/******************************************************************************/
void DlistTest::spliceBeforeTest()
{
  CDlist<int*> dlist1;
  CDlist<int*> dlist2;
  CDlist<int*>::Iter dest(nullptr);
  CDlist<int*>::Iter to(nullptr);
  CDlist<int*>::Iter from(nullptr);

  printf("\n******************* Splice - TEST ***************************\n");

  int a(5);
  int b(55);
  int c(555);
  int d(5555);
  int e(55555);
  dlist1.pushBack(&a);
  dlist1.pushBack(&b);
  dlist1.pushBack(&c);

  dlist2.pushBack(&d);
  dlist2.pushBack(&e);

  equalityTest<size_t>(dlist1.size(), 3);
  equalityTest<size_t>(dlist2.size(), 2);

  dest = dlist1.next(dlist1.next(dlist1.begin()));
  from = dlist2.next(dlist2.begin());
  to = dlist2.next(from);
  CDlist<int*>::spliceBefore(dest, from, to);

  equalityTest<size_t>(dlist1.size(), 4);
  equalityTest<size_t>(dlist2.size(), 1);
}

/******************************************************************************/
void DlistTest::findTest()
{
  CDlist<int> dlist;
  CDlist<int>::Iter from(nullptr);
  CDlist<int>::Iter to(nullptr);

  printf("\n******************* Find - TEST *****************************\n");

  int a(5);
  int b(55);
  int c(55);
  int d(50);
  dlist.pushBack(a);
  dlist.pushBack(b);
  from = dlist.begin();
  to = dlist.end();

  equalityTest<CDlist<int>::Iter>(dlist.find(from, to, c, [](const int lhs, const int rhs, const ParamsBase* params) {return (lhs == rhs); }, nullptr), 
    dlist.next(dlist.begin()));
  equalityTest<CDlist<int>::Iter>(dlist.find(from, to, d, [](const int lhs, const int rhs, const ParamsBase* params) {return (lhs == rhs); }, nullptr),
    to);
}

