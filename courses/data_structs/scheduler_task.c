/*****************************************************************************
 * File name:   scheduler_task.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-26 17:35:36
 * Description: 
 *****************************************************************************/

#include <stdio.h>              /*       fprintf        */
#include <stdlib.h>             /*       Malloc         */
#include <time.h>               /*       time()         */
#include <assert.h>             /*       assert         */

#include "utils.h"              /*        Utils         */
#include "uid.h"                /*        Uid.c         */
#include "scheduler_task.h"     /* Forward declarations */

/* Macros                  */
  
/* Forward Declarations    */
struct sch_task_s
{
    unique_id_t id;
    scheduler_return_t (*function)(void *data);
    void *data;

    time_t interval_s;
    time_t scheduled_time;
}; 
 
/* Global variables        */
 
 
/******************************************************************************/
sch_task_t *TaskCreate(scheduler_return_t (*function)(void *data),
                       void *data, time_t interval_s)
{
    sch_task_t *task = (sch_task_t*)malloc(sizeof(sch_task_t));
    if (NULL == task)
    {
        DBG(fprintf(stderr, "Task creation failed!!!\n"));
        return (NULL);
    } 

    task->id = UIDCreate();
    task->function = function;
    if (UIDIsBad(task->id))
    {
        /*task->id = UIDCreate();*/
        free(task);
        return (NULL);
    }
    
    task->data = data;
    task->interval_s = interval_s;
    task->scheduled_time = time(NULL) + interval_s;
    
    return (task);
}   

/******************************************************************************/
void TaskDestroy(sch_task_t *task)
{
    assert(task);
    
    task->function = NULL;
    task->data = NULL;
    free(task);
    task = NULL;
}

/******************************************************************************/
unique_id_t TaskGetUID(const sch_task_t *task)
{
    assert(task);
    
    return (task->id);
}
    
/******************************************************************************/
scheduler_return_t TaskRun(sch_task_t *task)
{
    assert(task);
     
    return (task->function(task->data));
}

/******************************************************************************/
void TaskUpdateScheduledTime(sch_task_t *task)
{
    assert(task);
    
    task->scheduled_time = time(NULL) + task->interval_s;
}

/******************************************************************************/
time_t TaskGetScheduledTime(const sch_task_t *task)
{
    assert(task);
    
    return (task->scheduled_time);
}

/******************************************************************************/
int TaskIsSame(const sch_task_t *lhs, const unique_id_t *uid)
{
    assert(lhs);
    assert(uid);
    
    return (UIDIsSame(lhs->id, *uid));
}    

/******************************************************************************/
int TaskIsBefore(const sch_task_t *lhs, const sch_task_t *rhs,
                                             const void *param)
{
    assert(lhs);
    assert(rhs);
    
    UNUSED_VAR(param);
    
    return (lhs->scheduled_time < rhs->scheduled_time);
}







  
