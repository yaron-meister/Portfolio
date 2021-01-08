/*****************************************************************************
 * File name:   slave_types.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-05-13 15:17:12
 * Description: 
 *****************************************************************************/
 
#include <iostream>         // cout, cerr
#include <sys/types.h>      // socket
#include <sys/socket.h>		// socket
#include <strings.h>		// bzero
#include <arpa/inet.h> 		// inet
#include <netinet/in.h> 	// sockaddr_in
#include <cstring>          // memcpy, strchr

#include "utils.h"
#include "slave_types.h"    // Forward declarations 

using namespace ilrd;
/********************************* Macros *************************************/ 
const size_t BUFFER_SIZE = 4136;

 
/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/
Logger* slave_logger = Handleton<Logger>::GetInstance();
struct sockaddr_in address;
struct sockaddr_in client;




/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
/* Class SlaveProxy */
/******************************************************************************/
SlaveProxy::SlaveProxy(int port, std::string master_ip) :
								   m_fd(socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP))
{
	if (-1 == GetFD())
	{
		slave_logger->Write("SlaveProxy::socket failed"); 
		perror("SlaveProxy::socket failed");
		throw std::runtime_error("SlaveProxy::socket failed");
	}

	bzero(&address, sizeof(struct sockaddr_in));
	bzero(&client, sizeof(struct sockaddr_in));
	
    address.sin_family = AF_INET; 
	address.sin_port = htons(port); 
	address.sin_addr.s_addr = INADDR_ANY;

    if (inet_pton(AF_INET, master_ip.c_str(), &address.sin_addr) <= 0)  
	{ 
		slave_logger->Write
				("Gateway::inet_pton()-Invalid address/Address not supported"); 
		throw std::runtime_error("Gateway::inet_pton()");
	}
    
    if (bind(GetFD(), (const struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
        perror("bind failed"); 
		throw std::runtime_error("master_test: bind()");
    }
}

/******************************************************************************/
int SlaveProxy::GetFD()
{
    return (m_fd);
}

/******************************************************************************/
void SlaveProxy::GetRequest(std::unique_ptr<DataRequest>&& request)
{
	char buffer[BUFFER_SIZE];
std::cout << "REQUEST:\n";

printf("ID:\n");
for (int i = 0; i < 8; ++i)
{
	printf("%c", (request->GetID())[i]);
}
printf("\n");

printf("%lu ", *((size_t*)(request->GetID())));
printf("\nOFFSET: %lu\n", request->GetOffset());
printf("LENGTH: %lu\n", request->GetLen());

	Serialize(buffer, std::move(request));
std::cout << "buffer: " << buffer << "\n";
	sendto(GetFD(), buffer, BUFFER_SIZE, 0, (const struct sockaddr*) &client,
															    sizeof(client));
}

/******************************************************************************/
std::unique_ptr<DataRequest> SlaveProxy::Reply()
{
    std::vector<char> buffer(BUFFER_SIZE);
    size_t struct_size = sizeof(struct sockaddr_in);

	if (-1 == recvfrom(GetFD(), const_cast<char*>(buffer.data()), BUFFER_SIZE, 0, 
	  (struct sockaddr*) &client, reinterpret_cast<socklen_t *>(&struct_size)))
	{
		perror("GetRequest recvfrom failed"); 
        throw std::runtime_error("GetRequest recvfrom");
	} 

std::cout << buffer.data() << std::endl;
if (0 == strcmp("Hi moran I am your slave", buffer.data()))
{
	std::cout << "Got the slave\n";
	abort();
}

    return (std::move(Deserialize(buffer)));
}
 
/******************************************************************************/
std::unique_ptr<DataRequest> SlaveProxy::Deserialize(std::vector<char> message)
{
	size_t offset;
	size_t len;
	char id[8];
    long long_id;
	int type;
	std::vector<char> data(4*KB);

	sscanf(message.data(), "%lu;%lu;%ld;%d;", &offset, &len, &long_id, &type);
	char* runner = strchr(message.data(), '\0') + 1;

	memcpy(data.data(), runner, len);
    memcpy(id, &long_id, sizeof(long));

	return (std::unique_ptr<DataRequest>(new 
                    DataRequest(id, static_cast<DataRequest::RequestType>(type), 
                                                           data, offset, len)));
                                     
}

/******************************************************************************/
void SlaveProxy::Serialize(char* buffer, std::unique_ptr<DataRequest> request)
{
    // unsigned long long_id;

    // memcpy(&long_id, request->GetID(), sizeof(unsigned long));
sleep(1);
printf("SERIALIZE:\n");
printf("%lu ", *((size_t*)(request->GetID())));
printf("\nOFFSET: %lu\n", request->GetOffset());
printf("LENGTH: %lu\n", request->GetLen());
// printf("long: %ld\n", long_id);
	// int bytes_num = sprintf(buffer, "%lu;%lu;%d;%c",
    //                                    request->GetLen(), long_id, 
    //                                    static_cast<int>(request->GetType()), 0);
	int bytes_num = sprintf(buffer, "%lu;%c%c%c%c%c%c%c%c;%d;%c",
                                       request->GetLen(), 
									   (request->GetID())[0]/* long_id */, 
									   (request->GetID())[1], 
									   (request->GetID())[2], 
									   (request->GetID())[3], 
									   (request->GetID())[4], 
									   (request->GetID())[5], 
									   (request->GetID())[6], 
									   (request->GetID())[7], 
                                       static_cast<int>(request->GetType()), 0);
std::cout << "bytes_num: " << bytes_num << std::endl;

std::cout << "buffer: " << buffer << std::endl;
	memcpy(&(buffer[bytes_num]), request->GetData(), request->GetLen());

}



/******************************************************************************/ 
/* Class SlaveGateway */
/******************************************************************************/
SlaveGateway::SlaveGateway(SlaveProxy slave_proxy, std::shared_ptr<DriverProxy> dp):
                    RequestEngine<int, Params>::Gateway(slave_proxy.GetFD()), 
                    m_slave_proxy(slave_proxy), m_dp(dp)
{}

/******************************************************************************/
std::pair<int, Params> SlaveGateway::Read()
{
	std::unique_ptr<DataRequest> request = m_slave_proxy.Reply();
	int type = static_cast<int>(request->GetType());

	return (std::pair<int, Params>(/* type */ 1, 
								   Params(std::move(request), nullptr, m_dp)));
}



/******************************************************************************/ 
/* Class SlaveManager */
/******************************************************************************/
SlaveManager::SlaveManager(size_t storage_size) : m_storage_size(storage_size)
{}

/******************************************************************************/
void SlaveManager::AddProxy(SlaveProxy* slave_proxy)
{
	char buffer[BUFFER_SIZE];
	size_t struct_size = sizeof(struct sockaddr_in);

    if (nullptr != slave_proxy)
    {
        m_slave_proxys.push_back(slave_proxy);
		if (-1 == recvfrom(slave_proxy->GetFD(), const_cast<char*>(buffer), BUFFER_SIZE, 0, 
			(struct sockaddr*) &client, reinterpret_cast<socklen_t *>(&struct_size)))
		{
			perror("GetRequest recvfrom failed"); 
			throw std::runtime_error("GetRequest recvfrom");
		}
		printf("GOT: %s\n", buffer); 
    }
}

/******************************************************************************/
void SlaveManager::HandleRequest(std::unique_ptr<DataRequest>&& request)
{
	size_t storage_part = m_storage_size / m_slave_proxys.size();
	size_t offset = request->GetOffset();
	(m_slave_proxys[offset / storage_part])->GetRequest(std::move(request));
}



/******************************************************************************/
/* Class SlaveTask */
/******************************************************************************/
SlaveTask::SlaveTask(const Params& params) : 
            m_request(std::move(params.m_request)), m_dp(params.m_dp)  
{}

/******************************************************************************/
SlaveTask::~SlaveTask(){}

/******************************************************************************/
void SlaveTask::Execute()
{
	if (nullptr != m_dp)
	{
		m_dp->Reply(std::move(m_request));
	}
}




/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
