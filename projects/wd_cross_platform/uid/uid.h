/*****************************************************************************
* File name:   uid.h
* Developer:   Yaron
* Date:        2018-11-25 11:59:11
* Description: Header file for Unique ID
*****************************************************************************/

#ifndef __UID_H__
#define __UID_H__

#include <ctime>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/types.h>   // pid_t      
#endif // WIN32

class CUid
{
public:
  //CTor
  CUid(bool isBad = false);

  //Operators
  bool operator==(const CUid& other) const;
  bool operator!=(const CUid& other) const;

  /*
  * The function get uid and check if uid is valid.
  * return: 0 - false,
  *        !0 - true (counter = 0).
  * note: boolean function.
  */
  bool isBad();
  size_t getCounter() const;

private:

#ifdef WIN32
	DWORD m_pid;
#else
	pid_t m_pid;						// use getpid()
#endif // WIN32

	time_t m_time;   
  size_t m_counter;

  static size_t g_counter;
};


#endif     /* __UID_H__ */
