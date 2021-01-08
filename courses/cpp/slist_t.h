/*****************************************************************************
 * File name:   slist_t.h
 * Developer:   Yaron Meister
 * Date:        2019-02-20 14:36:04
 * Description: 
 *****************************************************************************/

#ifndef __SLIST_T_H__
#define __SLIST_T_H__

#include <cstdlib>	/* size_t */


namespace ilrd
{
	template <typename TYPE>
	class SListT
	{
	public:
		
		/*
		 * Ctor for Slist O(1)
		 */
		SListT();

		/*
		 * Dtor for Slist O(n)
		 */
		~SListT();

		/*
		 * The pop function will pop the head.
		 * return: pointer to data, NULL if empty list. O(1)
		 */
		TYPE Pop(void);

		/*
		 * Push to the head of the list
		 * can not fail (using new)
		 */
		void Push(TYPE data);

		/*
		 * return the size of the list. O(n)
		 *
		 */
		std::size_t Size(void) const;

		/*
		 * boolean function return: true - empty, false- not empty. O(1)
		 * 
		 */
		bool IsEmpty(void) const;

	private:

		struct Node // not taking any responsibilty there fore struct and not class
		{
			TYPE m_data;
			Node *m_next;
		};

		Node m_dummy; // dummy.next is pointer to the head of the list.
		//
		SListT(const SListT& s);
		SListT& operator= (const SListT& s);
	};
}



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




 
#endif     /* __SList_T_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/