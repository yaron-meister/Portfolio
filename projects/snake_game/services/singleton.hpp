/*****************************************************************************
 * File name:   singleton.hpp
 * Developer:   Yaron Meister
 * Date:        2019-04-02 14:26:20
 * Description: Singleton implementation file
 *****************************************************************************/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <mutex>
#include <atomic>


template <typename T>
class Singleton
{
public:
  static T* GetInstance();

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

private:
  static T*         m_instance;
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
T* Singleton<T>::m_instance(nullptr);

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

  // Mutex lock
  std::lock_guard<std::mutex> lock(m_mutex);

  if (nullptr == m_instance)
  {
    m_instance = new T;
  }

  return (m_instance);
}


#endif     /* __SINGLETON_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/