/*****************************************************************************
 * File name:   thread_pool.h
 * Developer:   HRD7
 * Version:     1
 * Date:        2019-04-14 10:43:22
 * Description: Thread Pool header
 *****************************************************************************/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <atomic>  

#include "wpq.h"

namespace ilrd
{

class Task;
class Pause;

/******************************************************************************/
class ThreadPool final
{
public:    
    static const size_t DEFAULT_THREADS = 4;

    explicit ThreadPool(size_t num_of_threads = DEFAULT_THREADS);
    ~ThreadPool();
    
    // Un-copyable
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Adding Task for threads to run
    // After finish running the task get removed from the pool
    void AddTask(std::shared_ptr<Task> task);

    // Adding threads means adding free threads to the pool
    // Removing threads means that <delta> threads that finish their tasks
    // first get removed from the pool
    void SetNumOfThreads(size_t num_of_threads);
    size_t GetNumOfThreads() const;

    // Blocks for at most <timeout> putting all the threads that finish their
    // tasks into paused state (see Resume())
    // returns num of running threads
    template< class Rep, class Period >
    std::size_t Pause(std::chrono::duration<Rep, Period> const& timeout);

    // Put all the threads in the pool into paused state
    // Blocks until all the threads finish their current tasks
    void Pause();

    // Resumes all the paused threads allowing them to proceed with the work
    void Resume();

private:
    struct CompareImpl
    {
        bool operator()(std::shared_ptr<Task> lhs, std::shared_ptr<Task> rhs);
    };

    WPQ<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, CompareImpl>
                                                                     m_task_pq;
    std::vector<std::thread> m_pool;
    
    // Garbage-collector
    std::vector<std::thread> m_garbage;
    
    // Pause mechanism
    std::atomic<bool>       m_pause_is_valid;
    std::mutex              m_pause_mutex;
    std::condition_variable m_pause_cond;
    std::atomic<size_t>     m_paused_counter;

    std::mutex              m_terminate_mutex;

    // Number of threads according to user's demand - the valid threads
    std::atomic<size_t>     m_desired_threads_num;
    mutable std::mutex      m_set_mutex;

    void ThreadFunc();
};

/******************************************************************************/
class Task
{
public:
    friend class ThreadPool;
    
    enum class Priority
    {
        // SYSTEM's priorities
        SYSTEM_TERMINATE = 0,
        SYSTEM_PAUSE,
        // USER's priorities
        VERY_HIGH,
        HIGH,
        MEDIUM,
        LOW,
        VERY_LOW
    };

    explicit Task(Priority priority = Priority::VERY_LOW);
    virtual ~Task() = 0;

    Priority GetPriority();
    bool operator<(const Task& other) const;
    
    // Un-copyable
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

private:
    virtual void Execute() = 0;
    Priority m_priority;
};

/******************************************************************************/
// A task class for implementing Pause methods
class Pause : public Task
{
public:
    Pause(std::atomic<bool>& pause_is_valid, std::mutex& mutex,
                                        std::condition_variable& pause_cond_var,
                                           std::atomic<size_t>& paused_counter);
    ~Pause() override;

private:
    std::atomic<bool>&       m_pause_is_valid;
    std::mutex&              m_pause_mutex;
    std::condition_variable& m_pause_cond;
    std::atomic<size_t>&     m_paused_counter;

    void Execute() override;
};

/******************************************************************************/
// A task class for implementing distructions
class Terminate : public Task
{
public:  
    Terminate();
    ~Terminate() override;

private:
    void Execute() override;
};

/*******************************************************************************
                     Template Functions Implementations
*******************************************************************************/  
template< class Rep, class Period >
std::size_t ThreadPool::Pause(std::chrono::duration<Rep, Period> const& timeout)
{
    m_pause_is_valid = true;
    std::shared_ptr<ilrd::Pause> task_pause (new ilrd::Pause(m_pause_is_valid,
                                m_pause_mutex, m_pause_cond, m_paused_counter));

    for (size_t i = 0; i < m_desired_threads_num; ++i)
    {
       AddTask(task_pause);
    }

    std::this_thread::sleep_for(timeout);
    m_pause_is_valid = false;

    return (m_desired_threads_num - m_paused_counter);
}



} // namespace ilrd

#endif //__THREAD_POOL_H__


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
