/*****************************************************************************
* File name:   Distinct.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Distict"
*****************************************************************************/

#include <cstdlib>

int Compare(const void* a, const void* b);

int solution(vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    size_t sizeA(A.size());
    int distinctValesNum(0 != sizeA);

    if (sizeA > 0)
    {
        qsort(&A[0], sizeA, sizeof(int), Compare);
        int tempVal(A[0]);

        for (unsigned int idx(0); idx < sizeA; ++idx)
        {
            if (A[idx] != tempVal)
            {
                ++distinctValuesNum;
                tempVal = A[idx];
            }
        }
    }

    return (distinctValuesNum);
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