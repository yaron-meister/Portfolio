/********************************************************/
/*            ba_luts_count_code_generation.c           */
/********************************************************/
#include <stdio.h>

/* Macros                  */


/* Forward Declarations    */

/* A function that counts the number of bits that is on.
 * It gets the list of the lines and returns an integer number that is the count
 */
int BitsCountOn(unsigned long bits);


/* A function that initiate an array with count of set bits */
int main(void)
{
    int count_lut[256] = {0};
    unsigned int i = 0;
    printf("static char lut[256] = { ");
    
    for (i = 0; i < 255; ++i)
    {
        count_lut[i] = BitsCountOn(i);
        printf("%d, ", count_lut[i]);
    }
    
    count_lut[i] = BitsCountOn(i);
    printf("%d}\n", count_lut[i]);
    
    return (0);
}



int BitsCountOn(unsigned long bits)
{
    int count = 0;
    
    while (bits > 0)
    {
        bits &= (bits - 1);
        ++count;
    }
    
    return (count);
}





