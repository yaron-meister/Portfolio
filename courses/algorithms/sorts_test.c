/*****************************************************************************
 * File name:   sorts_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	
 * Date:        2018-12-14 00:38:01
 *****************************************************************************/
 
#include <stdio.h>              /*       printf         */
#include <stdlib.h>             /*  EXIT_SUCCESS, qsort */
#include <time.h>	   		    /*	     clock	        */
#include <assert.h>			    /*		 assert		    */

#include "utils.h"				/*	  UNUSED_VAR		*/
#include "sorts.h"     		    /* Forward Declarations */



/**************************** Forward Declarations ****************************/
static int Compare(const void *left, const void *right);
static int IsBefore(const void *left, const void *right, void *param);
static void PrintArray(int *arr, size_t arr_size, int arr_num);
/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{ 
	clock_t time   =  0 ;
    int arr1[5000] = {0};
    int arr2[5000] = {0};
    int arr3[5000] = {0};
    int arr4[5000] = {0};
    unsigned int arr5[5000] = {0};
    int arr6[5000] = {0};
    int arr7[5000] = {0};
    int arr8[5000] = {0};
    int arr9[5000] = {0};
    int i = 0;

	for (i = 0; i < 5000; ++i)
	{
		arr1[i] = rand() % 101;
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		arr4[i] = arr1[i];
		arr5[i] = arr1[i];
		arr6[i] = arr1[i];
		arr7[i] = arr1[i];
		arr8[i] = arr1[i];
		arr9[i] = arr1[i];		
	}
	
	printf("\n");
  	printf("*****************************************************************");
  	printf("\n");
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n");
  	printf("*****************************************************************");
  	printf("\n");
  	printf("\n");
	
	printf("\n******************* BUBBLE-SORT *****************************\n");	
	time = clock();
	BubbleSort(arr1, 5000);
	time = clock() - time;
	printf("BubbleSort    made it in %f seconds\n",
												 ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr1, 5000, 1);

	printf("\n***************** SELECTION-SORT ****************************\n");	
	time = clock();
    SelectionSort(arr2, 5000);
	time = clock() - time;
	printf("SelectionSort made it in %f seconds\n",
												 ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr2, 5000, 2);

	printf("\n***************** INSERTION-SORT ****************************\n");	
	time = clock();
    InsertionSort(arr3, 5000);
	time = clock() - time;
	printf("InsertionSort made it in %f seconds\n",
												 ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr3, 5000, 3);
    
  	printf("\n******************* COUNTING-SORT ***************************\n");
	time = clock();
	CountingSort(arr4, 5000, 100);
	time = clock() - time;
	printf("CountingSort made it in %f seconds\n",((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr4, 5000, 4);
    
    printf("\n******************* RADIX-SORT ******************************\n");
	time = clock();
	RadixSort(arr5, 5000);
	time = clock() - time;
	printf("RadixSort made it in %f seconds\n", ((double)time)/CLOCKS_PER_SEC);
	printf("The sorted array5 is:\n[ ");

	for (i = 4990; i < 5000; ++i)
	{
		printf("%d ", arr5[i]);
	}

	printf("]\n");
    
    printf("\n******************* MERGE-SORT ******************************\n");
	time = clock();
	MergeSort(arr6, 5000, sizeof(int), &Compare);
	time = clock() - time;
	printf("MergeSort made it in %f seconds\n", ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr6, 5000, 6);
    
    printf("\n********************* Q-SORT ********************************\n");
	time = clock();
	qsort(arr7, 5000, sizeof(int), &Compare);
	time = clock() - time;
	printf("qSort made it in %f seconds\n", ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr7, 5000, 7);

	printf("\n******************** HEAP-SORT ******************************\n");
	time = clock();
	HeapSort(arr8, 5000, sizeof(int), &IsBefore, NULL);
	time = clock() - time;
	printf("HeapSort made it in %f seconds\n", ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr8, 5000, 8);
	
	printf("\n******************* QUICK-SORT ******************************\n");
	time = clock();
	qsort(arr9, 5000, sizeof(int), &Compare);
	time = clock() - time;
	printf("QuickSort made it in %f seconds\n", ((double)time)/CLOCKS_PER_SEC);
	PrintArray(arr9, 5000, 9);

	return (EXIT_SUCCESS);
}

/******************************************************************************/
static int Compare(const void *left, const void *right)
{
	return (*(int*)left - *(int*)right);
}

/******************************************************************************/
static int IsBefore(const void *left, const void *right, void *param)
{
	assert(left);
	assert(right);
	
	UNUSED_VAR(param);
	
	return (*(int*)left > *(int*)right);
}

/******************************************************************************/
static void PrintArray(int *arr, size_t arr_size, int arr_num)
{
	size_t i = 0;
	
	assert(arr);
	
	printf("The sorted array%d is:\n[ ", arr_num);

	while ((arr_size - i) >=0 && i < 10)
    {
        printf("%d ", arr[arr_size - 1 - i]);
        ++i;
    }

    printf("]\n");
}


/******************************************************************************/
/****************************** END OF FILE ***********************************/
/******************************************************************************/
