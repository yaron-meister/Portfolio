/*****************************************************************************
* File name:   MaxProductOfThree.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Max Number Of Three"
*****************************************************************************/

#include <cstdlib>
#include <vector>

int Compare(const void* a, const void* b);

int Solution(vector<int>& A)
{
  // write your code in C++14 (g++ 6.2.0)

  size_t sizeA(A.size());

  qsort(&A[0], sizeA, sizeof(int), Compare);

  int firstPro(A[sizeA - 1] * A[sizeA - 2] * A[sizeA - 3]);
  int secondPro(A[0] * A[1] * A[2]);
  int thirdPro(A[0] * A[1] * A[sizeA - 1]);
  int fourthPro(A[0] * A[sizeA - 1] * A[sizeA - 2]);

  int max(firstPro);
  if (secondPro > max)
  {
    max = secondPro;
  }
  if (thirdPro > max)
  {
    max = thirdPro;
  }
  if (fourthPro > max)
  {
    max = fourthPro;
  }

  return (max);
}

int Compare(const void* a, const void* b)
{
  int retVal;

  if (*(int*)a < *(int*)b)
  {
    retVal = -1;
  }
  else if (*(int*)a == *(int*)b)
  {
    retVal = 0;
  }
  else
  {
    retVal = 1;
  }

  return (retVal);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 