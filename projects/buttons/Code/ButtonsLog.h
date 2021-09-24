/*****************************************************************************
 * File name:   ButtonsLog.h
 * Developer:   Yaron Meister
 * Date:        2021-09-17 11:04:53
 * Description: Header file for logging the Buttons
 *****************************************************************************/

#ifndef __BUTTONS_LOG_H__
#define __BUTTONS_LOG_H__

#include "Utils.h"

/***** Functions Declarations *****/

/**************************************************
* Function Name: logButtons
* Description:   Does the actual logging
* Return Value:  None
**************************************************/
void logButtons(void);

/**************************************************
* Function Name: sendData
* Description:   Sends the log data to its dest
* Return Value:  None
**************************************************/
void sendData(char* data);


#endif     /* __BUTTONS_LOG_H__ */

/* END OF FILE */