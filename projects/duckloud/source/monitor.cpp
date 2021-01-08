/*****************************************************************************
 * File name:   monitor.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-29 17:25:47
 * Description: 
 *****************************************************************************/

#include <exception>    // runtime_exception
#include <sys/epoll.h>  // epoll_create1
#include <unistd.h>     // close

#include "monitor.h"    // Forward declarations
#include "utils.h"      // DBG

using namespace ilrd;
/********************************* Macros *************************************/ 
const int STDIN_FD   = 0;
const int MAX_EVENTS = 1;


/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/
struct epoll_event events[MAX_EVENTS];


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/  
Monitor::Monitor() : m_logger(Handleton<Logger>::GetInstance())
{
    m_epoll_fd = epoll_create1(0);
    if (-1 == m_epoll_fd)
    {
        m_logger->Write("epoll_create");
        perror("epoll_create");
        throw std::runtime_error("epoll_create");
    }
}

/******************************************************************************/
Monitor::~Monitor()
{
    close(m_epoll_fd);
}

/******************************************************************************/
void Monitor::Add(int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &event))
    {
        m_logger->Write("epoll_ctl");
        perror("epoll_ctl");
        close(m_epoll_fd);
        throw std::runtime_error("epoll_ctl");
    }

    m_events.push_back(event);
} 

/******************************************************************************/
int Monitor::Wait()
{
    DBG(std::cout << "\n\nNext epoll_wait()\n\n");
    m_logger->Write("\n\nNext epoll_wait()\n\n");

    int nfds = epoll_wait(m_epoll_fd, events, MAX_EVENTS, -1);
    if (-1 == nfds)
    {
        if (EINTR != errno) 
        {
            m_logger->Write("epoll_wait");
            perror("epoll_wait");
            throw std::runtime_error("epoll_wait");
        }
        else
        {
            return (EXIT_FAILURE);
        }
    }

    DBG(printf("\n\nepoll_wait DONE\n\n"));
    m_logger->Write("\n\nepoll_wait DONE\n\n");

    return (events[0].data.fd);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
