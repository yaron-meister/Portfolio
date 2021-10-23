/*****************************************************************************
* File name:   Server.h
* Developer:   Yaron Meister
* Date:        2021-09-28 14:12:57
* Description: Header file for the Server's API
*****************************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "Utils.h"

/***** Functions Declarations *****/

/**************************************************
* Function Name:	serverCreateConnection
* Description:		Opens communication port with the Server
*									This function call consumes 1 micro sec
* Return Value:		!0 - A valid communication handle 
*									 0 - If invalid
**************************************************/
int serverCreateConnection(void);

/**************************************************
* Function Name:	serverCloseConnection
* Description:		Closes communication port with the Server
* Return Value:		None
**************************************************/
void serverCloseConnection(int* pOpenedConnection);

/**************************************************
* Function Name:	serverIsBusy
* Description:		Indicates if the Server is busy
*									This function call consumes 1 micro sec
* Return Value:		TRUE - Busy, FALSE - otherwise
**************************************************/
Boolean serverIsBusy(int commHandle);

/**************************************************
* Function Name:	serverTxMeasuredDuration
* Description:		Sends the measured duration to the Server
*									This function call consumes 1 micro sec
* Return Value:		If valid - The communication handle input
*									If invalid - 0
**************************************************/
int serverTxMeasuredDuration(int commHandle, int measuredDuration);

/**************************************************
* Function Name:	serverRxResponse
* Description:		Gets the real processed duration from the Server
*									This function call consumes 1 micro sec
* Return Value:		If valid - The processed duration
**************************************************/
int serverRxResponse(int commHandle);


#endif     /* __SERVER_H__ */

/* END OF FILE */