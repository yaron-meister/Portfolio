/*****************************************************************************
 * File name:   avl.c
 * Developer:   Yaron Meister
 * Reviewer: 	
 * Date:        2018-12-27 15:56:16
 * Description: AVL Search Tree data structure's implementation
 *****************************************************************************/
 
#include <stdio.h>	   /*        fprintf       */
#include <stdlib.h>    /* 		 malloc 	   */
#include <assert.h>	   /* 		 assert 	   */
#include <unistd.h>	   /*		 ssize_t	   */

#include "utils.h"	   /* 		DBG, MAX       */
#include "avl.h"       /* Forward declarations */


/************************** Forward Declarations ******************************/
typedef struct avl_node
{	
	size_t height;
	struct avl_node *left;
	struct avl_node *right;
	void *data;
} avl_node_t;
 
struct avl
{
	avl_node_t *root;
	int (*cmp_func)(const void *left, const void *right);		
};

/********************** Functions for use in 'AVLDestroy' *********************/
static void	DestroyRec(avl_node_t *local_root);
static void DestroyNode(avl_node_t *node);
/********************* Recursive func for use in 'AVSize' *********************/
static size_t SizeRec(avl_node_t *local_root);
/********************** Functions for use in 'AVLInsert' **********************/
static avl_node_t *CreateNode(void *data);
static avl_node_t *InsertNodeRec(avl_t *avl, avl_node_t *local_root, void *data);
/************************* Functions for BALANCING ****************************/
static void UpdateHeight(avl_node_t *node);
static avl_node_t *RotateLeft(avl_node_t *local_root);
static avl_node_t *RotateRight(avl_node_t *local_root);
static ssize_t GetBalanceFactor(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *local_root);
/********************** Functions for use in 'AVLRemove' **********************/
static avl_node_t *RemoveRec(avl_t *avl, avl_node_t *node, void *data);
static avl_node_t *FindNextRec(avl_node_t *node);
/******************** Recursive func for use in 'AVLFind' *********************/
static void *FindRec(const avl_t *avl, avl_node_t *local_root, void *data);
/****************** Recursive func for use in 'AVLForEach' ********************/
static int ForEachRec(avl_node_t *local_root, 
			          int(*action_func)(void *data, void *param) ,void *param);

/************************ Function for Printing AVL ***************************/
static void AVLPrintNode(const avl_node_t *node, size_t depth);


/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
avl_t *AVLCreate(int(*cmp_func)(const void *left, const void *right))
{
	avl_t *avl = NULL;
	
	assert(cmp_func);
	
	avl = (avl_t*)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		DBG(fprintf(stderr, "Malloc failed\n"));
		return (NULL);
	}
	
	avl->root = NULL;
	avl->cmp_func = cmp_func;
	
	return (avl);
}

		
/******************************************************************************/
void AVLDestroy(avl_t *avl)
{
	assert(avl);
	
	DestroyRec(avl->root);
	
	avl->root 	  = NULL;
	avl->cmp_func = NULL;
	free(avl);
	avl = NULL;
}
		
/******************************************************************************/
size_t AVLHeight(avl_t *avl)
{
	size_t height = 0;
 
	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		height = avl->root->height;
	}

	return (height);
}

/******************************************************************************/
static void	DestroyRec(avl_node_t *local_root)
{
	/* Type of implementation: POST-ORDER */ 
	if (NULL == local_root)
	{
		return;
	}
	
	DestroyRec(local_root->left);
	DestroyRec(local_root->right);
	
	DestroyNode(local_root);
	local_root = NULL;
}

/******************************************************************************/
size_t AVLSize(const avl_t *avl)
{
	size_t count = 0;
	
	assert(avl);
	
	if (!AVLIsEmpty(avl))
	{
		count = SizeRec(avl->root);
	}
	
	return (count);
}

/******************************************************************************/
int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return (NULL == avl->root);
}

/******************************************************************************/
int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(avl);
	assert(data);
	
	if (!AVLIsEmpty(avl))
	{
		new_node = InsertNodeRec(avl, avl->root, data);
		if (NULL == new_node)
		{
			return (-1);
		}

		avl->root = new_node;	
	}
	else
	{
		new_node = CreateNode(data);
		if (NULL == new_node)
		{
			return (-1);
		}
		
		avl->root = new_node;
	}
	
	return (0);
}

/******************************************************************************/	
void AVLRemove(avl_t *avl, void *data)
{	
	assert(avl);
	assert(data);
	
	avl->root = RemoveRec(avl, avl->root, data);
}

/******************************************************************************/		
void *AVLFind(const avl_t *avl, void *data)
{
	assert(avl);
	
	if (AVLIsEmpty(avl) || NULL == data)
	{
		return (NULL);
	}
	
	return (FindRec(avl, avl->root, data));
}

/******************************************************************************/	
int AVLForEach(avl_t *avl, int(*action_func)(void *data, void *param)
	                                                   ,void *param)
	                                                  
{	
	assert(avl);                                                   	
	
	return (ForEachRec(avl->root, action_func, param));
}


/*******************************************************************************
************************* INTERNAL STATIC FUNCTIONS ****************************
*******************************************************************************/
static size_t SizeRec(avl_node_t *local_root)
{
	/* Type of implementation: PRE-ORDER */ 
	size_t count = 1;
	
	/* If <local_root> is a leaf */ 
	if (NULL == local_root->left && NULL == local_root->right)
	{
		return (1);
	}
	
	if (NULL != local_root->left)
	{
		count += SizeRec(local_root->left);
	}

	if (NULL != local_root->right)
	{
		count += SizeRec(local_root->right);
	}
	
	return (count);
}
	
/******************************************************************************/
static avl_node_t *CreateNode(void *data)
{
	avl_node_t *node = (avl_node_t*)malloc(sizeof(avl_node_t));
	
	if (NULL == node)
	{
		DBG(fprintf(stderr, "node creation failed!!!\n"));
		return (NULL);
	}
	
	/* The height of a new node that is also a leaf is '1' */
	node->height = 1;
	node->left 	 = NULL;
	node->right	 = NULL;
	node->data	 = data;
	
	return (node);
}
			
/******************************************************************************/
static avl_node_t *RotateLeft(avl_node_t *local_root)
{
	avl_node_t *right_son = local_root->right;
	avl_node_t *grandson  = right_son->left;
					
	right_son->left = local_root;
	local_root->right = grandson;	
	
	UpdateHeight(local_root);
	UpdateHeight(right_son);	

	return (right_son);
}	

/******************************************************************************/
static avl_node_t *RotateRight(avl_node_t *local_root)
{
	avl_node_t *left_son = local_root->left;
	avl_node_t *grandson = left_son->right;
	
	left_son->right  = local_root;
	local_root->left = grandson;	
	
	UpdateHeight(local_root);
	UpdateHeight(left_son);	
	
	return (left_son);
}

/******************************************************************************/
static void UpdateHeight(avl_node_t *node)
{
	size_t left_height  = 0;
	size_t right_height = 0;

	if (NULL != node->left)
	{
		left_height = node->left->height;
	}
	
	if (NULL != node->right)
	{
		right_height = node->right->height;
	}
	
	node->height = (MAX(left_height, right_height) + 1);
}
	
/******************************************************************************/
static ssize_t GetBalanceFactor(avl_node_t *node)
{
	/* If possitive - LEFT is taller */
	size_t left_height = 0;
	size_t right_height = 0;
	ssize_t diff = 0;
	
	if (NULL != node->left)
	{
		left_height = node->left->height;
	}
	
	if (NULL != node->right)
	{
		right_height = node->right->height;
	}
	
	diff = left_height - right_height;
	
	return (diff);
}

/******************************************************************************/
static avl_node_t *Balance(avl_node_t *local_root)
{
	ssize_t balance_factor = GetBalanceFactor(local_root);

	/* If is NOT balanced */
	if (balance_factor > 1 ||  balance_factor < -1)
	{
		/* Son is LEFT case  */
		if (balance_factor > 1)
		{
			/* 'Left - Left' case */
			if (GetBalanceFactor(local_root->left) > 0)
			{
				return (RotateRight(local_root));
			}
			/* 'Left - Right' case */
			else
			{
				local_root->left = RotateLeft(local_root->left);
				return (RotateRight(local_root));
			}
		}
		/* Son is Right case  */
		else
		{
			/* 'Right - Right' case */
			if (GetBalanceFactor(local_root->right) < 0)
			{
				return (RotateLeft(local_root));
			}
			/* 'Right - Left' case */	
			else
			{
				local_root->right = RotateRight(local_root->right);
				return (RotateLeft(local_root));
			}
		}
	}
	
	/* Returning the new local_root (if has changed) */
	return (local_root);
}
					
/******************************************************************************/
static avl_node_t *InsertNodeRec(avl_t *avl, avl_node_t *local_root, void *data)
{
	int cmp_return = 0;
	
	assert(avl);
	assert(local_root);
	
	cmp_return = avl->cmp_func(data, local_root->data);
	
	if (NULL == local_root)
	{
		return (NULL);
	}
	
	/* If need to insert in my LEFT son */
	if (cmp_return < 0 && NULL == local_root->left)
	{
		local_root->left = CreateNode(data);
		UpdateHeight(local_root);
		
		return (local_root);
	}
	/* If need to insert in my RIGHT son */
	else if (cmp_return > 0 && NULL == local_root->right)
	{
		local_root->right = CreateNode(data);
		UpdateHeight(local_root);
		
		return (local_root);
	}		
	
	/* If I can't insert a node in one of my sons */	
	if (cmp_return > 0)
	{
		local_root->right = InsertNodeRec(avl, local_root->right, data);
	}
	else if (cmp_return < 0)
	{
		local_root->left  = InsertNodeRec(avl, local_root->left, data);
	}
	else
	{
		return (NULL);
	}
	
	local_root = Balance(local_root);		
	UpdateHeight(local_root);		
			
	return (local_root);
}

/******************************************************************************/	
static avl_node_t *RemoveRec(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *temp = NULL;
	int cmp_return   = 0;
	ssize_t balance = 0;

	if (NULL == node)
	{
		return (node);
	}

	cmp_return = avl->cmp_func(data, node->data);

	/* Going right */
	if (cmp_return > 0)
	{
		node->right = RemoveRec(avl, node->right , data);
	}
	/* Going left */
	else if (cmp_return < 0)
	{
		node->left = RemoveRec(avl, node->left , data);
	}
	/* I found the one to remove!!! */
	else
	{
		/* If I have at most one son */
		if (NULL == node->left || NULL == node->right)
		{
			/* If he is left */
			if (NULL != node->left)
			{
				temp = node->left;
			}
			else
			{
				temp = node->right;
			}
			
			/* If I'm a leaf */
			if (NULL == temp)
			{
				DestroyNode(node);
				node = NULL;
			}
			else
			{
				*node = *temp;
				DestroyNode(temp);
				temp = NULL;
			}
		}
		/* I have two sons */
		else
		{
			temp = FindNextRec(node->right);
			node->data = temp->data;
			node->right = RemoveRec(avl, node->right, temp->data);
		}
	}

	if (NULL == node)
	{
		return (node);
	}
	
	UpdateHeight(node);
	
	balance = GetBalanceFactor(node); 
  
    if (balance > 1 && GetBalanceFactor(node->left) >= 0)
    {
		return (RotateRight(node));
	}  
    
    if (balance > 1 && GetBalanceFactor(node->left) < 0) 
    { 
		node->left =  RotateLeft(node->left); 
		return (RotateRight(node)); 
    }
    
    if (balance < -1 && GetBalanceFactor(node->right) <= 0)
	{
		return (RotateLeft(node));
	}
    
    if (balance < -1 && GetBalanceFactor(node->right) > 0) 
    { 
		node->right = RotateRight(node->right); 
		return (RotateLeft(node)); 
    } 
    
	return (node);
}


/******************************************************************************/
static void DestroyNode(avl_node_t *node)
{
	assert(node);
	
	node->data  = NULL;
	node->right = NULL;
	node->left  = NULL;
	free(node);
}	

/******************************************************************************/
static avl_node_t *FindNextRec(avl_node_t *node)
{
	assert(node);
	
	if (NULL == node->left)
	{
		return (node);
	}
	
	return (FindNextRec(node->left));
}	

/******************************************************************************/		
static void *FindRec(const avl_t *avl, avl_node_t *local_root, void *data)
{
	int cmp_return = 0;
	
	if (NULL == local_root)
	{
		return (NULL);
	}
	
	cmp_return = avl->cmp_func(data, local_root->data);
	
	/* I found it!!! */
	if (0 == cmp_return)
	{
		return (local_root->data);
	}
	/* Time to go right */	
	if (cmp_return > 0)
	{
		return (FindRec(avl, local_root->right, data));
	}
	/* Time to go left */	
	return (FindRec(avl, local_root->left, data));
}

/******************************************************************************/	
static int ForEachRec(avl_node_t *local_root, 
			          int(*action_func)(void *data, void *param) ,void *param)
{
	/* Type of implementation: IN-ORDER */ 
	int status = 0;
	
	if (NULL != local_root)
	{
		/* Action on my left */
		if (NULL != local_root->left)
		{
			status = ForEachRec(local_root->left, action_func , param);
		}
		/* Action on me */
		if (0 != action_func(local_root->data, param))
		{
			return (-1);
		}
		/* Action on my right */
		if (0 == status && NULL != local_root->right)
		{
			status = ForEachRec(local_root->right, action_func , param);          
		}	
	}         
	
	return (status);
}	          
			          
/******************************************************************************/
static void AVLPrintNode(const avl_node_t *node, size_t depth)
{
    size_t i = 0;
    for (i = 0; i < depth; ++i)
    {
        printf("│  ");
    }
    if (NULL != node)
    {
        printf("├╴ %p -> %d\n", (void*) node, *(int*)node->data);
        AVLPrintNode(node->left, depth + 1);
        AVLPrintNode(node->right, depth + 1);
    } else {
        printf("├╴ X\n");
    }
}

void AVLPrint(const avl_t *avl)
{
    assert(NULL != avl);

    if (NULL != avl->root)
    {
        printf("\nStart Print:\n");
        printf("%p -> %d\n", (void*)avl->root,
                *(int*)avl->root->data);
        AVLPrintNode(avl->root->left, 0);
        AVLPrintNode(avl->root->right, 0);
    }
}	
	

/******************************************************************************/
/*************************** END OF FILE **************************************/
/******************************************************************************/
