/*****************************************************************************
 * File name:   slave_types.h
 * Developer:   HRD7
 * Date:        2019-05-13 15:17:12
 *****************************************************************************/

#ifndef __SLAVE_TYPES_H__
#define __SLAVE_TYPES_H__

namespace ilrd
{
    class SlaveProxy;
    class SlaveManager;
    class SlaveGateway;
    class SlaveTask;
}

#include "params.h"
#include "request_engine.h"

namespace ilrd
{

class SlaveProxy
{
public: 
        SlaveProxy(int port, std::string master_ip);

        int GetFD();

        void GetRequest(std::unique_ptr<DataRequest>&& request);
        // std::unique_ptr<DataRequest> GetRequest();
        std::unique_ptr<DataRequest> Reply();

        std::unique_ptr<DataRequest> Deserialize(std::vector<char> message);
        void Serialize(char* buffer, std::unique_ptr<DataRequest> request);

private:
    int m_fd;
};

/**********************/
class SlaveManager
{
public:
    explicit SlaveManager(size_t storage_size);
    
    void AddProxy(SlaveProxy* slave_proxy);
    void HandleRequest(std::unique_ptr<DataRequest>&& request);
    
private:
    std::vector<SlaveProxy*> m_slave_proxys;
    size_t m_storage_size; 
};

/**********************/
class SlaveGateway : public RequestEngine<int, Params>::Gateway
{
public:
	SlaveGateway(SlaveProxy slave_proxy, std::shared_ptr<DriverProxy> dp);
    ~SlaveGateway() = default;

	SlaveGateway(const SlaveGateway&) = delete;
	SlaveGateway& operator=(const SlaveGateway&) = delete;

    std::pair<int, Params> Read();

private:
    SlaveProxy m_slave_proxy;
    std::shared_ptr<DriverProxy> m_dp;
};

/********************/
class SlaveTask : public RequestEngine<int,Params>::Task
{
public:
    SlaveTask(const Params& params);
    ~SlaveTask() override;

    // Un-copyable
    SlaveTask(const SlaveTask&) = delete;
    SlaveTask& operator=(const SlaveTask&) = delete;

private:
    void Execute() override;

    std::unique_ptr<DataRequest> m_request;
    std::shared_ptr<DriverProxy> m_dp;
};




} //ilrd
 
 
#endif     /* __SLAVE_TYPES_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
