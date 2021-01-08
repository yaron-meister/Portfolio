/*****************************************************************************
 * File name:   params.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-05-14 15:40:26
 * Description: 
 *****************************************************************************/
 
#include <iostream>     /* 	cout, cerr	*/
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "params.h"

using namespace ilrd;
/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
Params::Params(std::unique_ptr<DataRequest> request, 
           SlaveManager* slave_manager, 
           std::shared_ptr<DriverProxy> dp)
       : m_request(std::move(request)), m_slave_manager(slave_manager), m_dp(dp)
{}

/******************************************************************************/
Params::Params(const Params& p)
    : m_request(std::move(p.m_request)), 
        m_slave_manager(p.m_slave_manager), 
        m_dp(p.m_dp)
{}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
