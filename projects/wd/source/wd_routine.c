/*****************************************************************************
 * File name:   wd_routine.c
 * Developer:   Yaron Meister
 * Date:        2019-02-10 11:00:56
 * Description: Routine for watch_dog.c
 *****************************************************************************/

#define _GNU_SOURCE			/*		 execvp			*/	

#include <stdio.h>     		/* 		 fprintf  	   	*/
#include <stdlib.h>    		/* EXIT_SUCCESS, getenv */
#include <assert.h>			/*		 assert			*/
#include <semaphore.h>		/*		semaphore		*/
#include <pthread.h>		/*  	pthread_t		*/
#include <signal.h>			/*    	  signal		*/
#include <unistd.h>			/*	  	  sleep			*/
#include <sys/types.h> 		/*	   	  kill			*/
#include <fcntl.h>          /*    O_* constants 	*/
#include <sys/stat.h>       /*    mode constants 	*/
#include <sys/wait.h>		/*		  wait			*/

#include "utils.h"			/*	  DBG, UNUSED_VAR	*/
#include "scheduler.h"		/*		scheduler.c		*/
#include "wd_routine.h"		/* Forward declarations */

/********************************* Macros *************************************/ 
#define SEM1_NAME "/semaphore1"
#define SEM2_NAME "/semaphore2"

enum setenv_overwrite
{
	NO_OVERWRITE,
	OVERWRITE
};
 
/************************** Forward Declarations ******************************/
/** Opens Named-Semaphore **/
static void SemLink(void);
/** Handlers for sigaction **/
static void USR1Handler(int sig_num);
static void USR2Handler(int sig_num);

static int CreateWD(void);
static void Communicate(void);
/** Stops Scheduler when g_stop_flag == ON **/			
static scheduler_return_t StopSched(void *data);

static scheduler_return_t NotifyAlive(void *data);
static scheduler_return_t CheckAlive(void);
static void Revive(void);

/** Closes Named-Semaphores **/
static void SemClose(void);
 
/***************************** Global variables *******************************/
scheduler_t *scheduler   = NULL;
int g_check_counter 	 =  0;
pid_t g_program_pid		 =  0;
pid_t g_wd_pid			 =  0;
thread_arg_t thread_args = {0};
int g_stop_flag	 		 = OFF;

/* Named-Semaphores **/
sem_t *semaphore1 		 = NULL;
sem_t *semaphore2 		 = NULL;


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
int WDRoutine(thread_arg_t input_st)
{
	int status 		 	 = EXIT_SUCCESS;
	struct sigaction sa1 = {0};
	struct sigaction sa2 = {0};
	
	thread_args = input_st;
		
	sigemptyset(&sa1.sa_mask);
	sigemptyset(&sa2.sa_mask);

	sa1.sa_handler = USR1Handler;
	sa2.sa_handler = USR2Handler;
	
	SemLink();

	if (0 == sigaction(SIGUSR1, &sa1, NULL) &&
	    0 == sigaction(SIGUSR2, &sa2, NULL))
	{
		/** If WD is Alive **/
		if (NULL == getenv("PID_TO_SEND"))
		{
			CreateWD();
			sem_wait(semaphore2);
		}
		
		scheduler = SchCreate();
		if (NULL == scheduler)
		{
			perror("SchedCreate failed");
			return (EXIT_FAILURE);
		}
		
		sem_post(semaphore2);
		
		Communicate();
	}
	else
	{
		perror("Setting sigaction of comm thread failed");
		status = EXIT_FAILURE;
	}

	SemClose();

	return (status);
}

/********************* 								      *********************/ 
/** Opens Named-Semaphore **/
static void SemLink(void)
{
    semaphore1 = sem_open(SEM1_NAME, O_RDWR);
    semaphore2 = sem_open(SEM2_NAME, O_RDWR);

	if (SEM_FAILED == semaphore1 || SEM_FAILED == semaphore2)
	{
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }
}

/******************************************************************************/
static void USR1Handler(int sig_num)
{
	UNUSED_VAR(sig_num);

	g_check_counter = 0;
}

/******************************************************************************/
static void USR2Handler(int sig_num)
{
	UNUSED_VAR(sig_num);

	g_stop_flag = ON;
}	

/********************* 								      *********************/ 		
static int CreateWD(void)	
{
	char thread_pid_str[20] = "";
	char wd_pid_str[20]		= "";
	pid_t parent_pid 		= getpid();
	int status	 			= EXIT_FAILURE;
    
    if (0 == setenv("PID_TO_SEND", "-1", NO_OVERWRITE))
    {
    	status = EXIT_SUCCESS;
		/* Duplicate this process */
		g_wd_pid = fork();
	
		/** If I am the program **/
		if (0 != g_wd_pid)
		{
			sprintf(thread_pid_str, "%d", g_wd_pid);			
			setenv("PID_TO_SEND", thread_pid_str, OVERWRITE);
		}
		/** If I am WD **/
		else 
		{
			sprintf(wd_pid_str, "%d", parent_pid);			
			setenv("PID_TO_SEND", wd_pid_str, OVERWRITE);

			execvp("./wd.out", thread_args.argv);
			/* The execvp function returns only if an error occurs */
			perror("an error occurred in execvp1 of thread\n");
			abort();
		}
	}

	return (status);
}

/********************* 								      *********************/ 			
static void Communicate(void)	
{    
	if (!UIDIsBad(SchAddTask(scheduler, NotifyAlive, NULL, 1)) &&
		!UIDIsBad(SchAddTask(scheduler,
		 (scheduler_return_t (*)(void*))CheckAlive, NULL, 1)) &&
		!UIDIsBad(SchAddTask(scheduler, StopSched, NULL, 1)))
	{
		sem_post(semaphore1);
	
		SchRun(scheduler);
	
		SchDestroy(scheduler);
		scheduler = NULL;
	}
	else
	{
		perror("Failed at adding tasks to scheduler");
	}
}	

/********************* 								      *********************/ 
/** Stops Scheduler when g_stop_flag == ON **/			
static scheduler_return_t StopSched(void *data)
{
	UNUSED_VAR(data);
	
	if (ON == g_stop_flag)
	{
		SchStop(scheduler);
	}
	
	return (SCHEDULER_REPEAT);
}


/********************* 								      *********************/ 			
scheduler_return_t NotifyAlive(void *data)
{
	UNUSED_VAR(data);
	
	kill(atoi(getenv("PID_TO_SEND")), SIGUSR1);
	
	return (SCHEDULER_REPEAT);
}

/********************* 								      *********************/ 			
scheduler_return_t CheckAlive(void)
{
	/** <g_check_counter> and <thread_args.interval> are in [s] **/
	if (g_check_counter > thread_args.interval)
	{
		Revive();
	}
	else
	{
		++g_check_counter;
	}
	
	return (SCHEDULER_REPEAT);
}

/********************* 								      *********************/ 			
static void Revive(void)
{
	char *prog_pid 			 = getenv("PROG_PID");
	char new_pid_to_send[20] = "";

	/* wait(NULL); */
	
	g_check_counter = 0;

	/** If I am WD **/
	if (atoi(getenv("PID_TO_SEND")) == atoi(prog_pid))
	{
		/** Re-setting <PID_TO_SEND> of PROGRAM **/
        sprintf(new_pid_to_send, "%d", getpid());			
		setenv("PID_TO_SEND", new_pid_to_send, OVERWRITE);
		g_program_pid = fork();
	
		if (0 == g_program_pid)
		{
			execvp("./user_prog.out", thread_args.argv);
			/* The execvp function returns only if an error occurs */
			DBG(fprintf(stderr, "an error occurred in execvp\n"));
			abort();
		}
		
		/** Re-setting <PID_TO_SEND> of WD **/
		sprintf(new_pid_to_send, "%d", g_program_pid);			
		setenv("PID_TO_SEND", new_pid_to_send, OVERWRITE);
		
	}
	/**	If I am PROGRAM **/
	else 
	{
		CreateWD();
	}
}

/******************************************************************************/
/** Closes Named-Semaphores **/
static void SemClose(void)
{
	if (sem_close(semaphore1) < 0 || sem_close(semaphore2) < 0)
	{
        perror("sem_close failed");
	}
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
