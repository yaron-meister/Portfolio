/*****************************************************************************
 * File name:   slist_t.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-02-20 14:36:04
 * Description: 
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/

#include "slist.h"      /* Forward declarations */


using namespace ilrd;



/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
template<typename TYPE>
SListT<TYPE>::SListT()
{
	m_dummy.m_data = (TYPE)0xDEADBEEFDEADBEEF;
	m_dummy.m_next = 0;
}

/******************************************************************************/
template<typename TYPE>
SListT<TYPE>:: ~SListT()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

/******************************************************************************/
template<typename TYPE>
void SListT<TYPE>::Push(TYPE data)
{
	Node *pushed   = new Node;
	pushed->m_data = data;
	pushed->m_next = m_dummy.m_next;
	m_dummy.m_next = pushed;
}

/******************************************************************************/
template<typename TYPE>
TYPE SListT<TYPE>::Pop(void)
{
	TYPE data 	 = 0;
	Node *popped = 0;

	if (!IsEmpty())
	{
		popped = m_dummy.m_next; 
		data   = popped->m_data;

		m_dummy.m_next = popped->m_next;

		delete popped;
		popped = 0;
	}
	
	return (data);
}

/******************************************************************************/
template<typename TYPE>
bool SListT<TYPE>::IsEmpty(void) const
{
	return (0 == m_dummy.m_next);
}

/******************************************************************************/
template<typename TYPE>
std::size_t SListT<TYPE>::Size(void) const
{
	std::size_t size = 0;
	Node *iter 		 = 0;

	if (!IsEmpty())
	{
		iter = m_dummy.m_next;

		while (0 != iter)
		{
			++size;
			iter = iter->m_next;
		}
	}

	return (size);
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   