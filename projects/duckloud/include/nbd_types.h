/*****************************************************************************
 * File name:   nbd_types.h
 * Developer:   HRD7
 * Version: 
 * Date:        2019-05-13 15:17:18
 * Description: 
 *****************************************************************************/


#ifndef __NBD_TYPES_H__
#define __NBD_TYPES_H__

#include "params.h"
#include "request_engine.h"
#include "slave_types.h"

namespace ilrd
{

class NBDGateway : public RequestEngine<int, Params>::Gateway
{
public:
    NBDGateway(std::shared_ptr<DriverProxy> driver_proxy, SlaveManager& slave_manager);
    ~NBDGateway();

    NBDGateway(const NBDGateway&) = delete;
    NBDGateway& operator=(const NBDGateway&) = delete;

    std::pair<int, Params> Read() override;
private:
    std::shared_ptr<DriverProxy> m_dp;
    SlaveManager& m_slave_manager;
};

/********************/
class NBDTask : public RequestEngine<int,Params>::Task
{
public:
    NBDTask(const Params& params);
    ~NBDTask() override;

    // Un-copyable
    NBDTask(const NBDTask&) = delete;
    NBDTask& operator=(const NBDTask&) = delete;

private:
    void Execute() override;

    std::unique_ptr<DataRequest> m_request;
    SlaveManager* m_slave_manager;
};




} //ilrd
 
 
#endif     /* __NBD_TYPES_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
