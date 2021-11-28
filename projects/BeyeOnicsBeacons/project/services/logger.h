////////////////////////////////////////////////////////////////////////////////
//  File name:  logger.h
//  Developer:  Yaron Meister
//  Date:       05.04.2019
//  Desciption: A header file for Logger
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "singleton.hpp"

#include <fstream>
#include <iostream>


class Logger
{
public:
  friend class Singleton<Logger>;
  ~Logger();

  // Un-copyable
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void Write(const std::string& str);

private:
  // CTor
  Logger();

  std::ofstream m_file;
  std::mutex    m_mutex;
};

template class Singleton<Logger>;

class LoggerException : public std::runtime_error
{
public:
  LoggerException(const char* what_arg) : runtime_error(what_arg)
  {}

  virtual ~LoggerException() {}
};



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
