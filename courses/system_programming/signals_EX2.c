/*****************************************************************************
 * File name:   signals.c
 * Developer:   Yaron Meister
 * Reviewer:	Rachel
 * Date:        2019-02-04 16:52:12
 * Description: Ping-Pong exercise using fork() - Ping process
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <signal.h>		/*    signal	*/
#include <unistd.h>		/*	  sleep		*/
#include <sys/types.h> 	/*	   kill		*/


/************************** Forward Declarations ******************************/
void PingPong(int sig_num);
 
/***************************** Global variables *******************************/
int pid = 0;

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	struct sigaction sa = {0};
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = PingPong;
	int status = EXIT_FAILURE;
	
	if(0 == sigaction(SIGUSR1, &sa, NULL) && 0 == sigaction(SIGUSR2, &sa, NULL))
	{
		pid = fork();
		if (pid < 0) 
		{ 
		    perror("fork"); 
		    exit (EXIT_FAILURE); 
		}
	
		while (1)
		{
			if (0 != pid)
			{
				if (0 != kill(pid, SIGUSR1))
				{
					perror("kill failed");
					exit (EXIT_FAILURE);
				}
			}
		}
		
		status = EXIT_SUCCESS;
	}
	else
	{
		perror("sigaction failed");
	}
	
    return (status);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void PingPong(int sig_num)
{
	if (SIGUSR1 == sig_num)
	{
		sleep(1);
		printf("Ping\n");
		
		if (0 != kill(getppid(), SIGUSR2))
		{
			perror("SIGUSR1's kill failed");
			exit (EXIT_FAILURE);
		}
		
		sleep(1);
	}
	else if (SIGUSR2 == sig_num)
	{
		sleep(1);
		printf("Pong\n");
		
		if (0 != kill(pid, SIGUSR1))
		{
			perror("SIGUSR2's kill failed");
			exit (EXIT_FAILURE);
		}
		
		sleep(1);
	}
	else
	{
		perror("Wrong SIGUSR");
		abort();
	}
}
	
	
	

	
	


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
