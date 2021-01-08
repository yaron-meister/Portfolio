/*****************************************************************************
 * File name:   signal_EX4_1.c
 * Developer:   Yaron Meister
 * Reviewer:	Rachel
 * Date:        2019-02-05 11:10:11
 * Description: Ping-Pong exercise using fork() + exec() - Ping process
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <signal.h>		/*    signal	*/
#include <unistd.h>		/*	  sleep		*/
#include <sys/types.h> 	/*	   kill		*/


/************************** Forward Declarations ******************************/
void Ping(int sig_num); 
 
/***************************** Global variables *******************************/
pid_t child_pid = 0;

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	struct sigaction sa = {0};
	int status = EXIT_FAILURE;
	char *arg_list[] = {"./prog2", NULL};
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = Ping;
	
	if (0 == sigaction(SIGUSR1, &sa, NULL))
	{	
		/* Duplicate this process */
		child_pid = fork();
	
		if (0 != child_pid)
		{
			status = EXIT_SUCCESS;
			
			while (1)
			{}
		}
		else 
		{
			/* Now execute prog2, searching for it in the path */
			execvp(arg_list[0], arg_list);
			/* The execvp function returns only if an error occurs */
			fprintf(stderr, "an error occurred in execvp\n");
			abort();
		}
 	}
 	
    return (status);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void Ping(int sig_num)
{
	sleep(1);
	printf("Ping\n");
	
	if (0 != kill(child_pid, SIGUSR2))
	{
		perror("SIGUSR1's kill failed");
		exit (EXIT_FAILURE);
	}
	
	sleep(1);
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
