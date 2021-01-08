/*****************************************************************************
 * File name:   uid_test.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-25 11:59:11
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "uid.h"       /*              */
#include "utils.h"     /* UNUSED_VAR   */

/* Macros                  */
 
/* Forward Declarations    */
void UID_Test(void);

/* Global variables        */
static int success = 0;
static int tests = 0;

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main()
{
    UID_Test();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", success, tests - success); 
    printf("\n");
    
    return (EXIT_SUCCESS);
}

/*****************************************************************************/ 
void UID_Test(void)
{
    unique_id_t uid1 = UIDCreate();
    unique_id_t uid2 = UIDCreate();
    unique_id_t uid3 = {0, {0}, 0};
    int i = 0;
    i = 5;
    UNUSED_VAR(i);
    uid3 = UIDCreate();
    
    printf("\n********************* UID-TEST ******************************\n");
    
    if (1 != uid1.counter)
    {
        printf("Test No. 1 failed\n");
    }
    else
    {
        printf("Test No. 1 succeeded\n");
        ++success;
    }
    
    ++tests;
    
    if (2 != uid2.counter)
    {
        printf("Test No. 2 failed\n");
    }
    else
    {
        printf("Test No. 2 succeeded\n");
        ++success;
    }
    
    ++tests;
    uid2.counter = 1;
    
    if (!UIDIsSame(uid1, uid2))
    {
        printf("Test No. 3 failed\n");
    }
    else
    {
        printf("Test No. 3 succeeded\n");
        ++success;
    }
    
    ++tests;
    uid3.counter = 0;
    
    if (!UIDIsBad(uid3))
    {
        printf("Test No. 4 failed\n");
    }
    else
    {
        printf("Test No. 4 succeeded\n");
        ++success;
    }
    
    ++tests;
    
    if (UIDIsBad(uid2))
    {
        printf("Test No. 5 failed\n");
    }
    else
    {
        printf("Test No. 5 succeeded\n");
        ++success;
    }
    
    ++tests;
}    






 
