/*****************************************************************************
 * File name:   handleton.h
 * Developer:   HRD7
 * Version: 
 * Date:        2019-04-04 13:29:14
 * Description: 
 *****************************************************************************/

#ifndef __HANDLETON_H__
#define __HANDLETON_H__


#include <mutex>
#include <atomic>

namespace ilrd
{

template <typename T>
class Handleton
{
    public:
        static T* GetInstance();

        // Un-copyable
        Handleton(const Handleton&) = delete;
        Handleton& operator=(const Handleton&) = delete;
            
        T& operator*();              // for *ptr = val
        T* operator->();             // for ptr->x = val

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
std::atomic<T*> Handleton<T>::m_instance(nullptr);

template <typename T>
std::mutex Handleton<T>::m_mutex;

/********************************** Macros ************************************/
#define INIT_HANDLETON(type) \
template<> \
type* Handleton<type>::m_instance = nullptr; \
template<> \
std::mutex Handleton<type>::m_mutex;

/*******************************************************************************
                        Functions Implementations
*******************************************************************************/  
template <typename T>
T* Handleton<T>::GetInstance() 
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
template<typename T>
T& Handleton<T>::operator*()
{
	return (*m_instance);
}

/******************************************************************************/
template<typename T>
T* Handleton<T>::operator->()
{
	return (m_instance);
}


} //ilrd
 


#endif     /* __HANDLETON_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
