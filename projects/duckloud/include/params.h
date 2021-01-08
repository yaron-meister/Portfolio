/*****************************************************************************
 * File name:   params.h
 * Developer:   HRD7
 * Date:        2019-05-13 15:54:55
 *****************************************************************************/

#ifndef __PARAMS_H__
#define __PARAMS_H__

namespace ilrd
{
    struct Params;
}

#include "driver_proxy.h"
#include "slave_types.h"

namespace ilrd
{

struct Params
{
    Params(std::unique_ptr<DataRequest> request, 
           SlaveManager* slave_manager, 
           std::shared_ptr<DriverProxy> dp);
    Params(const Params& p);
    
    mutable std::unique_ptr<DataRequest> m_request;
    SlaveManager* m_slave_manager;
    std::shared_ptr<DriverProxy> m_dp;
};


} //ilrd
 
 
#endif     /* __PARAMS_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
