/*****************************************************************************
* File name:   System.h
* Developer:   Yaron Meister
* Date:        2021-09-28 14:14:15
* Description: Header file for the System's API
*****************************************************************************/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__


/***** Functions Declarations *****/

/**************************************************
* Function Name: doSystemInit
* Description: Initiates System module
* Return Value: None
**************************************************/
void doSystemInit(void);

/**************************************************
* Function Name: systemTime
* Description: Returns the System's Time in [ms]
* Return Value: System's time in [ms], as integer
**************************************************/
int systemTime(void);

/**************************************************
* Function Name: systemPrintInt
* Description: Prints to stdio
* Return Value: None
**************************************************/
void systemPrintInt(int valueToPrint);


#endif     /* __SYSTEM_H__ */

/* END OF FILE */