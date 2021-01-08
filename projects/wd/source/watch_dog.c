/*****************************************************************************
 * File name:   watch_dog.c
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2019-02-07 13:04:07
 * Description: Watch Dog implementation
 *****************************************************************************/

#define _GNU_SOURCE			/*		 execvpe		*/	

#include <stdio.h>     		/* 		 fprintf  	   	*/
#include <stdlib.h>    		/*    setenv, getenv    */
#include <assert.h>			/*		 assert			*/
#include <semaphore.h>		/*		semaphore		*/
#include <pthread.h>		/*  	pthread_t		*/
#include <signal.h>			/*    	  signal		*/
#include <unistd.h>			/*	  	  sleep			*/
#include <sys/types.h> 		/*	   	  kill			*/
#include <stdlib.h>   	 	/*    EXIT_SUCCESS		*/
#include <fcntl.h>          /*    O_* constants 	*/
#include <sys/stat.h>       /*    mode constants 	*/

#include "utils.h"			/*	  DBG, UNUSED_VAR	*/
#include "scheduler.h"		/*		scheduler.c		*/
#include "watch_dog.h"      /* Forward declarations */
#include "wd_routine.h"	

/********************************* Macros *************************************/ 
#define INITIAL_VALUE (0) 
#define SEM1_NAME "/semaphore1"
#define SEM2_NAME "/semaphore2"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define BUFFER_SIZE (20)

enum set_env_overwrite
{
	NO_OVERWRITE,
	OVERWRITE
};

/************************** Forward Declarations ******************************/
/** Initiates Named-Semaphore **/
static void SemsInit(void);
/** Communication-thread function **/
static void *CommThreadFunc(thread_arg_t *thread_args);
static void DestroyWD(void);
 
/***************************** Global variables *******************************/
/** Named-Semaphores **/
sem_t *sem1		 = NULL;
sem_t *sem2 	 = NULL;
/** A flag for schedulers stop **/
extern int g_stop_flag;

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
int WDKeepMeAlive(int prog_argc, char *prog_argv[], char *env[],
															    time_t interval)
{
	thread_arg_t thread_args = {0};
	pthread_t thread_id 	 =  0;
    int ret_pid				 = -1;
	char *pid_to_send_env 	 = getenv("PID_TO_SEND");
    char prog_pid_str[BUFFER_SIZE] = "";	/* A buffer for prog pid Env Var */
	char interval_str[BUFFER_SIZE] = "";	/* A buffer for interval Env Var */

	assert(interval);

	thread_args.argc 	 = prog_argc;
	thread_args.argv 	 = prog_argv;
	thread_args.env 	 = env;
	thread_args.interval = interval;

	SemsInit();						

	/* Env Var for reserving the prog's pid */
    sprintf(prog_pid_str, "%d", getpid());			
	setenv("PROG_PID", prog_pid_str, OVERWRITE);

	/* Env Var for reserving the interval */
    sprintf(interval_str, "%d", (int)interval);			
	setenv("WD_INTERVAL", interval_str, OVERWRITE);
			
	pthread_create(&thread_id, NULL, (void*(*)(void*))CommThreadFunc,
														   (void*)&thread_args);
	/* Waiting for Schedulers Run */
	sem_wait(sem1);
	sem_wait(sem1);

	if (NULL != pid_to_send_env)
	{
		ret_pid = atoi(pid_to_send_env);
	}
	
	return (ret_pid);
}
	
/********************* 								      *********************/
/** Initiates Named-Semaphore **/ 	
static void SemsInit(void)
{
	sem1 = sem_open(SEM1_NAME, O_CREAT, SEM_PERMS, INITIAL_VALUE);
	sem2 = sem_open(SEM2_NAME, O_CREAT, SEM_PERMS, INITIAL_VALUE);

	if (SEM_FAILED == sem1 || SEM_FAILED == sem2)
	{
        perror("sem_open of thread error");
        exit(EXIT_FAILURE);
    }
}

/********************* 								      *********************/
/** Communication-thread function **/ 	
static void *CommThreadFunc(thread_arg_t *thread_args)
{	
	assert(thread_args);

	WDRoutine(*thread_args);
	
	return (NULL);
}

/******************************************************************************/
void WDLetMeDie(int wd_pid)
{
	UNUSED_VAR(wd_pid);
	
	DestroyWD();
	
	g_stop_flag	= ON;		/* For destroying my own Sceduler */

	if (sem_close(sem1) < 0 || sem_close(sem2) < 0)
	{
        perror("sem_close failed");
	}
	
	if (sem_unlink(SEM1_NAME) < 0 || sem_unlink(SEM2_NAME) < 0)
	{
        perror("sem_unlink failed");
	}
}
	
/******************************************************************************/
static void DestroyWD(void)
{
	char *pid_to_send_env = getenv("PID_TO_SEND");

	if (NULL != pid_to_send_env)
	{
		kill(atoi(pid_to_send_env), SIGUSR2);
	}
	else
	{
		perror("PID_TO_SEND is NULL at DestroyWD");
	}
}
	
	
	

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
