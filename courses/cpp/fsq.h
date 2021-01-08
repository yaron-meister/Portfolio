/*****************************************************************************
 * File name:   fsq.h
 * Developer:   Yaron Meister
 * Version: 	0
 * Date:        2019-03-11 23:51:29
 * Description: Fixed-Size Queue header
 *****************************************************************************/

#ifndef __FSQ_H__
#define __FSQ_H__

#include "lock.h"			/*	   Lock 	*/
#include "semaphore.h"		/*	   Sem 		*/

namespace ilrd
{
	template <size_t SIZE>
	class FSQ
	{
		public:
			
			FSQ();

			void Read(size_t *other_buffer);
			void Write(int integer);
			//void Print();

		private:

			int m_buffer[SIZE];
			int* m_reader;
			int* m_writer;
			Sem w_sem;
			Sem r_sem;
			std::mutex w_mutex;
			std::mutex r_mutex;

			FSQ(const FSQ& other);
			FSQ& operator=(const FSQ& other);
	};


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
template <size_t SIZE>
FSQ<SIZE>::FSQ() : w_sem(SIZE), r_sem(0)
{
	m_reader = m_buffer;
	m_writer = m_buffer;
}

/******************************************************************************/
template <size_t SIZE>
void FSQ<SIZE>::Read(size_t *other_buffer)
{
	r_sem.Wait();

	{
		Lock<std::mutex> lock(&r_mutex);

		*other_buffer = *m_reader;

		if (m_reader == (m_buffer + SIZE))
		{
			m_reader = m_buffer;
		}
		else
		{
			++m_reader;
		}
	}

	w_sem.Post();
}

/******************************************************************************/
template <size_t SIZE>
void FSQ<SIZE>::Write(int integer)
{
	w_sem.Wait();

	{
		Lock<std::mutex> lock(&w_mutex);

		*m_writer = integer;

		if (m_writer == (m_buffer + SIZE))
		{
			m_writer = m_buffer;
		}
		else
		{
			++m_writer;
		}
	}

	r_sem.Post();
}

/******************************************************************************/
/*
template <size_t SIZE>
void FSQ<SIZE>::Print()
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		std::cout << m_buffer[i] << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
}
*/

} //ilrd	

 
#endif     /* __FSQ_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
