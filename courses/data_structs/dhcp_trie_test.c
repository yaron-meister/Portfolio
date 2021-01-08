/*****************************************************************************
 * File name:   dhcp_trie_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Daria
 * Date:        2019-01-15 17:47:23
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>     		/* 		  printf   	    */
#include <stdlib.h>    		/*     EXIT_SUCCESS 	*/
 
#include "dhcp_trie.h"      /* Forward declarations */


/********************************* Macros *************************************/ 
#define A (8)
#define B (16)
#define C (24)
	
 
/**************************** Forward Declarations ****************************/
static void IntEqualityTest(int actual_value, int expected_value,
													    	   int num_of_test);
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
													    	   int num_of_test);
static void ArrEqualityTest(address_t arr1, address_t arr2, size_t size,
							    				   		 	   int num_of_test);
static void CreateAndDestroy_Test(void);
static void GetIP_Test(void);
static void FreeIP_Test(void);
static void CountFreeIP_Test(void);

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{   
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
	CreateAndDestroy_Test();
	GetIP_Test();    
	FreeIP_Test();
	CountFreeIP_Test();

	printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static void IntEqualityTest(int actual_value, int expected_value,
												 int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
							    				   		 int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static void ArrEqualityTest(address_t arr1, address_t arr2, size_t size,
							    				   		 		int num_of_test)
{
	size_t i = 0;
	int flag = 0;

	for (; i < size && 0 == flag; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			flag = 1;
		}
	}

	if (0 != flag)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}
/******************************************************************************/
static void CreateAndDestroy_Test(void)
{
	dhcp_t *dhcp				   = NULL;
	const address_t subnet 		   = {13, 0, 0, 0};
	const unsigned int subnet_mask = B; /* class */

	dhcp = DHCPCreate(subnet, subnet_mask);
	DHCPDestroy(dhcp);
}

/******************************************************************************/
static void GetIP_Test(void)
{
	dhcp_t *dhcp		   		   = NULL;
	ip_status_t status	   		   = SUCCESS;
	const address_t subnet 		   = {13, 0, 0, 0};
	address_t regular     		   = {13, 0, 3, 28};
	address_t reserved    		   = {13, 0, 255, 255};
	address_t invalid      		   = {13, 3, 3, 255};
	address_t null_expected		   = {13, 0, 0, 1};
	address_t reserved_expected	   = {13, 0, 0, 2};
	address_t invalid_expected	   = {13, 0, 0, 3};
	address_t out_ip 			   = {0};
	const unsigned int subnet_mask = B;

	printf("************************ GetIP - Test ***************************");
  	printf("\n");

	dhcp = DHCPCreate(subnet, subnet_mask);

	/* Regular test */
	status = DHCPGetIP(dhcp, regular, out_ip);
	ArrEqualityTest(regular, out_ip, 4, 1);
	IntEqualityTest(status, SUCCESS, 2);

	/* Requested == NULL test */
	status = DHCPGetIP(dhcp, NULL, out_ip);
	ArrEqualityTest(null_expected, out_ip, 4, 3);
	IntEqualityTest(status, SUCCESS, 4);

	/* Requested == Reserved test */
	status = DHCPGetIP(dhcp, reserved, out_ip);
	ArrEqualityTest(reserved_expected, out_ip, 4, 5);
	IntEqualityTest(status, TAKEN_IP, 6);

	/* Invalid test */
	status = DHCPGetIP(dhcp, invalid, out_ip);
	ArrEqualityTest(invalid_expected, out_ip, 4, 7);
	IntEqualityTest(status, INVALID_IP, 8);

	DHCPDestroy(dhcp);
}

/******************************************************************************/
static void FreeIP_Test(void)
{
	dhcp_t *dhcp		   		   = NULL;
	ip_status_t status	   		   = SUCCESS;
	size_t count 				   = 0;
	const address_t subnet 		   = {13, 0, 0, 0};
	address_t regular     		   = {13, 0, 0, 28};
	address_t reserved    		   = {13, 0, 0, 255};
	address_t invalid      		   = {13, 3, 3, 255};
	address_t freed		   		   = {13, 0, 0, 1};
	address_t out_ip 			   = {0};
	const unsigned int subnet_mask = C;

	printf("*********************** FreeIP - Test ***************************");
  	printf("\n");

	dhcp = DHCPCreate(subnet, subnet_mask);
	DHCPGetIP(dhcp, regular, out_ip);

	/* Regular test */
	status = DHCPFreeIP(dhcp, regular);
	count  = DHCPCountFree(dhcp);
	IntEqualityTest(status, SUCCESS, 9);
	SizeTEqualityTest(count, 253, 10);

	/* Free Resereved test */
	status = DHCPFreeIP(dhcp, reserved);
	count  = DHCPCountFree(dhcp);
	IntEqualityTest(status, RESERVED_IP, 11);
	SizeTEqualityTest(count, 253, 12);
	
	/* Free Freed test */
	status = DHCPFreeIP(dhcp, freed);
	count  = DHCPCountFree(dhcp);
	IntEqualityTest(status, FREE_IP, 13);
	SizeTEqualityTest(count, 253, 14);

	/* Invalid test */
	status = DHCPFreeIP(dhcp, invalid);
	count  = DHCPCountFree(dhcp);
	IntEqualityTest(status, INVALID_IP, 15);
	SizeTEqualityTest(count, 253, 16);

	DHCPDestroy(dhcp);
}

/******************************************************************************/
static void CountFreeIP_Test(void)
{
	dhcp_t *dhcp		   		   = NULL;
	size_t count 				   = 0;
	const address_t subnet 		   = {13, 0, 0, 0};
	const address_t broadcast	   = {13, 255, 255, 255};
	const address_t server	   	   = {13, 255, 255, 254};
	address_t regular     		   = {13, 5, 0, 28};
	address_t out_ip 			   = {0};
	const unsigned int subnet_mask = A;

	printf("******************** CountFreeIP - Test *************************");
  	printf("\n");

	dhcp = DHCPCreate(subnet, subnet_mask);

	count  = DHCPCountFree(dhcp);
	SizeTEqualityTest(count, 16777213, 17);

	DHCPGetIP(dhcp, regular, out_ip);

	count  = DHCPCountFree(dhcp);
	SizeTEqualityTest(count, 16777212, 18);

	DHCPGetIP(dhcp, server, out_ip);

	count  = DHCPCountFree(dhcp);
	SizeTEqualityTest(count, 16777211, 19);

	DHCPGetIP(dhcp, broadcast, out_ip);

	count  = DHCPCountFree(dhcp);
	SizeTEqualityTest(count, 16777210, 20);

	DHCPDestroy(dhcp);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
 
