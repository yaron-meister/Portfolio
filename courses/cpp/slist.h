/*****************************************************************************
 * File name:   slist.h
 * Developer:   HRD7
 * Date:        2019-02-20 10:40:46
 * Description: SList header
 *****************************************************************************/

#ifndef __SLIST_H__
#define __SLIST_H__

#include <cstdlib>	/* size_t */


namespace ilrd
{
	class SList
	{
	public:
		
		/*
		 * Ctor for Slist O(1)
		 */
		SList();

		/*
		 * Dtor for Slist O(n)
		 */
		~SList();

		/*
		 * The pop function will pop the head.
		 * return: pointer to data, NULL if empty list. O(1)
		 */
		void *Pop(void);

		/*
		 * Push to the head of the list
		 * can not fail (using new)
		 */
		void Push(void* const data);

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
			void *m_data;
			Node *m_next;
		};

		Node m_dummy; // dummy.next is pointer to the head of the list.
		//
		SList(const SList& s);
		SList& operator= (const SList& s);
	};
}
 
#endif     /* __SList_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
