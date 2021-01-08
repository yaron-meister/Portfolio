/*****************************************************************************
 * File name:   driver_proxy.h
 * Developer:   HRD07
 * Version: 	4
 * Date:        2019-03-27 10:26:28
 * Description: Driver Proxy header
 *****************************************************************************/
#ifndef __DRIVER_PROXY_H__
#define __DRIVER_PROXY_H__

#include <cstddef>      /* size_t */
#include <memory>
#include <vector>
#include <thread>
#include <string>
#include <exception>
#include <mutex>

#include "logger.h"
#include "handleton.h"

namespace ilrd
{

const size_t id_size = 8;

// Manage the request 
class DataRequest
{

public:
    enum class RequestType
    {
        READ,
        WRITE,
        DISCONNECT,
        FLUSH,
        TRIM
    };

    DataRequest(const char req_id[id_size], const RequestType type, 
                const std::vector<char>& data, size_t offset, size_t length);

    const char* GetID() const;
    RequestType GetType() const;
    const char* GetData() const;
    size_t GetOffset() const;
    size_t GetLen() const;
    unsigned int GetError() const;

    void SetData(std::vector<char>&& data);
    void SetOffset(size_t offset);
    void SetLength(size_t length);
    void SetError(unsigned int error);

    DataRequest(const DataRequest&) = delete;
    DataRequest& operator=(const DataRequest&) = delete;    

private:
    char m_id[id_size];
    RequestType m_type; 
    std::vector<char> m_data;
    size_t m_offset;
    size_t m_len;
    unsigned int m_error;
};

// like BUSE, control streaming between <device&driver> and <memory dest>
class DriverProxy final // cannot be inherited
{
public:    
    DriverProxy(const std::string& dev_path, size_t storage_size);
    DriverProxy(const std::string& dev_path, size_t block_size, 
                                                        size_t num_of_blocks);
    
    ~DriverProxy();

    std::unique_ptr<DataRequest> GetRequest();
    void Reply(std::unique_ptr<DataRequest> request);
    
    void Disconnect();
    int GetFD();

    //Un-copyable 
    DriverProxy(const DriverProxy&) = delete;               
    DriverProxy& operator=(const DriverProxy&) = delete;     

private:
    const std::string m_dev_path;
    size_t m_storage_size;
    int m_socket_fds[2];
    int m_nbd_fd;
    std::thread m_thread;
    std::mutex m_mutex;

    void Init();
    void ThreadFunc(int nbd_fd, int sock_fd);
};

class DriverException : public std::runtime_error
{
    public:
        DriverException(const char* what_arg) : runtime_error(what_arg)
        {}

        virtual ~DriverException(){}
};


} // namespace ilrd

#endif     /* __DRIVER_PROXY_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
