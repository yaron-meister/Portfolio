/*****************************************************************************
* File name:   Embedded.h
* Developer:   Yaron Meister
* Date:        2021-09-28 14:25:41
* Description: Header file for the Embedded app
*****************************************************************************/

#ifndef __EMBEDDED_H__
#define __EMBEDDED_H__


#include "Utils.h"

/***** Functions Declarations *****/

/**************************************************
* Function Name:	checkForPress	
* Description:		Indicates if a button press occurred
* Return Value:		Measured Press Duration
*									0 - If a press didn't occur
**************************************************/
int checkForButtonPress(void);


#endif     /* __EMBEDDED_H__ */

/* END OF FILE */