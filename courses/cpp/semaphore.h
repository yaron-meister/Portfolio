/*****************************************************************************
 * File name:   semaphore.h
 * Developer:   HRD7
 * Version: 
 * Date:        2019-03-11 18:40:29
 * Description: 
 *****************************************************************************/

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <iostream>     /* 	cout, cerr	*/
#include <cstdlib>      /* EXIT_SUCCESS */
#include <semaphore.h>	/*	  sem_t 	*/
#include <cerrno>		/*	  errno		*/
#include <unistd.h>		/*	  sleep		*/


namespace ilrd
{
	class Sem
	{
	public:
		Sem(int initial_val);
		~Sem();

		int Wait();
		int Post();
		int TryWait();
		int TimedWait(const struct timespec* abs_timeout);

	private:
		sem_t* m_sem;

		Sem(const Sem& other);
		Sem& operator=(const Sem& other);
	};

 
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
Sem::Sem(int initial_val) : m_sem(new sem_t)
{
	sem_init(m_sem, 0, initial_val);
}

/******************************************************************************/
Sem::~Sem()
{
	sem_destroy(m_sem);

	delete m_sem;
	m_sem = 0;
}

/******************************************************************************/
int Sem::Wait()
{
	return (sem_wait(m_sem));
}

/******************************************************************************/
int Sem::Post()
{
	return (sem_post(m_sem));
}

/******************************************************************************/
int Sem::TryWait()
{
	return (sem_trywait(m_sem));
}

/******************************************************************************/
int Sem::TimedWait(const struct timespec* abs_timeout)
{
	return (sem_timedwait(m_sem, abs_timeout));
}


} //namespace ilrd 

 

 
#endif     /* __SEMAPHORE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
