/*****************************************************************************
 * Project:     ws4_if_else                                                  *             
 * Date:        21.10.18                                                     *
 * Written by:  Yaron                                                        *
 * Reviewer:    Daria                                                        *
 *                                                                                                                                                         
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


 
#include <stdio.h>      /* puts, getchar */
#include <errno.h>	    /* errno */

#define Esc 27

void PrintA(void);      
void PrintT(void);
void Foo(void);        /* A function for the rest of the functions array */


int main()
{
    char key = 0;                           /* Keyboard key to press */
    int i = 0;                              /* For filling the array */
    void (*arr_of_funcs[256])(void);        /* Array of functions */
    while (i < 256)
    {
        arr_of_funcs[i] = Foo;
         ++i;
    }   
    arr_of_funcs[65] = PrintA;              /* Appropriate function PrintA */
    arr_of_funcs[84] = PrintT;              /* Appropriate function PrintA */
    
    if (0 != system("stty -icanon -echo"))
	{
		fprintf(stderr, "Couldn't execute stty -icanon -echo, errno = %d\n"
		        , errno);
		        
		return (1);
	}                                   /* Shot down <ENTER> key */
	
    while (Esc != key)                       /* Exit when pressing <Esc> key */
    {
        key = getchar();
        arr_of_funcs[(unsigned char)(key)]();   /* Calling appropriate func. */
    }
    
    if (0 != system("stty icanon echo"))
	{
		fprintf(stderr, "Couldn't execute stty icanon echo, errno = %d\n",
		         errno);
		         
		return (1);
	}                                   /* Restoring default of bash */
    
    return (0);
}
 
 

  /**************************************************************/

void PrintA(void)
{
    puts("A is pressed");
}

  /**************************************************************/ 

void PrintT(void)
{
    puts("T is pressed");
}

  /**************************************************************/ 

void Foo(void)
{                         /* A function without a purpose */
}

    

     
