/*****************************************************************************
 * File name:   lock.h
 * Developer:   HRD7
 * Version: 	0
 * Date:        2019-03-11 18:47:50
 * Description: Class Lock header
 *****************************************************************************/

#ifndef __LOCK_H__
#define __LOCK_H__

#include <iostream>     /* 	cout, cerr	 */
#include <cstdlib>      /* EXIT_SUCCESS  */
#include <mutex>		/*	  mutex 	 */
#include <pthread.h>	/* pthread_mutex */



/***************************** Global variables *******************************/
pthread_mutex_t g_pthread_mutex = PTHREAD_MUTEX_INITIALIZER;

std::mutex g_std_mutex;

std::recursive_mutex g_rec_mutex;

/******************************************************************************/

namespace ilrd
{
	template<typename T>
	class Lock
	{
	public:
		Lock(T*);
		~Lock();

	private:
		T* m_mutex;
		Lock(const Lock& other);
		Lock& operator=(const Lock& other);
	};
 
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
template <typename T>
Lock<T>::Lock(T* mutex) : m_mutex(mutex)
{
	m_mutex->lock();
}

/******************************************************************************/
template<>
Lock<pthread_mutex_t>::Lock(pthread_mutex_t* mutex) : m_mutex(mutex)
{
	pthread_mutex_lock(m_mutex);
}

/******************************************************************************/
template <typename T>
Lock<T>::~Lock()
{
	m_mutex->unlock();
}

/******************************************************************************/
template<>
Lock<pthread_mutex_t>::~Lock()
{
	pthread_mutex_unlock(m_mutex); 
}

}// namespace ilrd


 

 
#endif     /* __LOCK_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
