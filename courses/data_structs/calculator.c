/*****************************************************************************
 * File name:   calculator.c
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2018-12-24 18:29:59
 * Description: An implementation for a claculator that gets a string as an
				input and returns a double which is the result of the calculate
 *****************************************************************************/
 
#include <stdlib.h>    		/* 		  strtod        */
#include <string.h>			/* 		  strlen 		*/
#include <assert.h>			/*		  assert 		*/
#include <float.h>			/* 		 DBL_MAX 		*/
#include <math.h>			/* 		fabs, pow	 	*/

#include "utils.h"			/* 	 	UNUSED_VAR	    */
#include "stack.h"			/* 	 	  Stacks 	    */
#include "calculator.h"     /*  Forward declaratins */


/********************************** Macros ************************************/
#define NUM_OF_ASCII_VALUES (256)

typedef enum status
{
	SUCCESS,
	ALLOCATION_FAILURE,
	SYNTAX_ERROR,
	MATH_ERROR,
	EXIT
} status_t;
 
typedef enum state
{
	GET_NUM,
	GET_OP,
	MAX_STATES
} state_t;

typedef enum associativity
{
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT		/* power */
} asso_t;

typedef status_t(*handle_t)(stack_t *, stack_t *, const char *);

/*************************** Forward Declarations *****************************/
static status_t ErrorHandler
						(stack_t *numbers, stack_t *operators, const char *exp);
static status_t NumbersHandler
						(stack_t *numbers, stack_t *operators, const char *exp);
static status_t OperatorsHandler
						(stack_t *numbers, stack_t *operators, const char *exp);
static int IsOperator(char character);
static void PresedenceArrInit(int *arr);

/* A function that makes the actual calculate */
static double GetResult(double first_arg, double second_arg, stack_t *operators);

/***************************** Global variables *******************************/
static state_t g_state = GET_NUM;
static int presedence_array[NUM_OF_ASCII_VALUES] = {0};
static asso_t asso_array[NUM_OF_ASCII_VALUES]    = {LEFT_TO_RIGHT};

/************************ Functions's implementations *************************/
double Calculate(const char *exp, int *status)
{
	state_t i        = 0;
	int j 	         = 0;
	double result    = 0;
	double first_arg = 0;
	status_t current_status = SUCCESS;
	handle_t table[MAX_STATES][NUM_OF_ASCII_VALUES] = {0}; /* FSM */
	stack_t *numbers_stack   = NULL;
	stack_t *operators_stack = NULL;
	
	/* 
	 * A dummy for the operators_stack that has a value in the presedence table.
	 * It's nessecary for comparing the first operator's presedence.
	 */
	char dummy 				 = '%'; 

/* If the string is empty - returnning '0' */	
	if (NULL == exp)
	{
		if (NULL != status)
		{
			*status = SUCCESS;
		}
		
		return (result);
	}
	
	numbers_stack   = StackCreate((strlen(exp)), sizeof(double));
	if (NULL == numbers_stack)
	{
		if (NULL != status)
		{
			*status = ALLOCATION_FAILURE;
		}
		
		return (result);
	}
		
	operators_stack = StackCreate((strlen(exp)), sizeof(char));
	if (NULL == operators_stack)
	{
		StackDestroy(numbers_stack);
		
		if (NULL != status)
		{
			*status = ALLOCATION_FAILURE;
		}
		
		return (result);
	}

	PresedenceArrInit(presedence_array);
	asso_array['^'] = RIGHT_TO_LEFT;		/* Initializing asso_array */
	StackPush(operators_stack, &dummy);	/* Pushing DUMMY to <operators_stack> */
	g_state = GET_NUM;					

	/* Initializing FSM */	
	for (i = 0; i < MAX_STATES; ++i)
	{
		for (j = 0; j < NUM_OF_ASCII_VALUES; ++j)
		{
			table[i][j] = ErrorHandler;
		}
	}

	table[GET_NUM]['0'] = NumbersHandler; 
	table[GET_NUM]['1'] = NumbersHandler;
	table[GET_NUM]['2'] = NumbersHandler;
	table[GET_NUM]['3'] = NumbersHandler;
	table[GET_NUM]['4'] = NumbersHandler;
	table[GET_NUM]['5'] = NumbersHandler;
	table[GET_NUM]['6'] = NumbersHandler;
	table[GET_NUM]['7'] = NumbersHandler;
	table[GET_NUM]['8'] = NumbersHandler;
	table[GET_NUM]['9'] = NumbersHandler;

	table[GET_OP]['+']  = OperatorsHandler;
	table[GET_OP]['-']  = OperatorsHandler;
	table[GET_OP]['*']  = OperatorsHandler;
	table[GET_OP]['/']  = OperatorsHandler;
	table[GET_OP]['^']  = OperatorsHandler;
	table[GET_OP]['\0'] = OperatorsHandler;

	/* Making the calculation */	
	while (SUCCESS == current_status)
	{
		current_status = table[g_state][*(unsigned char*)exp]
										   (numbers_stack,operators_stack, exp);
		if (GET_NUM == g_state)
		{
			++exp;
		}
		else
		{
			strtod(exp, (char**)&exp);
		}
	}

	/* After running above the string without errors */	
	if (EXIT == current_status && NULL != StackPeek(numbers_stack))
	{
		result = *(double*)StackPeek(numbers_stack);
		current_status = SUCCESS;
	}
	
	if (NULL != status)
	{
		*status = current_status;
	}

	/* Emptying the stacks and making the rest of the calculations */	
	while (2 <= StackSize(numbers_stack) && 1 != StackSize(operators_stack))
	{
		StackPop(numbers_stack);
		first_arg = *(double*)StackPeek(numbers_stack);
		StackPop(numbers_stack);
		/* result is the second arg */		
		result = GetResult(first_arg, result, operators_stack);
		StackPush(numbers_stack, &result);

	/* Checking there is a divide by '0' in the string */		
		if (fabs(result) > DBL_MAX || result != result)
		{
			return (MATH_ERROR);
		}
		
		StackPop(operators_stack);
	}
		 
	StackDestroy(numbers_stack);
	StackDestroy(operators_stack);

	return (result);
}
 
/******************************************************************************/
status_t ErrorHandler(stack_t *numbers_stack, stack_t *operators_stack,
															    const char *exp)
{
	status_t status = SYNTAX_ERROR;
	
	assert(exp);
	
	UNUSED_VAR(numbers_stack);
	UNUSED_VAR(operators_stack);
	
	if (IsOperator(*exp))
	{
		status = MATH_ERROR;
	}
	
	return (status);
}

/******************************************************************************/
static status_t NumbersHandler(stack_t *numbers_stack, stack_t *operators_stack,
															    const char *exp)			       			 
{	
	double number = 0;
	status_t status = SUCCESS;
	
	assert(exp);
	
	UNUSED_VAR(operators_stack);
	number = strtod(exp, (char**)&exp);
	status = StackPush(numbers_stack, &number); /* fails = ALOCCATION_FAILURE */
	g_state = GET_OP;
	
	return (status);
}
	
/******************************************************************************/
static status_t OperatorsHandler	
		       			 (stack_t *numbers, stack_t *operators, const char *exp)
{
	double first_arg  = 0;
	double second_arg = 0;
	double result	  = 0;
	status_t status   = SUCCESS;
	
	assert(numbers);
	assert(operators);
	assert(exp);
	
	/* If presedence of stack is before the presedence of <*exp> 
		and the associativity is LEFT_TO_RIGHT - make the former calculation */ 
	while (presedence_array[*(unsigned char*)StackPeek(operators)] >= 
		   								 presedence_array[*(unsigned char*)exp]
		  && !('^' == *exp && 
		  		asso_array[*(unsigned char*)StackPeek(operators)] == 
		  	    asso_array[*(unsigned char*)exp])) 
	{
		second_arg = *(double*)StackPeek(numbers);
		StackPop(numbers);
		first_arg = *(double*)StackPeek(numbers);
		StackPop(numbers);
		
		result = GetResult(first_arg, second_arg, operators);
		
		/* Checking there is a divide by '0' in the string */	
		if (fabs(result) > DBL_MAX || result != result)
		{
			return (MATH_ERROR);
		}
		
		StackPush(numbers, &result);
		StackPop(operators);
		
		if ('\0' == *exp)
		{
			return (EXIT);
		}
	}
	
	status = StackPush(operators, exp);
	g_state = GET_NUM;

	return (status);
}

/******************************************************************************/
static int IsOperator(char character)
{
	return ('+' == character || '-' == character || '*' == character || 
			'/' == character || '^' == character);
}

/******************************************************************************/
static void PresedenceArrInit(int *arr)
{
	arr['+']  = 1;
	arr['-']  = 1;
	arr['*']  = 2;
	arr['/']  = 2;
	arr['^']  = 3;
}

/******************************************************************************/
static double GetResult(double first_arg, double second_arg, stack_t *operators)
{
	double result = 0;
	
	if (NULL != StackPeek(operators))
	{
		switch (*(char*)StackPeek(operators))
			{
				case '+':
					result = first_arg + second_arg;
					break;
				
				case '-':
					result = first_arg - second_arg;
					break;
				
				case '*':
					result = first_arg * second_arg;
					break;
				
				case '/':
					result = first_arg / second_arg;
					break;
					
				case '^':
					result = pow(first_arg, second_arg);
					break;
						
				default:
					break;
			}		
	}

	return (result);
}

/****************************** END OF FILE ***********************************/  

