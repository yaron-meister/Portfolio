/*****************************************************************************
 * File name:   dict_test.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-01-04 15:06:38
 * Description: Testing hash map by the LINUX Dict
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <assert.h>	   /*	 assert    */
#include <string.h>	   /*    string	   */

#include "utils.h"	   /*	UNUSED_VAR */
#include "dlist.h"	   /*   dlist.c    */
#include "hash.h"	   /*    hash.c	   */


/****************************** Global variables ******************************/
static char word[100000][20] = {0};

/*************************** Forward Declarations *****************************/
static size_t HashFunc(const void *data, void *param);
static size_t Hash2(const void *data, void *param);
static size_t Hash3(const void *data, void *param);
static int CompareFunc(const void *left, const void *right);
static int PrintHash(void *data, void *act_param);

/*******************************************************************************
******************************* MAIN FUNCTION **********************************
*******************************************************************************/

int main(void)
{
	int i = 0;
	int j = 0;
	size_t param = 100;
	hash_t *hash = HashCreate(100, &param, &Hash2, &CompareFunc);
	int status = 0;
	
	char *str = "Aaron";
	FILE *dict = fopen("dict", "r"); 
	if (NULL == dict)
	{
		return (EXIT_FAILURE);
	}

	/* while (NULL != fgets(word, 20, dict)) */

	while (EOF != fscanf(dict, "%s", word[i]))
	{
		++i;
	}
	
	for (; j < i; ++j)
	{
		status = HashInsert(hash, word[j]);

		if (0 != status)
		{
			printf("There was a problam!!!\n");
			return (EXIT_FAILURE);
		}
	} 
	
	fclose(dict);
	
	printf("The size of the hash table is: %lu\n", HashSize(hash));
	HashForEach(hash, &PrintHash, NULL);
	HashDestroy(hash);
 
    return (EXIT_SUCCESS);
} 
 
/******************************************************************************/
static size_t HashFunc(const void *data, void *param)
{
    size_t hash = 5381;
    int c = 0;
	char *data_runner = NULL;

	assert(data);
	assert(param);

	data_runner = (char*)data;
	c = *data_runner;

    while (c)
	{
        hash = ((hash << 5) + hash) + c;
		++data_runner;
		c = *data_runner; 
	}
   
	return (hash % *(size_t*)param);
}

/******************************************************************************/
static int CompareFunc(const void *left, const void *right)
{
	assert(left);
	assert(right);
	
	return (strcmp((char*)left, (char*)right));
}  

/******************************************************************************/
static size_t Hash2(const void *data, void *param)
{
	size_t hash = 0;

	assert(data);
	assert(param);
 
	while (*(char*)data)  
	{
		hash = 5 * hash + *(char*)data;   
		data = (char*)data + 1;
	}

	return (hash % *(size_t*)param);
}

/******************************************************************************/
static size_t Hash3(const void *data, void *param)
{
	assert(data);
	assert(param);
	
	return (*(char*)data - 'A');
}

/******************************************************************************/
static int PrintHash(void *data, void *act_param)
{
	assert(data);
	
	UNUSED_VAR(act_param);

	printf("%s ", (char*)data);
	
	return (0);
}





/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
