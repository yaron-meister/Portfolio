/*****************************************************************************
* File name:   FrogRiverOne.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Frog River One"
*****************************************************************************/

int Solution(int X, vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    int sizeA(A.size());
    vector<int> B(100001, -1);

    int idx(0);
    for (; idx < sizeA; ++idx)
    {
        if (-1 == B[A[idx]])
        {
            B[A[idx]] = idx;
        }
    }

    int earliestTime(-1);

    if (X > 0 && X <= 100000)
    {
        for (idx = 1; idx <= X && -1 != B[idx]; ++idx)
        {
            if (earliestTime < B[idx])
            {
                earliestTime = B[idx];
            }
        }

        if (idx <= X)
        {
            earliestTime = -1;
        }
    }

    return (earliestTime);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 