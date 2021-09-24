/*****************************************************************************
 * File name:   ButtonsMonitor.h
 * Developer:   Yaron Meister
 * Date:        2021-09-17 11:04:53
 * Description: Header file for Monitoring the Buttons
 *****************************************************************************/

#ifndef __BUTTONS_MONITOR_H__
#define __BUTTONS_MONITOR_H__

#include "ButtonsDef.h"
#include "Utils.h"

/***** Functions Declarations *****/

/**************************************************
* Function Name: getPress
* Description:   Gets the current 'port' button's state
* Return Value:  ON, OFF
**************************************************/
EButtonsStateType getPress(unsigned port);

/**************************************************
* Function Name: isStopProgram
* Description:   Gets the logging status
* Return Value:  TRUE - Keep logging, FALSE - stop
**************************************************/
Boolean isStopProgram(void);

/**************************************************
* Function Name: monitorButtons
* Description:   Monitors the buttons activity
* Return Value:  None
**************************************************/
void monitorButtons(void);

#endif     /* __BUTTONS_MONITOR_H__ */


/* END OF FILE */