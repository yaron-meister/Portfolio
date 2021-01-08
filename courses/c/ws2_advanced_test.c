/*****************************************************************************
 * Project:     WS2_Advanced                                                  *
 * Date:        17.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Sandra                                                        *
 *                                                                            *
 *  This program does 5 main things:                                          *
 *   - Checking if a given string is a PALINDROME                             *
 *   - Displaying the game "7 BOOM"                                           *
 *   - Swaps between two int-pointers                                         *
 *   - Fixes a sentence with too many BLANK SPACES                            *
 *   - Calculates the sum of two BIG NUMBERS                                  *                                          
 *                                                                            *
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


#include <stdio.h>    /* printf */ 
#include <string.h>   /* all string functions */ 

#include "ws2.h"


void IsPalindrom_test(void);
void SevenBoom_test(void);
void PoiSwap_test(void);
void RmSpaces_test(void);
void BigAdd_test(void);


int main(void)
{
    IsPalindrom_test();
    SevenBoom_test();
    PoiSwap_test();
    RmSpaces_test();
    BigAdd_test();
   
    return 0;
} 




   /************************************************************/  
  
void IsPalindrom_test(void)
{
    char str1[] = "abba";
    char str2[] = "abcba";
    char str3[] = "abcde";
    if (IsPalindrom(str1))
    {
        printf("\n%s is a palindrom\n", str1);
    }
    else
    {
        printf("\n%s is NOT a palindrom\n", str1);
    }
    if (IsPalindrom(str2))
    {
        printf("\n%s is a palindrom\n", str2);
    }
    else
    {
        printf("\n%s is NOT a palindrom\n", str2);
    }
    if (IsPalindrom(str3))
    {
        printf("\n%s is a palindrom\n", str3);
    }
    else
    {
        printf("\n%s is NOT a palindrom\n", str3);
    }
}


   /************************************************************/ 
   
void SevenBoom_test(void)
{
    SevenBoom(50, 80);
}


   /************************************************************/ 

void PoiSwap_test(void)
{
    int a = 3;
    int b = 5;
    int *pa = &a;
    int *pb = &b;
    printf("pa points to: %p and the value inside is: %d\n", (void*) pa, *pa);
    printf("pb points to: %p and the value inside is: %d\n", (void*) pb, *pb);
    PoiSwap(&pa, &pb);
    printf("and after swaping:\n");
    printf("pa points to: %p and the value inside is: %d\n", (void*) pa, *pa);
    printf("pb points to: %p and the value inside is: %d\n\n", (void*) pb, *pb);

}


   /************************************************************/ 
   
void RmSpaces_test(void)
{
    char src[] = "      Hello    world              !";
    char dest[100];
    printf("\nThe NON-FIXED sentence is: %s\n", src);
    RmSpaces(dest, src);    
    printf("The fixed sentence is: %s\n", dest);
}


   /************************************************************/ 

void BigAdd_test(void)
{
    const char A[] = "14587";
    const char B[] = "2548763";
    char sum[9];    
    printf("\nThe sum of %s + %s = ", A, B);
    BigAdd(A, B, sum);
    printf("%s\n", sum);
}

