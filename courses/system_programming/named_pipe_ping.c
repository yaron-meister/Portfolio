/*****************************************************************************
 * File name:   named_pipe_ping_pong.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-18 18:31:05
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/********************************* Macros *************************************/ 
#define FIFO_FILE1 "/tmp/fifo_twoway1"
#define FIFO_FILE2 "/tmp/fifo_twoway2"

/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
    int fd1;
    int fd2;
    char readbuf[5];
    char pong[] = "Pong";

    /* Create the FIFO if it does not exist */
	mkfifo(FIFO_FILE1, S_IFIFO|0640);
	mkfifo(FIFO_FILE2, S_IFIFO|0640);

	fd1 = open(FIFO_FILE1, O_RDWR);
	fd2 = open(FIFO_FILE2, O_RDWR);

	while(1) 
	{
		read(fd2, readbuf, 4);
		sleep(1);
		printf("%s\n\n", readbuf);
		write(fd1, pong, 4);
	}

	close(fd1);
	close(fd2);

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
