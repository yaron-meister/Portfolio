/*****************************************************************************
* File name:   CyclicRotation.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Cyclic Rotation"
*****************************************************************************/

vector<int> Solution(vector<int> &A, int K) {
    // write your code in C++14 (g++ 6.2.0)
    size_t sizeA(A.size());
    
    if (0 != sizeA && 0 != K && K != sizeA)
    {
        int tempVal(A[sizeA - 1]);

        if (sizeA < K)
        {
            K %= sizeA;
        }

        for (int i(0); i < K; ++i)
        {
            for (int j(sizeA - 2); j >= 0; --j)
            {
                A[j + 1] = A[j];
            }

            A[0] = tempVal;
            tempVal = A[sizeA - 1];
        }
    }

    return (A);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/