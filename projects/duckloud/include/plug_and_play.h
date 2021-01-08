/*****************************************************************************
 * File name:   plug_and_play.h
 * Developer:   HRD07
 * Version: 	0
 * Date:        2019-04-22 09:54:54
 * Description: Plug & Play header
 *****************************************************************************/

#ifndef __PLUG_AND_PLAY_H__
#define __PLUG_AND_PLAY_H__

#include <cstddef>      // size_t
#include <thread>       // std::thread

#include "publisher_subscriber.h"

namespace ilrd
{
    class iNotify
    {
    public:
        friend class DirMonitor;

        explicit iNotify(const std::string& path_name);
        ~iNotify();

        //UnCopyable
        iNotify(const iNotify& other)        = delete;
        iNotify& operator=(const iNotify&)   = delete;
        
        //UnMoveable
        iNotify(iNotify&& other)             = delete;
        iNotify& operator=(iNotify&&)        = delete;

    private:
        std::string m_path_name;
        int         m_fd;
        int         m_wd;
    };
/*****************************************************************************/
    class DirMonitor
    {
    public:
        // DirMonitor recives the monitored file pathname. 
        // exception is thrown if ctor failed(run_time error)
        explicit DirMonitor(const std::string& path_name);
        ~DirMonitor();
        
        //Un-Copyable
        DirMonitor(const DirMonitor& other)        = delete;
        DirMonitor& operator=(const DirMonitor&)   = delete;
        
        //Un-Moveable
        DirMonitor(DirMonitor&& other)             = delete;
        DirMonitor& operator=(DirMonitor&&)        = delete;
        
        Publisher<std::string> *GetPublisher();

    private:    
        Publisher<std::string> m_publisher;
        std::string            m_path_name;
        int                    m_notify_fd;
        int                    m_notify_wd;
        std::thread            m_thread;

        void ThreadFunc();
    };

/*****************************************************************************/
    class DllLoader
    {
    public:    
        explicit DllLoader(Publisher<std::string>* publisher);
        ~DllLoader();

        //Un-Copyable
        DllLoader(const DllLoader& other)        = delete;
        DllLoader& operator=(const DllLoader&)   = delete;

        //Un-Moveable
        DllLoader(DllLoader&& other)             = delete;
        DllLoader& operator=(DllLoader&&)        = delete;

        void Load(const std::string& file_name);
        void Stop();

    private:
        Subscriber<std::string, DllLoader> m_subscriber;
        std::vector<void*>                 m_handles;
    };

/*****************************************************************************/
    


}//ILRD

 
#endif     /* __PLUG_AND_PLAY_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
