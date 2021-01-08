/*****************************************************************************
 * File name:   search.c
 * Developer:   Yaron Meister
 * Reviewer: 	Majd 
 * Date:        2019-01-10 16:34:38
 * Description: Searching algorithms implementation
 *****************************************************************************/
 
#include <assert.h>			/*		  assert		*/	 

#include "utils.h"			/*	  RUN_TO_ADDRESS	*/
#include "search.h"         /* Forward declarations */


/********************************* Macros *************************************/ 
typedef enum status
{
	SUCCESS,
	FAILURE
} status_t;
 
/************************** Forward Declarations ******************************/
static size_t FindNumOfJumps(size_t nmemb);
/* static size_t FindNumOfJumps1(size_t nmemb); */

/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
void *BinarySearchIter(const void *base, size_t nmemb, size_t element_size,
         int (*cmp_func)(const void *left, const void *right), const void *data)
{
	void *ret_address = NULL;
	void *runner      = (void*)base;
	int cmp_return	  = 0;				
	size_t new_size   = nmemb;
	status_t status	  = FAILURE;		/* flag */
	
	assert(base);
	assert(nmemb);
	assert(element_size);
	assert(cmp_func);
	assert(data);
	
	/* new_size cut in half every loop */
	while (SUCCESS != status && new_size > 0)
	{
		cmp_return = cmp_func(data, 
							RUN_TO_ADDRESS(runner, element_size, new_size / 2));
		
		/* if I need to search 'data' at the right side */
		if (cmp_return > 0)
		{
			/* 'runner' = address at the middle of the sub-array */
			runner = RUN_TO_ADDRESS(runner, element_size, new_size / 2);
			
			if (1 != new_size)
			{
				new_size = new_size - (new_size / 2);
			}
			else
			{
				new_size = 0;
			}
		}
		else if (cmp_return < 0)
		{
			new_size /= 2;
		}
		else 
		{
			runner = RUN_TO_ADDRESS(runner, element_size, new_size / 2);
			status = SUCCESS;
		}
	}
	
	if (SUCCESS == status)
	{
		ret_address = runner;
	}
	
	return (ret_address);
}
			
/******************************************************************************/
void *BinarySearchRec(const void *base, size_t nmemb, size_t element_size,
         int (*cmp_func)(const void *left, const void *right), const void *data)
{
	void *ret_address = NULL;
	void *middle      = NULL;

	assert(base);
	assert(nmemb);
	assert(element_size);
	assert(cmp_func);
	assert(data);
	
	if (1 == nmemb)
	{
		if (0 == cmp_func(base, data))
		{
			ret_address = (void*)base;
		}
		
		return (ret_address);
	}
	
	middle = RUN_TO_ADDRESS(base, element_size, nmemb / 2);

	/* If I need to search at the right side of the sub-array */
	if (cmp_func(data, middle) > 0)
	{
		ret_address = BinarySearchRec(middle, nmemb - (nmemb / 2),
												  element_size, cmp_func, data);
    }
	/* If I need to search at the left side of the sub-array */
	else if (cmp_func(data, middle) < 0)
	{
		ret_address = BinarySearchRec(base, nmemb / 2, element_size,
													    	    cmp_func, data);
	}
	/* If I found it */
	else
	{
		ret_address = middle;
	}
	
	return (ret_address);
}

/******************************************************************************/
void *JumpSearch(const void *base, size_t nmemb, size_t element_size,
         int (*cmp_func)(const void *left, const void *right), const void *data)
{
	void *ret_address = NULL;
	void *runner	  = (void*)base;
	size_t jump 	  = 1;
	void *end         = NULL;

	assert(base);
	assert(nmemb);
	assert(element_size);
	assert(cmp_func);
	assert(data);

	
	jump = FindNumOfJumps(nmemb);
	end  = RUN_TO_ADDRESS(base, element_size, nmemb - 1);
		
	/* Jump while runner is above the array && runner < data */
	while (runner <= end && cmp_func(data, runner) > 0)
	{
		runner = RUN_TO_ADDRESS(runner, element_size, jump);
	}
	
	/* If one jump back won't take me outside the array */
	if ((((char*)runner - (char*)base) / element_size) > jump)
	{
		runner = RUN_TO_ADDRESS(runner, element_size, jump * (-1));	
	}
	else
	{
		runner = (void*)base;
	}
	
	/* Jump one step each loop */
	while (runner <= end && cmp_func(data, runner) > 0)
	{
		runner = RUN_TO_ADDRESS(runner, element_size, 1);
	}
	
	/* If I found it */
	if (runner <= end && 0 == cmp_func(data, runner))
	{
		ret_address = runner;
	}
	
	return (ret_address);
}


/***************												***************/ 
static size_t FindNumOfJumps(size_t nmemb)
{
    size_t jump = 1;

    while ((jump * jump) <= nmemb)
    {
        ++jump;
    }

    return (--jump);
}

/***************												***************/ 
/*
static size_t FindNumOfJumps1(size_t nmemb)
{
    size_t op  = nmemb;
    size_t res = 0;
    size_t one = 1ul << 62; 

    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op  = op - (res + one);
            res = res +  2 * one;
        }

        res >>= 1;
        one >>= 2;
    }

    return (res);
}

*/

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
