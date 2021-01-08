/*****************************************************************************
 * File name:   monitor.h
 * Developer:   HRD7
 * Date:        2019-04-29 17:25:47
 * Description: Monitor header
 *****************************************************************************/

#ifndef __MONITOR_H__
#define __MONITOR_H__


#include <vector>           // std::vector

#include "logger.h"

namespace ilrd
{

class Monitor
{
public:
    Monitor();
    ~Monitor();

    // Un-copyable
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    void Add(int fd);
    int Wait();

private:
    int m_epoll_fd;
    std::vector<struct epoll_event> m_events;
    Logger* m_logger;
};


} //ilrd
 
 
#endif     /* __MONITOR_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
