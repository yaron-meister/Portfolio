#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     

#include "ws2.h"

void Strlen_test(void);
void Strcmp_test(void);
void Strcpy_test(void);
void Strncpy_test(void);
void Strcasecmp_test(void);
void Strchr_test(void);
void Strdup_test(void);
void Strcat_test(void);
void Strncat_test(void);
void Strstr_test(void);
void Strspn_test(void);
void Strtok_test(void);


int main(void)
{
    
    Strlen_test();
    Strcmp_test();
    Strcpy_test();
    Strncpy_test();
    Strcasecmp_test();
    Strchr_test();
    Strdup_test();
    Strcat_test();
    Strncat_test();
    Strstr_test();
    Strspn_test();
    Strtok_test();

   
    return 0;
} 



  /************************************************************/

void Strlen_test(void)
{
    char str[] = "Hello";
    printf("\nThe length of the string is: %ld\n", Strlen(str));
}
    
    
  /************************************************************/

void Strcmp_test(void)
{
    char str1[] = "He2lo";
    char str2[] = "Hello";
    printf("\nThe result of the comparison between '%s' and '%s' is: %d\n",
             str1, str2, (Strcmp(str1, str2)));
}


  /************************************************************/

void Strcpy_test(void)
{
    char src[] = "World";
    char dest[20];
    printf("\nThe copy of '%s' is: %s\n", src, Strcpy(dest, src));
}

  /************************************************************/
  
void Strncpy_test(void)
{
    char src[] = "World";
    char dest[20];
    printf("\nThe Strncpy of '%s' is: %s\n", src, Strncpy(dest, src, 3));
}


  /************************************************************/

void Strcasecmp_test(void)
{
    char str1[] = "HELLO";
    char str2[] = "hello";
    printf("\nThe result of the case comparison between '%s' and '%s' is: %d\n",
             str1, str2, (Strcasecmp(str1, str2)));
}


  /************************************************************/

void Strchr_test(void)
{
    char str[] = "hello";
    printf("\nThe first address that 'l' appears at the string is: %p\n\n",
                 Strchr(str, 108));
}


  /************************************************************/

void Strdup_test(void)
{
    char str[] = "beautiful";
    printf("The duplication of %s is: %s\n", str, Strdup(str));
    free(Strdup(str));
}


  /************************************************************/

void Strcat_test(void)
{
    char str1[] = "Hello";
    char str2[] = "There";
    printf("\nThe merging is: %s\n", Strcat(str1, str2));
}


  /************************************************************/

void Strncat_test(void)
{
    char str1[] = "Hello";
    char str2[] = "There";
    printf("\nThe Strncat merging is: %s\n", Strncat(str1, str2, 3));
}
    
    
  /************************************************************/    
    
void Strstr_test(void)
{
    char str1[] = "Hello my friend";
    char str2[] = "fri";
    printf("\nThe place where the sub-string: '%s' is " 
            "appearing in the string: '%s' is: %s\n",
             str2, str1, Strstr(str1, str2));
}
    
    
   /************************************************************/    
    
void Strspn_test(void)
{
    char str1[20] = "baaabcaadllcloHello";
    char str2[20] = "aab";
    printf("\nThe result of Strspn is: %ld\n", Strspn(str1, str2));  
}  
 
 
   /************************************************************/     
 
void Strtok_test(void)
{
    char str[] = "My name is Yaron Meister";
    char delim[] = " ";
    char *p = NULL;
    printf("\nThe next word is: %s\n", 
    (p=Strtok(str, delim)) ? p : "No token");
    printf("\nThe next word is: %s\n", 
    (p=Strtok(NULL, delim)) ? p : "No token");
    printf("\nThe next word is: %s\n", 
    (p=Strtok(NULL, delim)) ? p : "No token");
    printf("\nThe next word is: %s\n", 
    (p=Strtok(NULL, delim)) ? p : "No token");
    printf("\nThe next word is: %s\n", 
    (p=Strtok(NULL, delim)) ? p : "No token");
    printf("\nThe next word is: %s\n", 
    (p=Strtok(NULL, delim)) ? p : "No token");
}
 
 
   /************************************************************/  
  

    
    
     
  
