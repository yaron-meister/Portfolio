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
int i;
    char readbuf[5];
    char ping[] = "Ping";

    fd1 = open(FIFO_FILE1, O_RDWR);
    fd2 = open(FIFO_FILE2, O_RDWR);

    for (i = 0; i < 3; ++i)/*while (1)*/ 
    {
        write(fd2, ping, 4);
        read(fd1, readbuf, 4);
        sleep(1);
        printf("%s\n\n", readbuf);
    }
    
    close(fd1);
    close(fd2);   

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 




   
 