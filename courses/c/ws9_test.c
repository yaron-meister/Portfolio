/*****************************************************************************
 * File name:   ws9_test.c
 * Developer:   Yaron
 * Reviewer:    Daria
 * Date:        2018-10-30 16:10:50
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* free         */
#include <stddef.h>    /* size_t       */

#include "ws9.h"       /*              */


/* Macros                  */
#define IS_LITTLE (1 == *(unsigned short*)"\1")                                         /* בקסלש 1 זה אוקטאל 1 */

/* Forward Declarations    */
 
/* Global variables        */
 

/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{
    const int num1 = -12543;
    char str1[12] = {0};
    const char str2[] = "-25fr6";
    char str3[] = "Hello";
    char str4[] = "beautiful";
    char str5[] = "world";
    char str6[] = "My name is Yaron";
    char str7[] = "Have a nice day";
    char destination1[] = "shsghdghdghghghdghdhdhdhdfh";
    char destination2[] = "yyrurururririiririririririr";
    int ch = 'c';
    size_t num = 13;
    char *dest = NULL;
    printf("num = %s\n", Int2Str10(str1, num1));
    printf("num = %s\n", Int2Str(str1, num1, 16));
    printf("num = %d\n", Str2Int(str2));
    dest = AppearesIn2(str3, str4, str5, 6, 10, 6);
    printf("The matched chars in str3 and str4 are: %s\n", dest);
    free(dest);
    Memset((void*)str6, ch, num);
    printf("After set, the string is: %s\n", str6);
    Memcpy((void*)destination1, (void*)str7, 10);
    printf("After copying with Memcpy, destination1 is: %s\n", destination1);
    Memmove((void*)destination2, (void*)str7, 10);
    printf("After copying with Memmove, destination2 is: %s\n", destination2);
    
    if (IsALittleEndian())
    {
        printf("This system is a LITTLE endian\n");
    }
    else
    {
        printf("This system is a BIG endian\n");  
    }
    
    if (IS_LITTLE)
    {
        printf("This system is a LITTLE endian\n");
    }
    else
    {
        printf("This system is a BIG endian\n");  
    }
        
    return (0);
}
  
