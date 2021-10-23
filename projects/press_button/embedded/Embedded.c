/*****************************************************************************
* File name:   Embedded.c
* Developer:   Yaron Meister
* Date:        2021-09-28 14:26:21
* Description: Source file for Embedded app
*****************************************************************************/

#include "Embedded.h"
#include "System.h"

#include <stdlib.h>
#include <Windows.h>

/* Macros */
#define MAX_SAVED_PRESSES (2)
#define BUTTON_KEY ('1')
#define SHORT_HIGH_BIT (0x8000)

/* Static/Global variables */
static int durations[MAX_SAVED_PRESSES] = { 0 };
static int pressStartTime = 0;
static unsigned char pressCounter = 0;
static unsigned char currentPressReadIdx = 0;
static unsigned char currentPressWriteIdx = 0;
static Boolean isKeyPressed = FALSE;

/* Forward Declarations */

/**************************************************
* Function Name:  runPressCheckRoutine
* Description:    Checks if a button press occurs/occurred
* Return Value:   None
**************************************************/
static void runPressCheckRoutine(void);


/*******************************************************************************
                          Functions Implementations
*******************************************************************************/
int checkForButtonPress(void)
{
  Boolean isButtonPressed = 0;
  int measuredDuration = 0;

  runPressCheckRoutine();
  isButtonPressed = (0 != pressCounter);

  if (isButtonPressed)
  {
    --pressCounter;
    measuredDuration = durations[currentPressReadIdx];
    currentPressReadIdx = !currentPressReadIdx;
  }

  return (measuredDuration);
}

/******************************************************************************/
static void runPressCheckRoutine(void)
{
  if (pressCounter < MAX_SAVED_PRESSES)
  {
    if (GetKeyState(BUTTON_KEY) & SHORT_HIGH_BIT)
    {
      if (FALSE == isKeyPressed)
      {
        isKeyPressed = TRUE;
        pressStartTime = systemTime();
      }
    }
    else
    {
      if (TRUE == isKeyPressed)
      {
        ++pressCounter;
        durations[currentPressWriteIdx] = systemTime() - pressStartTime;
        currentPressWriteIdx = !currentPressWriteIdx;
        isKeyPressed = FALSE;
      }
    }
  }
}

/* END OF FILE */