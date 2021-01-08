/*****************************************************************************
 * File name:   signal_EX4_2.c
 * Developer:   Yaron Meister
 * Reviewer:	Rachel
 * Date:        2019-02-05 11:10:28
 * Description: Ping-Pong exercise using fork() + exec() - Pong process
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <signal.h>		/*    signal	*/
#include <unistd.h>		/*	  sleep		*/
#include <sys/types.h> 	/*	   kill		*/

 
/************************** Forward Declarations ******************************/
void Pong(int sig_num); 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	struct sigaction sa = {0};
	int status = EXIT_FAILURE;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = Pong;
	
	if (0 == sigaction(SIGUSR2, &sa, NULL))
	{	
		if (0 != kill(getppid(), SIGUSR1))
		{
			perror("SIGUSR2's kill failed");
			exit (EXIT_FAILURE);
		}
		
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
void Pong(int sig_num)
{
	sleep(1);
	printf("Pong\n");
	
	if (0 != kill(getppid(), SIGUSR1))
	{
		perror("SIGUSR2's kill failed");
		exit (EXIT_FAILURE);
	}
	
	sleep(1);
}




/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
