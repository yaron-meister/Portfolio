/*****************************************************************************
 * File name:   bst.c
 * Developer:   Yaron Meister
 * Reviewer: 	Shiran
 * Date:        2018-12-18 14:56:01
 * Description: Binaric Search Tree data structure's implementation
 *****************************************************************************/
 
#include <stdio.h>	   /*        fprintf       */
#include <stdlib.h>    /* 		 malloc 	   */
#include <assert.h>	   /* 		 assert 	   */

#include "utils.h"	   /* 	DBG, UNUSED_VAR	   */
#include "bst.h"       /* Forward declarations */


/********************************** Macros ************************************/
#ifdef __i386__
#define DEADBEEF 0xDEADBEEF

#elif __x86_64__
#define DEADBEEF 0xDEADBEEFDEADBEEF

#else
#error I am sorry

#endif /* Platform */

/************************** Forward Declarations ******************************/

typedef struct bst_node
{
	struct bst_node *left;
	struct bst_node *right;
	struct bst_node *parent;
	void *data;
}bst_node_t;

struct bst
{
	bst_node_t ground;
	int(*is_before)(void *element1, void *element2, void *param);
	void *param;
}; 

/* A function that checks if a node Is A Leaf */ 
static int IsALeaf(iter_t iter);
/* An action_func that counts */
static int CounterFunc(void *data, void *counter);
/* A function that destroys one node for each call */
static void DestroyNode(iter_t iter);

 
/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
bst_t *BSTCreate(int(*is_before)(void *element1, void *element2, void *param),
																   void *param)
{
	bst_t *bst = NULL;
	
	if (NULL != is_before)
	{	
		bst = (bst_t *)malloc(sizeof(bst_t));
		if (NULL == bst)
		{
			DBG(fprintf(stderr,"bst creation failed - malloc failure!\n"));
			return (NULL);
		}														   																    
	  
	 	bst->ground.left   = NULL;
	 	bst->ground.right  = NULL;
	 	bst->ground.parent = NULL;
	 	bst->ground.data   = (void*)DEADBEEF;
	 	
	 	bst->is_before     = is_before;
	 	bst->param         = param;
	}
	
 	return (bst);
} 

/******************************************************************************/
void BSTDestroy(bst_t *bst)
{
	iter_t iter = NULL;
	iter_t parent = NULL;
	
	assert(bst);	

	iter = BSTBegin(bst);
	
	while (!BSTIsEmpty(bst))
	{
		/* If I am the leftest and I have a right son */
		while (!IsALeaf(iter))
		{
			iter = BSTNext(iter);
		}
		
		parent = iter->parent;
		
		/* If I am a left son */
		if (BSTIsSameIter(iter, parent->left))
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
				
		DestroyNode(iter);
		iter = parent;
	}
	
	bst->is_before = NULL;
	bst->param = NULL;
	
	free(bst);
	bst = NULL;				
}     

/******************************************************************************/
size_t BSTCount(const bst_t *bst)
{
	size_t counter = 0;
	int(*action_func)(void *data, void *param) = CounterFunc;

	assert(bst);

	BSTForEach(BSTBegin(bst), BSTEnd(bst), action_func, &counter, NULL);

	return (counter);
}
		  
/******************************************************************************/  
int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	
	return (NULL == bst->ground.left);
}
  
/******************************************************************************/  
iter_t BSTBegin(const bst_t *bst)
{
	iter_t begin = NULL;
	
	assert(bst);  

	begin = BSTEnd(bst);
	
	while (NULL != begin->left)
	{
		begin = begin->left;
	}
	
	return (begin);
}  
  
/******************************************************************************/  
iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);
	
	return ((iter_t)&bst->ground);
}

/******************************************************************************/
iter_t BSTPrev(iter_t iter)
{
	assert(iter);
	
	/* If I have a left son, I need to go one left and right until the bottom */
	if (NULL != iter->left)
	{
		iter = iter->left;
		
		while (NULL != iter->right)
		{
			iter = iter->right;
		}
		
		return (iter);
	}	
	
 /* 
  *	  If I am a right son (and I don't have a left son), my parent is my<prev> 
  *	 	and I shouldn't get into the loop
  */
  
	while (BSTIsSameIter(iter, iter->parent->left))
	{
		iter = iter->parent;
	}

	return (iter->parent);
}

/******************************************************************************/
iter_t BSTNext(iter_t iter)
{
	assert(iter);
	
  /* If I have a right son, I need to go one right and left until the bottom */
	if (NULL != iter->right)
	{
		iter = iter->right;
		
		while (NULL != iter->left)
		{
			iter = iter->left;
		}
		
		return (iter);
	}	
	
 /* 
  *	 If I am a left son (and I don't have a right son), my parent is my <next>
  * 	and I shouldn't get into the loop
  */
 
 
	while (BSTIsSameIter(iter, iter->parent->right))
	{
		iter = iter->parent;
	}

	return (iter->parent);
}	
  
/******************************************************************************/  
void *BSTGetData(iter_t iter)
{
	assert(iter);
	
	return (iter->data);
} 

/******************************************************************************/
iter_t BSTInsert(bst_t *bst, void *data)
{
	iter_t iter    = NULL;
	bst_node_t *node = NULL;
	
	assert(bst);
	assert(data);
	
	node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == node)
	{
		DBG(fprintf(stderr, "Insertion failure - creating node failed\n"));
		return (NULL);
	}
	
	/* New node's initialization */
	node->left   = NULL;
	node->right  = NULL;
	node->parent = NULL;
	node->data   = data;
	
	if (BSTIsEmpty(bst))
	{
		bst->ground.left = node;
		node->parent     = BSTEnd(bst);
		return (bst->ground.left);
	}
	
	/* If !BSTIsEmpty */
	iter = BSTEnd(bst)->left;
	
	while (!IsALeaf(iter))
	{
		/* Going left */
		if (bst->is_before(data, iter->data, bst->param))
		{
			if (NULL == iter->left)
			{
				iter->left   = node;
				node->parent = iter;
				return (iter->left);
			}
			else
			{
				iter = iter->left;
			} 
		}
		/* Going right */
		else
		{
			if (NULL == iter->right)
			{
				iter->right  = node;
				node->parent = iter;
				return (iter->right);
			}
			else
			{
				iter = iter->right;
			} 
		}
	}
	
	/* Which son am I going to be in the leaf */
	if (bst->is_before(data, iter->data, bst->param))
	{
		iter->left   = node;
		node->parent = iter;
		return (iter->left);
	}
	else
	{
		iter->right  = node;
		node->parent = iter;
		return (iter->right);
	}
}

/******************************************************************************/
void BSTRemove(iter_t iter)
{
	iter_t next = NULL;
	iter_t temp = NULL;
	
	if (!IsALeaf(iter))
	{
		/* One son case */
		if (NULL == iter->left || NULL == iter->right)
		{
			/* If I am a left son */
			if (BSTIsSameIter(iter, iter->parent->left))
			{
				/* If I have a left son */
				if (NULL != iter->left)
				{
					iter->parent->left = iter->left;
					iter->left->parent = iter->parent;
				}
				else
				{
					iter->parent->left = iter->right;
					iter->right->parent = iter->parent;
				}
			}
			else
			{
				/* If I have a left son */
				if (NULL != iter->left)
				{
					iter->parent->right = iter->left;
					iter->left->parent = iter->parent;
				}
				else
				{
					iter->parent->right = iter->right;
					iter->right->parent = iter->parent;
				}		
			}
		}
		/* Two sons case */
		else
		{	
			next = BSTNext(iter);
			temp = next->right;
			
			/* If I am a left son */
			if (BSTIsSameIter(iter, iter->parent->left))
			{
				iter->parent->left = next;
			}
			else
			{
				iter->parent->right = next;
			}
			
			iter->left->parent  = next;
			
			
			iter->right->parent = next;
			next->parent->left = temp;
			
			if (NULL != next->right)
			{
				next->right->parent = next->parent;
			}
			
			if (next != iter->right)
			{
				next->right = iter->right;
			}
			
			next->parent = iter->parent;
			next->left = iter->left;
		}
	}
	/* A leaf case */
	else
	{
		if (BSTIsSameIter(iter, iter->parent->left))
		{
			iter->parent->left = NULL;
		}
		else 
		{
			iter->parent->right = NULL;
		}
	}
	
	DestroyNode(iter);
	iter = NULL;
}
			
/******************************************************************************/
int BSTForEach(iter_t from, iter_t to,
									 int(*action_func)(void *data, void *param),
					       		       		  void *param, iter_t *failed_iter)
{
	int status = 0;
	iter_t iter = NULL;

	assert(action_func);
	assert(from);
	assert(to);
	
	iter = from;

	while (iter != to && status == 0)
	{
		status = action_func(iter->data, param);
		iter = BSTNext(iter);
	}

	if (0 != status && NULL != failed_iter)
	{
		*failed_iter = (BSTPrev(iter));
	}

	return (status);
}

/******************************************************************************/ 
iter_t BSTFind(const bst_t *bst, void *data)
{
	iter_t iter = NULL;
	
	assert(bst);
	
	if (NULL == data)
	{
		return (BSTEnd(bst));
	}
	
	if (!BSTIsEmpty(bst))
	{
		iter = BSTEnd(bst)->left;
		
		while (NULL != iter)
		{
			if (bst->is_before(data, BSTGetData(iter), bst->param) == 
							 bst->is_before(BSTGetData(iter), data, bst->param))
			{
				return (iter);
			}
			
			else if (bst->is_before(data, BSTGetData(iter), bst->param))
			{
				iter = iter->left;
			}
			else
			{
				iter = iter->right;
			}
		}
	}	
				
	return (BSTEnd(bst));
}
			 
/******************************************************************************/ 
int BSTIsSameIter(iter_t iter1, iter_t iter2)
{
	return (iter1 == iter2);
} 
    
/******************************************************************************/  
static int IsALeaf(iter_t iter)
{
	return (iter->left == NULL && iter->right == NULL);
} 
  
/******************************************************************************/  
static int CounterFunc(void *data, void *counter)
{
	UNUSED_VAR(data);

	++(*(int*)counter);

	return (0);
}   

/******************************************************************************/ 
static void DestroyNode(iter_t iter)
{
	assert(iter);
	
	iter->left   = NULL;
	iter->right  = NULL;
	iter->parent = NULL;
	iter->data   = NULL;
		
	free(iter);
}   
  
/************************** END OF FILE ***************************************/

