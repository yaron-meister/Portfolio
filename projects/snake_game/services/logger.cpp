/*****************************************************************************
 * File name:   logger.cpp
 * Developer:   Yaron Meister
 * Date:        2019-04-05 14:45:19
 * Description: Implementation of class Logger
 *****************************************************************************/

#include <iostream>     
#include <cstdlib>      
#include <chrono>
#include <ctime> 

#include "logger.h"     


////////////////////////////////////////////////////////////////////////////////
//                         Functions Implementations
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Logger::Logger()
{
  m_file.open("logger.log");
}

////////////////////////////////////////////////////////////////////////////////
Logger::~Logger()
{
  m_file.close();
}

////////////////////////////////////////////////////////////////////////////////
void Logger::write(const std::string& str)
{
  try
  {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    // Writing on file
    m_file << std::ctime(&end_time) << ":  " << str << std::endl;
  }
  catch (...)
  {
    throw LoggerException("write");
  }
}
