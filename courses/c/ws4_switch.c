/*****************************************************************************
 * Project:     ws4_if_else                                                  *             
 * Date:        21.10.18                                                     *
 * Written by:  Yaron                                                        *
 * Reviewer:    Daria                                                              *
 *                                                                           *                                                                           
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


 
#include <stdio.h>      /* puts, getchar */
#include <errno.h>	    /* errno */

#include "ws4.h"        /* The declarations for the functions */ 

#define Esc 27

int main()
{
    Switch_Case();
    
    return (0);
}
 
 

  /**************************************************************/
  
int Switch_Case(void)
{
    char key = 0;                       /* Keyboard key to press */
    int flag = 0;                       /* For exit when pressing <Esc> key */
    
    if (0 != system("stty -icanon -echo"))
	{
		fprintf(stderr, "Couldn't execute stty -icanon -echo, errno = %d\n"
		        , errno);
		        
		return (1);
	}                                   /* Shot down <ENTER> key */
	
    while (0 == flag)
    {
        key = getchar();
        switch (key)
        {
            case 'A':
                puts("A pressed\n");
                break;
            case 'T':
                puts("T pressed\n");
                break;
            case Esc:
                flag = 1;
                break;
            default:
                puts("This key is not a shortcut\n");
                break;
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








    
