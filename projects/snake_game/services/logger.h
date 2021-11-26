/*****************************************************************************
 * File name:   logger.h
 * Developer:   Yaron Meister
 * Date:        2019-04-05 14:45:19
 * Description: Header file for Logger
 *****************************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>
#include <iostream>

#include "singleton.hpp"      /* class handleton */
#include "params.h"


class Logger
{
public:
  friend class Singleton<Logger>;
  ~Logger();

  // Un-copyable
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void write(const std::string& str);

private:
  // CTor
  Logger();

  std::ofstream m_file;
  std::mutex m_mutex;
};

template class Singleton<Logger>;

class LoggerException : public std::runtime_error
{
public:
  LoggerException(const char* what_arg) : runtime_error(what_arg)
  {}

  virtual ~LoggerException() {}
};


#endif     /* __LOGGER_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
