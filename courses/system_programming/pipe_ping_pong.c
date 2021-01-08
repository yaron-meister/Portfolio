/*****************************************************************************
 * File name:   pipe_ping_pong.c
 * Developer:   Yaron Meister
 * Reviewer: 	Shiran
 * Date:        2019-03-18 16:36:41
 * Description: Ping-Pong using a regular PIPE
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <stdio.h>
#include <unistd.h>


/********************************* Macros *************************************/ 
 
 
/************************** Forward Declarations ******************************/
 
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	int pipefds1[2], pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	char pipe1writemessage[5] = "Ping";
	char pipe2writemessage[5] = "Pong";
	char readmessage[5];
	returnstatus1 = pipe(pipefds1);

	if (-1 == returnstatus1) 
	{
	  printf("Unable to create pipe 1 \n");
	  return (EXIT_FAILURE);
	}
	
	returnstatus2 = pipe(pipefds2);

	if (-1 == returnstatus2)
	{
	  printf("Unable to create pipe 2 \n");
	  return (EXIT_FAILURE);
	}

	pid = fork();

	if (pid != 0) /* Parent process  */
	{
		close(pipefds1[0]); /* Close the unwanted pipe1 read side */
		close(pipefds2[1]); /* Close the unwanted pipe2 write side */

		while (1)
		{
			if (-1 == write(pipefds1[1], pipe1writemessage,
													 sizeof(pipe1writemessage)))
			{
				perror("write");
				return (EXIT_FAILURE);
			}

			if (-1 == read(pipefds2[0], readmessage, sizeof(readmessage)))
			{
				perror("read");
				return (EXIT_FAILURE);
			}

			sleep(1);
			printf("%s\n\n", readmessage);
		}

		close(pipefds1[1]); 
		close(pipefds2[0]); 

	}
	else /* child process */
	{ 
		close(pipefds1[1]); /* Close the unwanted pipe1 write side */
		close(pipefds2[0]); /* Close the unwanted pipe2 read side */

		while (1)
		{
			if (-1 == read(pipefds1[0], readmessage, sizeof(readmessage)))
			{
				perror("read");
				return (EXIT_FAILURE);
			}

			sleep(1);
			printf("%s\n\n", readmessage);

			if (-1 == write(pipefds2[1], pipe2writemessage,
													 sizeof(pipe2writemessage)))
			{
				perror("write");
				return (EXIT_FAILURE);	
			}
		}

		close(pipefds1[0]); 
		close(pipefds2[1]); 
	}

 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
