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

//---------------------//
//   CPrioritizedData
//---------------------//
class CPrioritizedData
{
public:
  typedef enum EPriority
  {
    TOP_PRIORITY,
    HIGH_PRIORITY,
    MEDIUM_PRIORITY,
    LOW_PRIORITY,
    LOWEST_PRIORITY
  }EPriority;

  //CTor
  CPrioritizedData(int data = 0, EPriority priority = LOWEST_PRIORITY);

  //Operators
  bool operator==(const CPrioritizedData& pd) const;
  bool operator!=(const CPrioritizedData& pd) const;
  bool operator>(const CPrioritizedData& pd) const;
  bool operator<(const CPrioritizedData& pd) const;
  bool operator<=(const CPrioritizedData& pd) const;
  bool operator>=(const CPrioritizedData& pd) const;

  inline int getData();

private:
  int m_data;
  EPriority m_priority;
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
  CPriorityQ<CPrioritizedData> pq;
  CPrioritizedData peek;

  printf("\n******************* Enqueue - TEST **************************\n");

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  pq.enqueue(data1);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);
  
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);
  pq.enqueue(data2);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 500);

  CPrioritizedData data3(800, CPrioritizedData::TOP_PRIORITY);
  pq.enqueue(data3);
  peek = pq.peek();
  equalityTest<int>(peek.getData(), 800);
}

/******************************************************************************/
void PriorityQTest::dequeueTest()
{
  CPriorityQ<CPrioritizedData> pq;
  CPrioritizedData peek;
  CPrioritizedData dequeued(0);

  printf("\n******************* Dequeue - TEST **************************\n");

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);
  CPrioritizedData data3(800, CPrioritizedData::TOP_PRIORITY);

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
  CPriorityQ<CPrioritizedData> pq;
  CPrioritizedData peek;

  printf("\n******************* Peek - TEST *****************************\n");

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);
  CPrioritizedData data3(800, CPrioritizedData::TOP_PRIORITY);

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
  CPriorityQ<CPrioritizedData> pq;
  
  printf("\n******************* IsEmpty - TEST **************************\n");

  equalityTest<bool>(pq.isEmpty(), true);

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  pq.enqueue(data1);
  equalityTest<bool>(pq.isEmpty(), false);

  pq.dequeue();
  equalityTest<bool>(pq.isEmpty(), true);
}

/******************************************************************************/
void PriorityQTest::sizeTest(void)
{
  CPriorityQ<CPrioritizedData> pq;

  printf("\n******************* Size - TEST *****************************\n");

  equalityTest<size_t>(pq.size(), 0);

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);

  pq.enqueue(data1);
  equalityTest<size_t>(pq.size(), 1);

  pq.enqueue(data2);
  equalityTest<size_t>(pq.size(), 2);
}

/******************************************************************************/
void PriorityQTest::clearTest(void)
{
  CPriorityQ<CPrioritizedData> pq;

  printf("\n******************* Clear - TEST ****************************\n");

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);
  CPrioritizedData data3(800, CPrioritizedData::TOP_PRIORITY);

  pq.enqueue(data1);
  pq.enqueue(data2);
  pq.enqueue(data3);

  pq.clear();

  equalityTest<bool>(pq.isEmpty(), true);
}

/******************************************************************************/
void PriorityQTest::eraseTest(void)
{
  CPriorityQ<CPrioritizedData> pq;
  CPrioritizedData peek;
  CPrioritizedData retData;
  
  
  
  printf("\n******************* Erase - TEST ****************************\n");

  CPrioritizedData data1(500, CPrioritizedData::HIGH_PRIORITY);
  CPrioritizedData data2(300, CPrioritizedData::LOWEST_PRIORITY);
  CPrioritizedData data3(800, CPrioritizedData::TOP_PRIORITY);

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

/******************************************************************************/
CPrioritizedData::CPrioritizedData(int data, EPriority priority) : 
  m_data(data)
, m_priority(priority)
{}
                                                                        
/******************************************************************************/
bool CPrioritizedData::operator==(const CPrioritizedData& pd) const
{
  return (m_data == pd.m_data);
}

/******************************************************************************/
bool CPrioritizedData::operator!=(const CPrioritizedData& pd) const
{
  return (m_data != pd.m_data);
}

/******************************************************************************/
bool CPrioritizedData::operator>(const CPrioritizedData& pd) const
{
  return (m_priority > pd.m_priority);
}

/******************************************************************************/
bool CPrioritizedData::operator<(const CPrioritizedData& pd) const
{
  return (m_priority < pd.m_priority);
}

/******************************************************************************/
bool CPrioritizedData::operator<=(const CPrioritizedData& pd) const
{
  return (m_data <= pd.m_data);
}

/******************************************************************************/
bool CPrioritizedData::operator>=(const CPrioritizedData& pd) const
{
  return (m_data >= pd.m_data);
}

/******************************************************************************/
inline int CPrioritizedData::getData()
{
  return (m_data);
}




