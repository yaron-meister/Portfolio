/*****************************************************************************
 * File name:   driver_proxy.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-27 15:05:12
 * Description: 
 *****************************************************************************/
 
#include <iostream>             /* 		cout, cerr		*/
#include <cstdlib>              /*       	       	    */
#include <linux/nbd.h>          /*         NBD          */
#include <cstring>              /*        memcpy        */
#include <sys/types.h>          /*      socketpair      */
#include <sys/socket.h>         /*      socketpair      */
#include <thread>               /*      std::thread     */
#include <sys/stat.h>           /*         open         */
#include <fcntl.h>              /*         open         */
#include <linux/nbd.h>          /*          nbd         */
#include <sys/ioctl.h>          /*         ioctl        */
#include <signal.h>             /*        sigset_t      */
#include <unistd.h>             /*         close        */
#include <arpa/inet.h>          /*         ntohl        */       
#include <mutex>                /*      std::mutex      */

#include "utils.h"              /*         DBG          */
#include "driver_proxy.h"       /* Forward declarations */

using namespace ilrd;
/********************************* Macros *************************************/ 
#define htonll ntohll

/************************** Forward Declarations ******************************/
u_int64_t ntohll(u_int64_t a);

/******************************* Global vars **********************************/ 
Logger* logger = Handleton<Logger>::GetInstance();

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/
/* DriverProxy class */
/******************************************************************************/
DriverProxy::DriverProxy(const std::string& dev_path, size_t storage_size) :
     m_dev_path(dev_path), m_storage_size(storage_size), m_nbd_fd(-1)
                                                         
{
    Init();
}

/******************************************************************************/
DriverProxy::DriverProxy(const std::string& dev_path, size_t block_size, 
                                                         size_t num_of_blocks) :
                               DriverProxy(dev_path, block_size * num_of_blocks)
{}

/******************************************************************************/
void DriverProxy::Init()
{
    int sock_fds[2] = {0};

    if (0 != socketpair(AF_UNIX, SOCK_STREAM, 0, sock_fds))
    {
        logger->Write("socketpair failed");
        throw DriverException("socketpair");
    }

    m_socket_fds[0] = sock_fds[0];
    m_socket_fds[1] = sock_fds[1];

    m_nbd_fd = open(m_dev_path.c_str(), O_RDWR);
    if (-1 == m_nbd_fd)
    {
        logger->Write("open failed");
        throw DriverException("open");
    }

    if (-1 == ioctl(m_nbd_fd, NBD_SET_SIZE, m_storage_size))
    {
        logger->Write("ioctl - SetSize");
        throw DriverException("ioctl - SetSize");
    }

    if (-1 == ioctl(m_nbd_fd, NBD_CLEAR_SOCK))
    {
        logger->Write("ioctl - ClearSock before MT");
        throw DriverException("ioctl - ClearSock before MT");
    }

    m_thread = std::thread(&DriverProxy::ThreadFunc, this,
                                                     m_nbd_fd, m_socket_fds[1]);
}

/******************************************************************************/
void DriverProxy::ThreadFunc(int nbd_fd, int sock_fd)
{
    DBG(std::cout << "ThreadFunc CALLED\n\n");
    logger->Write("ThreadFunc CALLED\n\n");

    sigset_t sigset;
    if (0 != sigfillset(&sigset) ||  
        0 != pthread_sigmask(SIG_SETMASK, &sigset, NULL))
    {
        logger->Write("sigfillset OR pthread_sigmask");
        throw DriverException("sigfillset OR pthread_sigmask");
    }

    if(-1 == ioctl(nbd_fd, NBD_SET_SOCK, sock_fd))
    {
        logger->Write("ioctl NBD_SET_SOCK");
        throw DriverException("ioctl NBD_SET_SOCK");
    }

    int flags;
    #if defined NBD_SET_FLAGS
        flags = 0;
    #if defined NBD_FLAG_SEND_TRIM
        flags |= NBD_FLAG_SEND_TRIM;
    #endif
    #if defined NBD_FLAG_SEND_FLUSH
        flags |= NBD_FLAG_SEND_FLUSH;
    #endif
        if ((flags != 0) && (0 > ioctl(nbd_fd, NBD_SET_FLAGS, flags)))
        {
            DBG(perror("ioctl"));
        }
    #endif

    DBG(std::cout << "Activating NBD_DO_IT\n\n");
    if(-1 ==  ioctl(nbd_fd, NBD_DO_IT))
    {
        logger->Write("ioctl NBD_DO_IT");
        throw DriverException("ioctl NBD_DO_IT");
    }

    DBG(std::cout << "NBD_DO_IT STOPPED\n\n");
    logger->Write("NBD_DO_IT STOPPED\n\n");
}

/******************************************************************************/
DriverProxy::~DriverProxy()
{
    close(m_socket_fds[0]);
    close(m_socket_fds[1]);
    close(m_nbd_fd);
    m_thread.join();
}

/******************************************************************************/
int DriverProxy::GetFD()
{
    return (m_socket_fds[0]);
}

/******************************************************************************/
std::unique_ptr<DataRequest> DriverProxy::GetRequest()
{
    struct nbd_request request;
    unsigned int error = 1;
    DataRequest::RequestType type;
    std::vector<char> vec;

    if (read(m_socket_fds[0], &request, sizeof(struct nbd_request)) > 0)
    {
        error = 0;

        switch (ntohl(request.type))
        {
            case NBD_CMD_READ:
                type = DataRequest::RequestType::READ;
                break;

            case NBD_CMD_WRITE:
                type = DataRequest::RequestType::WRITE;
                if (EXIT_SUCCESS != ReadAll(GetFD(), vec, ntohl(request.len)))
                {
                    error = 1;
                }
                break;

            case NBD_CMD_DISC:
                type = DataRequest::RequestType::DISCONNECT;
                break;

            case NBD_CMD_FLUSH:
                type = DataRequest::RequestType::FLUSH;
                break;

            case NBD_CMD_TRIM:
                type = DataRequest::RequestType::TRIM;
                break;

            default:
                error = 1;
                break;
        }
    }
      
    std::unique_ptr<DataRequest> data_req(new DataRequest(request.handle,
                         type, vec, ntohll(request.from), ntohl(request.len)));
    data_req->SetError(error);

    return (std::move(data_req));

}

/******************************************************************************/
u_int64_t ntohll(u_int64_t a) 
{
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  
  return (((u_int64_t) lo) << 32U | hi);
}

/******************************************************************************/
void DriverProxy::Reply(std::unique_ptr<DataRequest> request)
{
    struct nbd_reply reply;

    memcpy(&reply.handle, request->GetID(), id_size);
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(request->GetError());
    
    DBG(std::cout << "REPLYING\n\n");
    logger->Write("REPLYING\n\n");

    std::lock_guard<std::mutex> lock(m_mutex);
    WriteAll(GetFD(), (char*)&reply, sizeof(struct nbd_reply));
   
    if (DataRequest::RequestType::READ == request->GetType())
    {
        WriteAll(GetFD(), (char*)request->GetData(), request->GetLen());
    }
}

/******************************************************************************/
void DriverProxy::Disconnect()
{
    if (-1 != m_nbd_fd)
    {
        if (-1 == ioctl(m_nbd_fd, NBD_DISCONNECT))
        {
            logger->Write("ioctl NBD_DISCONNECT");
            throw DriverException("ioctl NBD_DISCONNECT");
        }

        if (-1 == ioctl(m_nbd_fd, NBD_CLEAR_QUE) ||
            -1 == ioctl(m_nbd_fd, NBD_CLEAR_SOCK))
        {  
            logger->Write("NBD_CLEAR_QUE or NBD_CLEAR_SOCK");
            throw DriverException("NBD_CLEAR_QUE or NBD_CLEAR_SOCK");
        }

        DBG(std::cout << "NBD successfully disconnected\n\n");
        logger->Write("NBD successfully disconnected\n\n");
    }
}



/* DataRequest class */
/******************************************************************************/ 
DataRequest::DataRequest(const char req_id[id_size], const RequestType type, 
                  const std::vector<char>& data, size_t offset, size_t length) :
        m_type(type), m_data(data), m_offset(offset), m_len(length), m_error(1)
{
    memcpy(m_id, req_id, id_size);
}

/******************************************************************************/
const char* DataRequest::GetID() const
{
    return (m_id);
}

/******************************************************************************/
DataRequest::RequestType DataRequest::GetType() const
{
    return (m_type);
}

/******************************************************************************/
const char* DataRequest::GetData() const
{
    return (m_data.data());
}

/******************************************************************************/
size_t DataRequest::GetOffset() const
{
    return (m_offset);
}

/******************************************************************************/
size_t DataRequest::GetLen() const
{
    return (m_len);
}

/******************************************************************************/
unsigned int DataRequest::GetError() const
{
    return (m_error);
}

/******************************************************************************/
void DataRequest::SetData(std::vector<char>&& data)
{
    m_data = std::move(data);
}

/******************************************************************************/
void DataRequest::SetOffset(size_t offset)
{
    m_offset = offset;
}

/******************************************************************************/
void DataRequest::SetLength(size_t length)
{
    m_len = length;
}

/******************************************************************************/
void DataRequest::SetError(unsigned int error)
{
    m_error = error;
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
