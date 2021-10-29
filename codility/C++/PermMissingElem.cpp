/*****************************************************************************
* File name:   PermMissingElem.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Perm Missing Elem"
*****************************************************************************/

int Solution(vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)

    size_t sizeA(A.size());
    int retVal(0);

    if (sizeA <= 100000)
    {
        vector<bool> B(sizeA + 1, false);
        unsigned idx(0);

        for (; idx < sizeA; ++idx)
        {
            B[A[idx] - 1] = true;
        }

        idx = 0;

        while (true == B[idx])
        {
            ++idx;
        }

        retVal = idx + 1;
    }

    return (retVal);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 