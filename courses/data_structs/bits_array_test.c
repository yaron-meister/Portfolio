/*****************************************************************************
 * File name:   bits_array_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Shiran
 * Date:        2018-11-05 14:19:43
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "bits_array.h"       
#include "bits_array_internal.h"       
#include "utils.h"


/* Macros                  */
#define BITS_ARRAY_ALL_ON (~0ul)
#define BITS_ARRAY_ALL_OFF (0ul)

/* Forward Declarations    */
void BitsArrayAllOn_test(void);
void BitsArrayAllOff_test(void);
void BitsArraySetOn_test(void);
void BitsArraySetOff_test(void);
void BitsArrayIsOn_test(void);
void BitsArrayIsOff_test(void);
void BitsArrayCountOn_test(void);
void BitsArrayCountOff_test(void);
void BitsArrayMirror_test(void);
void BitsArrayRotateLeft_test(void);
void BitsArrayRotateRight_test(void);
void BitsArrayBitFlip_test(void); 
void BitsArraySetBit_test(void);
void BitsArraySetRangeOn_test(void);
void BitsArraySetRangeOff_test(void);
void BitsArrayLUTCountOn_test(void);
void BitsArrayLUTMirror_test(void);

 
/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{
    unsigned long bits = 10;
    BitsArrayAllOn_test();    
    BitsArrayAllOff_test();
    BitsArraySetOn_test();    
    BitsArraySetOff_test();
    BitsArrayIsOn_test();
    BitsArrayIsOff_test();
    BitsArrayCountOn_test();     
    BitsArrayCountOff_test();     
    BitsArrayMirror_test();
    BitsArrayRotateLeft_test();
    BitsArrayRotateRight_test();
    BitsArrayBitFlip_test();
    BitsArraySetBit_test();
    BitsArraySetRangeOn_test();
    BitsArraySetRangeOff_test();
    BitsArrayLUTCountOn_test();
    BitsArrayLUTMirror_test();
    
#ifdef UNIT_TEST

    BitsArrayPrintBits(bits);
    
#endif /* UNIT_TEST */
            
    return (EXIT_SUCCESS);
}

/******************************************************************************/
void BitsArrayAllOn_test(void)
{
    unsigned long bits = 50;
    printf("After 'All-On' bits = 0x%lx\n", bits = BITS_ARRAY_ALL_ON);
}

/******************************************************************************/ 
void BitsArrayAllOff_test(void)
{
    unsigned long bits = 50;
    printf("After 'All-Off' bits = 0x%lx\n", BitsArrayAllOff(bits));
} 

/******************************************************************************/ 
void BitsArraySetOn_test(void)
{
    unsigned long bits = 50;
    printf("After seting index 0 on, bits = 0x%lx\n", BitsArraySetOn(bits, 0));       
}

/******************************************************************************/ 
void BitsArraySetOff_test(void)
{
   unsigned long bits = 51;
   printf("After seting index 0 off, bits = 0x%lx\n", BitsArraySetOff(bits, 0));       
}

/******************************************************************************/ 
void BitsArrayIsOn_test(void)
{
    unsigned long bits = 51;
    
    if (BitsArrayIsOn(bits, 0))
    {
        printf("At 'bits', the bit at index '0' is 'ON'\n");    
    }
    else
    {
        printf("At 'bits', the bit at index '0' is 'OFF'\n"); 
    }
}           

/******************************************************************************/ 
void BitsArrayIsOff_test(void)
{
    unsigned long bits = 50;
    
    if (BitsArrayIsOff(bits, 0))
    {
        printf("At 'bits', the bit at index '0' is 'OFF'\n");    
    }
    else
    {
        printf("At 'bits', the bit at index '0' is 'ON'\n"); 
    }
}      

/******************************************************************************/
void BitsArrayCountOn_test(void)
{
    unsigned long bits = 50;
    printf("The number of bits that is ON at 'bits' is: %d\n",
                                        BitsArrayCountOn(bits)); 
}

/******************************************************************************/
void BitsArrayCountOff_test(void)
{
    unsigned long bits = 50;
    printf("The number of bits that is OFF at 'bits' is: %d\n",
                                        BitsArrayCountOff(bits)); 
}

/******************************************************************************/
void BitsArrayMirror_test(void)
{
    unsigned long bits = 0xebf13fcb9e12ae33;
    printf("Before MIRROR, 'bits' is: 0x%lx\n", bits);
    printf("After MIRROR, 'bits' is: 0x%lx\n", BitsArrayMirror(bits));
}

/******************************************************************************/
void BitsArrayRotateLeft_test(void)
{
    unsigned long bits = 0x8000000000000000;
    printf("After ROTATING LEFT, 'bits' is: 0x%lx\n",
                       BitsArrayRotateLeft(bits, 64));
}
        
/******************************************************************************/
void BitsArrayRotateRight_test(void)
{
    unsigned long bits = 1;
    printf("After ROTATING RIGHT, 'bits' is: 0x%lx\n",
                       BitsArrayRotateRight(bits, 64));
}    
    
/******************************************************************************/   
void BitsArrayBitFlip_test(void)
{
    unsigned long bits = 3;
    printf("After FLIPING, 'bits' is: 0x%lx\n",
                       BitsArrayBitFlip(bits, 1)); 
}  
    
/******************************************************************************/    
void BitsArraySetBit_test(void)
{
    unsigned long bits = 5;
    printf("After SETING BIT, 'bits' is: 0x%lx\n", BitsArraySetBit(bits, 1, 1));
}

/******************************************************************************/
void BitsArraySetRangeOn_test(void)
{
    unsigned long bits = 1;
    printf("After SETING A RANGE OF BITS ON, 'bits' is: 0x%lx\n",
                                 BitsArraySetRangeOn(bits, 1, 3));
}
    
/******************************************************************************/
void BitsArraySetRangeOff_test(void)
{
    unsigned long bits = 15;
    printf("After SETING A RANGE OF BITS OFF, 'bits' is: 0x%lx\n",
                                 BitsArraySetRangeOff(bits, 1, 3));
}    
    
    
#ifdef UNIT_TEST
    
/******************************************************************************/
void BitsArrayPrintBits(unsigned long bits)
{
    int i = 0;
    printf("\nThe state of the bits is:\n");
    
    for (i = 0; i < 64; ++i)
    {
        printf("%d", (!(!(bits & 0x8000000000000000))));
        bits <<= 1;
    }
    
    printf("\n");
}

#endif /* UNIT_TEST */  

/******************************************************************************/
void BitsArrayLUTCountOn_test(void)
{
    unsigned long bits = 7;
    printf("At 'bits', there are %d bits that are 'ON'\n",
                               BitsArrayLUTCountOn(bits));
}

/******************************************************************************/
void BitsArrayLUTMirror_test(void)
{
    unsigned long bits = 0xebf13fcb9e12ae33;
    printf("Before LUT-MIRROR, 'bits' is: 0x%lx\n", bits);
    printf("After LUT-MIRROR, 'bits' is: 0x%lx\n", BitsArrayLUTMirror(bits));
}


     
