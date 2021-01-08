/*****************************************************************************
 * File name:   ws9.h
 * Developer:   Yaron
 * Reviewer:    Daria
 * Date:        2018-10-30 16:10:50
 * Description: 
 *****************************************************************************/

#ifndef __WS9_H__
#define __WS9_H__


/******Fills the first n bytes of the memory area s with the constant c********/
void *Memset(void *str, int ch, size_t num);

/*********************Copies n bytes from src to dest**************************/
void *Memcpy(void *dest, const void *src, size_t num);

/************Copies n bytes from src to dest and safe for alignment************/
void *Memmove(void *dest, const void *src, size_t num);

/******************Converting an integer to a string in 10 base****************/
char *Int2Str10(char *str, const int num);

/******************Converting an integer to a string***************************/
char *Int2Str(char *str, const int num, int base);

/******************Converting a string to an integer***************************/
int Str2Int(const char *str);

/******************************************************************************/
char *AppearesIn2(char *str1, char *str2, char *str3,
                              size_t size1, size_t size2, size_t size3);
                              
/*******************Checks if a system is a little endian**********************/
int IsALittleEndian(void);
 

 
#endif     /* __WS9_H__ */
