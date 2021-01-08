/*****************************************************************************
 * File name:   uid.cpp
 * Developer:   Yaron Meister
 * Date:        2018-11-25 11:59:11
 * Description: Source file for Unique ID
 *****************************************************************************/

#ifndef WIN32
#include <sys/time.h>   // gettimeofday
#include <unistd.h>     // getpid    
#endif

#include "uid.h"  


// Global variables
size_t CUid::g_counter = 1;


/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CUid::CUid(bool isBad) : m_pid(0), m_time(0), m_counter(0)
{
#ifdef WIN32
  m_pid = GetCurrentProcessId();
#else
  m_pid = getpid();
#endif

  if ( !isBad && (-1 != time(&m_time)) )
  {
    m_counter = g_counter;
  }

  ++g_counter;
}

/////////////////////////////////////////////////////////////////////////////
bool CUid::operator==(const CUid& other) const
{
  return (m_pid == other.m_pid && m_counter == other.m_counter);
}

/////////////////////////////////////////////////////////////////////////////
bool CUid::operator!=(const CUid& other) const
{
  return !(operator==(other));
}

/////////////////////////////////////////////////////////////////////////////
bool CUid::isBad()
{
  return (0 == m_counter);
}

/////////////////////////////////////////////////////////////////////////////
size_t CUid::getCounter() const
{
  return (m_counter);
}