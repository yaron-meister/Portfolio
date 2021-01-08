/*****************************************************************************
 * File name:   dhcp_trie.c
 * Developer:   Yaron Meister
 * Reviewer: 	Daria
 * Date:        2019-01-15 17:47:23
 * Description: DHCP Building
 *****************************************************************************/

#include <stdio.h>			/*		fprintf			*/
#include <stdlib.h>  		/*     	 malloc    	    */
#include <assert.h>			/*		 assert			*/

#include "utils.h"			/*		  DBG			*/
#include "dhcp_trie.h"      /* Forward declarations */


/********************************* Macros *************************************/ 
#define BYTES_IN_ADDRESS  (4) 
#define BITS_IN_ADDRESS   (32)
#define RESERVED_CAPACITY (3)

enum flag
{
	OFF,
	ON
};

enum boolean
{
	FALSE,
	TRUE
};

/******************************* Structurs ************************************/
typedef struct trie_node
{
    struct trie_node *children[2];
    struct trie_node *parent;
    int is_full;
} trie_node_t;

struct dhcp
{
	trie_node_t *root;
	address_t subnet;
	unsigned int subnet_mask;
};

/************************** Forward Declarations ******************************/
static trie_node_t *CreateNode(void);

/* Get address_t of 'broadcast' and 'server' */
static void GetBroadAndServ(dhcp_t *dhcp, address_t broadcast, address_t server);

static void DestroyNode(trie_node_t *node);

static void	DestroyRec(trie_node_t *parent);

/* Gets the height of the 'trie' which is according to <24 - 'subnet_mask'> */	
static unsigned int GetLevel(const dhcp_t *dhcp);

/* Checks if 'requested_ip' is in range */
static int IsValid(const address_t subnet, const address_t requested_ip, 
													  unsigned int subnet_mask);

static ip_status_t GetIPRec(trie_node_t *parent, unsigned int requested_ip, 
   															unsigned int level);

/* <address_t> to <unsigned int> */	
static unsigned int Address2UI(const address_t address,
													  unsigned int subnet_mask);

/* <unsigned int> to <address_t> */	
static void UI2Address(unsigned int address, address_t add_ip, 
													  unsigned int subnet_mask);

static ip_status_t FreeIPRec(trie_node_t *parent, unsigned int ip,
													    	unsigned int level);

/* Counts taken IPs */	
static size_t CountFullRec(const trie_node_t *parent, unsigned int level);



/***************************** Global variables *******************************/
/* A flag for initiating RESERVED IPs */
static int g_reserved_flag = OFF; 
 
 
 
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/
dhcp_t *DHCPCreate(const address_t subnet, const unsigned int subnet_mask)
{
	unsigned int i			  = 0;
	address_t broadcast 	  = {0};
	address_t server	      = {0};
	address_t out_ip		  = {0};		
	dhcp_t *dhcp 			  = NULL;
	ip_status_t subnet_status = SUCCESS;
	ip_status_t broad_status  = SUCCESS;
	ip_status_t server_status = SUCCESS;
								
	assert(subnet);
	
	dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
	if (NULL != dhcp)
	{
		/* Initiating dhcp->subnet */
		for (i = 0; i < BYTES_IN_ADDRESS; ++i)
		{
			dhcp->subnet[i] = subnet[i];
		}
		
		dhcp->subnet_mask = subnet_mask;
		dhcp->root		  = CreateNode();
		if (NULL == dhcp->root)
		{
			DBG(fprintf(stderr, "DHCP creation failed\n"));
			
 			DHCPDestroy(dhcp);
			dhcp = NULL;
			
			return (NULL);
		}
		
		GetBroadAndServ(dhcp, broadcast, server);
		
		/* Allocating the reserved IPs */
		subnet_status = DHCPGetIP(dhcp, subnet, out_ip);
		broad_status  = DHCPGetIP(dhcp, broadcast, out_ip);
		server_status = DHCPGetIP(dhcp, server, out_ip);
		/* Turning flag ON - subnet, server and broadcast are initiated */
		g_reserved_flag = ON;
		
		/* If fails at allocating RESERVED IPs */
		if (SUCCESS != subnet_status || SUCCESS != broad_status ||
													   SUCCESS != server_status)
		{
			DBG(fprintf(stderr, "DHCP creation failed\n"));
			
 			DHCPDestroy(dhcp);
			dhcp = NULL;			
		}	
	}
			
	return (dhcp);
}

/*********															***********/
/* Get address_t of 'broadcast' and 'server' */
static void GetBroadAndServ(dhcp_t *dhcp, address_t broadcast, address_t server)
{
	unsigned int i			  	  = 0;
	unsigned int changeable_bytes = 0;

	assert(dhcp);
	assert(broadcast);
	assert(server);

	/*
	 * Class A: changeable_bytes = 3
	 * Class B: changeable_bytes = 2
	 * Class C: changeable_bytes = 1
	 */
	changeable_bytes = BYTES_IN_ADDRESS - (dhcp->subnet_mask / BITS_IN_BYTE);

	/* Initializing 'broadcast' and 'server' according
												    to 'subnet' and the CLASS */
	for (i = 0; i < BYTES_IN_ADDRESS; ++i)
	{
		broadcast[i] = dhcp->subnet[i];
		server[i]    = dhcp->subnet[i];
	}
	
	/* Setting all changeable to 255 (last address at the char) */
	for (i = 1; i <= changeable_bytes; ++i)
	{
		broadcast[BYTES_IN_ADDRESS - i] = 255;
		server[BYTES_IN_ADDRESS - i]	= broadcast[BYTES_IN_ADDRESS - i];
	}
	
	/* 'server' gets the address before 'broadcast' */ 
	--server[3];
}

/*********															***********/
static trie_node_t *CreateNode(void)
{
	trie_node_t* node = (trie_node_t*)malloc(sizeof(trie_node_t)); 
	if (NULL != node)
	{
		node->children[0] = NULL;
		node->children[1] = NULL;
		node->parent	  = NULL;
		node->is_full	  = FALSE;
	}
	
	return (node);
}
 
/******************************************************************************/
void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);
	
	DestroyRec(dhcp->root);
	
	dhcp->root = NULL;
	/* Turning flag OFF - subnet, server and broadcast are not initiated */
	g_reserved_flag = OFF;	

	free(dhcp);
	dhcp = NULL;
}

/*********															***********/ 
static void	DestroyRec(trie_node_t *node)
{ 
	if (NULL == node)
	{
		return;
	}
	
	DestroyRec(node->children[0]);
	DestroyRec(node->children[1]);
		
	DestroyNode(node);
	node = NULL;
}

/*********															***********/ 
static void DestroyNode(trie_node_t *node)
{
	assert(node);
	
	node->children[0] = NULL;
	node->children[1] = NULL;
	node->parent	  = NULL;
	
	free(node);
	node = NULL;
}

/******************************************************************************/
ip_status_t DHCPGetIP(dhcp_t *dhcp, const address_t requested_ip, 
   															  address_t out_ip)
{
	unsigned int i			  = 0;
	unsigned int ui_requested = 0;
	unsigned int ui_subnet    = 0;
	unsigned int ui_broad	  = 0;
	unsigned int ui_server	  = 0;
	unsigned int level 		  = 0;
	address_t broadcast		  = {0};
	address_t server		  = {0};	
	ip_status_t status	      = DHCP_FULL;
	ip_status_t temp_status	  = SUCCESS;
	
	assert(dhcp);
	assert(out_ip);

	/* If ! DHCP_FULL */
	if (FALSE == dhcp->root->is_full)
	{
		/*
		 * The only bytes that will change at 'out_ip' are the relevante
		 *		bytes according to mask. Therefore --> Initiating 'out_ip'
		 *		according to 'subnet' and changing after.
		 */
		for (i = 0; i < BYTES_IN_ADDRESS; ++i)
		{	
			out_ip[i] = dhcp->subnet[i];
		}
		
		GetBroadAndServ(dhcp, broadcast, server);
		ui_subnet = Address2UI(dhcp->subnet, dhcp->subnet_mask);
		ui_broad  = Address2UI(broadcast, dhcp->subnet_mask); 
		ui_server = ui_broad - 1; 
		level     = GetLevel(dhcp);
		
		if (NULL != requested_ip)
		{
			ui_requested = Address2UI(requested_ip, dhcp->subnet_mask);
		}

		/* If 'requested' is INVALID */
		if (!IsValid(dhcp->subnet, requested_ip, dhcp->subnet_mask))
		{
			temp_status = INVALID_IP;
			ui_requested = ui_subnet + 1;
		}
		
		status = GetIPRec(dhcp->root, ui_requested, level);

		if (INVALID_IP != temp_status)
		{
			temp_status = status;
		} 

		while (SUCCESS != status && MEM_FAILURE != status)
		{
			++ui_requested;
			/* If DHCP got to the end of the range */
			if (ui_server == ui_requested)											/* && ON == g_reserved_flag (?) */		
			{
				ui_requested = ui_subnet + 1;
			}
			
			status = GetIPRec(dhcp->root, ui_requested, level);
		}
		
		if (MEM_FAILURE != status)
		{
			/* Translating succeeded UI to 'out_ip' */
			UI2Address(ui_requested, out_ip, dhcp->subnet_mask);
			/* If first requested was problematic */
			if (SUCCESS != temp_status && NULL != requested_ip)
			{
				status = temp_status;
			}
		}
		/* If MEM_FAILURE, sets 'out_ip' to {0, 0, 0, 0} */
		else
		{
			for (i = 0; i < BYTES_IN_ADDRESS; ++i)
			{	
				out_ip[i] = 0;
			}
		}	
	}
	
	return (status);
}		

/**************												   ****************/ 
/* Gets the height of the 'trie' which is according to <24 - 'subnet_mask'> */	
static unsigned int GetLevel(const dhcp_t *dhcp)
{
	assert(dhcp);
	
	return (BITS_IN_ADDRESS - dhcp->subnet_mask);
}

/**************												   ****************/ 
/* Checks if 'requested_ip' is in range */ 
static int IsValid(const address_t subnet, const address_t requested_ip, 
													   unsigned int subnet_mask)
{
	/*
	 * Class A: unchangeable_bytes = 1
	 * Class B: unchangeable_bytes = 2
	 * Class C: unchangeable_bytes = 3
	 */
	unsigned int unchangeable_bytes = subnet_mask / BITS_IN_BYTE;
	unsigned int i				    = 0;
	int is_different 				= FALSE;
	
	assert(subnet);

	if (NULL != requested_ip)
	{	
		/* Checking only if the UNCHANGEABLE BYTES are different */
		for (i = 0; i < unchangeable_bytes && !is_different; ++i)
		{
			if (subnet[i] != requested_ip[i])
			{
				is_different = TRUE;
			}
		}
	}
	/* requested == NULL --> NOT VALID */
	else
	{
		is_different = TRUE;
	}
	
	return (!is_different);
}

/**************												   ****************/ 
static ip_status_t GetIPRec(trie_node_t *node, unsigned int requested_ip, 
   															 unsigned int level)	
{
	trie_node_t *next_child = NULL;
	ip_status_t status		= SUCCESS;
	unsigned int next_bit	= 0;

	assert(node);
	
	if (node->is_full)
	{
		return (TAKEN_IP);
	}
	
	if (!(node->is_full) && 0 == level)
	{
		node->is_full = TRUE;

		return (SUCCESS);
	}

	next_bit = ((requested_ip >> (level - 1)) & 1 );
	/* If the child does not exist */
	if (NULL == node->children[next_bit])
	{
		/* Allocating a new node */
		node->children[next_bit] = CreateNode();
		if (NULL == node->children[next_bit])
		{
			return (MEM_FAILURE);
		}
	}
	
	next_child = node->children[next_bit];
	
	status = GetIPRec(next_child, requested_ip, level - 1);

	/* 
	 * Setting is_full for everyone who is relevante:
	 *		If you have 2 children and both of them are full ---> YOU ARE FULL
	 */
	if (NULL != node->children[0] && NULL != node->children[1] &&
	    node->children[0]->is_full && node->children[1]->is_full)
    {
    	node->is_full = TRUE;
	}
	
	return (status);	
}   															  

/**************												   ****************/ 
/* <address_t> to <unsigned int> */	 
static unsigned int Address2UI(const address_t address,
													   unsigned int subnet_mask)
{
	unsigned int ui_ip = 0;
	/*
	 * Class A: unchangeable_bytes = 1
	 * Class B: unchangeable_bytes = 2
	 * Class C: unchangeable_bytes = 3
	 */
	unsigned int unchangeable_bytes = subnet_mask / BITS_IN_BYTE;
	unsigned int i				    = unchangeable_bytes;
	
	assert(address);
	
	for (i = unchangeable_bytes; i < BYTES_IN_ADDRESS; ++i)
	{
		ui_ip <<= BITS_IN_BYTE;
		ui_ip |= address[i];
	}	
	
	return (ui_ip);
}

/**************												   ****************/ 
/* <unsigned int> to <address_t> */	
static void UI2Address(unsigned int address, address_t add_ip, 
													   unsigned int subnet_mask)
{ 
	/*
	 * Class A: changeable_bytes = 3
	 * Class B: changeable_bytes = 2
	 * Class C: changeable_bytes = 1
	 */
	unsigned int changeable_bytes = BYTES_IN_ADDRESS - 
												   (subnet_mask / BITS_IN_BYTE);
	unsigned int i				  = 1;
	
	/* Setting from the end to beginning */
	for (; i <= changeable_bytes; ++i)
	{
		add_ip[BYTES_IN_ADDRESS - i] = address & 0xff;
		address >>= BITS_IN_BYTE;
	}
}
		
/******************************************************************************/
ip_status_t DHCPFreeIP(dhcp_t *dhcp, address_t ip)
{
	ip_status_t status 	   = INVALID_IP;
	unsigned int ui_ip	   =  0;
	unsigned int ui_subnet =  0;
	unsigned int ui_broad  =  0;
	unsigned int ui_server =  0;
	unsigned int level 	   =  0;
	address_t broadcast	   = {0};
	address_t server	   = {0};
	
	assert(dhcp);
	assert(ip);
	
	/* If ip IS VALID */
	if (IsValid(dhcp->subnet, ip, dhcp->subnet_mask))
	{
		GetBroadAndServ(dhcp, broadcast, server);
		level 	  = GetLevel(dhcp);
		ui_ip     = Address2UI(ip, dhcp->subnet_mask);
		ui_subnet = Address2UI(dhcp->subnet, dhcp->subnet_mask);
		ui_broad  = Address2UI(broadcast, dhcp->subnet_mask); 
		ui_server = ui_broad - 1;
		
		/* If ip is RESERVED */
		if (ui_ip == ui_subnet || ui_ip == ui_broad || ui_ip == ui_server)
		{
			status = RESERVED_IP;
		}
		else
		{
			status = FreeIPRec(dhcp->root, ui_ip, level);
		}
	}
	
	return (status);
}

/**************												   ****************/ 
static ip_status_t FreeIPRec(trie_node_t *node, unsigned int ip,
															 unsigned int level)
{
	ip_status_t status = SUCCESS;
	
	if (NULL == node || (0 == level && 0 == node->is_full))
	{
		return (FREE_IP);
	}
	
	if (0 == level && 1 == node->is_full)
	{
		node->is_full = 0;
		return (SUCCESS);
	}
	
	status = FreeIPRec(node->children[((ip >> (level - 1)) & 1 )],
																 ip, level - 1);
	/* 
	 * Setting NOT is_full for everyone who is relevante:
	 *		If SUCCESS ---> someone at the bottom is free so you are not full
	 */
	if (SUCCESS == status)
	{
		node->is_full = 0;
	}
	
	return (status);
}
	
/******************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t capacity    = 0;
	size_t count_full  = 0;
	unsigned int level = 0;
	
	assert(dhcp);

	level 	 = GetLevel(dhcp);
	capacity = (1 << level); /* 2^(level) */

	count_full = CountFullRec(dhcp->root, level);
	
	/* FREE = CAPACITY - TAKEN */
	return (capacity - count_full);
}

/**************												   ****************/ 
/* Counts taken IPs */	
static size_t CountFullRec(const trie_node_t *node, unsigned int level)
{
	size_t count = 0;
	
	assert(node);
	
	if (node->is_full)
	{
		return (1 << level); /* 2^(level) */
	}
	
	if (NULL != node->children[0])
	{
		count += CountFullRec(node->children[0], level - 1);
	}
	
	if (NULL != node->children[1])
	{
		count += CountFullRec(node->children[1], level - 1);
	}
	
	return (count);
}
	

 
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
