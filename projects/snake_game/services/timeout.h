/*****************************************************************************
 * File name:   timeout.h
 * Developer:   Yaron Meister
 * Date:        2021-02-07
 * Description: Header file for the class 'CTimeout'
 *****************************************************************************/

#ifndef __TIMEOUT_H__
#define __TIMEOUT_H__

#include <chrono>

class CTimeout
{
public:
  typedef std::chrono::duration < double, std::milli> DurationInMilli;

  // CTor
  CTimeout();

  void startNow(std::chrono::duration<double, std::milli> intervalInMilli);
  bool hasExpired();
	
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
  DurationInMilli m_durationInMilli;
};


#endif // __TIMEOUT_H__