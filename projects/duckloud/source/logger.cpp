/*****************************************************************************
 * File name:   logger.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-04-05 14:45:19
 * Description: Class Logger implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*       	       	    */
#include <chrono>
#include <ctime> 

#include "logger.h"     /* Forward declarations */

using namespace ilrd; 
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
Logger::Logger()
{
    m_file.open("logger.txt");
}

/******************************************************************************/
Logger::~Logger()
{
    m_file.close();
}

/******************************************************************************/
void Logger::Write(const std::string& str)
{
    try
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        
        // Writing on file
        m_file << std::ctime(&end_time) << ":  " << str << std::endl;
    }
    catch(...)
    {
        throw LoggerException("write");
    }
}
    
    
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
