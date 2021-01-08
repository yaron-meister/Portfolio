/*****************************************************************************
 * File name:   thread_pool.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Alon
 * Date:        2019-04-14 10:43:22
 * Description: Thread Pool implementation
 *****************************************************************************/
 
#include <iostream>         /* 		cout, cerr		*/

#include "thread_pool.h"    /* Forward declarations */

using namespace ilrd;
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
/* class ThreadPool */
/******************************************************************************/
ThreadPool::ThreadPool(std::size_t num_of_threads) : 
                                   m_pause_is_valid(false),
                                   m_paused_counter(0),
                                   m_desired_threads_num(0)
{
    // Initiating the threads according to the desired number
    SetNumOfThreads(num_of_threads);
}

/******************************************************************************/
void ThreadPool::ThreadFunc()
{
    std::shared_ptr<Task> task(nullptr);

    try
    {
    
        // While I didn't meet TASK TERMINATE - pop and execute
        do
        {
            m_task_pq.Pop(task);
            task->Execute();
        }
        while (Task::Priority::SYSTEM_TERMINATE != task->GetPriority());
    
    }
    catch(const std::exception& e)
    {
        std::cerr << "POP || EXECUTE\n";
        std::cerr << e.what() << '\n';
    }
    
    // Getting to this line says that I'm about to be terminated.
    // The loop searches me in the pool and passes me to the garbage-collector 
    std::lock_guard<std::mutex> lock(m_terminate_mutex);
    for (auto it = m_pool.begin(); it != m_pool.end(); ++it)
    {
        if (std::this_thread::get_id() == it->get_id())
        {
            m_garbage.push_back(std::move(*it));
            m_pool.erase(it);

            break;
        }    
    }
}

/******************************************************************************/
ThreadPool::~ThreadPool()
{
    // SetNumOfThreads terminates threads in case of decreasing num of threads
    SetNumOfThreads(0);

    // Confirms that there are no paused threads  
    Resume(); 

    // Confirms that all the threads are at the Garbage-collector
    while (!m_pool.empty())
    {}

    size_t garbage_size = m_garbage.size();

    for (size_t i = 0; i < garbage_size; ++i)
    {
        m_garbage[i].join();
    }
}

/******************************************************************************/
void ThreadPool::AddTask(std::shared_ptr<Task> task)
{
    m_task_pq.Push(task);
}

/******************************************************************************/
void ThreadPool::SetNumOfThreads(size_t num_of_threads)
{
    std::lock_guard<std::mutex> lock(m_set_mutex);

    // If USER wants more, initiate threads
    for (; m_desired_threads_num < num_of_threads; ++m_desired_threads_num)
    {
        m_pool.push_back(std::thread(&ThreadPool::ThreadFunc, this));
    }

    // If USER wants less, terminate threads
    for (; m_desired_threads_num > num_of_threads; --m_desired_threads_num)
    {
        std::shared_ptr<Terminate> task_terminate(new Terminate());
        AddTask(task_terminate);
    }
}

/******************************************************************************/
size_t ThreadPool::GetNumOfThreads() const
{
    // Accessing <m_desired_threads_num> is from 'SetNumOfThreads' also - 
    // demands syncing 
    std::lock_guard<std::mutex> lock(m_set_mutex);
    return (m_desired_threads_num);
}

/******************************************************************************/
void ThreadPool::Pause()
{
    m_pause_is_valid = true;
    // Creating task PAUSE
    std::shared_ptr<ilrd::Pause> task_pause (new ilrd::Pause(m_pause_is_valid,
                                m_pause_mutex, m_pause_cond, m_paused_counter));
    // Adding PAUSE tasks for every one of the threads
    for (size_t i = 0; i < m_desired_threads_num; ++i)
    {
       AddTask(task_pause);
    }

    // Blocking the main thread until all of the threads got paused 
    while (m_paused_counter != m_desired_threads_num)
    {}
}

/******************************************************************************/
void ThreadPool::Resume()
{
    m_paused_counter = 0;
    m_pause_is_valid = false;
    m_pause_cond.notify_all();
}

/******************************************************************************/
bool ThreadPool::CompareImpl::operator()
                          (std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs)
{
    // Lower value = Higher priority
    return (*rhs < *lhs);
}

/******************************************************************************/
/* class Task */
/******************************************************************************/
Task::Task(Priority priority) : m_priority(priority)
{}

/******************************************************************************/
// Default Task-Dtor implementation (because of the pure virtual)  
Task::~Task(){}

/******************************************************************************/
Task::Priority Task::GetPriority()
{
    return (m_priority);
}

/******************************************************************************/
bool Task::operator<(const Task& other) const
{
    return (m_priority < other.m_priority);
}

/******************************************************************************/
/* class Pause */
/******************************************************************************/
Pause::Pause(std::atomic<bool>& pause_is_valid, std::mutex& mutex,
 std::condition_variable& pause_cond_var, std::atomic<size_t>& paused_counter) :
                 Task(Priority::SYSTEM_PAUSE), m_pause_is_valid(pause_is_valid),
                             m_pause_mutex(mutex), m_pause_cond(pause_cond_var),
                                                m_paused_counter(paused_counter)
// 'Pause' shares the sync means of 'ThreadPool'
{}

/******************************************************************************/
Pause::~Pause()
{}

/******************************************************************************/
void Pause::Execute()
{
    if (m_pause_is_valid)
    {
        ++m_paused_counter;
    }

    // 'while' instead of 'if' because cond.wait() may awake surprisingly
    while (m_pause_is_valid)
    {
        std::unique_lock<std::mutex> lock(m_pause_mutex);
        m_pause_cond.wait(lock);
    }
}

/******************************************************************************/
/* class Terminate */
/******************************************************************************/
Terminate::Terminate() : Task(Task::Priority::SYSTEM_TERMINATE)
{}

/******************************************************************************/
Terminate::~Terminate()
{}

/******************************************************************************/
void Terminate::Execute()
{}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
