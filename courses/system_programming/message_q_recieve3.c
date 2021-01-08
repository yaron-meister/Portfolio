/*****************************************************************************
 * File name:   message_q_recieve.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-19 15:05:26
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>


/********************************* Macros *************************************/ 
#define PERMS 0644 
 
/************************** Forward Declarations ******************************/
struct my_msgbuf 
{
   long mtype;
   char mtext[200];
}; 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	struct my_msgbuf buf;
	int msqid;
	int toend;
	key_t key = ftok("msgq.txt", 'B');

	if (-1 == key) 
	{
	  perror("ftok");
	  return (EXIT_FAILURE);
	}

	msqid = msgget(key, PERMS);

	if (-1 == msqid) 
	{ /* connect to the queue */
	  perror("msgget");
	  return (EXIT_FAILURE);
	}

	if (-1 == msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) 
	{
	     perror("msgrcv");
	     exit(1);
	}

	printf("recvd3: %s\n", buf.mtext);
 
	system("rm msgq.txt");
	
    return (EXIT_SUCCESS);
} 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 





   