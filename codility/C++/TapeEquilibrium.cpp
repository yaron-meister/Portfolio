/*****************************************************************************
* File name:   TapeEquilibrium.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Tape Equilibrium"
*****************************************************************************/

int Solution(vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    unsigned int sizeA(A.size());
    vector<int> sums(sizeA - 1, 0);
    int rightSum(A[0]);
    int leftSum(0);
    unsigned idx(1);

    for (; idx < sizeA; ++idx)
    {
        leftSum += A[idx];
    }

    for (idx = 0; idx < sizeA - 1; ++idx)
    {
        sums[idx] = abs(leftSum - rightSum);
        rightSum += A[idx + 1];
        leftSum -= A[idx + 1];
    }

    int minDiff(sums[0]);

    for (idx = 0; idx < sizeA - 1; ++idx)
    {
        if (minDiff > sums[idx])
        {
            minDiff = sums[idx];
        }
    }

    return (minDiff);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 