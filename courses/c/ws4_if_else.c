/*****************************************************************************
 * Project:     ws4_if_else                                                  *             
 * Date:        21.10.18                                                     *
 * Written by:  Yaron                                                        *
 * Reviewer:    Daria                                                            *
 *                                                                           *                                                                           
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


 
#include <stdio.h>      /* puts, getchar */
#include <errno.h>	    /* errno */

#include "ws4.h"        /* The declarations for the functions */ 

#define Esc 27

int main()
{
    If_Else();
    
    return (0);
}
 
 

  /**************************************************************/
  
int If_Else(void)
{
    char key = 0;                       /* Keyboard key to press */
    int flag = 0;
                                        /* For exit when pressing <Esc> key */
    if (0 != system("stty -icanon -echo"))
	{
		fprintf(stderr, "Couldn't execute stty -icanon -echo, errno = %d\n"
		        , errno);
		        
		return (1);
	}                                   /* Shot down <ENTER> key */
	
    while (0 == flag)
    {
        key = getchar();
        if ('A' == key)
        {
            puts("A pressed\n");
        }
        else if ('T' == key)
        {
            puts("T pressed\n"); 
        }
        else if (Esc == key)
        {
            flag = 1;
        }
        
    }
    
    if (0 != system("stty icanon echo"))
	{
		fprintf(stderr, "Couldn't execute stty icanon echo, errno = %d\n",
		         errno);
		         
		return (1);
	}                                   /* Restoring default of bash */
	
	return (0);
}  








    
