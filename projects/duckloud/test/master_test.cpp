/*****************************************************************************
 * File name:   master_test.cpp
 * Developer:   Yaron Meister
 * Date:        2019-05-12 13:26:48
 *****************************************************************************/
 
#include <iostream>         // cout, cerr	
#include <stdlib.h>         // EXIT_SUCCESS 
#include <signal.h>         // sigset_t 
#include <stdio.h>          // printf

#include "utils.h"
#include "slave_types.h"
#include "nbd_types.h"
#include "request_engine.h"

using namespace ilrd;
/********************************* Macros *************************************/ 
const int NBD_TASK = 0;
const int SLAVE_TASK = 1;


/************************** Forward Declarations ******************************/
void SigAction(int sig);
void ConfigTasks(RequestEngine<int, Params>& req_engine);

/***************************** Global variables *******************************/
Logger* g_logger = Handleton<Logger>::GetInstance();
RequestEngine<int, Params>* re_ptr(nullptr);


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(int argc, char* argv[])
{
    UNUSED_VAR(argc);
    
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

    size_t storage_size = 4194304;
    SlaveManager slave_manager(storage_size);
    printf("slave-MANAGER: %p\n", (void*)&slave_manager); 

    SlaveProxy slave_proxy(8080, "127.0.0.1");
    slave_manager.AddProxy(&slave_proxy);

    std::shared_ptr<DriverProxy> driver_proxy(new DriverProxy(argv[1], /* cfg.lookup("storage_size") */ 4194304));
    // dp_ptr = &driver_proxy;
   
    SlaveGateway slave_gateway(slave_proxy, driver_proxy);

    RequestEngine<int, Params> req_engine(/* cfg.lookup("path_folder") */ "/home/yaronmeister/git/yaron-meister/projects/master_monitor");
	re_ptr = &req_engine;


    NBDGateway nbd_gateway(driver_proxy, slave_manager);

    req_engine.AddGateway(nbd_gateway);
    req_engine.AddGateway(slave_gateway);

    ConfigTasks(req_engine);

    req_engine.Run();

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
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
void ConfigTasks(RequestEngine<int, Params>& req_engine)
{
    req_engine.ConfigTask(NBD_TASK, [](Params params) 
                { return std::unique_ptr<RequestEngine<int,Params>::Task>
                                                ( new NBDTask(params)); });
    req_engine.ConfigTask(SLAVE_TASK, [](Params params) 
                { return std::unique_ptr<RequestEngine<int,Params>::Task>
                                                ( new SlaveTask(params)); });
    
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
