/*****************************************************************************
 * Project:     WS2                                                           *
 * Date:        14.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Sandra                                                        *
 *                                                                            *
 *  ~ String.h implementation by Yaron ~                                      *                                       
 *                                                                            *
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */

#include <stdio.h>      /* printf */
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "ws2.h"

size_t Strlen(const char *s)
{
    size_t count = 0;
    assert(s);
    while (*s != '\0')
    {
        count++;
        ++s;
    }
    
    return (count);
}
 

  /**************************************************************/
  
int Strcmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);
    while (((*s1) == (*s2)) && ('\0' != *s1))
    {
        ++s1;
        ++s2;
    }
    return (*s1 - *s2);
}


  /**************************************************************/


char *Strcpy(char *dest, const char *src)
{ 
    char *addr = dest;
    assert(dest);
    assert(src);
    while ( '\0' != *src)
        {
        *dest = *src;
        ++dest;
        ++src;
        }
    return (addr);
}

    
  /**************************************************************/            

char *Strncpy (char *destination, const char *src, size_t num)
{
    char *address = destination;
    unsigned int i = 0;
    assert(destination);
    assert(src);
    if (num > Strlen(src))
    {
        while ( '\0' != *src)
        {
        *destination = *src;
        ++destination;
        ++src;
        }
        while ((destination - address) < ((unsigned) num))
        {
        
            *destination = '\0';    
            destination++;
        }
        
    }
    else
    {
        for (i = 0; i < ((unsigned) num) ; i++)
        {
            *destination = *src;
            ++destination;
            ++src;
        }
        *destination = '\0';
    }
    
    return (address);
}     


  /************************************************************/  
                
int Strcasecmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);
    while ((tolower(*s1) == tolower(*s2)) && ('\0' != *s1))
    {
        ++s1;
        ++s2;
    }
    return (*s1 - *s2);
}  


  /************************************************************/  
  
char *Strchr(char *str, int ch)
{
    char *ret = str;
    assert(str);
    while (('\0' != *str) && (*str != ch))
    {
        ++str;
    }
    if ((*str == ch) || ('\0' == ch))
    {
        ret = str;
        return (ret);
    }
    else
    {   
        return NULL;
    }
} 


  /************************************************************/     
 
char *Strdup(const char *s)
{
    char *runner = NULL;
    char *dest = NULL;
    assert(s);
    runner = (char*)malloc(Strlen(s) + 1);
    
    /* if (NULL = runner) --> DBG(fprintf(stderr, -------)); return (NULL);                                                     חייבים לבדוק מאלוק לאחר הקצאה!!!!!!!!!!!!!*/
   
    dest = runner;
    while ('\0' != *s)
    {
        *runner = *s;
        ++s;
        ++runner;
    }
    
    return (dest);
}


  /************************************************************/     

char *Strcat(char *dest, const char *src)
{
    
    char *str = NULL;
    
    assert(dest);
    assert(src);
    
    str = (dest + Strlen(dest));
    while ('\0' != *src)
    {
        *str = *src;
        ++str;
        ++src;
    }
    *str = '\0';

    return ((char*)dest);
}


  /************************************************************/     

char *Strncat(char *dest, const char *src, size_t num)
{
    unsigned int i = (Strlen(dest)) + (Strlen(src)) + 1;
    assert(dest);
    assert(src);
    if (num == (Strlen(src)))
    {
        Strcat(dest, src);
    }
    else if (num > (Strlen(src)))
    {
        Strcat(dest, src);
        while (i < ((unsigned) num))
        {
            *(dest + i) = '0';
            ++i;
        }
    }
    else
    {
        char *str = (dest + Strlen(dest));
    for (i = 0; i < ((unsigned)num); i++)
    {
        *str = *src;
        ++str;
        ++src;
    }
    *str = '\0';
    }

    return ((char*) dest);
}   


  /************************************************************/   
  

char *Strstr(const char *big, const char *little)
{

	char const *save_dest = little;
	int flag = 0;
	while (0 != *big)
	{
		while ((*big == *little) || (0 == *little))
		{
			flag = 1;
			if (0 == *little)
			{
				return (char *) (big - (little - save_dest));
			}		
			++big;	
			++little;		
		}
		if (1 == flag)
		{	
			return NULL;
		}
	++big;	
	}
	
	return NULL;
}


  /************************************************************/ 

size_t Strspn(const char *big_str, const char *small_str)
{
    size_t counter = 0;
    
    {
        while (Strchr((char*)small_str, (int) *big_str))
        {
            ++counter;
            ++big_str;
        }
    }
    
    return (counter);
}


  /************************************************************/ 

static int IsDelimeter(char c, const char *delim)
{
    while ('\0' != *delim)
    {
        if (c == *delim)
        {
            return (1);
        }
        
        ++delim;
    }
    
    return (0);
}

  /************************************************************/ 
char *Strtok(char *str, const char *delim)
{
    static char *strtok_string = NULL;
    
    char *working_string = (NULL != str) ? (str) : (strtok_string);  
    char *token = NULL;
    
    /* if working_string is NULL, return NULL */
    if (NULL == working_string)
    {
        return (NULL);
    }
    
    /* 
     * Skip over delimeters, till first non-delimeter character.
     * token will point to the begining of the token.
     */
    while (('\0' != *working_string) && IsDelimeter(*working_string, delim))
    {
        ++working_string;
    }
    
    if ('\0' == *working_string)
    {
        return (NULL);
    }
    
    token = working_string;
    working_string += 1;
    
     
    /*
     * Skip over all non-delimeter characters, till first delimeter or '\0'.
     * If deleimeter terminating the token is NOT '\0', then:
     * - Replace it with '\0'
     * - strtok_string will point to the following character.
     */
    
    while (('\0' != *working_string) && !IsDelimeter(*working_string, delim))
    {
        ++working_string;
    }
    
    if ('\0' == *working_string)
    {
        strtok_string = NULL;
    }
    else
    {
        *working_string = '\0';
        strtok_string = working_string + 1;
    }
    
    return (token);
}


  /************************************************************/
  

         
         
    
    
