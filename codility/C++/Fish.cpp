/*****************************************************************************
* File name:   Fish.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Fish"
*****************************************************************************/

#include <stack>

int Solution(vector<int>& A, vector<int>& B)
{
  // write your code in C++14 (g++ 6.2.0)

  size_t sizeA(A.size());
  size_t idx(0);
  stack<size_t> indeces;

  while (idx < sizeA)
  {
    if (indeces.empty() || 1 != B[indeces.top()] || 0 != B[idx])
    {
      indeces.push(idx);
      ++idx;
    }
    else
    {
      if (A[indeces.top()] < A[idx])
      {
        indeces.pop();
      }
      else
      {
        ++idx;
      }
    }
  }

  return (static_cast<int>(indeces.size()));
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 