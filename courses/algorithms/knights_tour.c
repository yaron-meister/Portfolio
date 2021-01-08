/*****************************************************************************
 * File name:   knights_tour.c
 * Developer:   Yaron Meister
 * Reviewer: 	Shiran
 * Date:        2019-01-13 14:25:40
 * Description: Knight's tour implementation
 *****************************************************************************/
 
#include <stdio.h>    		/* 	      fprintf 	    */
#include <assert.h>			/*		  assert		*/	 
#include <stdlib.h>			/*		  qsort			*/		

#include "utils.h"			/*   		DBG			*/ 
#include "bits_array.h"		/*		bits_array.c	*/
#include "sorts.h"			/*		QuickSort		*/
#include "knights_tour.h"   /* Forward declarations */


/********************************* Macros *************************************/ 
#define UNITE_INDECES(y,x) ((8 * (y)) + (x))
#define INVALID_INDEX (100)
#define NUM_OF_ROWS (8)
#define NUM_OF_COLS (8)
#define MOVES (8)

/* An enum of statuses */
typedef enum status
{
	SUCCESS,
	FAILURE
} status_t;

/* An enum to check if 'moves_lut' is initiated */
typedef enum lut_status
{
	NOT_INITIATE,
	INITIATE
} lut_status_t;

/* A struct to reserve 'next_index' with his updated
						  degree (num of next steps) */
typedef struct heuristic
{
	unsigned int next_index;
	int degree;
} heuristic_t;
 
 
/************************** Forward Declarations ******************************/
static int KnightsTourRec(unsigned long bits, unsigned int united_index, 
					   unsigned int *out_solution_array, unsigned int *counter);			   
/* A function that initiates 'moves_lut' */
static void MovesLUTInit(void);
/* A function that checks if a cell is on the board */ 
static int IsValidIndex(int y, int x);
/* A function that initiates and sorts 'Heuristic_array' */ 
static int GetHeuristicArray(unsigned int united_index, unsigned long bits,
	       										  heuristic_t *heuristic_array);	       								  
/* A function that calculates updated degree for an index */ 	       										  
static int GetDegree(unsigned long bits, unsigned int united_index);
/* A function that compares between to structs according to their degree */ 
static int Compare(const void *left, const void *right);
/* A function that prints 'out_solution_array' */ 	
static void PrintSolArr(unsigned int *out_solution_array);



/*************************** Global variables *********************************/
int moves_lut[NUM_OF_ROWS*NUM_OF_COLS][MOVES] = {0}; /* moves_lut[64][8] */
lut_status_t g_lut = NOT_INITIATE;



/*******************************************************************************
                        Functions's implementations
*******************************************************************************/ 
/******************************************************************************/
void KnightsTour(const unsigned int starting_x, const unsigned int starting_y,
			     							   unsigned int *out_solution_array)
{
	unsigned int united_index  = 0;
	unsigned int count  	   = 0;
	unsigned long bits		   = 0;
	int index 				   = 0;
	status_t status 		   = FAILURE;

	assert(out_solution_array);
	
	/* If moves_lut is not initiate - initiate it */
	if (NOT_INITIATE == g_lut)
	{
		MovesLUTInit();
		g_lut = INITIATE;
	}
	
	if (IsValidIndex((int)starting_y, (int)starting_x))
	{
		united_index = UNITE_INDECES(starting_y, starting_x);
		status = KnightsTourRec(bits, united_index, out_solution_array, &count);
	} 

	/* If FAILURE -> put INVALID_INDEX in every cell at 'solution_array' */	
	if (SUCCESS != status)
	{
		for (; index < NUM_OF_ROWS*NUM_OF_COLS; ++index)
		{
			out_solution_array[index] = INVALID_INDEX;
		}
	}

	PrintSolArr(out_solution_array);	
}
		
/***************												***************/ 
static int KnightsTourRec(unsigned long bits, unsigned int united_index, 
						  unsigned int *out_solution_array, unsigned int *count)
{
	/* Initialization of an array of 8 heuristic structs */
	heuristic_t heuristic_array[8] = {{0},{0}};
	unsigned int i 				   = 0;
 	status_t status	               = FAILURE;
 	/* Using QuickSort - option to FAIL */
	status_t heuristic_status	   = SUCCESS;
				
	assert(out_solution_array);
	assert(count);
	
	/* Turning 'ON' current bit */
	bits = BitsArraySetOn(bits, united_index);
	/* Update number of step inside 'out_array_solution' */
	out_solution_array[united_index] = *count;
	++(*count);

	/* If all cell filled with '1' */
	if (bits == BitsArrayAllOn(bits))
	{
		return (SUCCESS);
	}
	
	heuristic_status = GetHeuristicArray(united_index, bits, heuristic_array);
	if (SUCCESS != heuristic_status)
	{
		DBG(fprintf(stderr,
						 "Heuristics didn't work, proceeding without it!!!\n"));
	}

	for (i = 0; i < MOVES && SUCCESS != status; ++i)
	{
		/* If 'next_index' is VALID and set off */
		if (INVALID_INDEX != heuristic_array[i].next_index 
						  && 
			BitsArrayIsOff(bits, heuristic_array[i].next_index))
		{
			status = KnightsTourRec(bits, heuristic_array[i].next_index, 
						  			out_solution_array, count);	
		}
	}

	if (SUCCESS == status)
	{
		return (status);
	}
	
	/* If dead end -> Back tracing */
	
	bits = BitsArraySetOff(bits, moves_lut[united_index][i]);
	--(*count);		
	
	return (FAILURE);
}	
 
/***************												***************/ 
/* A function that initiates 'moves_lut' */
static void MovesLUTInit(void)
{
	int x = 0;
	int y = 0;
	
	for (y = 0; y < NUM_OF_ROWS; ++y)
	{
		for (x = 0; x < NUM_OF_COLS; ++x)
		{	
			if (IsValidIndex(y - 2, x + 1))
			{
			   	moves_lut[UNITE_INDECES(y, x)][0] = UNITE_INDECES(y - 2, x + 1);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][0] = INVALID_INDEX;
			} 

			if (IsValidIndex(y - 1, x + 2))
			{
			   	moves_lut[UNITE_INDECES(y, x)][1] = UNITE_INDECES(y - 1, x + 2);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][1] = INVALID_INDEX;
			}			
			
			if (IsValidIndex(y + 1, x + 2))
			{
			   	moves_lut[UNITE_INDECES(y, x)][2] = UNITE_INDECES(y + 1, x + 2);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][2] = INVALID_INDEX;
			}

			if (IsValidIndex(y + 2, x + 1))
			{
			   	moves_lut[UNITE_INDECES(y, x)][3] = UNITE_INDECES(y + 2, x + 1);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][3] = INVALID_INDEX;
			}

			if (IsValidIndex(y + 2, x - 1))
			{
			   	moves_lut[UNITE_INDECES(y, x)][4] = UNITE_INDECES(y + 2, x - 1);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][4] = INVALID_INDEX;
			}

			if (IsValidIndex(y + 1, x - 2))
			{
			   	moves_lut[UNITE_INDECES(y, x)][5] = UNITE_INDECES(y + 1, x - 2);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][5] = INVALID_INDEX;
			}

			if (IsValidIndex(y - 1, x - 2))
			{
			   	moves_lut[UNITE_INDECES(y, x)][6] = UNITE_INDECES(y - 1, x - 2);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][6] = INVALID_INDEX;
			}

			if (IsValidIndex(y - 2, x - 1))
			{
			   	moves_lut[UNITE_INDECES(y, x)][7] = UNITE_INDECES(y - 2, x - 1);
			}
			else
			{
				moves_lut[UNITE_INDECES(y, x)][7] = INVALID_INDEX;
			}
		}
	}
} 

/***************												***************/
/* A function that checks if a cell is on the board */ 
static int IsValidIndex(int y, int x)
{
	return ((y < 8 && y >= 0) && (x < 8 && x >= 0));
}

/***************												***************/
/* A function that initiates and sorts 'Heuristic_array' */ 
static int GetHeuristicArray(unsigned int united_index, unsigned long bits,
												   heuristic_t *heuristic_array)
{
	status_t status = SUCCESS;
	int i 			= 0;
	
	assert(heuristic_array);
	
	for (; i < MOVES; ++i)
	{
		/* Filling the fields of each struct at the array of the structs */
		heuristic_array[i].next_index = moves_lut[united_index][i];
		heuristic_array[i].degree = GetDegree(bits, moves_lut[united_index][i]);
	}
	
	/* Sorting the array of the structs according 'degree' */
	qsort(heuristic_array, 8, sizeof(heuristic_t), &Compare);
	
	return (status);
}
	
/***************												***************/ 
/* A function that calculates updated degree for an index */ 
static int GetDegree(unsigned long bits, unsigned int united_index)
{
	int next_index = 0;
	int counter    = 0;
	int i	  	   = 0;
	
	for (; i < MOVES; ++i)
	{
		next_index = moves_lut[united_index][i];
		/* If 'next_index' is VALID an set off */
		if (INVALID_INDEX != next_index && BitsArrayIsOff(bits, next_index))
		{
			++counter;
		}
	}
	
	return (counter);
}

/***************												***************/ 
/* A function that compares between to structs according to their degree */ 
static int Compare(const void *left, const void *right)
{
	assert(left);
	assert(right);
	
	return (((heuristic_t*)left)->degree - ((heuristic_t*)right)->degree);
}

/***************												***************/ 
/* A function that prints 'out_solution_array' */ 	
static void PrintSolArr(unsigned int *out_solution_array)
{
	int i = 0;
	int j = 0;
	
	assert(out_solution_array);
	
	printf("\t");
	
	for (i = 0; i < 8; ++i)
	{
		printf("%d\t", i);
	}
	
	printf("\n");
	printf("\n");
	
	for (i = 0; i < 8; ++i)
	{
		printf("%d\t", i);
		
		for (j = (i * 8); j < (i * 8) + 8; ++j)
		{
			printf("[%d]\t", out_solution_array[j]);
		}
		
		printf("\n\n");	
	}
	
	printf("\n");
}

 
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
