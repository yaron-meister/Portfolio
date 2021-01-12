/*****************************************************************************
* File name:   priority_queue.h
* Developer:   Yaron
* Date:        2018-11-22 18:02:53
* Description: Header file for Priority Queue
*****************************************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "sortlist.h"



//---------------------//
//     CPriorityQ
//---------------------//
template<typename Type>
class CPriorityQ
{
public:
  /* Inserts the element to the queue according to its priority */
  /* is_before determines the sorting criteria */
  /* Complexity: O(n) */
  void enqueue(Type data);

  /* Removes the top priority element */
  /* returns NULL if queue is empty */
  /* Complexity: O(1) */
  Type dequeue();

  /* Shows the top priority data */
  /* returns NULL if queue is empty */
  /* Complexity: O(1) */
  const Type peek();

  /* Returns true if queue is empty */
  /* returns false if queue is not empty */
  /* Complexity: O(1) */
  bool isEmpty();

  /* Returns the number of elements in the queue or 0 if empty */
  /* Complexity: O(n) */
  size_t size();

  /* Dequeues all the elements from the queue */
  /* Complexity: O(n) */
  void clear();

  /* Remove the similar element (if found by operator==) */
  /* and returns its data */
  /* if not found, returns NULL */
  /* Complexity: O(n) */
  Type erase(Type data);

private:
  CSortList<Type> m_list;
};

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void CPriorityQ<Type>::enqueue(Type data)
{
  m_list.insert(data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CPriorityQ<Type>::dequeue()
{
  Type popped(NULL);

  if (!isEmpty())
  {
    popped = m_list.popFront();
  }

  return (popped);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
const Type CPriorityQ<Type>::peek() 
{
  Type retVal(NULL);

  if (!isEmpty())
  {
    retVal = m_list.getData(m_list.begin());
  }

  return (retVal);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPriorityQ<Type>::isEmpty()
{
  return (m_list.isEmpty());
}

//////////////////////////////////////////////////////////////////////////////
template<typename Type>
size_t CPriorityQ<Type>::size()
{
  return (m_list.size());
}

//////////////////////////////////////////////////////////////////////////////
template<typename Type>
void CPriorityQ<Type>::clear()
{
  while (!isEmpty())
  {
    dequeue();
  }
}

//////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CPriorityQ<Type>::erase(Type data)
{
  Type erased(NULL);
  typename CSortList<Type>::Iter iter(m_list.find(m_list.begin(), m_list.end(), data));
  typename CSortList<Type>::Iter end(m_list.end());

  if (iter != end)
  {
    iter = m_list.erase(iter, &erased);
  }

  return (erased);
}


#endif     /* __PRIORITY_QUEUE_H__ */