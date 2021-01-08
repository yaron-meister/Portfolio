/*****************************************************************************
 * File name:   slave_test.cpp
 * Developer:   Yaron Meister
 * Date:        2019-05-02 13:29:30
 * Description: Slave app for DuCkloud
 *****************************************************************************/
 
#include <iostream>         // cout, cerr	
#include <stdlib.h>         // EXIT_SUCCESS 
#include <unistd.h>         // close
#include <sys/types.h>      // socket
#include <sys/socket.h>		// socket
#include <strings.h>		// bzero
#include <arpa/inet.h> 		// inet
#include <netinet/in.h> 	// sockaddr_in
#include <cstring>			// getline
#include <sstream>			// stringstream
#include <signal.h>         // sigset_t      
// #include <libconfig.h++>	// libconfig

#include "utils.h"
#include "driver_proxy.h"  
#include "factory.h"
#include "request_engine.h"
#include "storage.h"

using namespace ilrd;
// using namespace libconfig;
/********************************* Macros *************************************/ 
const size_t BUFFER_SIZE = 4136;
const int READ = 0;
const int WRITE = 1;
const size_t SIZE_STORAGE = 8388608;

struct UDPMessage;
struct Params;
/***************************** Global variables *******************************/
struct sockaddr_in address;
Logger* g_logger = Handleton<Logger>::GetInstance();
Storage storage(SIZE_STORAGE);
RequestEngine<int, Params>* re_ptr(nullptr); 

/********************************* Structs ************************************/ 
class FD
{
public:
	explicit FD(int fd = -1) : m_fd(fd)
    {}
	~FD() 
    { 
        if (m_fd != -1) close(m_fd); 
    }

	FD(const FD&) = delete;
	FD& operator=(const FD&) = delete;
	
    int GetFD() const 
    { 
        return m_fd; 
    }

	FD& operator=(FD&& other) noexcept
	{
		if (m_fd != -1)
		{
			close(m_fd);
		}

		m_fd = other.m_fd;
		
		other.m_fd = -1;
		
		return (*this);
	}

	operator int() 
    { 
        return m_fd; 
    }


private:
	int m_fd;
};

/**********************/
struct UDPMessage
{
	UDPMessage(int socket_fd, int req_id, int type, size_t offset, 
	 size_t len, std::vector<char> data);

	int m_socket_fd;
	int m_req_id;
    int m_type; 
    size_t m_offset;
    size_t m_len;
	std::vector<char> m_data;
};

/**********************/
struct Params
{
    Params(std::unique_ptr<UDPMessage> msg)
        : m_message(std::move(msg)) {}

    Params(const Params& p)
        : m_message(std::move(p.m_message)) {}
    
    mutable std::unique_ptr<UDPMessage> m_message;
};

/**********************/
class MasterGateway : public RequestEngine<int, Params>::Gateway
{
public:
	MasterGateway(int port, std::string master_ip);
    ~MasterGateway() = default;

	MasterGateway(const MasterGateway&) = delete;
	MasterGateway& operator=(const MasterGateway&) = delete;

	UDPMessage Deserialize(std::vector<char> data);

    std::pair<int, Params> Read();
};

/********************/
class DPTask : public RequestEngine<int,Params>::Task
{
public:
    DPTask(const Params& params) : m_msg(std::move(params.m_message))
	{}

    virtual ~DPTask() 
	{}

    std::unique_ptr<UDPMessage>& GetUniqueMsg() 
	{ 
		return m_msg; 
	}

private:
    virtual void Execute() = 0;

    std::unique_ptr<UDPMessage> m_msg;
};

/********************/
class Read : public DPTask
{
public:
    Read(const Params& params);
    ~Read() override;

    // Un-copyable
    Read(const Read&) = delete;
    Read& operator=(const Read&) = delete;

private:
    void Execute() override;
};

/********************/
class Write : public DPTask
{
public:
    Write(const Params& params);
    ~Write() override;

    // Un-copyable
    Write(const Write&) = delete;
    Write& operator=(const Write&) = delete;

private:
    void Execute() override;
};


/************************** Forward Declarations ******************************/
void SigAction(int sig);
void Reply(UDPMessage* message);
void Serialize(char* buffer, const UDPMessage& message);

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main()
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

	// Config cfg;
    // cfg.readFile("slave_config.cfg");

	RequestEngine<int, Params> req_engine("/home/yaronmeister/git/yaron-meister/projects/monitor"/* cfg.lookup("path_folder") */);
	re_ptr = &req_engine;

    MasterGateway master_gateway(/* cfg.lookup("slave_socket_port") */ 8080, 
								 /* cfg.lookup("master_ip") */ "127.0.0.1");

    req_engine.AddGateway(master_gateway);

    req_engine.ConfigTask(0, [](Params params) 
                { return std::unique_ptr<RequestEngine<int,Params>::Task>
                                                ( new Read(params)); });
    req_engine.ConfigTask(1, [](Params params) 
                { return std::unique_ptr<RequestEngine<int,Params>::Task>
                                                ( new Write(params)); });

    req_engine.Run();
 
    return (EXIT_SUCCESS);
} 


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/ 
/******************************************************************************/ 
/* Struct UDPMessage */
/******************************************************************************/
UDPMessage::UDPMessage(int socket_fd, int req_id, int type, size_t offset, 
	 size_t len, std::vector<char> data) :
						m_socket_fd(socket_fd), m_req_id(req_id), m_type(type),
						m_offset(offset), m_len(len), m_data(data)
				
{}


/******************************************************************************/ 
/* Class MasterGateway */
/******************************************************************************/
MasterGateway::MasterGateway(int port, std::string master_ip)
        : RequestEngine<int, Params>::Gateway
                                       (socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP))
{
	if (-1 == GetFD())
	{
		g_logger->Write("MasterGateway::socket failed"); 
		perror("MasterGateway::socket failed");
		throw std::runtime_error("MasterGateway::socket failed");
	}

	bzero(&address, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET; 
	address.sin_port = htons(port); 
	address.sin_addr.s_addr = INADDR_ANY;

	if (inet_pton(AF_INET, master_ip.c_str(), &address.sin_addr) <= 0)  
	{ 
		g_logger->Write
				("Gateway::inet_pton()-Invalid address/Address not supported"); 
		throw std::runtime_error("Gateway::inet_pton()");
	}

	const char* connect = "Hi moran I am your slave";

	if (-1 == sendto(GetFD(), connect, strlen(connect), 0,
							(const struct sockaddr*) &address, sizeof(address)))
	{
		perror("slave_test: sendto()");
		throw std::runtime_error("slave_test: sendto()");
	} 
}

/******************************************************************************/
UDPMessage MasterGateway::Deserialize(std::vector<char> message)
{
	size_t offset;
	size_t len;
	int id;
	int type;
	std::vector<char> data(4*KB);

	sscanf(message.data(), "%lu;%lu;%d;%d;", &offset, &len, &id, &type);
	char* runner = strchr(message.data(), '\0') + 1;
	memcpy(data.data(), runner, len);

	return (UDPMessage(GetFD(), id, type, offset, len, data));
}

/******************************************************************************/
std::pair<int, Params> MasterGateway::Read()
{
	std::vector<char> data;
	data.reserve(BUFFER_SIZE);

	size_t struct_size = sizeof(struct sockaddr_in);

	if (-1 == recvfrom(GetFD(), const_cast<char*>(data.data()), BUFFER_SIZE, 0, 
	  (struct sockaddr*) &address, reinterpret_cast<socklen_t *>(&struct_size)))
	{
		perror("recvfrom failed"); 
        throw std::runtime_error("recvfrom");
	} 

printf("\n\n");
printf("RECEIVING:\n");

for (size_t i = 0; i < 1000; ++i)
{
	printf("%c", ((data.data())[i]));
}
printf("\nFINISHED RECEIVING\n\n");
printf("\n\n");



	std::unique_ptr<UDPMessage> message(new 
									  UDPMessage(Deserialize(std::move(data))));
	int type = message->m_type;

	return (std::pair<int, Params>(type, Params(std::move(message))));
}


/******************************************************************************/
/* Class Read */
/******************************************************************************/
Read::Read(const Params& params) : DPTask(params) 
{}

/******************************************************************************/
Read::~Read(){}

/******************************************************************************/
void Read::Execute()
{
	std::vector<char> vec(BUFFER_SIZE);
    storage.Read(vec, GetUniqueMsg()->m_offset, GetUniqueMsg()->m_len);
	GetUniqueMsg()->m_data = vec;

	Reply(GetUniqueMsg().get ());
}


/******************************************************************************/
/* Class Write */
/******************************************************************************/
Write::Write(const Params& params) : DPTask(params)        										
{}

/******************************************************************************/
Write::~Write(){}

/******************************************************************************/
void Write::Execute()
{
    storage.Write(GetUniqueMsg()->m_data.data(), GetUniqueMsg()->m_offset,
														 GetUniqueMsg()->m_len);
    
	if (GetUniqueMsg()->m_offset < (SIZE_STORAGE / 2))
	{
		Reply(GetUniqueMsg().get());
	}

}


/******************************************************************************/
/* Free functions */
/******************************************************************************/
void SigAction(int sig)
{
    UNUSED_VAR(sig);

    re_ptr->Stop();

	std::cout << "\nSlave exited normally\n";
}

/******************************************************************************/
void Serialize(char* buffer, const UDPMessage& message)
{
	int bytes_num = sprintf(buffer, "%lu;%d;%d;%c",
						    message.m_len, message.m_req_id, message.m_type, 0);

	memcpy(&(buffer[bytes_num]), message.m_data.data(), message.m_len);
}

/******************************************************************************/
void Reply(UDPMessage* message)
{
	char buffer[BUFFER_SIZE];
	Serialize(buffer, *message);

printf("REPLYING:\n");
for (size_t i = 0; i < 1000; ++i)
{
	printf("%c", (buffer[i]));
}
printf("\nFINISHED REPLYING\n\n");


    if (-1 == sendto(message->m_socket_fd,
	 				buffer, 
					BUFFER_SIZE, 
					0,
					(const struct sockaddr*) &address, sizeof(address)))
	{
		perror("slave_test: sendto()");
		throw std::runtime_error("slave_test: sendto()");
	}
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
