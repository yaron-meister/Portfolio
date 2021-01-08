/*****************************************************************************
 * File name:   request_engine.h
 * Developer:   HRD7
 * Version:     2
 * Date:        2019-04-28 15:31:24
 * Description: Request Engine Framework header
 *****************************************************************************/

#ifndef __REQUEST_ENGINE_H__
#define __REQUEST_ENGINE_H__

#include <vector>           // std::vector
#include <exception>        // runtime_exception
#include <sys/epoll.h>      // epoll_create1
#include <unistd.h>         // close

#include "thread_pool.h"
#include "factory.h"
#include "plug_and_play.h"
#include "handleton.h"
#include "monitor.h"
#include "re_plugnplay.h"

namespace ilrd
{

/********************************* Macros *************************************/ 
const size_t NUM_OF_THREADS = (4);
const size_t STORAGE_SIZE = (128000000);

/***************************** Global variables *******************************/

/**************************** Forward Declarations ****************************/
class PlugNPlay;

/******************************************************************************/
template<typename Key, typename Params>
class RequestEngine
{
public:
    
    class Task;
    class Gateway;

    using CreatorFunc = 
                typename Factory<RequestEngine::Task, Key, Params>::FactoryFunc;
    
    RequestEngine(const std::string& path_name,
                                        size_t num_of_threads = NUM_OF_THREADS);
    ~RequestEngine() = default;

    bool ConfigTask(const Key& key, CreatorFunc creator);

    void AddGateway(Gateway& gateway);
    void Run();
    void Stop();

    // Un-copyable
    RequestEngine(const RequestEngine&) = delete;
    RequestEngine& operator=(const RequestEngine&) = delete;

private:
    std::vector<Gateway*> m_gateways; // Storing FDs
    Factory<RequestEngine<Key, Params>::Task, Key, Params>* m_factory;
    ThreadPool m_thread_pool;
    Logger* m_logger;
    Monitor m_monitor;
    bool m_stop;

    static std::unique_ptr<PlugNPlay> m_pnp_ptr;
};

template<typename Key, typename Params>
std::unique_ptr<PlugNPlay> RequestEngine<Key, Params>::m_pnp_ptr(nullptr);

/******************************************************************************/
template<typename Key, typename Params>
class RequestEngine<Key, Params>::Task : public ilrd::Task
{
public:
    using TaskPriority = Task::Priority;  
        
    // Possible values TaskPriority: VERY_HIGH, HIGH, MEDIUM, LOW, VERY_LOW
    explicit Task(TaskPriority priority = TaskPriority::VERY_LOW);
    
private:
    virtual void Execute() = 0;
};

/******************************************************************************/
template<typename Key, typename Params>
class RequestEngine<Key, Params>::Gateway
{
public:
    explicit Gateway(int fd);
    virtual ~Gateway();
    
    int GetFD() const;  

    virtual std::pair<Key, Params> Read() = 0;

private:
    int m_fd;
};



/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
/******************************************************************************/  
/* Class RequestEngine */
/******************************************************************************/
template<typename Key, typename Params>
RequestEngine<Key, Params>::
RequestEngine(const std::string& path_name, size_t num_of_threads) :
    m_factory(Handleton<Factory<RequestEngine<Key, Params>::Task, Key, Params>>
                                                               ::GetInstance()),
    m_thread_pool(num_of_threads),
    m_logger(Handleton<Logger>::GetInstance()),
    m_stop(false)
{
    std::unique_ptr<PlugNPlay> ptr(new PlugNPlay(path_name));
    m_pnp_ptr = std::move(ptr);
}

/******************************************************************************/
template<typename Key, typename Params>
bool RequestEngine<Key, Params>::
ConfigTask(const Key& key, RequestEngine<Key, Params>::CreatorFunc creator)
{
    return (m_factory->Add(key, creator));
}

/******************************************************************************/
template<typename Key, typename Params>
void RequestEngine<Key, Params>::AddGateway(Gateway& gateway)
{
    m_gateways.push_back(&gateway);
    m_monitor.Add(gateway.GetFD());
}

/******************************************************************************/
template<typename Key, typename Params>
void RequestEngine<Key, Params>::Run()
{
    while (!m_stop)
    {
        int fd = m_monitor.Wait();
        
        if (EXIT_FAILURE != fd)
        {
            for (size_t i = 0; i < m_gateways.size(); ++i)
            {
                if (fd == (m_gateways[i])->GetFD())
                {
                    std::pair<Key, Params> factory_input = (m_gateways[i])->Read();
                    
                    std::shared_ptr<RequestEngine<Key, Params>::Task> 
                                task = m_factory->CreateShared(factory_input.first,
                                                            factory_input.second);

                    m_thread_pool.AddTask(task);

                    break;
                }
            }
        }
    }
}

/******************************************************************************/
template<typename Key, typename Params>
void RequestEngine<Key, Params>::Stop()
{
    m_stop = true;
}

/******************************************************************************/  
/* Class RequestEngine<Key, Params>::Task */
/******************************************************************************/ 
template<typename Key, typename Params>
RequestEngine<Key, Params>::Task::Task(TaskPriority priority) : 
                                                            ilrd::Task(priority)
{}



/******************************************************************************/  
/* Class RequestEngine<Key, Params>::Gateway */
/******************************************************************************/ 
template<typename Key, typename Params>
RequestEngine<Key, Params>::Gateway::Gateway(int fd) : m_fd(fd)
{}

/******************************************************************************/
template<typename Key, typename Params>
RequestEngine<Key, Params>::Gateway::~Gateway()
{
    close(m_fd);
}

/******************************************************************************/
template<typename Key, typename Params>
int RequestEngine<Key, Params>::Gateway::GetFD() const
{
    return (m_fd);
}

                                       


} //ilrd
 
 
#endif     /* __REQUEST_ENGINE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
