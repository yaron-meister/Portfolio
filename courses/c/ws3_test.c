#include <stdio.h>    /* printf */  

#include "ws3.h"

int main(int argc, char *argv[], char *env[])
{
    int i = 0;              /* for scanf */
    EnvPrint(env);
    EnvCopy(env);
    printf("\n\n");
    printf("Please insert the size of your NAPOLEON CIRCLE:\n");
    scanf("%d", &i);   
    printf("\nThe index of the last survivor is: %d\n\n", NapLast(i));
    SizeOfType();
    
    return 0;
}



