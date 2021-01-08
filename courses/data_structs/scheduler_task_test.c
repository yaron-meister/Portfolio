/*****************************************************************************
 * File name:   scheduler_task_test.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-26 17:35:36
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>                /*        printf()       */
#include <stdlib.h>               /*      EXIT_SUCCESS     */

#include "utils.h"                /*        Utils          */
#include "uid.h"                  /*    White box testing  */
#include "scheduler_task.h"       /*  Forward declarations */


/* Macros                  */
 
/* Forward Declarations    */
struct sch_task_s
{
    unique_id_t id;
    scheduler_return_t (*function) (void *data);
    void *data;

    time_t interval_s;
    time_t scheduled_time;
}; 

void TaskCreate_test(void);
void TaskGetUID_test(void);
void TaskRun_test(void);
void TaskUpdateScheduledTime_test(void);
void TaskGetScheduledTime_test(void);
void TaskIsSame_test(void);
void TaskIsBefore_test(void);

scheduler_return_t PrintExampleFunc(void *data);

/* Global variables        */
static int count_g = 2;       /* count is the number of tests that succeeded */
static int tests_g = 2;       /* Create and Destroy approaved by valgrind    */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{    
    printf("\n******************* Create and Destroy - TEST ***************\n");
    printf("Test No.1 succeeded --- (by valgrind)\n");
    printf("Test No.2 succeeded --- (by valgrind)\n");
    
   /* TaskCreate_test(); */
    TaskGetUID_test();
    TaskRun_test();
    TaskUpdateScheduledTime_test();
    TaskGetScheduledTime_test();
    TaskIsSame_test();
    TaskIsBefore_test();

    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count_g, tests_g - count_g); 
    printf("\n");

    return (EXIT_SUCCESS);
}




/******************************************************************************/
/*
void TaskCreate_test(void)
{   
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task = TaskCreate(function, NULL, interval_s);
    
    TaskDestroy(task);
}
*/

/******************************************************************************/
void TaskGetUID_test(void)
{
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task1 = TaskCreate(function, NULL, interval_s);
    sch_task_t *task2 = TaskCreate(function, NULL, interval_s);
    
    printf("\n******************* GetUID - TEST ***************************\n");
    
    if (1 != (TaskGetUID(task1)).counter)
    {
        printf("Test No.3 failed\n");
    }
    else 
    {
        printf("Test No.3 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
    
    if (2 != (TaskGetUID(task2)).counter)
    {
        printf("Test No.4 failed\n");
    }
    else 
    {
        printf("Test No.4 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    
    TaskDestroy(task1);
    TaskDestroy(task2);
}

/******************************************************************************/
void TaskRun_test(void)
{
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task = TaskCreate(function, NULL, interval_s);
    
    printf("\n******************* Run - TEST ******************************\n");
    
    if (SCHEDULER_NOREPEAT != TaskRun(task))
    {
        printf("Test No.5 failed\n");
    }
    else 
    {
        printf("Test No.5 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
        
    TaskDestroy(task);
}

/******************************************************************************/
void TaskUpdateScheduledTime_test(void)
{
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task = TaskCreate(function, NULL, interval_s);
    time_t after = 0;
    time_t before = task->scheduled_time;
    TaskUpdateScheduledTime(task);
    after = task->scheduled_time;
    
    printf("\n************* UpdateScheduledTime - TEST ********************\n");
    
    if (after != (before + interval_s))
    {
        printf("Test No.6 failed\n");
    }
    else 
    {
        printf("Test No.6 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
        
    TaskDestroy(task);
}

/******************************************************************************/
void TaskGetScheduledTime_test(void)
{
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task = TaskCreate(function, NULL, interval_s);
    time_t after = 0;
    time_t before = TaskGetScheduledTime(task);
    TaskUpdateScheduledTime(task);
    after = TaskGetScheduledTime(task);
    
    printf("\n**************** GetScheduledTime - TEST ********************\n");
    
    if (after != (before + interval_s))
    {
        printf("Test No.7 failed\n");
    }
    else 
    {
        printf("Test No.7 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
        
    TaskDestroy(task);
}

/******************************************************************************/
void TaskIsSame_test(void)
{
    time_t interval_s = 5;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task = TaskCreate(function, NULL, interval_s);
    unique_id_t uid = UIDCreate();
    
    printf("\n********************* IsSame - TEST *************************\n");
    
    if (TaskIsSame(task, &uid))
    {
        printf("Test No.8 failed\n");
    }
    else 
    {
        printf("Test No.8 succeeded\n");
        ++count_g;
    }
    
    ++tests_g; 
    uid.counter = 6;
    
    if (!TaskIsSame(task, &uid))
    {
        printf("Test No.9 failed\n");
    }
    else 
    {
        printf("Test No.9 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
       
    TaskDestroy(task);
}

/******************************************************************************/
void TaskIsBefore_test(void)
{
    time_t interval_s1 = 5;
    time_t interval_s2 = 12;
    scheduler_return_t (*function)(void *data) = PrintExampleFunc;
    sch_task_t *task1 = TaskCreate(function, NULL, interval_s1);
    sch_task_t *task2 = TaskCreate(function, NULL, interval_s2);
       
    printf("\n********************* IsBefore - TEST ***********************\n");
    
    TaskUpdateScheduledTime(task1);
    TaskUpdateScheduledTime(task2);
    
    if (!TaskIsBefore(task1, task2, NULL))
    {
        printf("Test No.10 failed\n");
    }
    else 
    {
        printf("Test No.10 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    task1->interval_s = 10;  
    TaskUpdateScheduledTime(task1);
    
    if (!TaskIsBefore(task1, task2, NULL))
    {
        printf("Test No.11 failed\n");
    }
    else 
    {
        printf("Test No.11 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
    task1->interval_s = 15; 
    TaskUpdateScheduledTime(task1);
    
    if (TaskIsBefore(task1, task2, NULL))
    {
        printf("Test No.12 failed\n");
    }
    else 
    {
        printf("Test No.12 succeeded\n");
        ++count_g;
    }
    
    ++tests_g;
       
    TaskDestroy(task1);
    TaskDestroy(task2);
}


/******************************************************************************/
scheduler_return_t PrintExampleFunc(void *data)
{
    UNUSED_VAR(data);
    printf("\n\n***Run is working***\n\n");
    
    return (SCHEDULER_NOREPEAT);
}




















  
