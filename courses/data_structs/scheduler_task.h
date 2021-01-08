/*****************************************************************************
 * File name:   scheduler_task.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-26 17:35:36
 * Description: 
 *****************************************************************************/
#ifndef __SCHEDULER_TASK_H__
#define __SCHEDULER_TASK_H__
#include <stddef.h>             /* size_t     */
#include <time.h>               /* time_t     */

#include "scheduler_enum.h"     /* Sched enum */
#include "uid.h"                /* UID        */

typedef struct sch_task_s sch_task_t;

/*
 * Create a new Task
 * May fail
 *
 * Returns:
 * sch_task_t*      - new task
 * NULL             - on failure
 *
 * Passing function = NULL results in undefined behavior
 * Passing interval_s = 0 results in undefined behavior
 */
sch_task_t *TaskCreate(scheduler_return_t (*function)(void *data),
        void *data, time_t interval_s);

void TaskDestroy(sch_task_t *task);

unique_id_t TaskGetUID(const sch_task_t *task);

scheduler_return_t TaskRun(sch_task_t *task);

/*
 * Update Task's schedule time to interval_s seconds from *now*
 *
 * Returns new schedule time
 */
void TaskUpdateScheduledTime(sch_task_t *task);

/*
 * Peek on Task's schedule time
 */
time_t TaskGetScheduledTime(const sch_task_t *task);

/*
 * Check whether the lhs's uid and 'uid' are the same
 */
int TaskIsSame(const sch_task_t *task, const unique_id_t *uid);

/*
 * Check whether lhs is should be run before rhs
 */
int TaskIsBefore(const sch_task_t *lhs, const sch_task_t *rhs, const void *param);

#endif /* __SCHEDULER_TASK_H__ */
