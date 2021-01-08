
 /*****************************************************************************
 * Project:     WS1                                                           *
 * Date:        11.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Rachel                                                        *
 *                                                                            *                                                                           
 * This program does for main things:                                         *                                                                          
 * 1. Prints " "Hello world" "                                                *
 * 2. Calculates 10^N which N is a given number                               *
 * 3. Flips a number to his mirror number                                     *
 * 4. Swaps between the values of two addresses at the memory                 *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>

static void HelloWorld(void);
static float DecPower(int power);
static int Flip(int num);
static int Swa(int *a, int *b);

int main(void)
{
    
    
    int power = 0;                            /* variable for powering func */
    int num_for_flipping = 0;                 /* variable for flipping func */
    int foo = 5;                              /* Non meaningful variable */
    int bar = 3;                              /* Non meaningful variable */
    
    printf("*******************************\n\n");
    HelloWorld();
    printf("*******************************\n\n");
    printf("Please insert a power:\n");
    scanf("%d",&power);
    printf("10^%d = %f\n\n",power,DecPower(power));
    printf("*******************************\n\n");
    printf("Please insert your number to flip:\n");
    scanf("%d",&num_for_flipping);
    printf("A mirror pic of your number %d is %d\n\n",num_for_flipping
    ,Flip(num_for_flipping));
    printf("*******************************\n\n");
    printf("In %d address, the value is: %d\n", &foo, foo);
    printf("In %d address, the value is: %d\n", &bar, bar);
    Swa(&foo,&bar);                         /* Swaping between foo and bar 
                                               in the memory */
    printf("\nAnd after swaping\n\n");
    printf("In %d address the value is: %d\n", &foo, foo);
    printf("In %d address the value is: %d\n\n\n", &bar, bar);
    printf("*******************************\n\n");
    
}



    /* A function that prints "Hello world!" */
    
static void HelloWorld(void)
{
    char str[]={0x22,0x48,0x65,0x6C,0x6C,0x6F,0x20,0x57,0x6F,
                0x72,0x6C,0x64,0x21,0x22,0x0};
    printf("%s",str);
    printf("\n");
}



    /* A function that raise the power of the number 10 N times */
 
static float DecPower(int power)
{
    int i = 0;
    float result = 1;
    float ten=10;
    
    if (power < 0)
    {
        power *= (-1);
        ten = 0.1;
    }

    for ( i ; i < power ; ++i )   
    {
        result *= ten;
    }

    return result;
}


/* A function that producing a number that is a mirror picture of N */

static int Flip(int num)
{
    int new_num = 0;                   /* The mirror pic number */
    int count = 0;                     /* counting digits */
    int temp = num;        
    
    while ( 0 != temp )           /* A loop that counts digits */
    {
        ++count;
        temp /= 10;
    }


/* A loop that cut the right digit, multiple it in the place of the digit
                                  and adds it to the mirror pic number */
    while (count >= 0)              
    {
        new_num += (num%10) * DecPower(count-1);  /* Cutting and multipling */
        num /= 10;                              /* Cutting N for next loop */
        --count;                              
    }
    return new_num;
}



/* A function that swaps between the values of two 
   given addresses in the memory */
   
static int Swa(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}



