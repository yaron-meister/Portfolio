/*****************************************************************************
 * Developer:   Yaron Meister
 * Description: Creating a new PROCESS using FORK + EXEC
 *****************************************************************************/
 
 
#include <stdio.h>			/*     	   fprintf  	*/
#include <stdlib.h>			/*			abort		*/
#include <sys/types.h>		/*			pid_t		*/
#include <unistd.h>			/*  fork, execvp, sleep	*/



/************************* Forward Declarations *******************************/ 
int Invoke(char *program, char **arg_list);


/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main (void)
{
	/* The argument list to pass to the “echo” command */
	char* arg_list[] = 
	{
		"echo",     				      /* argv[0], the name of the program */
		"Hi everyone, I am FORK and EXEC", 
		NULL      				    /* The argument list must end with a NULL */
	};
	
	while (1)
	{
		/* Spawn a child process running the “echo” command. Ignore the
			returned child process ID */
		Invoke("echo", arg_list);
		sleep(1); 
	}
	
	return (0);
}


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/
/* Spawn a child process running a new program. PROGRAM is the name
of the program to run; the path will be searched for this program.
ARG_LIST is a NULL-terminated list of character strings to be
passed as the program’s argument list. Returns the process ID of
the spawned process.  */
int Invoke(char *program, char **arg_list)
{
	pid_t child_pid;
	
	/* Duplicate this process */
	child_pid = fork();
	
	if (0 != child_pid)
	{
		/* This is the parent process */
		return (child_pid);
	}
	else 
	{
		/* Now execute PROGRAM, searching for it in the path */
		execvp(program, arg_list);
		/* The execvp function returns only if an error occurs */
		fprintf(stderr, "an error occurred in execvp\n");
		abort();
	}
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/



