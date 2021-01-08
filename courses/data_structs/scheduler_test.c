/*****************************************************************************
 * File name:   scheduler_test.c
 * Developer:   xyz
 * Reviewer: 
 * Date:        2018-11-26 17:35:25
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>        /*        printf()     */
#include <stdlib.h>       /*     EXIT_SUCCESS    */

#include "utils.h"        /*       Utils         */ 
#include "scheduler.h"    /* Forward declaration */


/* Macros                  */
 
/* Forward Declarations    */
 
void SchedCreate_test(void);
void SchAddTask_test(void);
void SchRemoveTask_test(void);
void SchRunStop_test(void);
void SchTaskCount_test(void);
void SchIsEmpty_test(void);

scheduler_return_t PrintExampleFunc1(void *data);
scheduler_return_t PrintExampleFunc2(void *data);
scheduler_return_t PrintExampleFunc3(void *data);
scheduler_return_t PrintExampleFunc4(void *data);
scheduler_return_t StopFunc(void *data);

/* Global variables        */
static int count_g = 2;       /* count is the number of tests that succeeded */
static int tests_g = 2;       /* Create and Destroy approaved by valgrind    */
static int func1_runs_g = 0;
static int func2_runs_g = 0;
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{    
    printf("\n******************* Create and Destroy - TEST ***************\n");
    printf("Test No.1 succeeded --- (by valgrind)\n");
    printf("Test No.2 succeeded --- (by valgrind)\n");
    
    SchedCreate_test();
    SchAddTask_test();
    SchRemoveTask_test();
    SchRunStop_test(); 
    SchTaskCount_test();
    SchIsEmpty_test();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count_g, tests_g - count_g); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/******************************************************************************/
void SchedCreate_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    
    SchDestroy(scheduler);
}

/******************************************************************************/
void SchAddTask_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    scheduler_return_t (*function1)(void *data) = PrintExampleFunc1;
    time_t interval_s1 = 0;
    scheduler_return_t (*function2)(void *data) = PrintExampleFunc2;
    time_t interval_s2 = 5; 
    scheduler_return_t (*function3)(void *data) = PrintExampleFunc3;
    time_t interval_s3 = 12;  
    unique_id_t uid = SchAddTask(scheduler, function1, NULL, interval_s1);               
    
    printf("\n******************* Add - TEST ******************************\n");
                       
    if (!UIDIsBad(uid))
    {
        printf("Test No.3 failed\n");
    }
    else 
    {
        printf("Test No.3 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    uid = SchAddTask(scheduler, function2, NULL, interval_s2);
        
    if (2 != uid.counter)
    {
        printf("Test No.4 failed\n");
    }
    else 
    {
        printf("Test No.4 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;  
    SchAddTask(scheduler, function3, NULL, interval_s3);
    
    if (2 != SchTaskCount(scheduler))
    {
        printf("Test No.5 failed\n");
    }
    else 
    {
        printf("Test No.5 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    SchDestroy(scheduler);
}

/******************************************************************************/
void SchRemoveTask_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    scheduler_return_t (*function1)(void *data) = PrintExampleFunc1;
    time_t interval_s1 = 3;
    scheduler_return_t (*function2)(void *data) = PrintExampleFunc2;
    time_t interval_s2 = 5;
    int remove_status = 0;
    unique_id_t uid = UIDCreate();             
    
    printf("\n******************* Remove - TEST ***************************\n");
    
    remove_status = SchRemoveTask(scheduler, uid);
                    
    if (0 == remove_status)
    {
        printf("Test No.6 failed\n");
    }
    else 
    {
        printf("Test No.6 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    SchAddTask(scheduler, function1, NULL, interval_s1);
    SchAddTask(scheduler, function2, NULL, interval_s2);
    remove_status = SchRemoveTask(scheduler, uid);
        
    if (0 == remove_status)
    {
        printf("Test No.7 failed\n");
    }
    else 
    {
        printf("Test No.7 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
    uid.counter = 5; 
    remove_status = SchRemoveTask(scheduler, uid);
    
    if (0 != remove_status)
    {
        printf("Test No.8 failed\n");
    }
    else 
    {
        printf("Test No.8 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;

    if (1 != SchTaskCount(scheduler))
    {
        printf("Test No.9 failed\n");
    }
    else 
    {
        printf("Test No.9 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    SchDestroy(scheduler);
}

/******************************************************************************/
void SchRunStop_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    scheduler_return_t (*function1)(void *data) = PrintExampleFunc1;
    time_t interval_s1 = 4;
    scheduler_return_t (*function2)(void *data) = PrintExampleFunc2;
    time_t interval_s2 = 3;
    scheduler_return_t (*function3)(void *data) = StopFunc;
    time_t interval_s3 = 10;            
    
    printf("\n********************* Run/Stop - TEST ***********************\n");
    
    SchAddTask(scheduler, function1, NULL, interval_s1);
    SchAddTask(scheduler, function2, NULL, interval_s2);
    SchAddTask(scheduler, function3, scheduler, interval_s3);
    SchRun(scheduler);
                    
    if (2 != func1_runs_g)
    {
        printf("Test No.10 failed\n");
    }
    else 
    {
        printf("Test No.10 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    
    if (3 != func2_runs_g)
    {
        printf("Test No.11 failed\n");
    }
    else 
    {
        printf("Test No.11 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    
    SchDestroy(scheduler);
}

/******************************************************************************/
void SchTaskCount_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    scheduler_return_t (*function1)(void *data) = PrintExampleFunc1;
    time_t interval_s1 = 2;
    scheduler_return_t (*function2)(void *data) = PrintExampleFunc2;
    time_t interval_s2 = 5; 
    scheduler_return_t (*function3)(void *data) = PrintExampleFunc3;
    time_t interval_s3 = 12;                 
    
    printf("\n******************* Count - TEST ****************************\n");
                          
    if (0 != SchTaskCount(scheduler))
    {
        printf("Test No.12 failed\n");
    }
    else 
    {
        printf("Test No.12 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    SchAddTask(scheduler, function1, NULL, interval_s1);
    SchAddTask(scheduler, function2, NULL, interval_s2);
    SchAddTask(scheduler, function3, NULL, interval_s3);
        
    if (3 != SchTaskCount(scheduler))
    {
        printf("Test No.13 failed\n");
    }
    else 
    {
        printf("Test No.13 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;  

    SchDestroy(scheduler);
}

/******************************************************************************/
void SchIsEmpty_test(void)
{   
    scheduler_t *scheduler = SchCreate();
    scheduler_return_t (*function1)(void *data) = PrintExampleFunc1;
    time_t interval_s1 = 2;
    scheduler_return_t (*function2)(void *data) = PrintExampleFunc2;
    time_t interval_s2 = 5; 
    scheduler_return_t (*function3)(void *data) = PrintExampleFunc3;
    time_t interval_s3 = 12;                 
    
    printf("\n******************* IsEmpty - TEST **************************\n");
                          
    if (!SchIsEmpty(scheduler))
    {
        printf("Test No.14 failed\n");
    }
    else 
    {
        printf("Test No.14 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    SchAddTask(scheduler, function1, NULL, interval_s1);
    SchAddTask(scheduler, function2, NULL, interval_s2);
    SchAddTask(scheduler, function3, NULL, interval_s3);
        
    if (SchIsEmpty(scheduler))
    {
        printf("Test No.15 failed\n");
    }
    else 
    {
        printf("Test No.15 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;  

    SchDestroy(scheduler);
}

/******************************************************************************/
scheduler_return_t PrintExampleFunc1(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***Function 1 is working***\n\n");
    ++func1_runs_g;
    
    return (SCHEDULER_REPEAT);
}

/******************************************************************************/
scheduler_return_t PrintExampleFunc2(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***Function 2 is working***\n\n");
    ++func2_runs_g;
    
    return (SCHEDULER_REPEAT);
}

/******************************************************************************/
scheduler_return_t PrintExampleFunc3(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***Function 3 is working***\n\n");
    
    return (SCHEDULER_ERROR);
}

/******************************************************************************/
scheduler_return_t PrintExampleFunc4(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***Function 4 is working***\n\n");
    
    return (SCHEDULER_ERROR);
}

/******************************************************************************/
scheduler_return_t StopFunc(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***StopFunc is working***\n\n");
    
    SchStop(data);

    return (SCHEDULER_NOREPEAT);
}













  
