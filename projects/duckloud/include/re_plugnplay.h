/*****************************************************************************
 * File name:   re_plugnplay.h
 * Developer:   HRD7
 * Date:        2019-05-14 10:41:26
 *****************************************************************************/

#ifndef __RE_PLUGNPLAY_H__
#define __RE_PLUGNPLAY_H__

#include "plug_and_play.h"

namespace ilrd
{

class PlugNPlay
{
public:
    PlugNPlay(const std::string& path_name);
    ~PlugNPlay() = default;

    // Un-copyable
    PlugNPlay(const PlugNPlay&) = delete;
    PlugNPlay& operator=(const PlugNPlay&) = delete;

private:
    DirMonitor m_dir_monitor;
    DllLoader m_dll_loader;
};


} //ilrd
 
 
#endif     /* __RE_PLUGNPLAY_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
