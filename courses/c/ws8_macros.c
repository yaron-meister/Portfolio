#include <stdio.h>  /* printf */

#define SIZE(arg) ((char*)((&arg) + 1) - (char*)(&arg))

#define SIZE_OF_TYPE(argu) (size_t)(1 + ((argu*)0))                                             /* התוצאה של שורה זו היא באיזו כתובת אני נמצא עכשיו ולא ההפרש כתובות!!!!!!!!! */

int main(void)
{
    int integer = 5;
    char ch = 'h';
    float flo = 3.14;
    double dou = 10;
    printf("The size of int is: %ld\nThe size of char is:"
            " %ld\nThe size of float is: %ld\nThe size of double is:"
            " %ld\n", SIZE(integer), SIZE(ch), SIZE(flo), SIZE(dou));
    printf("The size of int is: %lu\nThe size of char is:"
            " %lu\nThe size of float is: %lu\nThe size of double is:"
            " %lu\n",SIZE_OF_TYPE(int), SIZE_OF_TYPE(char),
                     SIZE_OF_TYPE(float), SIZE_OF_TYPE(double));
    
    return (0);
}
