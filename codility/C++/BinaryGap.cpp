/*****************************************************************************
* File name:   BinaryGap.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "BinaryGap"
*****************************************************************************/

int Solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
    int maxBinaryGap(0);
    int tempBinaryGap(0);

    if (0 != N)
    {
        while (0 == (N & 1))
        {
            N = N >> 1;
        }

        N = N >> 1;

        while (0 != N)
        {
            while (0 == (N & 1))
            {
                ++tempBinaryGap;
                N = N >> 1;
            }

            if (tempBinaryGap > maxBinaryGap)
            {
                maxBinaryGap = tempBinaryGap;
            }

            tempBinaryGap = 0;
            N = N >> 1;
        }
    }

    return (maxBinaryGap);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/