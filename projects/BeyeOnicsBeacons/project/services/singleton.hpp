////////////////////////////////////////////////////////////////////////////////
//  File name:  singleton.hpp
//  Developer:  Yaron Meister
//  Date:       02.04.2019
//  Desciption: A header file for Singleton
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <mutex>


template <typename T>
class Singleton
{
public:
  static T* GetInstance();

  // Un-copyable
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

////////////////////////////////////////////////////////////////////////////////
//													Functions Implementations
////////////////////////////////////////////////////////////////////////////////
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


