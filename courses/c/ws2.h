/******************************************************************************
 * Project:     WS2                                                           *
 * Date:        14.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Sandra                                                        *
 *                                                                            *
 ******************************************************************************/


/* It's the responsibility!!!!!!!!! */


#ifndef _WS2_H_
#define _WS2_H_


#include <stddef.h>                 /* size_t */



/* A function that counting the length of a string */
size_t Strlen (const char *s);


/* Return: reflection of the lexicographical order:
    -  0: s1 = s2
    - >0: s1 > s2
    - <0: s1 < s2
*/
int Strcmp(const char *s1, const char *s2);


/* A function that copies one string to another place in the memory */
char *Strcpy(char *dest, const char *src);


/* A function that copies one string to another place in the memory up to a 
    given number of charachters */
char *Strncpy(char *dest, const char *src, size_t num);
 
 
/* Return: reflection of the lexicographical order whithout differencing
   between lower to upper case:
    - 0: s1 = s2
    - >0: s1 > s2
    - <0: s1 < s2
*/
int Strcasecmp(const char *s1, const char *s2);


/* A function that searching for the first place which a 
   charachter appereances if it's exists */
char *Strchr (char *str, int ch);


/* A function that duplicates a string to a different address */
char *Strdup(const char *s);


/* A function that concatenate two given strings */
char *Strcat(char *dest, const char *src);


/* A function that concatenate two given strings up to a 
    given number of charachters */
char *Strncat(char *dest, const char *src, size_t num);


/* A function that finds the place in memory which a given  
   sub-string is located inside another given string */
char *Strstr(const char *haystack, const char *needle);


/* A function that finds how much charachters in  a first given 
    string in a row, takes place in a bigger second given string in a row */
size_t Strspn(const char *small_str, const char *big_str);


/* A function that seperates a sub-strings from one main string by delimiters */
char *Strtok(char *str, const char *delim);


/* A function that ckecks if a string is a palidrom */
int IsPalindrom(char *str);

/* A function that represents the game '7-BOOM' */
void SevenBoom(int from, int to);

/* A function that swaps between two int-pointers */
void PoiSwap(int **pa, int **pb);

/* A function that swaps between two int-pointers */
void RmSpaces(char *dest, char *src);

/* A function that swaps between two int-pointers */
char *BigAdd(const char *a, const char *b, char *c);

#endif
