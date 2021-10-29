/*****************************************************************************
* File name:   Triangle.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Triangle"
*****************************************************************************/

int Compare(const void* a, const void* b);
bool IsTriangle(int a, int b, int c);

int Solution(vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    size_t sizeA(A.size());
    int thereIsTri(false);

    if (sizeA > 2)
    {
        qsort(&A[0], sizeA, sizeof(int), Compare);

        for (unsigned int idx(0); idx < sizeA - 2 && !thereIsTri; ++idx)
        {
            thereIsTri = IsTriangle(A[idx], A[idx + 1], A[idx + 2]);
        }
    }

    return (thereIsTri);
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

bool IsTriangle(int a, int b, int c)
{
    return ((a > 0 && b > 0 && c > 0) &&
    ((a + b) > c || (a + b) < a) &&
    ((b + c) > a || (b + c) < b) &&
    ((a + c) > b || (a + c) < c));
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/