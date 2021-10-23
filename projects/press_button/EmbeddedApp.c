/*****************************************************************************
* File name:   PressButton.c
* Developer:   Yaron Meister
* Date:        2021-09-28 14:09:14
* Description: Runs the "Press Button" project's main function
*****************************************************************************/

#include "Embedded.h"
#include "Server.h"
#include "System.h"

#include <stdlib.h>
#include <conio.h>

/* Macros */


/* Static/Global variables */
static int measuredDuration = 0;
static int currentCommHandle = 0;
static Boolean waitingForServer = FALSE;

/* Forward Declarations */


/**************************************************
* Function Name:  processButtonPress 
* Description:    A routine for button press checking
* Return Value:   None
**************************************************/
static void processButtonPress(void);

/*******************************************************************************
                              Main Function
*******************************************************************************/
int main(void)
{
  char input = '\0';

  doSystemInit();

  while ('Q' != input && 'q' != input)
  {
    processButtonPress();

    if (_kbhit())
    {
      input = _getch();
    }
  }
}


/*******************************************************************************
                        Functions Implementations
*******************************************************************************/
static void processButtonPress(void)
{
  if (0 != measuredDuration)
  {
    if (!waitingForServer)
    {
      currentCommHandle = serverCreateConnection();

      if (0 != currentCommHandle)
      {
        if (serverTxMeasuredDuration(currentCommHandle, measuredDuration))
        {
          waitingForServer = TRUE;
        }
        else
        {
          waitingForServer = FALSE;
          serverCloseConnection(&currentCommHandle);
        }
      }
    }
    else
    {
      if (!serverIsBusy(currentCommHandle))
      {
        systemPrintInt(serverRxResponse(currentCommHandle));
        waitingForServer = FALSE;
        measuredDuration = 0;
        serverCloseConnection(&currentCommHandle);
      }
    }
  }
  else
  {
    measuredDuration = checkForButtonPress();
  }
}


/* END OF FILE */