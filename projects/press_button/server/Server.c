/*****************************************************************************
* File name:   Server.c
* Developer:   Yaron Meister
* Date:        2021-09-28 14:22:32
* Description: Source file for Server's API
*****************************************************************************/

#include "Server.h"

#include <stdlib.h>

/* Macros */

/* Static/Global variables */
static Boolean isBusy = FALSE;
static int realDuration = 0;

/* Forward Declarations */


/*******************************************************************************
                          Functions Implementations
*******************************************************************************/
int serverCreateConnection(void)
{
  return (rand());
}

/******************************************************************************/
void serverCloseConnection(int* pOpenedConnection)
{
  *pOpenedConnection = 0;
}


/******************************************************************************/
Boolean serverIsBusy(int commHandle)
{
  return (isBusy);
}

/******************************************************************************/
int serverTxMeasuredDuration(int commHandle, int measuredDuration)
{
  realDuration = measuredDuration;

  return (commHandle);
}

/******************************************************************************/
int serverRxResponse(int commHandle)
{
  return (realDuration);
}

/* END OF FILE */