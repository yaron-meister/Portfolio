/*****************************************************************************
 * File name:   hash.c
 * Developer:   Yaron Meister
 * Reviewer: 	Daria
 * Date:        2019-01-03 08:13:04
 * Description: Hash table implementation
 *****************************************************************************/
 
#include <stdio.h>	   /*        fprintf       */
#include <stdlib.h>    /* 		 malloc 	   */
#include <assert.h>	   /*		 assert		   */

#include "utils.h"	   /* 		  DBG          */
#include "dlist.h"	   /*		dlist.c		   */
#include "hash.h"      /* Forward declarations */


/************************** Forward Declarations ******************************/
struct hash
{
    size_t buckets_num;
    int (*cmp_func)(const void *left, const void *right);
    size_t (*hash_func)(const void *data, void *param);
    void *param;
    dlist_t **bucket;
};

static void DestroyHash(hash_t *hash);
static void DestroyBuckets(dlist_t **buckets_list,
						  					  size_t num_of_buckets_to_destroy);
/* A function that gets the iters: begin, end and founded one */
static void FindIters(const hash_t *hash, void *data, dlist_iter_t *start,
										 dlist_iter_t *iter, dlist_iter_t *end);
											   						  					  
/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
hash_t *HashCreate(size_t buckets_num, void *param,
                           size_t (*hash_func)(const void *data, void *param),
                           int(*cmp_func)(const void *left, const void *right))
{
	hash_t *hash    = NULL;
	size_t i		= 0;
			
	assert(hash_func);
	assert(cmp_func);
	
	hash = (hash_t*)malloc(sizeof(hash_t) + buckets_num * sizeof(dlist_t*));
	if (NULL == hash)
	{
		DBG(fprintf(stderr, "hash creation failed!!!\n"));
		return (NULL);
	}

	hash->buckets_num = buckets_num;
	hash->cmp_func    = cmp_func;
	hash->hash_func   = hash_func;
	hash->param       = param;	
	hash->bucket	  = (dlist_t **)((char*)(hash) + offsetof(hash_t, bucket) +
										                      sizeof(dlist_t*));
	/* Initializing all of the buckets lists */
	while (i < buckets_num)
	{
		hash->bucket[i] = DListCreate();
		/* If bucket creation failed */ 
		if (NULL == hash->bucket[i])
		{
			DBG(fprintf(stderr, "buckets creation failed!!!\n"));
			/* buckets_num - i = num of buckets to destroy */
			DestroyBuckets(hash->bucket, buckets_num - i);
			DestroyHash(hash);
			hash = NULL;
			break;
		}
		
		++i;
	}
	
	return (hash);
}
			
/******************************************************************************/
static void DestroyHash(hash_t *hash)
{
	if (NULL != hash)
	{
		hash->cmp_func  = NULL;
		hash->hash_func = NULL;
		hash->param     = NULL;
		hash->bucket    = NULL;
		
		free(hash);
	}
}

/******************************************************************************/
static void DestroyBuckets(dlist_t **buckets_list, size_t num_of_buckets)
{
	size_t i = 0;
	
	assert(buckets_list);
	
	while (i < num_of_buckets)
	{
		DListDestroy(buckets_list[i]);		 
		++i;
    }
}

/******************************************************************************/
void HashDestroy(hash_t *hash)
{
	assert(hash);
	
	DestroyBuckets(hash->bucket, hash->buckets_num);
	DestroyHash(hash);
	
	hash = NULL;
}

/******************************************************************************/
size_t HashSize(const hash_t *hash)
{
	size_t count  = 0;
	size_t i	  = 0; 

	assert(hash);
	
	while (i < hash->buckets_num)
	{
		count += DListCount(hash->bucket[i]);
		++i;
	}

	return (count);
}
	
/******************************************************************************/	
int HashIsEmpty(const hash_t *hash)
{
	size_t i = 0;
	
	assert(hash);
	
	while (i < hash->buckets_num)
	{
		if (!DListIsEmpty(hash->bucket[i]))
		{
			return (0);
		}
		
		++i;
	}
	
	return (1);
}

/******************************************************************************/	
int HashInsert(hash_t *hash, void *data)
{
	size_t key = 0;
	
	assert(hash);
	assert(data);
	
	key = hash->hash_func(data, hash->param);
	
	if (0 == DListPushBack(hash->bucket[key], data))
	{ 
		return (0);
	}
	
	return (-1);
}

/******************************************************************************/
void HashRemove(hash_t *hash, void *data)
{
	dlist_iter_t iter  = NULL;
	dlist_iter_t start = NULL;
	dlist_iter_t end   = NULL;
	
	assert(hash);
	assert(data);
	
	FindIters(hash, data, &start, &iter, &end);
	/* If it found the data */
	if (!DListIsSameIter(iter, end))
	{
		DListErase(iter, NULL);
	}
}

/******************************************************************************/
int HashForEach(hash_t *hash, int(*action_func)(void *data, void *act_param)
	                                                   	   ,void *act_param)
{
	int status         = 0;
	size_t i		   = 0;
	dlist_iter_t iter  = NULL;
	dlist_t *dlist	   = NULL;
	
	assert(hash);
	assert(action_func);

	while (i < hash->buckets_num)
	{
		dlist = hash->bucket[i];
		iter = DListForEach(DListBegin(dlist), DListEnd(dlist),
													    action_func, act_param);
		/* DListForEach failure case */
		if (!DListIsSameIter(iter, DListEnd(dlist)))
		{
			status = (-1);
			break;
		}
		
		++i;
	}
	
	return (status);
}

/******************************************************************************/
void *HashFind(const hash_t *hash, void *data)
{
	dlist_iter_t iter  = NULL;
	dlist_iter_t start = NULL;
	dlist_iter_t end   = NULL;
	
	assert(hash);
	
	if (NULL != data)
	{
		FindIters(hash, data, &start, &iter, &end);
		    
		if (!DListIsSameIter(iter, end))
		{
			/* If there are more nodes than the one we found in this dlist */
			if (!DListIsSameIter(iter, start))
			{
				/* Passing the founded node to the beginning */
				DListSpliceBefore(start, iter, DListNext(iter));
			}
			
			return (DListGetData(iter));      
		}
	}
	
	return (NULL);
}

/******************************************************************************/
static void FindIters(const hash_t *hash, void *data, dlist_iter_t *start,
										  dlist_iter_t *iter, dlist_iter_t *end)
{
	 size_t key = 0;
	 
	 assert(hash);
	
	if (NULL != data)
	{
		key   = hash->hash_func(data, hash->param);
		*start = DListBegin(hash->bucket[key]);	
		*end   = DListEnd(hash->bucket[key]);	
		*iter  = DListFind(*start, *end, hash->cmp_func, data);
	}
}


/*******************************************************************************	
****************************** END OF FILE *************************************
*******************************************************************************/	
  
