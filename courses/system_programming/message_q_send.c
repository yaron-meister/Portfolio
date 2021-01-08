/*****************************************************************************
 * File name:   message_q_send.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-19 15:03:24
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>
#include <errno.h>
#include <string.h>
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
	int len;
	key_t key;
	system("touch msgq.txt");

	key = ftok("msgq.txt", 'B');

	if (-1 == key) 
	{
	  perror("ftok");
	  return(EXIT_FAILURE);
	}

	msqid = msgget(key, PERMS | IPC_CREAT);

	if (-1 == msqid) 
	{
	  perror("msgget");
	  return(EXIT_FAILURE);
	}

	buf.mtype = 1; /* we don't really care in this case */

	
	strcpy(buf.mtext, "Hello world");
	len = strlen(buf.mtext);
	/* remove newline at end, if it exists */
	if ('\n' == buf.mtext[len - 1])
	{
		buf.mtext[len - 1] = '\0';
	}
	if (-1 == msgsnd(msqid, &buf, len + 1, 0)) /* +1 for '\0' */
	{
		perror("msgsnd");
	}

	strcpy(buf.mtext, "my name");
	len = strlen(buf.mtext);
	/* remove newline at end, if it exists */
	if ('\n' == buf.mtext[len - 1])
	{
		buf.mtext[len-1] = '\0';
	}
	if (-1 == msgsnd(msqid, &buf, len+1, 0)) /* +1 for '\0' */
	{
		perror("msgsnd");
	}
	
	strcpy(buf.mtext, "is Yaron");
	len = strlen(buf.mtext);
	if (-1 == msgsnd(msqid, &buf, len+1, 0)) /* +1 for '\0' */
	{
		perror("msgsnd");
	}

	printf("message queue: done sending messages\n");

	return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
