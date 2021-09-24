/*****************************************************************************
 * File name:   ButtonsLog.c
 * Developer:   Yaron Meister
 * Date:        2021-09-17 11:04:53
 * Description: Source file for logging the Buttons
 *****************************************************************************/

#include "ButtonsLog.h"
#include "ButtonsMonitor.h"
#include "ButtonsDef.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/* Macros */
#define MAX_LOG_STR_LENGTH (50)
#define MAX_STATE_STR_LENGTH (4)

/* Static/Global variables */
static FILE* errorLog = NULL;
static FILE* buttonsLog = NULL;
static SButtonType* buttons = NULL;
static unsigned numOfButtons = 0;
static SYSTEMTIME time = { 0 };

/* Forward Declarations */

/**************************************************
* Function Name: doInit
* Description:   Initiates static variables
* Return Value:  SUCCESS - All inits succeeded, FAILURE - Otherwise
**************************************************/
static EStatusType doInit(char* buttonsIds[]);

/**************************************************
* Function Name: doDestruction
* Description:   Frees allocations, Closes opened files
* Return Value:  None
**************************************************/
static void doDestruction(void);

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(int argc, char* argv[])
{
  Boolean initSucceeded = FALSE;
  EStatusType exitStatus = SUCCESS;

  errorLog = fopen("ErrorLog.txt", "w");
  if (NULL != errorLog)
  {
    numOfButtons = argc - 1; /* First arg is the program's name */
    initSucceeded = doInit(argv);

    if (SUCCESS == initSucceeded)
    {
      while (!isStopProgram())
      {
        monitorButtons();
        logButtons();
      }

      doDestruction();
    }
    else
    {
      fwrite("Initiation Failed\n", sizeof(char), sizeof("Initiation Failed\n"), errorLog);
      exitStatus = FAILURE;
    }

    fclose(errorLog);
  }
  else
  {
    fprintf(stderr, "Opening Error Log file failed");
    exitStatus = FAILURE;
  }

  return (exitStatus);
}


/*******************************************************************************
                          Functions Implementations
*******************************************************************************/
static EStatusType doInit(char* buttonsIds[])
{
  EStatusType initStatus = FAILURE;
  unsigned idx = 0;

  buttons = calloc(numOfButtons, sizeof(SButtonType));
  if (NULL != buttons && NULL != buttonsIds)
  {
    for (idx = 0; idx < numOfButtons; ++idx)
    {
      buttons[idx].id = buttonsIds[idx + 1][0] - '0';
    }

    buttonsLog = fopen("ButtonsLog.txt", "w");
    if (NULL != buttonsLog)
    {
      initStatus = SUCCESS;
    }
    else
    {
      free(buttons);
      buttons = NULL;
      fwrite("Opening Buttons Log file failed\n", sizeof(char), sizeof("Opening Buttons Log file failed\n"), errorLog);
    }
  }
  else
  {
    if (NULL == buttons)
    {
      fwrite("Allocation Failed\n", sizeof(char), sizeof("Allocation Failed\n"), errorLog);
    }
    else
    {
      fwrite("argv == NULL\n", sizeof(char), sizeof("argv == NULL\n"), errorLog);
    }
  }

  return (initStatus);
}

/******************************************************************************/
static void doDestruction(void)
{
  free(buttons);
  buttons = NULL;
  fclose(buttonsLog);
  buttonsLog = NULL;
}

/******************************************************************************/
void logButtons(void)
{
  char logStr[MAX_LOG_STR_LENGTH] = "";
  char onStr[] = "ON";
  char offStr[] = "OFF";
  char stateStr[MAX_STATE_STR_LENGTH] = "";
  unsigned idx = 0;
  Boolean pressState = OFF;

  for (idx = 0; idx < numOfButtons; ++idx)
  {
    pressState = getPress(buttons[idx].id);

    if (buttons[idx].state != pressState && INVALID != pressState)
    {
      buttons[idx].state = pressState;

      if (ON == buttons[idx].state)
      {
        sprintf_s(stateStr, MAX_STATE_STR_LENGTH, "%s", onStr);
      }
      else
      {
        sprintf_s(stateStr, MAX_STATE_STR_LENGTH, "%s", offStr);
      }

      sprintf_s(logStr, MAX_LOG_STR_LENGTH, "Button %u has been switched %s\n", buttons[idx].id, stateStr);
      sendData(logStr);
    }
    else if (INVALID == pressState)
    {
      fwrite("Got invalid port\n", sizeof(char), sizeof("Got invalid port\n"), errorLog);
    }
  }
}

/******************************************************************************/
void sendData(char* data)
{
  char timedLogStr[MAX_LOG_STR_LENGTH] = "";

  if (NULL != data)
  {
    GetLocalTime(&time);
    sprintf_s(timedLogStr, MAX_LOG_STR_LENGTH, "%u:%u:%u ", time.wHour, time.wMinute, time.wSecond);
    strcat(timedLogStr, data);
    fwrite(timedLogStr, sizeof(char), strlen(timedLogStr), buttonsLog);
  }
  else
  {
    fwrite("Got invalid data\n", sizeof(char), sizeof("Got invalid data\n"), errorLog);
  }
}


/* END OF FILE */