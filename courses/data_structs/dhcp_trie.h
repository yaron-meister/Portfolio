/*******************************************************************************
 * File name:   dhcp_trie.h
 * Developer:   HRD7
 * Version:     3 
 * Date:        2019-01-15 14:46:19
 * Description: DHCP Header
 ******************************************************************************/

#ifndef __DHCP_TRIE_H__
#define __DHCP_TRIE_H__

#include <stddef.h>      /* size_t */

typedef struct dhcp dhcp_t;

typedef unsigned char address_t[4];

typedef enum 
{
	SUCCESS,
	TAKEN_IP,
	INVALID_IP,
	RESERVED_IP,
	FREE_IP,
	DHCP_FULL,
	MEM_FAILURE
}ip_status_t;

/*
 * Creates the DHCP.
 * <subnet_mask> is the number of bits (from left) who can't be changed. 
 * Returns a pointer to the DHCP or NULL for failure.
 * reserved addresses can't be allocated or freed.
 */
dhcp_t *DHCPCreate(const address_t subnet, const unsigned int subnet_mask);

/*
 * Destroys the DHCP
 */
void DHCPDestroy(dhcp_t *dhcp);

/*
 * Allocate an available address and assign it to <out_ip>.
 * If <requested_ip> is NULL, <out_ip> will be the next available address.
 * return status: 
 * 	SUCCESS:    <requested_ip> was allocated successfully.  
 * 	TAKEN_IP:   <requested_ip> is taken. Next available address was allocated.
 * 	INVALID_IP: <requested_ip> is invalid. First available address is allocated.
 * 	
 * 	DHCP_FULL:   <dhcp> is full. No address was allocated. 
 *  MEM_FAILURE: memory allocation faliure. No address was allocated.
 */
ip_status_t DHCPGetIP(dhcp_t *dhcp, const address_t requested_ip, 
															  address_t out_ip);

/*
 * Frees a taken address <ip> from <dhcp>.
 * Return status:
 * 	SUCCESS:     <ip> was freed successfully.
 *  RESERVED_IP: <ip> is a reserved IP and can't be freed. 
 *  FREE_IP:     <ip> is already a free IP.
 *  INVALID_IP:  <ip> is not a valid ip in <dhcp>.
 */
ip_status_t DHCPFreeIP(dhcp_t *dhcp, address_t ip);

/*
 * Counts how many addresses are available.
 */
size_t DHCPCountFree(const dhcp_t *dhcp);
 
#endif     /* __DHCP_TRIE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
