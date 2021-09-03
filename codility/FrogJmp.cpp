/*****************************************************************************
* File name:   FrogJmp.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Frog Jump"
*****************************************************************************/

bool IsValid(int num);

int Solution(int X, int Y, int D)
{
  // write your code in C++14 (g++ 6.2.0)

  int retVal(0);

  if (IsValid(X) && IsValid(Y) && IsValid(D) && X <= Y)
  {
    int diff(Y - X);

    retVal = (diff / D);
    retVal += ((diff % D) ? 1 : 0);
  }

  return (retVal);
}

bool IsValid(int num)
{
  return (num > 0 && num <= 1000000000);
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 