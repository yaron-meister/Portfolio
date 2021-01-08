/*****************************************************************************
 * File name:   plug_and_play.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Daria
 * Date:        2019-04-22 11:33:22
 * Description: Plug & Play implementation
 *****************************************************************************/

#include <iostream>                 // cout
#include <sys/inotify.h>            // inotify_init, inotify_add_watch 
#include <errno.h>                  // perror
#include <unistd.h>                 // read
#include <dlfcn.h>                  // dlopen, dlclose
#include <stdexcept>                // std::runtime_error

#include "utils.h"                  // DBG
#include "plug_and_play.h"          // Forward declarations 

using namespace ilrd;
/********************************* Macros *************************************/ 
const int EVENT_SIZE = sizeof(struct inotify_event);  
const int BUF_LEN = 1024 * (EVENT_SIZE + 100);

/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/
// bool g_is_monitoring = true;

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/* Class DirMonitor */
/******************************************************************************/ 
DirMonitor::DirMonitor(const std::string& path_name) : m_path_name(path_name)
{
    m_notify_fd = inotify_init();
    if (-1 == m_notify_fd)
    {
        perror("inotify_init");
        throw std::runtime_error("inotify_init failure");
    }

    m_notify_wd = inotify_add_watch(m_notify_fd, m_path_name.c_str(), 
                                    IN_MODIFY | IN_CREATE);
    if (-1 == m_notify_wd)
    {
        perror("inotify_add_watch failure");
        throw std::runtime_error("inotify_add_watch failure");
    }

    m_thread = std::thread(&DirMonitor::ThreadFunc, this);
}

/******************************************************************************/
void DirMonitor::ThreadFunc()
{
    int length;
    char buffer[BUF_LEN];
    struct inotify_event* event;

    while (1) //(g_is_monitoring) 
    {
        int i = 0;

        length = read(m_notify_fd, buffer, BUF_LEN);
        if (-1 == length) 
        {
            perror("read");
            throw std::runtime_error("read");
        }  

        while (i < length) 
        {
            event = (struct inotify_event*) &(buffer[i]);
            
            if (event->len) 
            {
                if (event->mask & IN_CREATE) 
                {
                    if (event->mask & IN_ISDIR) 
                    {
                        DBG(std::cout << "The directory " <<
                                              event->name << " was created\n");
                        DBG(std::cout << "Doing nothing\n");
                    }
                    else 
                    {
                        DBG(std::cout << "The file " <<
                                         event->name << " was created\n");
                        m_publisher.Publish
                                 (m_path_name + "/" + std::string(event->name));
                    }
                }
                else if (event->mask & IN_MODIFY)
                {
                    if (event->mask & IN_ISDIR) 
                    {
                        DBG(std::cout << "The directory " <<
                                              event->name << " was modified\n");
                        DBG(std::cout << "Doing nothing\n");
                    }
                    else 
                    {
                        DBG(std::cout << "The file " <<
                                         event->name << " was modified\n");
                        m_publisher.Publish
                                 (m_path_name + "/" + std::string(event->name));
                    }
                }
            }

            i += EVENT_SIZE + event->len;
        }

        if (IN_IGNORED == event->mask)
        {
            break;
        }
    }
}

/******************************************************************************/ 
DirMonitor::~DirMonitor()
{
    if (-1 == inotify_rm_watch(m_notify_fd, m_notify_wd))
    {
        perror("inotify_rm_watch");
        throw std::runtime_error("inotify_rm_watch");
    }
    
    m_thread.join();

    if (-1 == close(m_notify_fd))
    {
        perror("close");
        throw std::runtime_error("close");
    }

}

/******************************************************************************/
Publisher<std::string>* DirMonitor::GetPublisher()
{
    return (&m_publisher);
}


/******************************************************************************/
/* Class DllLoader */
/******************************************************************************/
DllLoader::DllLoader(Publisher<std::string>* publisher) :
              m_subscriber(publisher, &DllLoader::Load, &DllLoader::Stop, *this)
{}

/******************************************************************************/
DllLoader::~DllLoader()
{
    for (auto it = m_handles.begin(); it != m_handles.end(); ++it)
    {
        if (0 != dlclose(*it))
        {
            throw std::runtime_error(dlerror());
        }
    }
}

/******************************************************************************/
void DllLoader::Load(const std::string& file_name)
{ 
    void* handle = dlopen(file_name.c_str(), RTLD_LAZY);
    if (nullptr == handle)
    {
        throw std::runtime_error(dlerror());
    }

    m_handles.push_back(handle);
}

/******************************************************************************/
void DllLoader::Stop()
{}



/******************************************************************************/
/* Class iNotify */
/******************************************************************************/
// iNotify::iNotify(const std::string& path_name) : m_path_name(path_name)
// {
//     m_notify_fd = inotify_init();
//     if (-1 == m_notify_fd)
//     {
//         perror("inotify_init");
//         throw std::runtime_error("inotify_init failure");
//     }

//     m_notify_wd = inotify_add_watch(m_notify_fd, m_path_name.c_str(), 
//                              IN_MODIFY | IN_CREATE | IN_DELETE );
//     if (-1 == m_notify_wd)
//     {
//         perror("inotify_add_watch failure");
//         throw std::runtime_error("inotify_add_watch failure");
//     }

//     UNUSED_VAR(path_name);
// }

// /******************************************************************************/
// iNotify::~iNotify()
// {
//     if (-1 == inotify_rm_watch(m_notify_fd, m_notify_wd))
//     {
//         perror("inotify_rm_watch");
//         throw std::runtime_error("inotify_rm_watch");
//     }
    
//     if (-1 == close(m_notify_fd))
//     {
//         perror("close");
//         throw std::runtime_error("close");
//     }
// }

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
