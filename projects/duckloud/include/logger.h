/*****************************************************************************
 * File name:   logger.h
 * Developer:   HRD7
 * Version: 
 * Date:        2019-04-05 14:45:19
 * Description: Class Logger header
 *****************************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>
#include <iostream>

#include "handleton.h"      /* class handleton */

namespace ilrd
{

class Logger
{
    public:
        friend class Handleton<Logger>;
        ~Logger();

        // Un-copyable
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        void Write(const std::string& str);

    private:
        std::ofstream m_file;
        std::mutex m_mutex;
        
        Logger();
};

template class Handleton<Logger>;

class LoggerException : public std::runtime_error
{
    public:
        LoggerException(const char* what_arg) : runtime_error(what_arg)
        {}

        virtual ~LoggerException(){}
};

} //ilrd

 

 
#endif     /* __LOGGER_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
