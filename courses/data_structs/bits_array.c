/*****************************************************************************
 * File name:   bits_array.c
 * Developer:   Yaron Meister
 * Reviewer:    Shiran
 * Date:        2018-11-05 14:19:43
 * Description: 
 *****************************************************************************/

#include <stdio.h> 

#include "bits_array.h"                
#include "utils.h"
#include "ba_count_lut.h"
#include "ba_mirror_lut.h"

/* Macros                  */
#define BYTE 8
#define WORD_LENGTH (sizeof(long) * BYTE) 
 
/* Forward Declarations    */
 
 
/* Global variables        */


/******************************************************************************/ 
unsigned long BitsArrayAllOn(unsigned long bits)
{
    UNUSED_VAR(bits);
    
    return (~0ul);
}

/******************************************************************************/ 
unsigned long BitsArrayAllOff(unsigned long bits)
{
    UNUSED_VAR(bits);
    
    return (0ul);
}  

/******************************************************************************/ 
unsigned long BitsArraySetOn(unsigned long bits, int index)
{
    unsigned long mask = 1;
    mask <<= index;
    bits |= mask;    
    
    return (bits);                                                                  /* return (bits |= (1ul << index)); */
}    

/******************************************************************************/ 
unsigned long BitsArraySetOff(unsigned long bits, int index)
{
    unsigned long mask = 1;
    mask <<= index;                     
    bits &= ~mask;    
    
    return (bits);                                                                    /* return (bits & (~(1ul << index))) */
}  

/******************************************************************************/ 
int BitsArrayIsOn(unsigned long bits, int index) 
{
    unsigned long mask = 1;
    
    return (((mask << index) & bits) ? 1 : 0);                                        /* return ((bits >> index) & 1ul) */
}

/******************************************************************************/ 
int BitsArrayIsOff(unsigned long bits, int index) 
{   
    return (!BitsArrayIsOn(bits, index));                                             /* return (!((bits >> index) & 1ul)) */
}

/******************************************************************************/ 
int BitsArrayCountOn(unsigned long bits)
{
    int count = 0;
    
    while (bits > 0)
    {
        bits &= (bits - 1);
        ++count;
    }
    
    return (count);
}

/******************************************************************************/ 
int BitsArrayCountOff(unsigned long bits)
{
    int count = 0;
    bits  = ~bits;
    
    while (bits > 0)
    {
        bits &= (bits - 1);
        ++count;
    }
    
    return (count);
}
    
/******************************************************************************/     
unsigned long BitsArrayMirror(unsigned long bits)
{      
    bits = ((bits & 0xAAAAAAAAAAAAAAAA) >> 1) | 
    ((bits & 0x5555555555555555) << 1);  
    bits = ((bits & 0xCCCCCCCCCCCCCCCC) >> 2) | 
    ((bits & 0x3333333333333333) << 2);  
    bits = ((bits & 0xF0F0F0F0F0F0F0F0) >> 4) | 
    ((bits & 0x0F0F0F0F0F0F0F0F) << 4);  
    bits = ((bits & 0xFF00FF00FF00FF00) >> 8) | 
    ((bits & 0x00FF00FF00FF00FF) << 8);
    bits = ((bits & 0xFFFF0000FFFF0000) >> 16) | 
    ((bits & 0x0000FFFF0000FFFF) << 16);
    bits = ((bits & 0xFFFFFFFF00000000) >> 32) | 
    ((bits & 0x00000000FFFFFFFF) << 32);        
        
    return (bits);
}  
    
/******************************************************************************/         
unsigned long BitsArrayRotateLeft(unsigned long bits, int times)
{
    int i = 0;
    unsigned long msb = 0;
    
    for (i = 0; i < times; ++i)
    {
        msb = (!(!(bits & 0x8000000000000000)));
        bits = (bits << 1) | msb;
    }
    
    return (bits);                                                                          /* return ((bits << times) | (bits >> (WORD_SIZE - times))); */
}
          
/******************************************************************************/         
unsigned long BitsArrayRotateRight(unsigned long bits, int times)
{
    int i = 0;
    unsigned long lsb = 0;
    
    for (i = 0; i < times; ++i)
    {
        lsb = (bits & 1) << (WORD_LENGTH - 1);
        bits = (bits >> 1) | lsb;
    }
    
    return (bits);
}   
    
/******************************************************************************/             
unsigned long BitsArrayBitFlip(unsigned long bits, int index)  
{
    bits ^= (1ul << index);
    
    return (bits);                                                                          /* return (bits ^= (1ul << index)); */
}  
    
/******************************************************************************/                
unsigned long BitsArraySetBit(unsigned long bits, int index, int state)
{
    unsigned long mask = 1ul << index;
    bits &= ~mask;
    bits |= (unsigned long)state << index;
    
    return (bits); 
}
    
/******************************************************************************/    
unsigned long BitsArraySetRangeOn(unsigned long bits, int start, int end)
{
    int i = 0;
    
    for (i = start; i <= end; ++i)
    {
        bits |= (1ul << i);
    }
    
    return (bits);
}     
    
/******************************************************************************/    
unsigned long BitsArraySetRangeOff(unsigned long bits, int start, int end)
{
    int i = 0;
    
    for (i = start; i <= end; ++i)
    {
        bits &= (~(1ul << i));
    }
    
    return (bits);
}              
    
/******************************************************************************/     
int BitsArrayLUTCountOn(unsigned long bits)
{
    unsigned long mask = 0xff;
    int count = 0;
    
    while (bits > 0)
    {
        count += (int)(lut[(bits & mask)]);
        bits >>= BYTE;
    }
        
    return (count);
}

/******************************************************************************/     
unsigned long BitsArrayLUTMirror(unsigned long bits)
{
    unsigned long mask = 0xff;
    unsigned long mirror = 0;
    unsigned int i = 0;
    
    for (i = 0; i < (WORD_LENGTH/BYTE - 1); ++i)
    {
        mirror |= mirror_lut[(bits & mask)];
        mirror <<= BYTE;
        bits >>= BYTE;
    }
    
    mirror |= mirror_lut[(bits & mask)];
    
    return (mirror);
}






    
