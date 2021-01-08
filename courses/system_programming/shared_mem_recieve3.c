/*****************************************************************************
 * File name:   shared_mem_recieve1.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-19 18:05:50
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


/********************************* Macros *************************************/ 
#define BUF_SIZE 1024
#define SHM_KEY 0x1234
 
/************************** Forward Declarations ******************************/
struct shmseg 
{
   int cnt;
   int complete;
   char buf[BUF_SIZE];
}; 
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	int shmid;
	struct shmseg* shmp;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);

	if (-1 == shmid) 
	{
	  perror("Shared memory");
	  return (EXIT_FAILURE);
	}

	/*Attach to the segment to get a pointer to it.*/
	shmp = shmat(shmid, NULL, 0);
	if ((void *) -1 == shmp) 
	{
	  perror("Shared memory attach");
	  return (EXIT_FAILURE);
	}
sleep(1);

	/*Transfer blocks of data from shared memory to stdout*/
	/*while (shmp->complete != 1) 
	{*/
	printf("segment contains : \n\"%s\"\n", shmp->buf);
	if (-1 == shmp->cnt) 
	{
	perror("read");
		return (EXIT_FAILURE);
	}

	printf("Reading Process3: Shared Memory: Read %d bytes\n", shmp->cnt);
	sleep(3);
	/*}*/

	printf("Reading Process3: Reading Done, Detaching Shared Memory\n");
	if (-1 == shmdt(shmp)) 
	{
	  perror("shmdt");
	  return (EXIT_FAILURE);
	}

	printf("Reading Process3: Complete\n");

	return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 