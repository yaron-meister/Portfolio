/*****************************************************************************
 * File name:   slist.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Yael 
 * Date:        2019-02-20 10:40:46
 * Description: Slist implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/

#include "slist.h"      /* Forward declarations */


using namespace ilrd;

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
SList:: SList()
{
	m_dummy.m_data = (void*)0xDEADBEEFDEADBEEF;
	m_dummy.m_next = 0;
}

/******************************************************************************/
SList:: ~SList()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

/******************************************************************************/
void SList::Push(void* const data)
{
	Node *pushed   = new Node;
	pushed->m_data = data;
	pushed->m_next = m_dummy.m_next;
	m_dummy.m_next = pushed;
}

/******************************************************************************/
void* SList::Pop(void)
{
	void *data 	 = 0;
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
bool SList::IsEmpty(void) const
{
	return (0 == m_dummy.m_next);
}

/******************************************************************************/
std::size_t SList::Size(void) const
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
