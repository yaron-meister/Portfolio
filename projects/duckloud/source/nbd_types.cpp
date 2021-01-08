/*****************************************************************************
 * File name:   nbd_types.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-05-13 15:17:18
 * Description: 
 *****************************************************************************/
 
#include <iostream>     // cout, cerr

#include "utils.h"
#include "nbd_types.h"  // Forward declarations 

using namespace ilrd;
/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/
// DriverProxy* dp_ptr(nullptr); 




/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/
/* Class NBDGateway */
/******************************************************************************/
NBDGateway::NBDGateway(std::shared_ptr<DriverProxy> driver_proxy, SlaveManager& slave_manager) : 
            RequestEngine<int, Params>::Gateway(driver_proxy->GetFD()),
            m_dp(driver_proxy), m_slave_manager(slave_manager)
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
    DBG(printf("Got DP Socket Event\n"));

    std::unique_ptr<DataRequest> request(m_dp->GetRequest());
    Params params(std::move(request), &m_slave_manager, nullptr);
std::cout << "got request\n";
    return (std::pair<int, Params>
            (/* static_cast<int>(params.m_request->GetType()) */ 0 , params)); 
}


/******************************************************************************/
/* Class NBDTask */
/******************************************************************************/
NBDTask::NBDTask(const Params& params): 
                                        m_request(std::move(params.m_request)), 
                                        m_slave_manager(params.m_slave_manager) 
{}

/******************************************************************************/
NBDTask::~NBDTask(){}

/******************************************************************************/
void NBDTask::Execute()
{
    if (nullptr != m_slave_manager)
    {
printf("m_slave-MANAGER: %p\n", (void*)m_slave_manager); 
        m_slave_manager->HandleRequest(std::move(m_request));
    }
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
