/*****************************************************************************
 * File name:   ws9.c
 * Developer:   Yaron
 * Reviewer:    Daria
 * Date:        2018-10-30 16:10:50
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <assert.h>    /* assert       */
#include <string.h>    /* strlen       */
#include <stddef.h>    /* size_t       */
#include <stdlib.h>    /* free         */

#include "ws9.h"       /*              */


/* Macros                  */
#define BYTE 8
#define UNUSED_VAR(x) (void)(x) 
#define SIZE_OF_ASCII_ARRAY 256

/* Forward Declarations    */
 
 
/* Global variables        */



/******************************************************************************/ 
void *Memset(void *str, int ch, size_t num)
{
    long word = 0;                 /* Machine word size all filled with 'ch' */
    unsigned int i = 0;
    void *runner = str;

    assert(str);
 
    /* filling word with 'ch' */   
    for (i = 0; i < sizeof(long); ++i)
    {
        word <<= BYTE;          
        word |= ch;
    }
    
    i = 0;

    /* Handling head of unaligned str */    
    while ((0 != (*(unsigned int*)&runner & 0x7)) && (i < num))
    {
        *(char*)runner = (char) ch;
        runner = (char*)runner + 1;
        ++i;
    }

    /* Handling aligned part of str */        
    while ((num - i) > sizeof(long))
    {
        *(long*)runner = word;
        runner = (char*)runner + sizeof(long);
        i += sizeof(long);
    }

    /* Handling tail of unaligned str */       
    while ( ('\0' != *(char*)runner) && i < num)
    {
        *(char*)runner = (char)ch;
        runner = (char*)runner + 1;
        ++i;  
    }
    
    return (str);
}
    
/******************************************************************************/     
void *Memcpy(void *dest, const void *src, size_t num)
{
    unsigned int i = 0;
    void *runner_s = (void*)src;        /* Runner of src  */
    void *runner_d = dest;              /* Runner of dest */
    
    assert(dest);
    assert(src);

    /* Handling head of unaligned dest */           
    while ((0 != (*(unsigned int*)&runner_d & 0x7)) && (i < num))
    {
        *(char*)runner_d = *(char*)runner_s;
        runner_s = (char*)runner_s + 1;
        runner_d = (char*)runner_d + 1;
        ++i;  
    }
 
    /* Handling aligned part of dest */           
    while ((num - i) > sizeof(long))
    {
        *(long*)runner_d = *(long*)runner_s;
        runner_s = (char*)runner_s + sizeof(long);
        runner_d = (char*)runner_d + sizeof(long);
        i += sizeof(long);
    }

    /* Handling tail of unaligned dest */           
    while ( ('\0' != *(char*)runner_s) && i < num)
    {
        *(char*)runner_d = *(char*)runner_s;
        runner_s = (char*)runner_s + 1;
        runner_d = (char*)runner_d + 1;
        ++i;  
    }
      
    return (dest);
}   
    
/******************************************************************************/
    
void *Memmove(void *dest, const void *src, size_t num)   
{
    unsigned int i = 0;
    unsigned int length = 0;            /* Length of src  */
    void *runner_s = NULL;              /* Runner of src  */
    void *runner_d = NULL;              /* Runner of dest */
    
    assert(dest);
    assert(src);

    /* If &dest is earlier then &src */   
    if (dest < src)
    {
        runner_s = (char*)src;
        runner_d = dest;
        Memcpy(dest, src, num);
    }
    else
    {
        length = strlen((char*)src);
        
        /* If num is longer than the src str */
        while (num > length)        
        {
            --num;
        }
        
        runner_s = (char*)src + num;
        runner_d = (char*)dest + num;

        /* Handling tail of unaligned dest */                   
        while ((0 != (*(unsigned int*)&runner_d & 0x7)) && (i < num))
        {
            runner_s = (char*)runner_s - 1;
            runner_d = (char*)runner_d - 1;
            *(char*)runner_d = *(char*)runner_s;
            ++i;  
        }

        /* Handling aligned part of dest */               
        while ((num - i) > sizeof(long))
        {
            runner_s = (char*)runner_s - sizeof(long);
            runner_d = (char*)runner_d - sizeof(long);
            *(long*)runner_d = *(long*)runner_s;
            i += sizeof(long);
        }

        /* Handling head of unaligned dest */                   
        while ( (dest < runner_d) && i < num)
        {
            runner_s = (char*)runner_s - 1;
            runner_d = (char*)runner_d - 1;
            *(char*)runner_d = *(char*)runner_s;
            ++i;  
        }
    }
    
    return (dest);
}   
    
    
    



 
/******************************************************************************/ 
char *Int2Str10(char *str, const int num)
{
    int temp = num;         
    int count = 0;

    assert(str);
    
    while (temp != 0)       /* Counting number of digits in num */
    {
        ++count;
        temp /= 10;
    }

    temp = num;

    if (num < 0)            /* Handling a negative case */
    {
        *str = '-';
        temp *= (-1);
    }
    else
    {
        *str = ' ';
    }
     
    str += (count + 1);     
    *str = '\0';
    --str;

    while (temp > 0)
    {
        *str = (temp % 10) + '0';
        --str;
        temp /= 10;
    }
        
    return (str);
}

/******************************************************************************/ 
char *Int2Str(char *str, const int num, int base)
{
    int temp = num;
    int count = 0;
    assert(str);
    
    while (temp != 0)                    /* Counting number of digits in num */
    {
        ++count;
        temp /= base;
    }

    temp = num;

    if (num < 0)                         /* Handling a negative case */
    {
        if (10 == base)
        {
            *str = '-';
        }
        else
        {
           *str = ' ';
        }
 
        temp *= (-1);
    }
    else
    {
        *str = ' ';
    }
     

    str += (count + 1);
    *str = '\0';
    --str;

    while (temp > 0)
    {
        if ((temp % base) < 10)          /* 0-9 case */
        {
            *str = (temp % base) + '0';
        }
        else                             /* 10-base case */
        {
            *str = (temp % base) + '7';
        }

        --str;
        temp /= base;
    }
        
    return (str);
}

        
/******************************************************************************/
int Str2Int(const char *str)
{
    int num = 0;
    unsigned int i = 0; 
    size_t length;
    assert(str);
    length = strlen(str);
    
    if ('-' == *str)
    {
        i = 1;
    }

    for (; (i < length) && ((str[i] >= '0') && (str[i] <= '9')); ++i)
    {
        /* Adding a digit from the right */
        num = (num * 10) + (str[i] - ('0'));    
    }
    
    if ('-' == *str)
    {
        num *= (-1);
    }

    return (num);
} 

/******************************************************************************/
char *AppearesIn2(char *str1, char *str2, char *str3,
                  size_t size1, size_t size2, size_t size3) 
{
    char *runner_s1 = str1;
    char *runner_s2 = str2;
    char *runner_s3 = str3;
    char *runner_d = NULL;
    int i = 0;

    char *dest = (char*)malloc(SIZE_OF_ASCII_ARRAY * sizeof(char));
    if (NULL == dest)
    {
        fprintf(stderr, "malloc faild!!!\n");
        return (NULL);
    }
    
    assert(str1);
    assert(str2);
    assert(str3);
    
    runner_d = dest;

    /* Turning in 1 all the chars that appears at str1 */    
    while (runner_s1 < (str1 + size1 - 1))
    {
        *(dest + *runner_s1) = 1;
        ++runner_s1;
    }

    /* Turning in 2 all the chars that appears at str1 & str2 */   
    while (runner_s2 < (str2 + size2 - 1))
    {
        if (1 == *(dest + *runner_s2))
        {
            *(dest + *runner_s2) = 2;
        }
        
        ++runner_s2;
    }

    /* Turning in 3 all the chars that appears at str1 & str2 & str3 */       
    while (runner_s3 < (str3 + size3 - 1))
    {
        if (2 == *(dest + *runner_s3))
        {
            *(dest + *runner_s3) = 3;
        }
        
        ++runner_s3;
    }

    /* Filling an array with all the chars that appears at str1 & str2 only */    
    for (i = 0; i < SIZE_OF_ASCII_ARRAY; ++i)
    {
        if (2 == (unsigned char)dest[i])
        {
            *runner_d = i;
            ++runner_d;
        }
    }
    
    *runner_d = '\0';
    
    return (dest);
}       
    
/******************************************************************************/
int IsALittleEndian(void)
{
    unsigned int num = 1;
    
    return (1 == *(char*)&num);
    
}


           
