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

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <ctype.h>      
#include <string.h>     /* all string functions */
#include "ws2.h"



  /************************************************************/
  
int IsPalindrom(char *str)
{
    unsigned int i = 0;
    
    assert(str);
    
    /* A loop that compares a charachter with
     *
     * her mirror matching charachter*/
    
    for (i = 0; i < ((((unsigned)strlen(str)) / 2) + 1); i++)
    {
        if ( *(str + i) != *((str + (strlen(str) - 1) - i)) )
        {
            return (0);
        }
    }
        
    return (1);
}
 
    
  /************************************************************/
  
void SevenBoom(int from, int to)
{
    int i = 0;                       
    int flag = 0;                       
    int temp = from;                    /* For including 7 test */
    for (i = from; i < (to + 1); i++)
    {
        temp = i;
        
    /* A loop that checks if the number includes 7 */
    
        while ((temp > 0) && (0 == flag))
        {
            if ( 7 == (temp % 10))
            {
                flag = 1;                               
            } 
            temp /= 10;                           /* Cutting a digit from temp*/    
        }                
            if ((0 != (i % 7)) && (1 != flag))    /* Divided by 7 check also*/
            {
                printf("%d ", i);
            }
            else
            {
                printf("%s ", "BOOM");
                flag = 0;
            }
    }
    printf("\n");
}
  



  /************************************************************/  
    
void PoiSwap(int **pa, int **pb)
{
    int *temp = NULL;
   
    assert(pa);
    assert(pb);
    
    temp = *pa;
    *pa = *pb;
    *pb = temp;
    
}
         
    
  /************************************************************/  

void RmSpaces(char *dest, char *src)
{

    /*
     *  initializing a READ runner and a WRITE runner
     */      
   
      char *read_runner = NULL;
      char *write_runner = NULL;
      size_t count_c = 0;

      
      assert(dest);
      assert(src);
      
      
      
      read_runner = src;
      write_runner = dest;
      
      
    /*
     *  The beginning of the sentence:
     *  - Jumping over spaces and tabs
     *  - writing the first word  
     */       
 
 
 
      if (NULL != (read_runner = strtok(src, " \t")))
      {
        count_c = strlen(read_runner);
        strncpy(write_runner, read_runner, count_c);
        read_runner = strtok(NULL, " \t");
        write_runner += count_c;
      }
      
   
   
    /*
     *  The middle and the end of the sentence:
     *  - When reaching to a non-delimeter - writing to the WRITE runner
     *  - Checking if it's the end of the sentence:
     *      -- If it is - putting a NULL
     *      -- If NOT - putting one space charachter   
     */      
    
    
      while (NULL != read_runner)
      {
        *write_runner = ' ';
        ++write_runner; 
        count_c = strlen(read_runner);
        strncpy(write_runner, read_runner , count_c);
        read_runner = strtok(NULL, " \t");
        write_runner += count_c ;
      }
      
        *write_runner = '\0';
        
}
     

  /************************************************************/  

char *BigAdd(const char *a, const char *b, char *dest)
{
    char *runner_a = NULL;              /* Runner back on first number */
    char *runner_b = NULL;              /* Runner back on second number */
    char *runner_dest = NULL;           /* Runner back on destination */
    int temp = 0;
    int carry = 0;                      /* For carrying ten's digit next */
    size_t length_a = 0;                
    size_t length_b = 0;                
    size_t length = 0;                  /* length of the destination's array */ 
    
    assert(a);
    assert(b);
    assert(dest);

    length_a = strlen(a);
    length_b = strlen(b);    
    runner_a = (char*) (a + length_a - 1);
    runner_b = (char*) (b + length_b - 1);
    


    /*
     *  Checking who is bigger for calculating length of destination
     */


    if (length_a > length_b)            
    {
        length = length_a + 1;
    }
    else
    {
        length = length_b + 1;
    }
    runner_dest = dest + length;
    *runner_dest = '\0';
    --runner_dest;


    
    while ((runner_a >= a) && (runner_b >= b))
    {
        temp = ((int) (*runner_a - '0')) + ((int) (*runner_b - '0')) + carry;


    /*
     *  Checking if carry is = '1' or '0'
     */



        if (temp > 9)
        {
            carry = 1;
            temp = temp % 10;
        }
        else
        {
            carry = 0;
        }
        *runner_dest = temp + '0';
        --runner_a;
        --runner_b;
        --runner_dest;
    }


    /*
     *      After reaching to the end of one of the numbers
     */


    while (runner_a >= a)
    {
        temp = ((int) (*runner_a - '0')) + carry;
        if (temp > 9)
        {
            carry = 1;
            temp = temp % 10; 
        }
        else
        {  
        carry = 0;
        }
        *runner_dest = temp +'0';
        --runner_a;
        --runner_dest;
    }
    while (runner_b >= b)
    {
        temp = ((int) (*runner_b - '0')) + carry;
        if (temp > 9)
        {
            carry = 1;
            temp = temp % 10; 
        }
        else
        {  
        carry = 0;
        }
        *runner_dest = temp +'0';       
        --runner_b;
        --runner_dest;
    }

    if (1 == carry)
    {
        *runner_dest = '1';
    }
    else 
    {
        *runner_dest = ' ';
    }

    return (dest);
    
}     
         

