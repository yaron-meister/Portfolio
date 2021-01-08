/********************************************************/
/*            bits_array.h                              */
/********************************************************/

/* 
  *Bits indexes are from 0 to 31 (32bit machine) or 0 to 63 (64bit machine).
 * Undefined otherwise 
 */

#ifndef __BITS_ARRAY_H__
#define __BITS_ARRAY_H__

#include <stddef.h>      /* size_t */

/* A function that set on/off all of the lines. It gets the list of the lines,
 * set all the lines off and returns it back 
 */
unsigned long BitsArrayAllOn(unsigned long bits);
unsigned long BitsArrayAllOff(unsigned long bits);


/* A function that set on/off one specific wanted line.
 * It gets the list of the lines and the wanted line and returns the list back
 * after the operation
 */
unsigned long BitsArraySetOn(unsigned long bits, int index);
unsigned long BitsArraySetOff(unsigned long bits, int index);



/* A function that checks if a specific line is on.
 * It gets the list of the lines and the wanted line and returns:
 * '1' - if it's on
 * '0' - if it's off
 */
int BitsArrayIsOn(unsigned long bits, int index);

/* A function that checks if a specific line is off.
 * It gets the list of the lines and the wanted line and returns:
 * '1' - if it's off
 * '0' - if it's on
 */
int BitsArrayIsOff(unsigned long bits, int index);

/* A function that checks if a specific range of lines is on.
 * It gets the list of the lines and the wanted range and returns:
 * '1' - if it's on
 * '0' - if it's off
 */
unsigned long BitsArraySetRangeOn(unsigned long bits, int start, int end);

                                  
/* A function that checks if a specific range of lines is off.
 * It gets the list of the lines and the wanted range and returns:
 * '1' - if it's off
 * '0' - if it's on
 */
unsigned long BitsArraySetRangeOff(unsigned long bits, int start, int end);

                                  
/* A function that counts the number of bits that is on/off.
 * It gets the list of the lines and returns an integer number that is the count
 */
int BitsArrayCountOn(unsigned long bits);
int BitsArrayCountOff(unsigned long bits);



/* A function that mirrors the status of the lines list.
 * It gets the list of the lines and returns it after the operation
 */
unsigned long BitsArrayMirror(unsigned long bits);

/* A function that shifts left/right the status of the lines list.
 * It gets the list of the lines and returns it after the operation
 */
unsigned long BitsArrayRotateLeft(unsigned long bits, int times);
unsigned long BitsArrayRotateRight(unsigned long bits, int times);


/* A function that flips one specific wanted line.
 * It gets the list of the lines and the wanted line and returns the list back
 * after the operation
 */
unsigned long BitsArrayBitFlip(unsigned long bits, int index);

/* A function that set on/off one specific wanted line accoarding to a demand.
 * It gets the list of the lines and the wanted line and returns the list back
 * after the operation
 */
/* State accepts 0 or 1. Undefined otherwise */
unsigned long BitsArraySetBit(unsigned long bits, int index, int state);

/* A function that counts the number of bits that is on using LUT.
 * It gets the list of the lines and returns an integer number that is the count
 */
int BitsArrayLUTCountOn(unsigned long bits);

/* A function that mirrors the status of the lines list using LUT.
 * It gets the list of the lines and returns it after the operation
 */
unsigned long BitsArrayLUTMirror(unsigned long bits);



 
 
 
 


#endif /* __BITS_ARRAY_H__ */























