/*****************************************************************************
 * File name:   watch_dog.h
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2019-02-07 13:04:07
 * Description: Watch Dog header
 *****************************************************************************/

#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__

#include <time.h>      /* time_t */

/* 
 * Return value: > 0 -> success, returns pid of the created watchdog
 * 			     < 0 -> failure
 *  <prog_argc> and <prog_argv> are the vars required to exec the user program
 *  if it fails. 
 *  <WDKeepMeAlive> sets its own handlers to SIGUSR1 & SIGUSR2, hence - they are
 *  not available for the user while using watch dog.
 *	<interval> is the desirable interval between live checks.
 */
int WDKeepMeAlive(int prog_argc, char *prog_argv[], char *env[], 
															   time_t interval);

/*
 * Destroys WD, SIGUSR1 & SIGUSR2 are available for the user.
 */
void WDLetMeDie(int wd_pid);

#endif     /* __WATCH_DOG_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
