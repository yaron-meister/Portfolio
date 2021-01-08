/*****************************************************************************
 * File name:   scheduler.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-26 17:35:25
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>           /*      fprintf()       */
#include <stdlib.h>          /*      malloc          */
#include <assert.h>          /*      assert          */
#include <unistd.h>          /*       sleep          */

#include "utils.h"           /*        Utils         */
#include "pqueue.h"          /*      pqueue.c        */
#include "scheduler.h"       /* Forward declarations */
#include "scheduler_task.h"  /*   Scheduler_task.c   */

/* Macros                  */
 
 
/* Forward Declarations    */
struct scheduler_s
{
    pq_t *task_queue;
    int should_stop;
}; 
 
/* Global variables        */
 
 
/******************************************************************************/
scheduler_t *SchCreate(void)
{
    int (*is_before)(const void *task1, const void *task2, const void *param)
                = (int(*)(const void*, const void*, const void*))TaskIsBefore;
       
    scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
    if (NULL == scheduler)
    {
        DBG(fprintf(stderr, "Scheduler creation failed!!!\n"));
        return (NULL);
    }
    
    scheduler->task_queue = PQCreate(is_before, NULL);
    if (NULL == scheduler->task_queue)
    {
        DBG(fprintf(stderr, "Scheduler creation failed!!!\n"));
        free(scheduler);
        return (NULL);
    }
    
    scheduler->should_stop = 0;
    
    return (scheduler);
}

/******************************************************************************/
void SchDestroy(scheduler_t *scheduler)
{
    assert(scheduler);
    
    /* User's responsibility to free the tasks */
    while (!SchIsEmpty(scheduler))  
    {
        TaskDestroy(PQDequeue(scheduler->task_queue));
    }
    
    PQDestroy(scheduler->task_queue);
    scheduler->task_queue = NULL;
    free(scheduler);
    scheduler = NULL;
}
    
/******************************************************************************/
unique_id_t SchAddTask(scheduler_t *scheduler, 
                       scheduler_return_t (*function)(void *data),
                       void *data, time_t interval_s)
{
    int enq_status = 0;
    sch_task_t *task = NULL;
    
    assert(scheduler);
    
    if (0 >= interval_s)
    {
        return (UIDCreateBad());
    }
    
    task = TaskCreate(function, data, interval_s);
    if (NULL == task)
    {
        return (UIDCreateBad());
    }
    
    enq_status = PQEnqueue(scheduler->task_queue, task);
    if (0 != enq_status)
    {
        TaskDestroy(task);
        task = NULL;
        return (UIDCreateBad());
    }
    
    return (TaskGetUID(task));
}   

/******************************************************************************/
int SchRemoveTask(scheduler_t *scheduler, unique_id_t uid)
{
    void *erased_task = NULL;
    int(*is_match)(const void *data,const void *args) 
                                = (int (*)(const void*, const void*))TaskIsSame;
                                   
    assert(scheduler);
     
    erased_task = PQErase(scheduler->task_queue, is_match, &uid);
    
    if (NULL == erased_task)
    {
        return (1);
    }

    /* User's responsibility to free the tasks */
    TaskDestroy(erased_task);
    erased_task = NULL;
 
    return (0);
}

/**************************************************************************/
scheduler_run_t SchRun(scheduler_t *scheduler)
{
    sch_task_t *task             = NULL;
    pq_t *new_pq                 = NULL;
    scheduler_return_t func_stat = SCHEDULER_REPEAT;
    scheduler_run_t ret_stat     = SCHEDULER_NO_FAILURES;
    
    assert(scheduler);
    
    scheduler->should_stop = 0;
    
    /* Refresh time of all tasks using new PQ */
    new_pq = PQCreate( (int (*)(const void *, const void *
                                            , const void *))TaskIsBefore, NULL);
    if (NULL == new_pq)
    {
        UT(fprintf(stderr, "SchRun failed, PQCreate returned NULL\n");)
        return(SCHEDULER_ALLOCATION_FAILURE);
    }

    while (!SchIsEmpty(scheduler))
    {
        task = PQDequeue(scheduler->task_queue);
        TaskUpdateScheduledTime(task);
        
        if (0 != PQEnqueue(new_pq, task))
        {
            while (!PQIsEmpty(new_pq))
            {
                TaskDestroy(PQDequeue(new_pq));
            }
            
            PQDestroy(new_pq);
            new_pq = NULL;
            UT(fprintf(stderr, "SchRun failed, PQEnqueue returned FAILURE\n");)
            return(SCHEDULER_ALLOCATION_FAILURE);
        }
    }
    
    /* destroy to the old PQ and assign to scheduler to time-updeted PQ */
    PQDestroy(scheduler->task_queue);
    scheduler->task_queue = new_pq;
    
    /* Run all tasks in the new PQ */
    while ( (!SchIsEmpty(scheduler)) && (0 == scheduler->should_stop))
    {
        task = PQDequeue(scheduler->task_queue);
        sleep(TaskGetScheduledTime(task) - time(NULL));
        func_stat = TaskRun(task);
        
        switch(func_stat)
        {
            case SCHEDULER_REPEAT:
                TaskUpdateScheduledTime(task);
            
                if (0 != PQEnqueue(scheduler->task_queue, task))
                {
                    UT(fprintf(stderr, "SchRun failed, PQEnqueue returned "
                                                                 "FAILURE\n");)
                    return(SCHEDULER_ALLOCATION_FAILURE);
                }
                break;
            case SCHEDULER_ERROR:
                ret_stat = SCHEDULER_USER_FAILURES;
                TaskDestroy(task);
                break;
            case SCHEDULER_NOREPEAT:
                TaskDestroy(task);
                break;    
            default :
                break;
        }
    }
    
    return (ret_stat);
}

/*
scheduler_run_t SchRun(scheduler_t *scheduler)
{
    int (*is_before)(const void *task1, const void *task2, const void *param)
                = (int(*)(const void*, const void*, const void*))TaskIsBefore;
                    
    pq_t *temp_pq = NULL;           
    sch_task_t *task = NULL;        
    sch_task_t *next_task = NULL;
    scheduler_return_t ret = SCHEDULER_NOREPEAT;    
    
    assert(scheduler);
    
    scheduler->should_stop = 0;                  
    
    while (!SchIsEmpty(scheduler) && 0 == scheduler->should_stop)
    {
        task = PQDequeue(scheduler->task_queue);

        
  ********************* while (timer < TaskGetScheduledTime(task))
        {
            timer = time(NULL);
        }***********************************************
        
        sleep(TaskGetScheduledTime(task) - time(NULL));
        ret = TaskRun(task);
        TaskUpdateScheduledTime(task);
        
        if (SCHEDULER_REPEAT == ret)
        {
            if (0 != PQEnqueue(scheduler->task_queue, task))
            {
                return (SCHEDULER_ALLOCATION_FAILURE);
            }
        }
        else 
        {
            TaskDestroy(task);
            
            if (SCHEDULER_ERROR == ret)
            {
                return (SCHEDULER_USER_FAILURES);
            }
        }                    
    }
    
    if (0 != scheduler->should_stop)
    {
        temp_pq = PQCreate(is_before, NULL);
        if (NULL == temp_pq)
        {
            DBG(fprintf(stderr, "Scheduler RUN failed!!!\n"));
            SchDestroy(scheduler);
            scheduler = NULL;
            return (SCHEDULER_ALLOCATION_FAILURE);
        }
        
        while (!PQIsEmpty(scheduler->task_queue))
        {
            next_task = PQDequeue(scheduler->task_queue);
            TaskUpdateScheduledTime(next_task);
            if (0 != PQEnqueue(temp_pq, next_task))
            {
                return (SCHEDULER_ALLOCATION_FAILURE);
            }
        }
        
        PQDestroy(scheduler->task_queue);
        scheduler->task_queue = temp_pq;
    }
    
    return (SCHEDULER_NO_FAILURES);
}*/

/******************************************************************************/
void SchStop(scheduler_t *scheduler)
{
    assert(scheduler);
    
    scheduler->should_stop = 1;
}
    
/******************************************************************************/   
size_t SchTaskCount(const scheduler_t *scheduler)
{
    assert(scheduler);
    
    return (PQSize(scheduler->task_queue));
}

/******************************************************************************/
int SchIsEmpty(const scheduler_t *scheduler)
{
    assert(scheduler);
    
    return (PQIsEmpty(scheduler->task_queue));
}
    











  
