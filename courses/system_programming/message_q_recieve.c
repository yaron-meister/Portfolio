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

/********************************* Macros *************************************/ 
#define PERMS 0644 
 
/************************** Forward Declarations ******************************/
struct my_msgbuf 
{
   long mtype;
   char mtext[200];
}; 
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	struct my_msgbuf buf;
	int msqid;
	int toend;
	key_t key;

	if ((key = ftok("msgq.txt", 'B')) == -1) {
	  perror("ftok");
	  exit(1);
	}

	if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
	  perror("msgget");
	  exit(1);
	}
	printf("message queue: ready to receive messages.\n");

	for(;;) { /* normally receiving never ends but just to make conclusion 
	         /* this program ends with string of end */
	  if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
	     perror("msgrcv");
	     exit(1);
	  }
	  printf("recvd: \"%s\"\n", buf.mtext);
	}
	printf("message queue: done receiving messages.\n");
	system("rm msgq.txt");
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 





   