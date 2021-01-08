/*****************************************************************************
 * File name:   sorts.c
 * Developer:   Yaron Meister
 * Reviewer: 	
 * Date:        2018-12-14 00:38:01
 * Description: An implementation of SORTING ALGORITHMS
 *****************************************************************************/
 
#include <assert.h>      /*        assert         */
#include <string.h>		 /*		   memcpy	      */
#include <stdlib.h>		 /*		malloc, calloc	  */
#include <stdio.h>		 /*		  fprintf		  */

#include "utils.h"		 /*			DBG			  */
#include "sorts.h"       /*  Forward Declarations */

/** Macros **/
#define HEX_BASE 16
#define PARENT(index) ((index - 1) / 2)
#define LEFT_CHILD(index) ((index + 1) * 2 - 1)
#define AT(BASE, ELEMENT_SZ, INDEX) ((char*)BASE + ((ELEMENT_SZ) * (INDEX)))

typedef enum status
{
	SUCCESS,
	FAILURE
} status_t;

/****************************Forward Declarations******************************/
static void Swap(int *x, int *y);
/* For Radix Sort */
static int CountSortRadix(unsigned int *base, size_t size, unsigned int digit);
static int CountMaxDigits(unsigned int *base, size_t size);
/* For Merge Sort */
static void MergeArrays(void *arr_a, size_t size_a, void *arr_b, size_t size_b,
	                    void *merged, 
	  int(*cmp_func)(const void *left, const void *right), size_t element_size);
	  
/* For Heap Sort */
static void HeapifyUp(void *base, size_t index, void *temp, size_t element_sz,
		   int (*is_before)(const void *left, const void *right, void *param),
       															  void *param);
static void HeapifyDown(void *base, size_t index, void *temp, size_t element_sz,
		   int (*is_before)(const void *left, const void *right, void *param),
       												 void *param, size_t nmemb);       															  
static void SwapFamilyMember(void *element1, void *element2,
												 void *temp, size_t element_sz);
/* For Quick Sort */
static void QuickSortRec(void *base, void *temp, size_t nmemb,
 	   size_t element_sz, int (*cmp_func)(const void *left, const void *right));                     
static size_t FindPivotIndex(void *base, size_t nmemb, size_t element_sz,
			   		     int (*cmp_func)(const void *left, const void *right));

/*******************************************************************************
************************* Functions's Definitions ******************************
*******************************************************************************/
static void Swap(int *x, int *y)
{
    int temp = 0;

    assert(x);
    assert(y);

    temp = *x;
    *x = *y;
    *y = temp;
}

/******************************************************************************/
int *BubbleSort(int *base, size_t size)
{
    size_t i = 0;
    size_t j = 0;

    assert(base);

    for (i = 0; i < size - 1; ++i)
    {
        for (j = 0; j < size - i - 1; ++j)
        {
            if (base[j] > base[j + 1])
            {
                Swap(base + j, base + j + 1);
            }
        }
    }

    return (base);
}
    
/******************************************************************************/
int *InsertionSort(int *base, size_t size)
{
    int *checking_runner = base + 1;
    int *inserting_runner = base;
    int i = 0;

    assert(base);

    while (checking_runner < (base + size))
    {
        if (*checking_runner < *(checking_runner - 1))
        {
            while (inserting_runner < checking_runner &&
                                           *inserting_runner < *checking_runner)
            {
                ++inserting_runner;
            }

            i = checking_runner - base;

            while (base + i > inserting_runner)
            {
                Swap(base + i, base + i - 1);
                --i;
            }
            
            inserting_runner = base;
        }

        ++checking_runner;
    }
    
    return (base);
}
    
/******************************************************************************/
int *SelectionSort(int *base, size_t size)
{
    size_t min = 0;
    size_t i   = 0;
    size_t j   = 0;

    assert(base);

    for (i = 0; i < size - 1; ++i)
    {
        min = i;

        for (j = i; j < size; ++j)
        {
            if (base[j] < base[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            Swap(base + min, base + i);
        }
    }

    return (base);
}

/******************************************************************************/
int CountingSort(int *base, size_t size, size_t range)
{
	int *dest = NULL;
	int *histogram = NULL;
	int *offset = NULL;
	size_t i = 0;
	
	assert(base);
	
	dest = (int*)malloc(size * sizeof(int));
	if (NULL == dest)
	{
		DBG(fprintf(stderr, "dest's malloc failed\n"));
		
		return (FAILURE);
	}	
	
	histogram = (int*)calloc(range + 1, sizeof(int));
	if (NULL == histogram)
	{
		DBG(fprintf(stderr, "histogram's malloc failed\n"));
		free(dest);
		dest = NULL;
		return (FAILURE);
	}	
	
	offset = (int*)calloc(range + 1, sizeof(int));
	if (NULL == offset)
	{
		DBG(fprintf(stderr, "offset's malloc failed\n"));
		free(dest);
		dest = NULL;
		free(histogram);
		histogram = NULL;
		return (FAILURE);
	}	

	for (i = 0; i < size; ++i)
	{
		++(histogram[base[i]]);
	}	

	for (i = 1; i < range + 1; ++i)
	{
		offset[i] = offset[i - 1] + histogram[i - 1];
	}
	
	for (i = 0; i < size; ++i)
	{
		dest[offset[base[i]]] = base[i];
		++offset[base[i]];
	}
	
	memcpy(base, dest, size * sizeof(int));
	
	free(dest);
	free(histogram);
	free(offset);
	
	dest = NULL;
	histogram = NULL;
	offset = NULL;
	
	return (SUCCESS);
}

/******************************************************************************/
int RadixSort(unsigned int *base, size_t size)
{
	unsigned int i = 0;
	unsigned int max_digit = 0;
	
	assert(base);
	
	max_digit = CountMaxDigits(base, size);
	
	for (i = 0; i < max_digit; ++i)
	{
		if (SUCCESS != CountSortRadix(base, size, i))
		{
			return (FAILURE);
		}
	}
	
	return (SUCCESS);
}
	
/******************************************************************************/
static int CountSortRadix(unsigned int *base, size_t size, unsigned int digit)
{
	int *dest = NULL;
	int histogram[HEX_BASE] = {0};
	int offset[HEX_BASE]    = {0};
	unsigned int temp = 0;
	size_t i          = 0;
	
	assert(base);
	
	dest = (int*)malloc(size * sizeof(int));
	if (NULL == dest)
	{
		DBG(fprintf(stderr, "dest's malloc failed\n"));
		
		return (FAILURE);
	}		

	for (i = 0; i < size; ++i)
	{
		temp = ((base[i]) >> (4 * digit)) & (0xF); 
		++(histogram[temp]);
	}	

	for (i = 1; i < HEX_BASE; ++i)
	{
		offset[i] = offset[i - 1] + histogram[i - 1];
	}
	
	for (i = 0; i < size; ++i)
	{
		temp = ((base[i]) >> (4 * digit)) & (0xF);
		dest[offset[temp]] = base[i];
		++offset[temp];
	}
	
	memcpy(base, dest, size * sizeof(int));
	
	free(dest);
	dest = NULL;
		
	return (SUCCESS);
}

/******************************************************************************/	
static int CountMaxDigits(unsigned int *base, size_t size)
{
	unsigned int max = 0;
	int count = 0;
	size_t i = 1;

	assert(base);
	
	max = base[0];
	
	while (i < size)
	{
		if (max < base[i])
		{
			max = base[i];
		}
		
		++i;
	}
	
	while (max > 0)
	{
		++count;
		max >>= 4;
	}
	
	return (count);
} 
	
/******************************************************************************/
int MergeSort(void *base, size_t num_of_elements, size_t element_size,
	int(*cmp_func)(const void *left, const void *right))
{
	int status = SUCCESS;
	size_t half_size = 0;
	void *merged_array = NULL;
	
	assert(base);
	assert(cmp_func);

	if (1 == num_of_elements)
	{
		return (SUCCESS);
	}
	
	half_size = num_of_elements / 2;
	/* Recursive call on left part */
	status = MergeSort(base, half_size, element_size, cmp_func);
	
	if (FAILURE != status)
	{
		/* Recursive call on right part */
		status = MergeSort((char*)base + half_size * element_size,
		 	               num_of_elements - half_size, element_size, cmp_func);
	}
	
	merged_array = malloc(num_of_elements * element_size);
	if (NULL == merged_array)
	{
		DBG(fprintf(stderr, "malloc failed\n"));
		return (FAILURE);
	}
	
	/* Merging parts */
	MergeArrays(base, half_size, (char*)base + half_size * element_size,
		     num_of_elements - half_size, merged_array, cmp_func, element_size);
	/* Copying for base */
	memcpy(base, merged_array, num_of_elements * element_size);
	free(merged_array);
	merged_array = NULL;
	
	return (status);
}

/******************************************************************************/
static void MergeArrays(void *arr_a, size_t size_a, void *arr_b, size_t size_b,
			           											  void *merged, 
	   int(*cmp_func)(const void *left, const void *right), size_t element_size)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	
	assert(arr_a);
	assert(arr_b);
	assert(merged);
	assert(cmp_func);
	
	while (i < size_a && j < size_b)
	{
		if (cmp_func((char*)arr_a + i * element_size,
										   (char*)arr_b + j * element_size) < 0)
		{
			memcpy((char*)merged + k * element_size,
								 (char*)arr_a + i * element_size, element_size);
			++i;
		}
		else
		{
			memcpy((char*)merged + k * element_size,
								 (char*)arr_b + j * element_size, element_size);
			++j;
		}
		
		++k;
	}
	
	if (i < size_a)
	{
		memcpy((char*)merged + k * element_size,
			      (char*)arr_a + i * element_size, (size_a - i) * element_size);
	}
	
	if (j < size_b)
	{
		memcpy((char*)merged + k * element_size,
				  (char*)arr_b + j * element_size, (size_b - j) * element_size);
	}
	
}

/******************************************************************************/
int HeapSort(void *base, size_t nmemb, size_t element_sz,
        int (*is_before)(const void *left, const void *right, void *param),
        void *param)
{
		/*
		 * 1. Heapify the array
		 
		 	  while (resizing > 1):
		 * 2. Swap between the root and the last element
		 * 3. resize the size of the array
		 * 4. Heapify Down the root
		*/
		
	status_t status = FAILURE;
	size_t index    = 0;					/* Iterator */
	void *temp      = malloc(element_sz);	/*  Buffer  */
	
	assert(base);
	assert(nmemb);
	assert(element_sz);
	assert(is_before);
	
	if (NULL != temp)
	{
		status = SUCCESS;
		
		for (; index < nmemb; ++index)
		{
			/* Heapify the array */
			HeapifyUp(base, index, temp, element_sz, is_before, param);
		}
	
		while (nmemb > 1)
		{
			SwapFamilyMember((char*)base + 0,
				 	  (char*)base + (nmemb - 1) * element_sz, temp, element_sz);
			--nmemb;
			HeapifyDown(base, 0, temp, element_sz, is_before, param, nmemb);
		}
	}
	
	free(temp);
	temp = NULL;

	return (status);
}
		
/*********															***********/
/* A function that push up a value according to Heap policy if necessary */
static void HeapifyUp(void *base, size_t index, void *temp, size_t element_sz,
		   int (*is_before)(const void *left, const void *right, void *param),
       															  void *param)
{	
	assert(base);
	assert(temp);
	assert(element_sz);
	assert(is_before);
	
	while (index > 0)
	{
		/* If 'index' is before his parent */
		if (is_before((char*)base + index * element_sz,
							   (char*)base + PARENT(index) * element_sz, param))
        {
        	/* Swap between them */
        	SwapFamilyMember((char*)base + index * element_sz,
        			(char*)base + PARENT(index) * element_sz, temp, element_sz);
    	}
    	
    	index = PARENT(index);	/* index = index's parent */		
	}	
}

/*********															***********/
static void SwapFamilyMember(void *element1, void *element2,
												  void *temp, size_t element_sz)
{
	memcpy(temp, element1, element_sz);
	memcpy(element1, element2, element_sz);
	memcpy(element2, temp, element_sz);
}	
		
/*********															***********/
/* A function that push down a value according to Heap policy if necessary */	
static void HeapifyDown(void *base, size_t index, void *temp, size_t element_sz,
		   int (*is_before)(const void *left, const void *right, void *param),
       												  void *param, size_t nmemb)	
{
	size_t left_index  	= LEFT_CHILD(index);
	size_t right_index 	= left_index + 1;
	size_t max_value_index = index;				
	
	assert(base);
	assert(temp);
	assert(element_sz);
	assert(is_before);
	
	/* While 'index' has at least one child */
	while (left_index < nmemb)
	{
		/* If there is a left child and he is before */ 
		if (is_before((char*)base + left_index * element_sz,
									   (char*)base + index * element_sz, param))
		{
			max_value_index = left_index;
		}
	
		/* If there is a right child and he is before 'max_value_index' */ 
		if (right_index < nmemb &&
			is_before((char*)base + right_index * element_sz,
							 (char*)base + max_value_index * element_sz, param))
		{
			max_value_index = right_index;
		}
	
		/* If swapping is necessary */ 
		if (max_value_index != index)
		{
			SwapFamilyMember((char*)base + index * element_sz,
				  (char*)base + max_value_index * element_sz, temp, element_sz);
		}
		/* If swapping is NOT necessary, return */
		else
		{
			break;
		}
	
		index 		= max_value_index;
		left_index  = LEFT_CHILD(index);
		right_index = left_index + 1;
	}
}

/******************************************************************************/	
int QuickSort(void *base, size_t nmemb, size_t element_sz,
      		               int (*cmp_func)(const void *left, const void *right))
{
		/*
		 * 1. Find a pivot	 
		 * 2. Take the pivot to the end
		 
		 while left runner < right runner
		 * 3. Find the first member from left that is greater than pivot
		 * 4. Find the first member from right that is lower than pivot
		 * 5. Swap between them
		 * 6. Swap between pivot and the first from left that is greater
		 * 7. Recursive call above left sub-array
		 * 8. Recursive call above right sub-array
		*/
		
	status_t status = FAILURE;
	void *temp      = malloc(element_sz);	/*  Buffer  */
	
	assert(base);
	assert(nmemb);
	assert(element_sz);
	assert(cmp_func);
	
	if (NULL != temp)
	{
		status = SUCCESS;
		QuickSortRec(base, temp, nmemb, element_sz, cmp_func);	
	}
	
	free(temp);
	temp = NULL;

	return (status);
}		              
   
/*********															***********/                  
static void QuickSortRec(void *base, void *temp, size_t nmemb,
 		size_t element_sz, int (*cmp_func)(const void *left, const void *right))                 
{
	size_t first = 0;				/* First index */
    size_t last  = nmemb - 1;		/* Last index */
    void *left	 = NULL;			/* Runner for sorting */
    void *right  = NULL;			/* Runner for sorting */
    size_t pivot = 0;				/* Index of pivot */
                 
	if (nmemb < 2)
	{
		return;
	}
	 
	pivot = FindPivotIndex(base, nmemb, element_sz, cmp_func);
	
	/* Taking 'pivot' to the end */
	if (pivot != last)
	{
		SwapFamilyMember(AT(base, element_sz, last),
		                 AT(base, element_sz, pivot), temp, element_sz);
    }
		
	pivot = last;
	left  = AT(base, element_sz, first);
	/* Right runner is the one before the pivot (one before the end) */
	right = AT(base, element_sz, last - 1);
	
	while (left < right)
	{
/* I am looking for the first element from left that is greater than pivot */
		while (cmp_func(AT(base, element_sz, pivot), left) > 0
									 &&
			   left < (void*)((char*)base + pivot * element_sz))
		{
			left = (char*)left + element_sz;
		}
/* I am looking for the first element from right that is lower than pivot */       
        while (cmp_func(AT(base, element_sz, pivot), right) < 0 
        							&&
         					  right > base)
		{
			right = (char*)right - element_sz;
		}         
    /* If swapping is required */
    	if (left < right)
    	{
    		SwapFamilyMember(left, right, temp, element_sz);
    		left = (char*)left + element_sz;
      		right = (char*)right - element_sz;
		}
	}
	
/* Now, swapping is required between pivot and the first element from left
												   that is greater than pivot */
	left = base;
	
/* while 'left valufe' is lower than 'pivot value' and
											     'left' is lower than 'pivot' */
	while (cmp_func(AT(base, element_sz, pivot), left) > 0
									 &&
			 left < (void*)(AT(base, element_sz, pivot)))
	{
		left = (char*)left + element_sz;
	}
	/* If the loop stopped when left != pivot */	
	if (left != AT(base, element_sz, pivot))
	{
		SwapFamilyMember(left, AT(base, element_sz, pivot), temp, element_sz);
		pivot = ((char*)left - (char*)base) / element_sz;
		/* Recursive call above left sub-array */
		QuickSortRec(base, temp, pivot, element_sz, cmp_func);
		/* Recursive call above right sub-array */
		QuickSortRec(AT(base, element_sz, pivot + 1), temp,
								     (nmemb - 1) - pivot, element_sz, cmp_func);
    }
}          
                 
/*********															***********/               
static size_t FindPivotIndex(void *base, size_t nmemb, size_t element_sz,
						  int (*cmp_func)(const void *left, const void *right))
{
	/*
	 * 1. Take the first, last and mid elements in the array
	 * 2. Find the one with the mid value inside
	 * 3. return it
	*/
	
	size_t first = 0;
	size_t mid   = (nmemb - 1) / 2;
	size_t last  = nmemb - 1;
	size_t pivot = mid;
	
	/* If 'first' and 'last' are smaller than mid */
	if (cmp_func(AT(base, element_sz, first),
	 			 AT(base, element_sz, mid)) < 0 
							&&
		cmp_func(AT(base, element_sz, last),
	 			 AT(base, element_sz, mid)) < 0)
	{
		/* If 'first' is smaller than 'last' - 'last' is at the middle */ 
		if (cmp_func(AT(base, element_sz, first),
	 			 AT(base, element_sz, last)) < 0)
		{
			pivot = last;
		}
		/* else - 'first' is at the middle */ 
		else
		{
			pivot = first;
		}
	}
	/* If 'first' and 'last' are bigger than mid */
	else if (cmp_func(AT(base, element_sz, first),
	 			 AT(base, element_sz, mid)) > 0 
							&&
		cmp_func(AT(base, element_sz, last), AT(base, element_sz, mid)) > 0)
	{
		/* If 'first' is bigger than 'last' - 'last' is at the middle */ 
		if (cmp_func(AT(base, element_sz, first),
	 			 AT(base, element_sz, last)) > 0)
		{
			pivot = last;
		}
		/* else - 'first' is at the middle */ 
		else
		{
			pivot = first;
		}
	}
	
	return (pivot);
}				
	                                     
                                                     
                  
                  
			
/*******************************************************************************
******************************* END OF FILE ************************************
*******************************************************************************/
