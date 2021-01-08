/*****************************************************************************
 * File name:   signals_EX3.c
 * Developer:   Yaron Meister
 * Reviewer:	Rachel
 * Date:        2019-02-05 08:30:59
 * Description: Ping-Pong exercise without fork (using sig_info)- Ping process
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <signal.h>		/*    signal	*/
#include <unistd.h>		/*	  sleep		*/
#include <sys/types.h> 	/*	   kill		*/
#include <assert.h>		/*	  assert	*/

/************************** Forward Declarations ******************************/
void PingPong(int sig_num, siginfo_t *sig_info, void *ucontext);
 
/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	struct sigaction sa = {0};
	int status = EXIT_FAILURE;
	
	sa.sa_sigaction = PingPong;
	sa.sa_flags = SA_SIGINFO;
	
	if (0 == sigaction(SIGUSR2, &sa, NULL))
	{
		status = EXIT_SUCCESS;
		
		while (1)
		{}
	}
	
    return (status);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void PingPong(int sig_num, siginfo_t *sig_info, void *ucontext)
{
	assert(sig_info);
	
	if (SIGUSR1 == sig_num)
	{
		sleep(1);
		printf("Pong\n");
		
		if (0 != kill(sig_info->si_pid, SIGUSR2))
		{
			perror("SIGUSR1's kill failed");
			exit (EXIT_FAILURE);
		}
		
		sleep(1);
	}
	else if (SIGUSR2 == sig_num)
	{
		sleep(1);
		printf("Ping\n");
		
		if (0 != kill(sig_info->si_pid, SIGUSR1))
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


