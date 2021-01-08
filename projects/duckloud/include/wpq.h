/*****************************************************************************
 * File name:   wpq.h
 * Developer:   HRD7
 * Version:     1
 * Date:        2019-04-11 16:12:40
 * Description: WPQ header
 *****************************************************************************/

#ifndef __WPQ_H__
#define __WPQ_H__
#include <queue>                /* priority_queue                            */
#include <vector>               /* vector                                    */
#include <functional>           /* less                                      */
#include <mutex>                /* mutex                                     */
#include <condition_variable>   /* condition_variable                        */
#include <chrono>               /* chrono                                    */

namespace ilrd
{

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>class WPQ final
{
public:
    WPQ() = default;

    /* WARNING: destructing the WPQ when some thread is blocked in Pop() yields
     * undefined behavior
     */
    ~WPQ() = default;

    WPQ(WPQ<T, Container, Compare> const& other) = delete;
    WPQ<T, Container, Compare>&
        operator=(WPQ<T, Container, Compare> const& other) = delete;

    /* Thread-safe functions:
     * Pop(), Push(), IsEmpty(), Size()
     * Each of these calls tries to establish an exclusive lock on the WPQ
     */

    /* O(log(N)) */
    /* If empty, blocks until an element is inserted (on concurrent runs, only
     * one waiting thread returns)
     * Returns a copy of the value
     */
    void Pop(T& out_val);

    template< class Rep, class Period >
    bool Pop(T& out_val, std::chrono::duration<Rep, Period> const& timeout);

    /* O(log(N)) */
    /* Copies the value */
    void Push(T const& val);

    std::size_t Size() const;
    bool IsEmpty() const;

private:
    std::priority_queue<T, Container, Compare> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
};


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
/******************************************************************************/
template<class T, class Container, class Compare>
void WPQ<T, Container, Compare>::Pop(T& out_val)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while (m_queue.empty())
    {
        m_cond.wait(lock);
    }

    out_val = m_queue.top();
    m_queue.pop();
}

/******************************************************************************/
template<class T, class Container, class Compare>
template<class Rep, class Period>
bool WPQ<T, Container, Compare>::
              Pop(T& out_val, std::chrono::duration<Rep, Period> const& timeout)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_queue.empty() &&
        std::cv_status::timeout == m_cond.wait_for(lock, timeout))
    {
        return (false);
    }
    
    out_val = m_queue.top();
    m_queue.pop();

    return (true);
}

/******************************************************************************/
template<class T, class Container, class Compare>
void WPQ<T, Container, Compare>::Push(T const& val)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_queue.push(val);

    m_cond.notify_one();
}

/******************************************************************************/ 
template<class T, class Container, class Compare>
std::size_t WPQ<T, Container, Compare>::Size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_queue.size());
}

/******************************************************************************/
template<class T, class Container, class Compare>
bool WPQ<T, Container, Compare>::IsEmpty() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_queue.empty());
}


} // namespace ilrd

#endif /* __WPQ_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
