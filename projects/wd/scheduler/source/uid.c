/*****************************************************************************
 * File name:   uid.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-25 11:59:11
 * Description: 
 *****************************************************************************/
 
#include <sys/time.h>   /*      gettimeofday    */
#include <unistd.h>     /*        getpid        */

#include "uid.h"        /* Forward declarations */

/* Macros                  */
 
 
/* Forward Declarations    */
 
 
/* Global variables        */
static size_t count = 1; 
 

/******************************************************************************/
unique_id_t UIDCreate(void)
{
    unique_id_t uid = {0, {0}, 0};
    uid.pid = getpid();  
    uid.counter = count;
    ++count;
    
    if (-1 == gettimeofday(&(uid.time), NULL))
    {
        uid.counter = 0;        
    }
       
    return (uid);
}

/******************************************************************************/
unique_id_t UIDCreateBad(void)
{
    unique_id_t uid = UIDCreate();
    uid.counter = 0;
    
    return (uid);
}
    
/******************************************************************************/
int UIDIsSame(unique_id_t uid1, unique_id_t uid2)
{
    return (uid1.counter == uid2.counter && uid1.pid == uid2.pid);
}    

/******************************************************************************/
int UIDIsBad(unique_id_t uid)
{
    return (0 == uid.counter);
}







  
