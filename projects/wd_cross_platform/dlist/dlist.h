/*****************************************************************************
* File name:   dlist.h
* Developer:   Yaron
* Date:        2018-11-20 11:04:53
* Description: Header file for Doubly Linked List
*****************************************************************************/

#ifndef __DLIST_H__
#define __DLIST_H__


#include <new>
#include <iostream>
#include <cstddef>
#include <functional>

#include "utils.h"
#include "params.h"

using namespace std;

template <typename Type>
class CDlist
{
private:
  class CNode
  {
  public:
    //CTors
    CNode();
    CNode(CNode* prev, CNode* next, Type data);

    //DTor
    ~CNode();

    Type    m_data;
    CNode*  m_prev;
    CNode*  m_next;
  };

public:
  typedef class CNode* Iter;
  using IsMatchFunc = std::function<bool(const Type, const Type, const ParamsBase*)>;

  enum EStatus
  {
    SUCCESS,
    FAILURE
  };

  //CTor
  CDlist();

  //DTor
  ~CDlist();

  /////////////////////////////////////////////////////////////////////////////
  // Complexity: O(n)
  /////////////////////////////////////////////////////////////////////////////
  size_t size();

  /////////////////////////////////////////////////////////////////////////////
  // Return value: 0 - not empty, !0 - empty
  // Complexity:   O(1)
  /////////////////////////////////////////////////////////////////////////////
  bool isEmpty();

  /////////////////////////////////////////////////////////////////////////////
  // Description: When dlist is empty - returns End 
  // Complexity:  O(1) 
  /////////////////////////////////////////////////////////////////////////////
  Iter begin();

  /////////////////////////////////////////////////////////////////////////////
  // Return value:  iterator to (stub) element after the last one 
  // Complexity:    O(1) 
  /////////////////////////////////////////////////////////////////////////////
  Iter end();

  /////////////////////////////////////////////////////////////////////////////
  // Description: Undefined behavior when iter = End, 
  // Complexity:  O(1) 
  /////////////////////////////////////////////////////////////////////////////
  Iter next(Iter iter);

  /////////////////////////////////////////////////////////////////////////////
  // Description: Undefined behavior when iter = Begin, 
  // Complexity O(1)
  /////////////////////////////////////////////////////////////////////////////
  Iter prev(Iter iter);

  /////////////////////////////////////////////////////////////////////////////
  // Return value:  NULL when iter = End 
  // Complexity:     O(1) 
  /////////////////////////////////////////////////////////////////////////////
  Type getData(const Iter iter);

  /////////////////////////////////////////////////////////////////////////////
  // Return value:  truthy - iter = End, 0 - else
  //                check iter validality(not assert) -> not for user
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  inline static bool isBadIter(Iter iter);

  /////////////////////////////////////////////////////////////////////////////
  // Description:   Insert data before where
  // Return value:  iter inserted = success, NULL = failure
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  Iter insert(Iter where, Type data);

  /////////////////////////////////////////////////////////////////////////////
  // Description: Returns iterator to following iter from the erased
  //              Data will be point to the data of the erased - if isn't NULL
  // Complexity:  O(1)
  /////////////////////////////////////////////////////////////////////////////
  Iter erase(Iter where, Type* data);

  /////////////////////////////////////////////////////////////////////////////
  // Description:   Push data before Begin
  // Return value:  0 = success, !0 = failure
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  EStatus pushFront(Type data);

  /////////////////////////////////////////////////////////////////////////////
  // Description:   Push data before End
  // Return value:  0 = success, !0 = failure 
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  EStatus pushBack(Type data);

  /////////////////////////////////////////////////////////////////////////////
  // Description:   Pop the Begin and return data
  // Return value:  NULL if dlist is empty
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  Type popFront();

  /////////////////////////////////////////////////////////////////////////////
  // Description:   Pop the element before End and return data
  // Return value:  NULL if dlist is empty
  // Complexity:    O(1)
  /////////////////////////////////////////////////////////////////////////////
  Type popBack();

  /////////////////////////////////////////////////////////////////////////////
  // Return value:  An iterator to the one who found,
  //                Returns 'to' if havn't found ('to' isn't included)
  //                T must be comparable
  /////////////////////////////////////////////////////////////////////////////
  Iter find(Iter from, Iter to, const Type data, IsMatchFunc isMatchFunc, ParamsBase* params);

  /////////////////////////////////////////////////////////////////////////////
  // Description: Elements between begin (including) to end (excluding) are 
  //              cut-paste src list remain valid
  // Complexity:  O(1)
  /////////////////////////////////////////////////////////////////////////////
  static void spliceBefore(Iter dest, Iter src_begin, Iter src_end);

private:
  static int destroyNode(CNode* node);

  CNode   m_start;
  CNode   m_end;
};


/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CDlist<Type>::CNode::CNode()  : m_prev(nullptr)
                              , m_next(nullptr)
                              , m_data(0)
{}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CDlist<Type>::CNode::CNode(CNode* prev, CNode* next, Type data) : m_prev(prev)
                                                                , m_next(next)
                                                                , m_data(data)
{}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CDlist<Type>::CNode::~CNode()
{
  m_prev = nullptr;
  m_next = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CDlist<Type>::CDlist()
{
  static const unsigned long DEADBEEF = static_cast<unsigned long>(0xDEADBEEFDEADBEEF);

  m_start.m_next = &m_end;
  m_start.m_prev = nullptr;
  m_start.m_data = (Type)DEADBEEF;

  m_end.m_next = nullptr;
  m_end.m_prev = &m_start;
  m_end.m_data = (Type)DEADBEEF;
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
CDlist<Type>::~CDlist()
{
  Iter iter(begin());
  Iter iterNext;

  while (!isBadIter(iter))
  {
    iterNext = next(iter);
    erase(iter, nullptr);
    iter = iterNext;
  }

  m_start.m_next = nullptr;
  m_end.m_prev = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
size_t CDlist<Type>::size()
{
  size_t count(0);
  CDlist<Type>::Iter iter(begin());
  CDlist<Type>::Iter end(end());

  while (iter != end)
  {
    ++count;
    iter = next(iter);
  }

  return (count);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CDlist<Type>::isEmpty()
{
  return (0 == size());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
inline bool CDlist<Type>::isBadIter(CDlist<Type>::Iter   iter)
{
  return (nullptr == iter || nullptr == iter->m_next || nullptr == iter->m_prev);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::begin()
{
  return (m_start.m_next);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::end()
{
  return (&m_end);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::next(Iter iter)
{
  return (iter->m_next);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::prev(Iter iter)
{
  return (iter->m_prev);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CDlist<Type>::getData(const Iter iter)
{
  Type data(0);

  if (!isBadIter(iter))
  {
    data = iter->m_data;
  }

  return (data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::insert(Iter where, Type data)
{
  CNode* node = new(nothrow) CNode(prev(where), where, data);

  if (nullptr == node)
  {
    DBG(cerr << "Insert failed!!!\n");
  }
  else
  {
    node->m_prev->m_next = node; // The next node of my PREV is ME
    node->m_next->m_prev = node; // The prev of my NEXT is ME
  }

  return (node);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::erase(Iter where, Type* pData)
{
  Iter whereNext(nullptr);
  Iter wherePrev(nullptr);

  if (!isBadIter(where))
  {
    whereNext = next(where);
    wherePrev = prev(where);

    if (nullptr != pData)
    {
      *pData = getData(where);
    }

    wherePrev->m_next = whereNext;
    whereNext->m_prev = wherePrev;

    CDlist::destroyNode(where);
  }

  return (whereNext);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::EStatus CDlist<Type>::pushFront(Type data)
{
  return (static_cast<EStatus>(nullptr == insert(begin(), data)));
}


/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::EStatus CDlist<Type>::pushBack(Type data)
{
  return (static_cast<EStatus>(nullptr == insert(end(), data)));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CDlist<Type>::popFront()
{
  Type data(0);

  if (!isEmpty())
  {
    erase(begin(), &data);
  }

  return (data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CDlist<Type>::popBack()
{
  Type data(0);

  if (!isEmpty())
  {
    erase(prev(end()), &data);
  }

  return (data);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CDlist<Type>::Iter CDlist<Type>::find(Iter from, Iter to, const Type data, IsMatchFunc isMatchFunc, ParamsBase* params)
{
  Iter iter(from);

  if (!isBadIter(iter))
  {
    while (iter != to && !isMatchFunc(data, getData(iter), params))
    {
      iter = next(iter);
    }
  }

  return (iter);
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void CDlist<Type>::spliceBefore(Iter dest, Iter srcBegin, Iter srcEnd)
{
  Iter endPrev(nullptr);

  if (srcBegin != srcEnd && !isBadIter(srcBegin))
  {
    // Cutting the pile from src
    endPrev = srcEnd->m_prev;
    srcBegin->m_prev->m_next = srcEnd;
    srcEnd->m_prev = srcBegin->m_prev;

    // Pushing the pile into the dest list
    srcBegin->m_prev = dest->m_prev;
    endPrev->m_next = dest;
    dest->m_prev->m_next = srcBegin;
    dest->m_prev = endPrev;
  }
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
int CDlist<Type>::destroyNode(CNode* node)
{
  delete(node);
  node = nullptr;

  return (SUCCESS);
}

#endif     /* __DLIST_H__ */

