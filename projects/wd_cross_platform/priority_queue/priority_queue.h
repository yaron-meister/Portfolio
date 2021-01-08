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
//   CPrioritizedData
//---------------------//
template <typename Type>
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
  CPrioritizedData(Type data = 0, EPriority priority = LOWEST_PRIORITY);

  //Operators
  bool operator==(const CPrioritizedData& pd) const;
  bool operator!=(const CPrioritizedData& pd) const;
  bool operator>(const CPrioritizedData& pd) const;
  bool operator<(const CPrioritizedData& pd) const;
  bool operator<=(const CPrioritizedData& pd) const;
  bool operator>=(const CPrioritizedData& pd) const;

  inline Type getData();

private:
  Type m_data;
  EPriority m_priority;
};

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
  void enqueue(CPrioritizedData<Type> data);

  /* Removes the top priority element */
  /* returns NULL if queue is empty */
  /* Complexity: O(1) */
  CPrioritizedData<Type> dequeue();

  /* Shows the top priority data */
  /* returns NULL if queue is empty */
  /* Complexity: O(1) */
  const CPrioritizedData<Type> peek();

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

  /* Remove the similar element (if found) */
  /* and returns its data */
  /* if not found, returns NULL */
  /* Complexity: O(n) */
  CPrioritizedData<Type> erase(CPrioritizedData<Type> data);

private:
  CSortList<CPrioritizedData<Type>> m_list;
};

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CPrioritizedData<Type>::CPrioritizedData(Type data, EPriority priority) : 
  m_data(data)
, m_priority(priority)
{}
                                                                        
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator==(const CPrioritizedData& pd) const
{
  return (m_data == pd.m_data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator!=(const CPrioritizedData& pd) const
{
  return (m_data != pd.m_data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator>(const CPrioritizedData& pd) const
{
  return (m_priority > pd.m_priority);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator<(const CPrioritizedData& pd) const
{
  return (m_priority < pd.m_priority);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator<=(const CPrioritizedData& pd) const
{
  return (m_data <= pd.m_data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CPrioritizedData<Type>::operator>=(const CPrioritizedData& pd) const
{
  return (m_data >= pd.m_data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
inline Type CPrioritizedData<Type>::getData()
{
  return (m_data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void CPriorityQ<Type>::enqueue(CPrioritizedData<Type> data)
{
  m_list.insert(data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CPrioritizedData<Type> CPriorityQ<Type>::dequeue()
{
  CPrioritizedData<Type> popped(NULL);

  if (!isEmpty())
  {
    popped = m_list.popFront();
  }

  return (popped);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
const CPrioritizedData<Type> CPriorityQ<Type>::peek() 
{
  CPrioritizedData<Type> retVal(NULL);

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
CPrioritizedData<Type> CPriorityQ<Type>::erase(CPrioritizedData<Type> data)
{
  CPrioritizedData<Type> erased(NULL);
  typename CSortList<CPrioritizedData<Type>>::Iter iter(m_list.find(m_list.begin(), m_list.end(), data));
  typename CSortList<CPrioritizedData<Type>>::Iter end(m_list.end());

  if (iter != end)
  {
    iter = m_list.erase(iter, &erased);
  }

  return (erased);
}


#endif     /* __PRIORITY_QUEUE_H__ */