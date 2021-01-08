/*****************************************************************************
 * File name:   ws6.c
 * Developer:   Yaron
 * Reviewer:    Shalev
 * Date:        2018-10-24 08:30:26
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf, scanf    */
#include <assert.h>


/* Macros                  */
typedef enum status
{
    SUCCESS,
    FAILURE,
    EXIT
} sta_t; 

#define BYTE 8
 
/* Forward Declarations    */
double pow2(unsigned int x, int y);
int IsPowOfTwoLoop(unsigned int num);
int IsPowOfTwoBW(unsigned int num);
double AddOne(unsigned int num);
void ThreeBitsOn(unsigned int arr[]);
unsigned int ByteMirrorLoop(unsigned int num);
unsigned int ByteMirrorNoLoop(unsigned int num);
unsigned int IsBothOn(unsigned char ch);
unsigned int IsAtLeastOneOn(unsigned char ch);
unsigned int SwapBits(unsigned int num, int b1, int b2);
unsigned int DividedBy16(unsigned int num);
void SwapVar(int *num1, int *num2);
int CountSetWithLoop(unsigned int num);
unsigned int CountSetWithoutLoop(unsigned int num);
void PrintBits(float num);

/* Global variables        */


int main()
{
    unsigned int num = 3;
    int pow = 4;
    unsigned int number = 41;
    unsigned int add_one = 7;
    unsigned int array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned int mirror = 240;
    unsigned int numb = 3;
    int b1 = 2;
    int b2 = 3;
    int a = 45;
    int b = -16;
    
    
    
    printf("%u * 2^%d =  %f\n",num, pow, pow2(num, pow));
    if (IsPowOfTwoLoop(number))
    {
        printf("%u is a power of 2\n", number);
    }
    else
    {
        printf("%u is NOT a power of 2\n", number);
    }
    if (IsPowOfTwoBW(number))
    {
        printf("%u is a power of 2\n", number);
    }
    else
    {
        printf("%u is NOT a power of 2\n", number);
    }
    
    printf("The sum of %u + 1 = %f\n", add_one, AddOne(add_one));
    ThreeBitsOn(array);
    printf("The original number is: %u and after mirroring is: %u\n",
                 mirror, ByteMirrorLoop(mirror));
    printf("The original number is: %u and after mirroring is: %u\n",
                 mirror, ByteMirrorNoLoop(mirror));
                 
    if (IsBothOn(34))
    {
        printf("At 34, bits 2 and 6 are 'on'\n");
    }
    else
    {
        printf("At 34, at least one of bits 2 and 6 is 'off'\n");
    }
    
    if (IsAtLeastOneOn(33))
    {
        printf("At 33, at least one of bits 2 and 6 is 'on'\n");
    }
    else
    {
        printf("At 33, bits 2 and 6 are 'off'\n");
    }
    
    printf("The closest smaller number to %u that is devided by 16th is: %u\n",
                number, DividedBy16(number));
    printf("BEFORE swaping bits the number is: %u and AFTER the number"
           " is: %u\n",numb, SwapBits(numb, b1-1, b2-1));
    printf("BEFORE swaping 'a' = %d and 'b' = %d\n", a, b);
    SwapVar(&a, &b);
    printf("AFTER swaping 'a' = %d and 'b' = %d\n", a, b);
    printf("At '%d' there are %d set bits\n", 5, CountSetWithLoop(5)); 
    printf("At '%d' there are %d set bits\n", 5, CountSetWithoutLoop(5));
    PrintBits(3);
    
    return (SUCCESS);
} 
 


/*****************************************************************/
double pow2(unsigned int x, int y)
{
    int result = 0;
    if (y >= 0)
    {
        result = (x << y);
    }
    else
    {
        y *= (-1);
        result = (x >> y);
    }
    
    return (result);
}

/***********************Using a LOOP**************************************/
int IsPowOfTwoLoop(unsigned int num)
{
    int count = 0;          /* Counts no. of turned on bits */
    while (num > 0)
    {
        if (num & 1)        /* If LSB is 'on' */
        {
            ++count;
        }
        
        num >>= 1;
    }
    
    return (1 == count);    /* Power of two syas that exactly 1 bit is 'on' */
}

/***********************Without a loop************************************/
int IsPowOfTwoBW(unsigned int num)
{
    /* Shuting down the lowest bit that is on */
    if (0 == (num & (num - 1)) && (0 != num))    
    {
        return (1);
    }
    else
    {   
        return(0);
    }
}

/*****************************************************************/
double AddOne(unsigned int num)
{
    int mask = 1;
    while (0 != (num & mask))
    {
        num = num & ~mask;      /* Shuting off the bit */
        mask = mask << 1;
    }
    num = num ^ mask;           /* Turning a bit to his opposite */
    
    return (num);
}       


/*****************************************************************/
void ThreeBitsOn(unsigned int arr[])
{
    int count = 0;
    int i = 0;
    unsigned int num = 0;
    printf("The three bits on integers in the array are:\n");
    for (i = 0; arr[i] ; ++i)
    {
        num = arr[i];
        
    /* Counts the number of bits that is 'on' */
        while (num > 0)
        {
            if (num & 1)
            {
                ++count;
            }
            
            num >>= 1;
        }
        if (3 == count)
        {
            printf("%u ", arr[i]);
        }
        count = 0;
    }
    printf("\n");
}

/*****************************************************************/
unsigned int ByteMirrorLoop(unsigned int num)
{
    unsigned int mask = 1;
    unsigned int mirror = 0;
    int i = 0;
    
    for (i = 0; i < BYTE; ++i)
    {
 /* In first loop, the 8th bit of the 
  * result of the function is at bit No. 1
  */
        mirror <<= 1;           
        
        if (num & mask)
        {
            mirror = mirror | mask;
        }
        
        num >>= 1;
    }
    
    return (mirror);
}
    
/*****************************************************************/
unsigned int ByteMirrorNoLoop(unsigned int num)
{
    num = ((num & 0xAA) >> 1) | ((num & 0x55) << 1);  /* Turning individuals */
    num = ((num & 0xCC) >> 2) | ((num & 0x33) << 2);  /* Turning pairs       */
    num = ((num & 0xF0) >> 4) | ((num & 0x0F) << 4);  /* Turning fours       */
    
    return (num);
}
      
/*****************************************************************/
unsigned int IsBothOn(unsigned char ch)
{
    return (0x22 == (ch & 0x22)); /* Checking if a 'num & mask = mask' */
}

/*****************************************************************/
unsigned int IsAtLeastOneOn(unsigned char ch)
{
    /* There are 3 masks:
        - 6 is 'on'
        - 2 is 'on'
        - Both are 'on'
       If one of the masks is equal, at least one is 'on'
     */
     
    return ((0x22 == ((ch & 0x20) | (ch & 0x02))) || 
            (0x20 == ((ch & 0x20) | (ch & 0x02))) ||                                            /* return (ch & 0x22) */
            (0x02 == ((ch & 0x20) | (ch & 0x02))));
} 

/*****************************************************************/  
unsigned int SwapBits(unsigned int num, int b1, int b2)
{
    /*
        - Isolating b1 and checking her status
        - Isolating b2 and checking her status
        - If they are different, turning bits for each one of them,
          else, not touching.
     */
     
    unsigned int is_different = ((num >> b1) & 1) ^ ((num >> b2) & 1);
    unsigned int temp = (is_different << b1) | (is_different << b2);
    num = num ^ temp;

    return (num);
}

/*****************************************************************/ 
      
unsigned int DividedBy16(unsigned int num)
{
    int count = 0;          /* Counting multiples of 16 */
    int i = 0;
    int temp = num;
    temp >>= 4;             /* All the bits under 16 are not interesting */
    
    while (temp > 0)
    {
        temp >>= 1;         /* Turning off all bits in temp and counts */                   /* return (num & 0xFFF0) */
        ++count;
    }
  
    if (num > 15)
    {
        temp = 1 << 4;      /* Initialize temp with bit No. 4 'on' */
        
        for (i = 1; i < count; ++i)
        {
            temp <<= 1;
        }
    }
        
        return (temp);
}

/*****************************************************************/   
void SwapVar(int *num1, int *num2)
{    
    assert (num1);
    assert (num2);
    *num1 = *num1 ^ *num2;      
    *num2 = *num1 ^ *num2;    
    *num1 = *num1 ^ *num2;      
}    

/*****************************************************************/  
int CountSetWithLoop(unsigned int num)
{
    int count = 0;
    
    while (num > 0)
    {
        ++count;
        num = num & (num - 1);
    }

    return (count);
}
             
/*****************************************************************/  
unsigned int CountSetWithoutLoop(unsigned int num)
{ 
    /* Using hamming weight */
    num = ((num & 0xAA) >> 1) + (num & 0x55);
    num = ((num & 0xCC) >> 2) + (num & 0x33);
    num = ((num & 0xF0) >> 4) + (num & 0x0F);
    
    return (num);
}
         
/*****************************************************************/  
void PrintBits(float num)
{
    int mask = 1;
    int i = 0;     
    for (i = 31; i >= 0; --i)
    {
        if ((*(int *)(&num)) & (mask = 1 << i))
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }       
    }
    printf("\n");
}




    
    
