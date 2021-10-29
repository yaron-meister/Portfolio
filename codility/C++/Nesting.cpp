/*****************************************************************************
* File name:   Nesting.cpp
* Developer:   Yaron Meister
* Date:        2021-02-05
* Description: A solution for the codility task "Nesting"
*****************************************************************************/

#include <stack>

using namespace std;

int Solution(string& S){
    // write your code in C++14 (g++ 6.2.0)
    bool properlyNested(true);
    stack<char> brackets;
    string::iterator it;

    for (it = S.begin(); it != S.end() && true == properlyNested; ++it)
    {
        switch (*it)
        {
            case '(':
                brackets.push(')');
            break;

            case ')':
                if (!brackets.empty())
                {
                    brackets.pop();
                }
                else
                {
                    properlyNested = false;
                }
            break;

            default:
                properlyNested = false;
            break;
        }
    }

    if (!brackets.empty())
    {
        properlyNested = false;
    }

    return (properlyNested);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 