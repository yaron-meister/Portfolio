/*****************************************************************************
 * File name:   ws8_polymorphism.c
 * Developer:   Yaron
 * Reviewer:    Majd
 * Date:        2018-10-28 16:33:27
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf       */
#include <stdlib.h>    /* realloc      */
#include <string.h>    /* strlen       */
#include <assert.h>    /* assert       */

/* Macros                  */

#define UNUSED_VAR(x) (void)(x)
 
/* Forward Declarations    */
void AddInt(void **p_int, int num); 
void AddFloat(void **p_flo, int num);                                                   
void AddString(void **str, int num);
void PrintInt(void *integer);
void PrintFloat(void *flo);
void PrintString(void *source);
void DoNothing(void *anything);
void FreeMem(void *source);

/* Global variables        */
typedef struct element
    {
        void *data;
        void (*add)(void**, int);
        void (*print)(void*);
        void (*free_mem)(void*);
    } element_t;

/*****************************************************************************
                               MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    int i = 0;
    int x = 5;
    float f = 3.14;
    void *str1 = malloc(15*sizeof(char));
    int y = 8;
    float g = 6.28;
    void *str2 = malloc(15*sizeof(char));
    element_t mission[] = {  {NULL, AddInt, PrintInt, DoNothing},
                             {NULL, AddFloat, PrintFloat, DoNothing},
                             {NULL, AddString, PrintString, FreeMem},
                             {NULL, AddInt, PrintInt, DoNothing},
                             {NULL, AddFloat, PrintFloat, DoNothing},
                             {NULL, AddString, PrintString, FreeMem}
                        };
                        
    
    if (NULL == str1 || NULL == str2)
    {
        printf("malloc faild!!!\n");
        return (1);
    }       
                 
    strcpy(str1, "Hello world");
    strcpy(str2, "A nice day");                        
    
    *(int*)&mission[0].data = x;                                                                   
    *(float*)&mission[1].data = f;
    mission[2].data = str1;
    *(int*)&mission[3].data = y;
    *(float*)&mission[4].data = g;
    mission[5].data = str2;
                        
    for (i = 0; i < 6; ++i)
    {
        mission[i].add(&mission[i].data, 2);   /* פוינטר לפוינטר */
        mission[i].print(mission[i].data);
        mission[i].free_mem(mission[i].data);
    }
    
    return (0);
} 
 
/*****************************************************************/
void AddInt(void **p_int, int num)
{
    assert(p_int);
    *(int*)p_int += num;
}

/*****************************************************************/
void AddFloat(void **p_flo, int num)
{
    assert(p_flo);
    *(float*)p_flo += num;
}

/*****************************************************************/
void AddString(void **str, int num)
{
    char ch[20] = "";           /* Turning integer to char */                          
    assert(*str);
    sprintf(ch, "%d", num);                                                                
    *str = realloc(*str, (strlen((char*)*str) + 2) * sizeof(char));
    if (NULL == *str)
    {
        printf("malloc faild!!!\n");
        exit(1);
    }
    strcat(*str, ch);                                                                       /* memcpy is better */
}

/*****************************************************************/
void PrintInt(void *integer)
{
    assert(integer);
    printf("%d\n", *(int*)&integer);
}

/*****************************************************************/
void PrintFloat(void *flo)
{
    assert(flo);
    printf("%f\n", *(float*)&flo);
}

/*****************************************************************/
void PrintString(void *source)
{
    assert(source);
    printf("%s\n", (char*)source);
}
      
/*****************************************************************/ 
void DoNothing(void *anything)
{
    /* This function is produced because struct has a pattern.
     * The action functions that use it don't require a strings
     * compare function 
     */
        UNUSED_VAR(anything);
}  

/*****************************************************************/ 
void FreeMem(void *source)
{
    assert(source);
    free(source);
}   
