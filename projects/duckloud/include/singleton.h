/*****************************************************************************
 * File name:   singleton.h
 * Developer:   HRD7
 * Version: 
 * Date:        2019-04-02 14:26:20
 * Description: Singleton header
 *****************************************************************************/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <mutex>
#include <atomic>

namespace ilrd
{

    template <typename T>
    class Singleton 
    {
        public:
            static T* GetInstance();

            Singleton(const Singleton&) = delete;
            Singleton& operator=(const Singleton&) = delete;
            
        private:
            static std::atomic<T*> m_instance;
            static std::mutex m_mutex;

            class MemGuard 
            {
                public: 
                    ~MemGuard() 
                    {
                        delete m_instance;
                        m_instance = nullptr;
                    }
            };
    };

template <typename T>
std::atomic<T*> Singleton<T>::m_instance(nullptr);

template <typename T>
std::mutex Singleton<T>::m_mutex;

/*******************************************************************************
                        Functions Implementations
*******************************************************************************/  
template <typename T>
T* Singleton<T>::GetInstance() 
{
    // Destruction guard
    static MemGuard guard;

    // 'tmp' for keeping 'm_instance' valid
    T* tmp = m_instance.load(std::memory_order_relaxed);
    
    // memory barrier
    std::atomic_thread_fence(std::memory_order_acquire);
    
    if (nullptr == tmp) 
    {
        // mutex lock
        std::lock_guard<std::mutex> lock(m_mutex); 
 
        // 'tmp' for keeping 'm_instance' valid
        tmp = m_instance.load(std::memory_order_relaxed);
        if (nullptr == tmp) 
        {
            tmp = new T;
            
            // memory barrier release
            std::atomic_thread_fence(std::memory_order_release);

            // updating 'm_instance'
            m_instance.store(tmp, std::memory_order_relaxed);
        }
    }
    
    return (tmp);
}
/******************************************************************************/

} //ilrd 

 
#endif     /* __SINGLETON_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
