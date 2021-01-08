/*****************************************************************************
* File name:   sortlist.h
* Developer:   Yaron
* Date:        2018-11-22 08:43:32
* Description: Header file for Sorted List
*****************************************************************************/

#ifndef __SORLTIST_H__
#define __SORLTIST_H__

#include "dlist.h"
#include <cstddef>     


/*
 * User is responsible for managing the lifetime of the data stored in the list
 * User provides a comparison operators that checks whether its first
 * argument should go before the second argument in the sorted list
 *
 * BadIter is an iterator that does not point after the end of the list [End()]
 * but IsBadIter(iter) on it is true
 */

template <typename Type>
class CSortList
{
public:
  typedef typename CDlist<Type>::Iter Iter;

  /*
   * Count list elements
   * Complexity: O(n)
   */
  size_t size();

  /*
   * Whether the list is empty
   * Returns truthy if the list is empty
   * Complexity: O(1)
   */
  bool isEmpty();

  /*
   * End() returns an iterator pointing to a pseudo-element after the last real one
   * Complexity: O(1)
   */
  Iter end();

  /*
   * Returns an iterator to the first element
   * If the list is empty, returns End()
   * Complexity: O(1)
   */
  Iter begin();

  /*
   * Returns an iterator pointing to the element after the given one
   * Returns End() if the given element is the last one
   *
   * Calling on End() is undefined
   * Complexity: O(1)
   */
  Iter next(Iter iter);

  /*
   * Returns an iterator pointing to the element before the given one
   *
   * Calling on Begin() is undefined
   * Complexity: O(1)
   */
  Iter prev(Iter iter);

  /*
   * Check whether the iterator is BadIter or points to the pseudo-element after
   * the end of the list [End()]
   * Returns boolean: iter is BadIter or iter is End()
   */
  static bool isBadIter(Iter iter);

  /*
   * Get the user data from the list element pointed to by the iterator
   *
   * Calling on End() returns NULL
   * Calling on BadIter is undefined
   * Complexity: O(1)
   */
  Type getData(const Iter iter);

  /*
   * Insert a new element containing data into the list
   * The list remains sorted
   * May fail (allocation failure), in such case returns BadIter
   *
   * Returns an iterator pointing to the newly inserted element
   * Complexity: O(n)
   */
  Iter insert(Type data);

  /*
   * Remove an element from the list
   * Calling on End() is undefined
   * Calling on BadIter is undefined
   *
   * Returns iterator to following iter from the erased
   * Stores data contained in the removed element inside 'data'
   * Complexity: O(1)
   */
  Iter erase(Iter where, Type* pData);

  /*
   * Remove an element from the beginning (end) of the list
   * Calling on empty list returns NULL
   *
   * Returns data contained in the removed element
   * Complexity: O(1)
   */
  Type popFront();
  Type popBack();

  /*
   * Traverse the range [from; to) until it returns equality
   * The <to> element is excluded from range
   * Calling on from = to results in returning <to>
   * Calling on compare_func = NULL is undefined
   * Calling on <from> pointing to a list different from the one <to> points to
   * results in undefined behavior
   * Calling on <from> pointing to the element after <to> is undefined
   *
   * Type's operator= must be implemented
   *
   * Returns the iterator <to> when none of the elements matched or an iterator
   * to the first element that matched
   * Complexity: O(n)
   */
  Iter find(Iter from, Iter to, Type data);

  /*
   * Move all the elements of <source> to <dest> keeping the sorted order
   * <source> is left empty (not destroyed)
   * <dest>'s is_before is expected to be able to handle <source>'s elements
   * Calling on empty <source> is well-defined
   * Complexity: O(n + m)
   */
  static void merge(CSortList& dest, CSortList& source);

private:
  CDlist<Type>  m_dlist;
};

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
size_t CSortList<Type>::size()
{
  return (m_dlist.size());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CSortList<Type>::isEmpty()
{
  return (m_dlist.isEmpty());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename typename CSortList<Type>::Iter CSortList<Type>::end()
{
  return (m_dlist.end());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::begin()
{
  return (m_dlist.begin());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::next(Iter iter)
{
  return (m_dlist.next(iter));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::prev(Iter iter)
{
  return (m_dlist.prev(iter));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool CSortList<Type>::isBadIter(CSortList::Iter iter)
{
  return (CDlist<Type>::isBadIter(iter));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CSortList<Type>::getData(const CSortList::Iter iter)
{
  return (m_dlist.getData(iter));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::insert(Type data)
{
  CSortList<Type>::Iter iter(m_dlist.begin());
  CSortList<Type>::Iter end(m_dlist.end());

  while (iter != end && data > m_dlist.getData(iter))
  {
    iter = m_dlist.next(iter);
  }

  return (m_dlist.insert(iter, data));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::erase(Iter where, Type* pData)
{
  return (m_dlist.erase(where, pData));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CSortList<Type>::popFront()
{
  return (m_dlist.popFront());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type CSortList<Type>::popBack()
{
  return (m_dlist.popBack());
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename CSortList<Type>::Iter CSortList<Type>::find
(CSortList::Iter from, CSortList::Iter to, Type data)
{
  return (m_dlist.find(from, to, data));
}

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void CSortList<Type>::merge(CSortList& dest, CSortList& source)
{
  CSortList::Iter destIter(dest.begin());
  CSortList::Iter destEnd(dest.end());

  CSortList::Iter srcIter(source.begin());
  CSortList::Iter srcEnd(source.end());

  while (!source.isEmpty())
  {
    while (destIter != destEnd && dest.getData(destIter) < source.getData(srcIter))
    {
      destIter = dest.next(destIter);
    }

    if (destIter == destEnd)
    {
      srcIter = source.end();
    }
    else
    {
      while (srcIter != srcEnd && source.getData(srcIter) < dest.getData(destIter))
      {
        srcIter = source.next(srcIter);
      }
    }

    CDlist<Type>::spliceBefore(destIter, source.begin(), srcIter);
    srcIter = source.next(srcIter);
    destIter = dest.next(destIter);
  }
}

#endif     /* __SORLTIST_H__ */


