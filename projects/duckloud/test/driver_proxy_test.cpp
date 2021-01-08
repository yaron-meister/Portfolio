/*****************************************************************************
 * File name:   driver_proxy_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-27 15:05:12
 * Test Flow: 
 *****************************************************************************/
 
#include <iostream>             /* 	    cout, cerr	    */
#include <cstdlib>              /*     EXIT_SUCCESS     */
#include <cassert>              /*        assert        */
#include <cstring>              /*        memcpy        */
#include <signal.h>             /*        sigset_t      */
#include <sys/epoll.h>          /*     epoll_create1    */
#include <unistd.h>             /*        close         */

#include "utils.h"              /*    DBG, UNUSED_VAR   */
#include "driver_proxy.h"       /* Forward declarations */
#include "storage.h"
#include "thread_pool.h"        /*      ThreadPool      */
#include "factory.h"            /*       Factory        */

using namespace ilrd;
/********************************* Macros *************************************/ 
const int NUM_OF_THREADS = 4;

/********************************* Classes ************************************/
class Params
{
public:
    friend class Read;
    friend class Write;

    Params(std::unique_ptr<DataRequest> request);

    Params(const Params& other);
    // Params& operator=(const Params& other);

    mutable std::unique_ptr<DataRequest> m_request;
};

/********************/
class Read : public Task
{
public:
    Read(std::unique_ptr<DataRequest> request, Priority priority = Priority::VERY_LOW);
    ~Read() override;

    // Un-copyable
    Read(const Read&) = delete;
    Read& operator=(const Read&) = delete;

private:
    std::unique_ptr<DataRequest> m_request;
    void Execute() override;
};

/********************/
class Write : public Task
{
public:
    Write(std::unique_ptr<DataRequest> request, Priority priority = Priority::VERY_LOW);
    ~Write() override;

    // Un-copyable
    Write(const Write&) = delete;
    Write& operator=(const Write&) = delete;

private:
    std::unique_ptr<DataRequest> m_request;
    void Execute() override;
};

/**************************** Forward Declarations ****************************/
void SigAction(int sig);
void ThreadFunc(Storage& storage, std::unique_ptr<DataRequest>&& request);
void FactoryAdd();

/***************************** Global variables *******************************/
DriverProxy* driver_proxy_ptr = nullptr;
struct epoll_event event1;
struct epoll_event event2;
struct epoll_event events[2];
const int STDIN_FD   = 0;
const int MAX_EVENTS = 20;
bool disconnect_flag = false;
Logger* test_logger = Handleton<Logger>::GetInstance();

Storage storage(128000000);
Factory<Task, int, Params> factory; 
ThreadPool thread_pool(NUM_OF_THREADS);

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(int argc, char* argv[])
{   
    UNUSED_VAR(argc);

	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 

    try 
    { 
        struct sigaction act;
        act.sa_handler = SigAction;
        act.sa_flags = SA_RESTART;
        
        if (0 != sigemptyset(&act.sa_mask) || 
            0 != sigaddset(&act.sa_mask, SIGINT) ||
            0 != sigaddset(&act.sa_mask, SIGTERM)) 
        {
        
            test_logger->Write("sigemptyset");
            perror("sigemptyset");
            return (EXIT_FAILURE);
        }

        if (0 != sigaction(SIGINT, &act, nullptr) ||
            0 != sigaction(SIGTERM, &act, nullptr))
        {
            test_logger->Write("sigaction");
            perror("sigaction");
            return (EXIT_FAILURE);
        }

        DriverProxy driver_proxy(argv[1], 128000000);
        driver_proxy_ptr = &driver_proxy;
        FactoryAdd();

        int epoll_fd = epoll_create1(0);
        if (-1 == epoll_fd)
        {
            test_logger->Write("epoll_create");
            perror("epoll_create");
            return (EXIT_FAILURE);
        }

        event1.events = EPOLLIN;
        event1.data.fd = STDIN_FD;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event1))
        {
            test_logger->Write("epoll_ctl1");
            perror("epoll_ctl1");
            close(epoll_fd);
            return (EXIT_FAILURE);
        }

        event2.events = EPOLLIN;
        event2.data.fd = driver_proxy_ptr->GetFD();
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, driver_proxy_ptr->GetFD(),
                                                                       &event2))
        {
            test_logger->Write("epoll_ctl2");
            perror("epoll_ctl2");
            close(epoll_fd);
            return (EXIT_FAILURE);
        }

        int nfds = 0;
        char buffer[10] = {0};
        std::unique_ptr<DataRequest> request(nullptr);

        while (true != disconnect_flag)
        {
            DBG(std::cout << "Next epoll_wait()\n");
            test_logger->Write("Next epoll_wait()\n");

            nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
            if (-1 == nfds) 
            {
                test_logger->Write("epoll_wait");
                perror("epoll_wait");
                return (EXIT_FAILURE);
            }

            DBG(printf("epoll_wait DONE\n"));
            test_logger->Write("epoll_wait DONE\n");

            for (int n = 0; n < nfds; ++n) 
            {
                if (STDIN_FD == events[n].data.fd) 
                {
                    if (-1 == read(STDIN_FD, buffer, sizeof(buffer)))
                    {
                        test_logger->Write("test read failed");
                        perror("read");
                        return (EXIT_FAILURE);
                    }

                    buffer[1] = '\0';
                    
                    if (0 == strcmp("q", buffer))
                    {
                        DBG(std::cout << "Gracefully Disconnected\n");
                        test_logger->Write("Gracefully Disconnected\n");
                        disconnect_flag = true;
                        driver_proxy_ptr->Disconnect();
                        break;
                    }
                }
                else
                {
                    DBG(printf("Got Socket Event\n"));
                    test_logger->Write("Got Socket Event\n");

                    request = driver_proxy_ptr->GetRequest();

                    std::shared_ptr<Task> task;

                    if (DataRequest::RequestType::READ == request->GetType())
                    {
                        Params params(std::move(request));
                        task = factory.CreateShared(0, params);

                        thread_pool.AddTask(task);
                    }
                    else if (DataRequest::RequestType::WRITE == request->GetType())
                    {
                        Params params(std::move(request));
                        task = factory.CreateShared(1, params);

                        thread_pool.AddTask(task);
                    } 
                    else
                    {
                        driver_proxy_ptr->Reply(std::move(request));
                    }
                }
            }  

            DBG(std::cout << "Handle done\n\n\n");
            test_logger->Write("Handle done\n\n\n");
        }

        if (close(epoll_fd))
        {
            test_logger->Write("close");
            perror("close");
            return (EXIT_FAILURE);
        }
    } 
    catch (const std::overflow_error& e) 
    {
    // this executes if f() throws std::overflow_error (same type rule)
    } 
    catch (const std::runtime_error& e) 
    {
    // this executes if f() throws std::underflow_error (base class rule)
        std::cout << e.what() << std::endl;
    } 
    catch (const std::exception& e)     
    {
    // this executes if f() throws std::logic_error (base class rule)
    } 
    catch (...) 
    {
    // this executes if f() throws unrelated type
    }


	printf("\n***************** END OF PROCCESS ***************************\n"); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void SigAction(int sig)
{
    UNUSED_VAR(sig);

    disconnect_flag = true;

    if (nullptr != driver_proxy_ptr)
    {
        driver_proxy_ptr->Disconnect();
    }
}

/******************************************************************************/
void ThreadFunc(Storage& storage, std::unique_ptr<DataRequest>&& request)
{
    std::vector<char> vec;
                    
    switch(request->GetType())
    {
        case (DataRequest::RequestType::READ) :
        
            storage.Read(vec, request->GetOffset(),
                                                request->GetLen());
            request->SetData(std::move (vec));
            break;

        case (DataRequest::RequestType::WRITE) :
            
            storage.Write(request->GetData(),
                        request->GetOffset(), request->GetLen());
            break;

        case (DataRequest::RequestType::DISCONNECT) :

            // storage.Disconnect();
            break;

        case (DataRequest::RequestType::FLUSH) :

            // storage.Flush();
            break;

        case (DataRequest::RequestType::TRIM) :

            // storage.Trim();
            break;

        default : 

            break;
    }

    driver_proxy_ptr->Reply(std::move(request));
}

/******************************************************************************/
void FactoryAdd()
{
    factory.Add(0, [](Params params)
       {return std::unique_ptr<Task>(new Read(std::move(params.m_request)));});
    factory.Add(1, [](Params params)
       {return std::unique_ptr<Task>(new Write(std::move(params.m_request)));});
}

/******************************************************************************/
/* Class Params */
/******************************************************************************/
Params::Params(std::unique_ptr<DataRequest> request) :
                                                   m_request(std::move(request))
{}

/******************************************************************************/
Params::Params(const Params& other) : m_request(std::move(other.m_request))
{}

// /******************************************************************************/
// Params& Params::operator=(const Params& other) : m_request(std::move(request))



/******************************************************************************/
/* Class Read */
/******************************************************************************/
Read::Read(std::unique_ptr<DataRequest> request, Priority priority) : 
                                                Task(priority), 
                                                m_request(std::move(request)) 
{}

/******************************************************************************/
Read::~Read(){}

/******************************************************************************/
void Read::Execute()
{
    std::vector<char> vec;
    storage.Read(vec, m_request->GetOffset(), m_request->GetLen());
            m_request->SetData(std::move(vec));
    driver_proxy_ptr->Reply(std::move(m_request));
}


/******************************************************************************/
/* Class Write */
/******************************************************************************/
Write::Write(std::unique_ptr<DataRequest> request, Priority priority) : 
                                                Task(priority), 
                                                m_request(std::move(request))
{}

/******************************************************************************/
Write::~Write(){}

/******************************************************************************/
void Write::Execute()
{
    storage.Write(m_request->GetData(),
                        m_request->GetOffset(), m_request->GetLen());
    driver_proxy_ptr->Reply(std::move(m_request));
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
