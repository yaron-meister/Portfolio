/*****************************************************************************
 * File name:   wd.c
 * Developer:   Yaron Meister
 * Date:        2019-02-07 16:26:24
 * Description: wd.out source file for watch_dog.c
 *****************************************************************************/

#include <stdio.h>     		/* 		 fprintf  	   	*/
#include <assert.h>			/*		 assert			*/
#include <semaphore.h>		/*		semaphore		*/
#include <signal.h>			/*    	  signal		*/
#include <unistd.h>			/*	  	  sleep			*/
#include <sys/types.h> 		/*	   	  kill			*/
#include <stdlib.h>   	 	/*    EXIT_SUCCESS		*/
#include <fcntl.h>          /*    O_* constants 	*/
#include <sys/stat.h>       /*    mode constants 	*/

#include "utils.h"			/*	  DBG, UNUSED_VAR	*/
#include "scheduler.h"		/*		scheduler.c		*/
#include "watch_dog.h"      /* Forward declarations */
#include "wd_routine.h"		/*		WDRoutine		*/

/********************************* Macros *************************************/ 
extern int g_stop_flag;

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(int argc, char *argv[], char *env[])
{
	thread_arg_t thread_args = {0};
	int status				 = EXIT_FAILURE;
	char *wd_interval		 = getenv("WD_INTERVAL");

	thread_args.argc = argc;
	thread_args.argv = argv;
	thread_args.env  = env;
	
	if (NULL != wd_interval)
	{
		status = EXIT_SUCCESS;
		thread_args.interval = atoi(wd_interval);
		WDRoutine(thread_args);
	}

    return (status);
} 



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
