/*****************************************************************************
 * File name:   request_engine_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-28 15:31:24
 * Test Flow: 
 *****************************************************************************/
 
#include <iostream>             // cout, cerr		
#include <cstdlib>              // EXIT_SUCCESS 	
#include <signal.h>             // sigset_t      

#include "utils.h"
#include "driver_proxy.h"
#include "storage.h"
#include "request_engine.h"     // Forward declarations 

using namespace ilrd;
/********************************* Macros *************************************/ 

/********************************* Classes ************************************/
class Params
{
public:
    friend class Read;
    friend class Write;
    friend class NBDGateway;

    Params(std::unique_ptr<DataRequest> request);

    Params(const Params& other);
    // Params& operator=(const Params& other);

    mutable std::unique_ptr<DataRequest> m_request;
};

/********************/
class NBDGateway : public RequestEngine<int, Params>::Gateway
{
public:
    NBDGateway(DriverProxy* driver_proxy);
    ~NBDGateway();

    NBDGateway(const NBDGateway&) = delete;
    NBDGateway& operator=(const NBDGateway&) = delete;

    std::pair<int, Params> Read() override;
private:
    DriverProxy* m_dp;
};

/********************/
class Read : public RequestEngine<int, Params>::Task
{
public:
    Read(std::unique_ptr<DataRequest> request,
                                        Priority priority = Priority::VERY_LOW);
    ~Read() override;

    // Un-copyable
    Read(const Read&) = delete;
    Read& operator=(const Read&) = delete;

private:
    std::unique_ptr<DataRequest> m_request;
    void Execute() override;
};

/********************/
class Write : public RequestEngine<int, Params>::Task
{
public:
    Write(std::unique_ptr<DataRequest> request,
                                        Priority priority = Priority::VERY_LOW);
    ~Write() override;

    // Un-copyable
    Write(const Write&) = delete;
    Write& operator=(const Write&) = delete;

private:
    std::unique_ptr<DataRequest> m_request;
    void Execute() override;
};

/********************/
class Other : public RequestEngine<int, Params>::Task
{
public:
    Other(std::unique_ptr<DataRequest> request,
                                        Priority priority = Priority::VERY_LOW);
    ~Other() override;

    // Un-copyable
    Other(const Other&) = delete;
    Other& operator=(const Other&) = delete;

private:
    std::unique_ptr<DataRequest> m_request;
    void Execute() override;
};


/**************************** Forward Declarations ****************************/
void SigAction(int sig);

/***************************** Global variables *******************************/
const int STDIN_FD   = 0;
bool disconnect_flag = false;
Storage storage(128000000);
DriverProxy* dp_ptr(nullptr);
RequestEngine<int, Params> 
            req_engine("/home/shiran/git/yaron-meister/projects/monitor");

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
            perror("sigemptyset");
            return (EXIT_FAILURE);
        }

        if (0 != sigaction(SIGINT, &act, nullptr) ||
            0 != sigaction(SIGTERM, &act, nullptr))
        {
            perror("sigaction");
            return (EXIT_FAILURE);
        }

        DriverProxy driver_proxy(argv[1], 128000000);
        dp_ptr = &driver_proxy;
        

        req_engine.ConfigTask(static_cast<int>(DataRequest::RequestType::READ), 
                              [](Params params)
        {return std::unique_ptr<RequestEngine<int, Params>::Task>
                                     (new Read(std::move(params.m_request)));});

        req_engine.ConfigTask(static_cast<int>(DataRequest::RequestType::WRITE), 
                              [](Params params)
        {return std::unique_ptr<RequestEngine<int, Params>::Task>
                                    (new Write(std::move(params.m_request)));});

        req_engine.ConfigTask(2, 
                              [](Params params)
        {return std::unique_ptr<RequestEngine<int, Params>::Task>
                                    (new Other(std::move(params.m_request)));});

        req_engine.ConfigTask(3, 
                              [](Params params)
        {return std::unique_ptr<RequestEngine<int, Params>::Task>
                                    (new Other(std::move(params.m_request)));});                                    

        req_engine.ConfigTask(4, 
                              [](Params params)
        {return std::unique_ptr<RequestEngine<int, Params>::Task>
                                    (new Other(std::move(params.m_request)));});


        NBDGateway nbd_gw(dp_ptr);

        req_engine.AddGateway(nbd_gw);
        req_engine.Run();

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

    req_engine.Stop();
}

/******************************************************************************/
/* Class NBDGateway */
/******************************************************************************/
NBDGateway::NBDGateway(DriverProxy* driver_proxy) : 
            RequestEngine<int, Params>::Gateway(driver_proxy->GetFD()),
            m_dp(driver_proxy)
{}


/******************************************************************************/
NBDGateway::~NBDGateway()
{
    if (nullptr != m_dp)
    {
        m_dp->Disconnect();
    }
}

/******************************************************************************/
std::pair<int, Params> NBDGateway::Read()
{
    DBG(printf("Got Socket Event\n"));

    std::unique_ptr<DataRequest> request(m_dp->GetRequest());

    Params params(std::move(request));

    return (std::pair<int, Params>
            (static_cast<int>(params.m_request->GetType()), params)); 
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
    dp_ptr->Reply(std::move(m_request));
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
    dp_ptr->Reply(std::move(m_request));
}


/******************************************************************************/
/* Class Other */
/******************************************************************************/
Other::Other(std::unique_ptr<DataRequest> request, Priority priority) : 
                                                Task(priority), 
                                                m_request(std::move(request))
{}

/******************************************************************************/
Other::~Other(){}

/******************************************************************************/
void Other::Execute()
{
    std::cout << "Other Task\n";
    dp_ptr->Reply(std::move(m_request));
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/  