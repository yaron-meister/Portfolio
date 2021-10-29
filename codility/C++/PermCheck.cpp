/*****************************************************************************
* File name:   PermCheck.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "PermCheck"
*****************************************************************************/

int Solution(vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    size_t sizeA(A.size());
    int result(A[0] ^ 1);

    for (size_t idx(1); idx < sizeA; ++idx)
    {
        result ^= (A[idx] ^ (idx + 1));
    }

    return (0 == result);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 