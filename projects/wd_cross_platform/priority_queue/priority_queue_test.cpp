/*****************************************************************************
* File name:   priority_queue_test.cpp
* Developer:   Yaron Meister
* Date:        2018-11-20 11:04:53
* Description: This file contains the 'main' function.
               Program execution begins and ends there.
* Test Flow:
*****************************************************************************/

#include "priority_queue.h"
#include "tests.h"
#include "utils.h"          

/* Forward Declarations    */

class PriorityQTest : public Test
{
public:
  void enqueueTest();
  void dequeueTest();
  void peekTest();
  void isEmptyTest();
  void sizeTest();
  void clearTest();
  void eraseTest();
};

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  PriorityQTest pqTest;

  pqTest.enqueueTest();
  pqTest.dequeueTest();
  pqTest.peekTest();
  pqTest.isEmptyTest();
  pqTest.sizeTest();
  pqTest.clearTest();
  pqTest.eraseTest();

  return (EXIT_SUCCESS);
}

/******************************************************************************/
void PriorityQTest::enqueueTest()
{
  CPriorityQ<int> pq;
  CPrioritizedData<int> peek;

  printf("\n******************* Enqueue - TEST **************************\n");

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  pq.enqueue(data1);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);
  
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);
  pq.enqueue(data2);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);

  CPrioritizedData<int> data3(800, CPrioritizedData<int>::TOP_PRIORITY);
  pq.enqueue(data3);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 800);
}

/******************************************************************************/
void PriorityQTest::dequeueTest()
{
  CPriorityQ<int> pq;
  CPrioritizedData<int> peek;
  CPrioritizedData<int> dequeued(0);

  printf("\n******************* Dequeue - TEST **************************\n");

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);
  CPrioritizedData<int> data3(800, CPrioritizedData<int>::TOP_PRIORITY);

  pq.enqueue(data1);
  pq.enqueue(data2);
  pq.enqueue(data3);
  
  pq.dequeue();
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);

  pq.dequeue();
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 300);

  pq.dequeue();
  dequeued = pq.dequeue();
  equalityTest<int>(dequeued.getData(), NULL);
}

/******************************************************************************/
void PriorityQTest::peekTest(void)
{
  CPriorityQ<int> pq;
  CPrioritizedData<int> peek;

  printf("\n******************* Peek - TEST *****************************\n");

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);
  CPrioritizedData<int> data3(800, CPrioritizedData<int>::TOP_PRIORITY);

  pq.enqueue(data1);
  pq.enqueue(data2);
  pq.enqueue(data3);

  peek = pq.peek();
  equalityTest<int>(peek.getData(), 800);
  
  pq.dequeue();
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);

  pq.dequeue();
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 300);

  pq.dequeue();
  peek = pq.peek();
  equalityTest<int>(peek.getData(), NULL);
}

/******************************************************************************/
void PriorityQTest::isEmptyTest(void)
{
  CPriorityQ<int> pq;
  
  printf("\n******************* IsEmpty - TEST **************************\n");

  equalityTest<bool>(pq.isEmpty(), true);

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  pq.enqueue(data1);
  equalityTest<bool>(pq.isEmpty(), false);

  pq.dequeue();
  equalityTest<bool>(pq.isEmpty(), true);
}

/******************************************************************************/
void PriorityQTest::sizeTest(void)
{
  CPriorityQ<int> pq;

  printf("\n******************* Size - TEST *****************************\n");

  equalityTest<size_t>(pq.size(), 0);

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);

  pq.enqueue(data1);
  equalityTest<size_t>(pq.size(), 1);

  pq.enqueue(data2);
  equalityTest<size_t>(pq.size(), 2);
}

/******************************************************************************/
void PriorityQTest::clearTest(void)
{
  CPriorityQ<int> pq;

  printf("\n******************* Clear - TEST ****************************\n");

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);
  CPrioritizedData<int> data3(800, CPrioritizedData<int>::TOP_PRIORITY);

  pq.enqueue(data1);
  pq.enqueue(data2);
  pq.enqueue(data3);

  pq.clear();

  equalityTest<bool>(pq.isEmpty(), true);
}

/******************************************************************************/
void PriorityQTest::eraseTest(void)
{
  CPriorityQ<int> pq;
  CPrioritizedData<int> peek;
  CPrioritizedData<int> retData;
  
  
  
  printf("\n******************* Erase - TEST ****************************\n");

  CPrioritizedData<int> data1(500, CPrioritizedData<int>::HIGH_PRIORITY);
  CPrioritizedData<int> data2(300, CPrioritizedData<int>::LOWEST_PRIORITY);
  CPrioritizedData<int> data3(800, CPrioritizedData<int>::TOP_PRIORITY);

  pq.enqueue(data1);
  pq.enqueue(data2);
  pq.enqueue(data3);
  
  int erased1(400);
  peek = pq.peek();
  pq.erase(erased1);
  equalityTest<int>(peek.getData(), 800);
  equalityTest<size_t>(pq.size(), 3);

  int erased2(500);
  pq.erase(erased2);
  peek = pq.peek();

  equalityTest<int>(peek.getData(), 800);
  equalityTest<size_t>(pq.size(), 2);

  int erased3(800);
  retData = pq.erase(erased3);
  peek = pq.peek();

  equalityTest<int>(peek.getData(), 300);
  equalityTest<int>(retData.getData(), 800);
}


