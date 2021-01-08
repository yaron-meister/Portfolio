/*****************************************************************************
 * Project:     WS3                                                           *
 * Date:        18.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Yael                                                          *
 *                                                                            *
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <ctype.h> /* tolower */
#include <string.h> /* strlen */

#include "ws3.h"


  /**************************************************************/
void EnvPrint(char *envi[])
{
    int i = 0;
    printf("The environment variables are:\n\n");
    while ('\0' != envi[i])
    {
        printf("%s\n", envi[i]);
        ++i;
    }
}

  /**************************************************************/
void EnvCopy(char *envi[])
{  
    size_t i = 0;
    int j = 0;
    int k = 0;
    size_t length = 0;
    size_t str_length = 0;
    char *runner_dest = NULL;
    char **dest = NULL;

    assert(envi);
    
    /* Checking the length of the ENV array */

    while ('\0' != envi[i])
    {
        ++length;
        ++i;
    }
       
    /* Allocating memory for the copy and putting NULL at the end of it */    
    dest = (char**) malloc((length + 1) * sizeof(char*));
    *(dest + length) = '\0';

    /* Allocating memory for each string and copying the original one */
    for (i = 0; i < length; i++)
    {
        str_length = strlen(envi[i]);
        dest[i] = (char*) malloc((str_length + 1) * sizeof(char));
        strcpy(dest[i], (envi[i]));
    }

    /* Turning each of the charachters to lower-case */
    while ('\0' != dest[j])
    {
        runner_dest = dest[j];
        while('\0' != *runner_dest)
        {
            *runner_dest = tolower(*runner_dest);
            ++runner_dest;
        }
        ++j;
    }
    printf("\n\n\nThe environment variables in lowercase are:\n\n");
    while ('\0' != dest[k])
    {
        printf("%s\n", dest[k]);
        ++k;
    }
    
    /* Freeing the allocation of each string */
    for (i = 0; i < length; i++)
    {
        free(dest[i]);
    }
    free(dest);
}

  /**************************************************************/
int NapLast(int size_of_circle)
{
	int *arr = NULL;            /* A circle represented in array */
	int sword = 0;              /* next to have a sword */
	int kill = 0;               /* next to be killed */
	int count = 0;              /* counts dead soldiers */

	arr = (int*)calloc(size_of_circle, sizeof(int));

    /* A loop that checks when only one soldier left */

	while (count < (size_of_circle - 1))
	{
        /* Checking if it's the end of the circle */

		if (sword == (size_of_circle - 1)) 
		{
			kill = 0;
		}
		else
		{
			kill = sword + 1;
		}

        /* next one to be killed */
        /* A loop to skip over the deads */

		while (0 != arr[kill])
		{
			if (kill == (size_of_circle - 1))
			{
				kill = 0;
			}
			else
			{
				++kill;
			}
		}
		arr[kill] = 1;                      /* 1 is dead, 0 is alive */
		++count;                     
		if (kill == (size_of_circle - 1))   /* next one to get sword */
		{
			sword = 0;
		}
		else
		{
			sword = kill + 1;
		}
		
		/* A loop to skip over the deads */
		while (0 != (arr[sword]))
		{
			if (sword == (size_of_circle - 1))
			{
				sword = 0;
			}
			else
			{
				++sword;
			}
		}
	}
	free(arr);                              

	return (sword);
}
        
    
  /**************************************************************/
void SizeOfType(void)
{
    printf("The size of a variable from the type 'short int' is: %ld\n",
             sizeof(short));
    printf("The size of a variable from the type 'unsigned short int' is: %ld\n",
             sizeof(unsigned short));
    printf("The size of a variable from the type 'unsigned int' is: %ld\n",
             sizeof(unsigned int));
    printf("The size of a variable from the type 'int' is: %ld\n",
             sizeof(int));
    printf("The size of a variable from the type 'long int' is: %ld\n",
             sizeof(long));
    printf("The size of a variable from the type 'unsigned long int' is: %ld\n",
             sizeof(unsigned long));
    printf("The size of a variable from the type 'signed char' is: %ld\n",
             sizeof(signed char));
    printf("The size of a variable from the type 'unsigned char' is: %ld\n",
             sizeof(unsigned char));
    printf("The size of a variable from the type 'float' is: %ld\n",
             sizeof(float));
    printf("The size of a variable from the type 'double' is: %ld\n",
             sizeof(double));
    printf("The size of a variable from the type 'long double' is: %ld\n",
             sizeof(long double));
}











