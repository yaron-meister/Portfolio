/*****************************************************************************
* File name:   System.c
* Developer:   Yaron Meister
* Date:        2021-09-28 14:19:18
* Description: Source file for System's API
*****************************************************************************/

#include "System.h"

#include <sys\timeb.h>
#include <stdio.h>

/* Macros */
#define SEC_TO_MS (1000)

/* Static/Global variables */
static struct timeb startTime, endTime;

/* Forward Declarations */

/*******************************************************************************
                        Functions Implementations
*******************************************************************************/
int systemTime(void)
{
  ftime(&endTime);

  return ((int)((endTime.time - startTime.time) * SEC_TO_MS) + (endTime.millitm - startTime.millitm));
}

/******************************************************************************/
void systemPrintInt(int valueToPrint)
{
  printf("%d\n", valueToPrint);
}

/******************************************************************************/
void doSystemInit(void)
{
  ftime(&startTime);
}


/* END OF FILE */