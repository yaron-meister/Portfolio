/*****************************************************************************
* File name:   timeout.cpp
* Developer:   Yaron
* Date:        2021-02-07 11:04:53
* Description: Source file for class 'CTimeout'
*****************************************************************************/

#include "timeout.h"

//////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CTimeout::CTimeout()	: m_startTime(std::chrono::high_resolution_clock::now())
											, m_durationInMilli(0)
{}

/////////////////////////////////////////////////////////////////////////////
void CTimeout::startNow(std::chrono::duration<double, std::milli> durationInMilli)
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_durationInMilli = durationInMilli;
}

/////////////////////////////////////////////////////////////////////////////
bool CTimeout::hasExpired()
{
	auto currentTime(std::chrono::high_resolution_clock::now());
	std::chrono::duration<double, std::milli> currentDurationInMilli(currentTime - m_startTime);

	return (currentDurationInMilli > m_durationInMilli);
}