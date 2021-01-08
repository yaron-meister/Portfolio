/*****************************************************************************
 * File name:   calculator_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2018-12-24 18:29:59
 * Description:	A test file for the calculator
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "calculator.h"       /*              */


/**************************** Forward Declarations ****************************/
void Presedence_Test(void);
void Associativity_Test(void);
void Errors_Test(void);

/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{    
	printf("\n*********** WELCOME TO YARON's UNIT-TEST ********************\n");
    Presedence_Test();
    Associativity_Test();
	Errors_Test();

    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void Presedence_Test(void)
{
	char exp1[]   = "10+5*2^3*5+10";
	char exp2[]	  = "2^3*5+10*2^3";
	int status    = 0;

	printf("\n**************** Presedence - TEST **************************\n");

	if (220 != Calculate(exp1, &status))
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (120 != Calculate(exp2, &status))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	if (0 != status)
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
void Associativity_Test(void)
{
	char exp1[] = "4^2^0";
	char exp2[] = "3^1^2";
	
	printf("\n************** Associativity - TEST *************************\n");

	if (4 != Calculate(exp1, NULL))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	if (3 != Calculate(exp2, NULL))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
void Errors_Test(void)
{
	char exp1[]   = "4*5/0";
	char exp2[]   = "3^^2";
	char exp3[]   = "3^ ^2";
	int status    = 0;
	double result = 0;

	printf("\n**************** Errors - TEST ******************************\n");

	result = Calculate(exp1, &status);

	if (3 != status || 0 != result)
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	result = Calculate(exp2, &status);

	if (3 != status || 0 != result)
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	result = Calculate(exp3, &status);

	if (2 != status || 0 != result)
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
}


/******************************* END OF FILE **********************************/

