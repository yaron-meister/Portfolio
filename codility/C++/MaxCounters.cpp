/*****************************************************************************
* File name:   MaxCounters.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Max Counters"
*****************************************************************************/

static int maxVal(0);
static int tempMaxVal(0);

void increase(int& X);

vector<int>  Solution(int N, vector<int>& A){
    // write your code in C++14 (g++ 6.2.0)
    size_t sizeA(A.size());
    vector<int> counters(N, 0);
    unsigned idx(0);
    int maxIndex(0);

    for (; idx < sizeA; ++idx)
    {
        if (A[idx] <= N)
        {
            increase(counters[A[idx] - 1]);
        }
        else
        {
            maxIndex = idx;
            maxVal = tempMaxVal;
        }
    }

    size_t sizeCounters(counters.size());

    for (idx = 0; idx < sizeCounters; ++idx)
    {
        counters[idx] = maxVal;
    }

    for (idx = maxIndex; idx < sizeA; ++idx)
    {
        ++(counters[A[idx] - 1]);
    }

    return (counters);
}

void increase(int& X)
{
    if (X < maxVal)
    {
        X = maxVal;
    }

    ++X;

    if (X > tempMaxVal)
    {
        tempMaxVal = X;
    }
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 