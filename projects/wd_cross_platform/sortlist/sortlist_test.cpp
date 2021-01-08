/*****************************************************************************
 * File name:   sortlist_test.cpp
 * Developer:   Yaron Meister
 * Date:        2018-11-20 11:04:53
 * Description: This file contains the 'main' function.
                Program execution begins and ends there.
 * Test Flow:
 *****************************************************************************/

#include "sortlist.h"
#include "tests.h"

/* Forward Declarations    */

class SortListTest : public Test
{
public:
  void sizeTest();
  void isEmptyTest();
  void endTest();
  void beginTest();
  void nextTest();
  void prevTest();
  void isBadIterTest();
  void getDataTest();
  void insertTest();
  void eraseTest();
  void popFrontTest();
  void popBackTest();
  void findTest();
  void mergeTest();
};

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main()
{
  SortListTest sortListTest;

  sortListTest.sizeTest();
  sortListTest.isEmptyTest();
  sortListTest.endTest();
  sortListTest.beginTest();
  sortListTest.nextTest();
  sortListTest.prevTest();
  sortListTest.isBadIterTest();
  sortListTest.getDataTest();
  sortListTest.insertTest();
  sortListTest.eraseTest();
  sortListTest.popFrontTest();
  sortListTest.popBackTest();
  sortListTest.findTest();
  sortListTest.mergeTest();

  return (EXIT_SUCCESS);
}

/******************************************************************************/
void SortListTest::sizeTest()
{
  CSortList<int> sortList;

  printf("\n******************* Size - TEST *****************************\n");

  equalityTest<size_t>(sortList.size(), 0);

  int a(5);
  sortList.insert(a);
  equalityTest<size_t>(sortList.size(), 1);

  int b(55);
  sortList.insert(b);
  equalityTest<size_t>(sortList.size(), 2);
}

/******************************************************************************/
void SortListTest::isEmptyTest()
{
  CSortList<int> sortList;

  printf("\n******************* IsEmpty - TEST **************************\n");

  int a(5);
  CSortList<int>::Iter iter(nullptr);
  equalityTest<bool>(sortList.isEmpty(), true);

  iter = sortList.insert(a);
  equalityTest<bool>(sortList.isEmpty(), false);

  sortList.erase(iter, nullptr);
  equalityTest<bool>(sortList.isEmpty(), true);
}

/******************************************************************************/
void SortListTest::endTest()
{
  CSortList<int> sortList;

  printf("\n******************* End - TEST ******************************\n");

  int a(5);
  int b(55);
  sortList.insert(a);
  sortList.insert(b);
  equalityTest<int>(sortList.getData(sortList.prev(sortList.end())), 55);
}

/******************************************************************************/
void SortListTest::beginTest()
{
  CSortList<int> sortList;

  printf("\n******************* Begin - TEST ****************************\n");

  int a(5);
  int b(55);

  equalityTest<CSortList<int>::Iter>(sortList.begin(), sortList.end());
  
  sortList.insert(a);
  sortList.insert(b);
  equalityTest<int>(sortList.getData(sortList.begin()), 5);
}

/******************************************************************************/
void SortListTest::nextTest()
{
  CSortList<int> sortList;

  printf("\n******************* Next - TEST *****************************\n");

  int b(55);
  int a(5);
  sortList.insert(b);
  sortList.insert(a);

  equalityTest<int>(sortList.getData(sortList.next(sortList.begin())), 55);
}

/******************************************************************************/
void SortListTest::prevTest()
{
  CSortList<int> sortList;

  printf("\n******************* Prev - TEST *****************************\n");

  int b(55);
  int a(5);
  sortList.insert(b);
  sortList.insert(a);

  equalityTest<int>(sortList.getData(sortList.prev(sortList.end())), 55);
}

/******************************************************************************/
void SortListTest::isBadIterTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(nullptr);

  printf("\n******************* IsBadIter - TEST ************************\n");

  equalityTest<bool>(CSortList<int>::isBadIter(iter), true);

  int a(5);
  iter = sortList.insert(a);
  equalityTest<bool>(CSortList<int>::isBadIter(iter), false);

  iter = sortList.end();
  equalityTest<bool>(CSortList<int>::isBadIter(iter), true);
}

/******************************************************************************/
void SortListTest::getDataTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(sortList.end());

  printf("\n******************* GetData - TEST **************************\n");

  equalityTest<int>(sortList.getData(iter), NULL);

  int a(5);
  iter = sortList.insert(a);
  equalityTest<int>(sortList.getData(iter), 5);
}

/******************************************************************************/
void SortListTest::insertTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(sortList.end());

  printf("\n******************* Insert - TEST ***************************\n");

  int a(5);
  int b(55);
  int c(555);
  sortList.insert(c);
  sortList.insert(a);
  sortList.insert(b);
  iter = sortList.begin();

  equalityTest<int>(sortList.getData(iter), 5);

  iter = sortList.next(iter);
  equalityTest<int>(sortList.getData(iter), 55);

  iter = sortList.next(iter);
  equalityTest<int>(sortList.getData(iter), 555);
}

/******************************************************************************/
void SortListTest::eraseTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(sortList.end());

  printf("\n******************* Erase - TEST ****************************\n");

  int a(5);
  int b(55);
  int c(555);
  sortList.insert(c);
  sortList.insert(a);
  sortList.insert(b);
  iter = sortList.begin();
  iter = sortList.erase(iter, nullptr);
  equalityTest<int>(sortList.getData(iter), 55);

  iter = sortList.erase(iter, nullptr);
  equalityTest<int>(sortList.getData(iter), 555);

  iter = sortList.erase(iter, nullptr);
  equalityTest<bool>(sortList.end() == iter, true);
}

/******************************************************************************/
void SortListTest::popFrontTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(sortList.end());
  
  printf("\n******************* PopFront - TEST *************************\n");

  int a(5);
  int b(55);
  int c(555);
  sortList.insert(c);
  sortList.insert(a);
  sortList.insert(b);
  sortList.popFront();
  iter = sortList.begin();
  equalityTest<int>(sortList.getData(iter), 55);

  sortList.popFront();
  iter = sortList.begin();
  equalityTest<int>(sortList.getData(iter), 555);

  sortList.popFront();
  equalityTest<int>(sortList.popFront(), NULL);
}

/******************************************************************************/
void SortListTest::popBackTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter iter(sortList.end());

  printf("\n******************* PopBack - TEST **************************\n");

  int a(5);
  int b(55);
  int c(555);
  sortList.insert(c);
  sortList.insert(a);
  sortList.insert(b);
  sortList.popBack();
  iter = sortList.begin();
  equalityTest<int>(sortList.getData(iter), 5);

  sortList.popBack();
  iter = sortList.begin();
  equalityTest<int>(sortList.getData(iter), 5);

  sortList.popBack();
  equalityTest<int>(sortList.popBack(), NULL);
}

/******************************************************************************/
void SortListTest::findTest()
{
  CSortList<int> sortList;
  CSortList<int>::Iter from(nullptr);
  CSortList<int>::Iter to(nullptr);

  int a(5);
  int b(55);
  int c(55);
  int d(50);
  sortList.insert(a);
  sortList.insert(b);
  from = sortList.begin();
  to = sortList.end();

  printf("\n******************* Find - TEST *****************************\n");

  equalityTest<CSortList<int>::Iter>(sortList.find(from, to, c), sortList.next(sortList.begin()));

  equalityTest<CSortList<int>::Iter>(sortList.find(from, to, d), to);
}

/******************************************************************************/
void SortListTest::mergeTest()
{
  CSortList<int> destSortList;
  CSortList<int> srcSortList;
  CSortList<int>::Iter iter(nullptr);

  printf("\n******************* Merge - TEST ****************************\n");
  
  int a(1);
  int b(2);
  int c(3);
  int d(4);
  int e(5);

  destSortList.insert(a);
  destSortList.insert(b);
  destSortList.insert(e);

  srcSortList.insert(c);
  srcSortList.insert(d);

  CSortList<int>::merge(destSortList, srcSortList);

  iter = destSortList.next(destSortList.next(destSortList.begin()));
  equalityTest<int>(destSortList.getData(iter), 3);

  iter = destSortList.next(iter);
  equalityTest<int>(destSortList.getData(iter), 4);

  iter = destSortList.prev(destSortList.end());
  equalityTest<int>(destSortList.getData(iter), 5);

  equalityTest<bool>(srcSortList.isEmpty(), true);
}


