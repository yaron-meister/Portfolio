/*****************************************************************************
 * File name:   shared_mem_send.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-19 18:05:43
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

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

int fill_buffer(char * bufptr, int size);

/***************************** Global variables *******************************/
static char ch = 'A';


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int shmid, numtimes;
	struct shmseg* shmp;
	char *bufptr;
	int spaceavailable;
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

	/* Transfer blocks of data from buffer to shared memory */
	bufptr = shmp->buf;
	spaceavailable = BUF_SIZE;
	for (numtimes = 0; numtimes < 5; numtimes++) 
	{
	  shmp->cnt = fill_buffer(bufptr, spaceavailable);
	  shmp->complete = 0;
	  printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmp->cnt);
	  bufptr = shmp->buf;
	  spaceavailable = BUF_SIZE;
	  sleep(20);
	}

	printf("Writing Process: Wrote %d times\n", numtimes);
	shmp->complete = 1;

	if (-1 == shmdt(shmp)) 
	{
	  perror("shmdt");
	  return (EXIT_FAILURE);
	}

	if (-1 == shmctl(shmid, IPC_RMID, 0)) 
	{
	  perror("shmctl");
	  return (EXIT_FAILURE);
	}

	printf("Writing Process: Complete\n");

	return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
int fill_buffer(char * bufptr, int size) 
{
   int filled_count;
   
   /* printf("size is %d\n", size); */
   memset(bufptr, ch, size - 1);
   bufptr[size-1] = '\0';
   
	if (ch > 122)
	{
		ch = 65;
	}

    if ((ch >= 65) && (ch <= 122)) 
    {
		if ((ch >= 91) && (ch <= 96)) 
		{
			ch = 65;
		}
    }

    filled_count = strlen(bufptr);
   
    ++ch;

   return (filled_count);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 









