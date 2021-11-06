/*****************************************************************************
* File name:   OddOccurrencesInArray.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Odd Occurrences In Array"
*****************************************************************************/

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)

    int oddValue(A[0]);
    size_t sizeA(A.size());

    for (size_t idx(1); idx < sizeA; ++idx)
    {
        oddValue ^= A[idx];
    }

    return (oddValue);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/