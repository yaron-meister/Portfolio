/*****************************************************************************
 * File name:   scope_lock.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-11 11:03:26
 * Description: 
 *****************************************************************************/
 
#include <iostream>     /* 	cout, cerr	 */
#include <cstdlib>      /* EXIT_SUCCESS  */
#include <mutex>		/*	  mutex 	 */
#include <pthread.h>	/* pthread_mutex */

 
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


/***************************** Global variables *******************************/
pthread_t threads_id[10] = {0};

pthread_mutex_t g_pthread_mutex = PTHREAD_MUTEX_INITIALIZER;

std::mutex g_std_mutex;

std::recursive_mutex g_rec_mutex;

/************************** Forward Declarations ******************************/
void PThreadTest(void);
void *LockAndPrint1(void *index);

void STDMutexTest(void);
void *LockAndPrint2(void *index);

void RecMutexTest(void);
void *LockAndPrint3(void *index);

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main()
{
	printf("\n****************** PThread - TEST ***************************\n");
	PThreadTest();

	printf("\n***************** STD::Mutex - TEST *************************\n");
 	STDMutexTest();

 	printf("\n****************** Rec-Mutex - TEST *************************\n");
 	RecMutexTest();

    return (EXIT_SUCCESS);
} 

/******************************************************************************/
void PThreadTest(void)
{
	size_t index = 0;
	
	for (index = 0; index < 10; ++index)
	{
		pthread_create(&threads_id[index], NULL, LockAndPrint1, (void*)index);
	}

	for (index = 0; index < 10; ++index)
	{
		pthread_join(threads_id[index], NULL);
	}

	printf("\n");
}

/**********    														 **********/
void *LockAndPrint1(void *index)
{
	{
		size_t i = 1;
		ilrd::Lock<pthread_mutex_t> lock(&g_pthread_mutex);
		for (; i <= (size_t)index; ++i)
		{
			printf("%lu ", i);
		}

		printf("\n");
	}

	return (NULL);
}

/******************************************************************************/
void STDMutexTest(void)
{
	size_t index = 0;
	
	for (index = 0; index < 10; ++index)
	{
		pthread_create(&threads_id[index], NULL, LockAndPrint2, (void*)index);
	}

	for (index = 0; index < 10; ++index)
	{
		pthread_join(threads_id[index], NULL);
	}

	printf("\n");
}

/**********    														 **********/
void *LockAndPrint2(void *index)
{
	{
		size_t i = 1;
		ilrd::Lock<std::mutex> lock(&g_std_mutex);
		for (; i <= (size_t)index; ++i)
		{
			printf("%lu ", i);
		}

		printf("\n");
	}

	return (NULL);
}

/******************************************************************************/
void RecMutexTest(void)
{
	size_t index = 0;
	
	for (index = 0; index < 10; ++index)
	{
		pthread_create(&threads_id[index], NULL, LockAndPrint3, (void*)index);
	}

	for (index = 0; index < 10; ++index)
	{
		pthread_join(threads_id[index], NULL);
	}

	printf("\n");
}

/**********    														 **********/
void *LockAndPrint3(void *index)
{
	{
		if ((size_t)index > 10)
		{
			return (NULL);
		}

		size_t i = 1;
		ilrd::Lock<std::recursive_mutex> lock(&g_rec_mutex);
		for (; i <= (size_t)index; ++i)
		{
			printf("%lu ", i);
		}

		printf("\n");

		LockAndPrint3((void*)((size_t)index + 1));
	}

	return (NULL);
}
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
