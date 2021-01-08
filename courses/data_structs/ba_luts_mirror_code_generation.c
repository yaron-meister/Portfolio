/********************************************************/
/*            ba_luts_mirror_code_generation.c          */
/********************************************************/
#include <stdio.h>

/* Macros                  */


/* Forward Declarations    */

/* 
 *  A function that mirrors a BYTE
 */
unsigned int ByteMirrorNoLoop(unsigned int num);


/* A function that initiate an array with byte mirror */
int main(void)
{
    int mirror_lut[256] = {0};
    unsigned int i = 0;
    printf("static char mirror_lut[256] = { ");
    
    for (i = 0; i < 255; ++i)
    {
        mirror_lut[i] = ByteMirrorNoLoop(i);
        printf("%d, ", mirror_lut[i]);
    }
    
    mirror_lut[i] = ByteMirrorNoLoop(i);
    printf("%d};\n", mirror_lut[i]);
    
    return (0);
}



unsigned int ByteMirrorNoLoop(unsigned int num)
{
    num = ((num & 0xAA) >> 1) | ((num & 0x55) << 1);  
    num = ((num & 0xCC) >> 2) | ((num & 0x33) << 2);  
    num = ((num & 0xF0) >> 4) | ((num & 0x0F) << 4);  
    
    return (num);
}

