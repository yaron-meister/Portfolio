/*****************************************************************************
 * File name:   ButtonsMonitor.c
 * Developer:   Yaron Meister
 * Date:        2021-09-17 11:04:53
 * Description: Source file for Monitoring the Buttons
 *****************************************************************************/

#include "ButtonsMonitor.h"

#include <conio.h>

/* Macros */
#define MAX_BUTTONS_NUM (10) /* 10 is an asumption for this exercise */

/* Static/Global variables */
EButtonsStateType monitoredButtons[MAX_BUTTONS_NUM] = {OFF};
Boolean stopProgram = FALSE;

/*******************************************************************************
                          Functions Implementations
*******************************************************************************/
EButtonsStateType getPress(unsigned port)
{
  EButtonsStateType buttonState = INVALID;

  if (port < MAX_BUTTONS_NUM)
  {
    buttonState = monitoredButtons[port];
  }

  return (buttonState);
}

/******************************************************************************/
Boolean isStopProgram(void)
{
  return (stopProgram);
}

/******************************************************************************/
void monitorButtons(void)
{
  char input = '\0';
  unsigned buttonId = 0;

  if (_kbhit())
  {
    input = _getch();

    if (input >= '0' && input <= '9')
    {
      buttonId = input - '0';
      monitoredButtons[buttonId] = (OFF == monitoredButtons[buttonId] ? ON : OFF);
    }
    else if ('q' == input || 'Q' == input)
    {
      stopProgram = TRUE;
    }
  }
}


/* END OF FILE */