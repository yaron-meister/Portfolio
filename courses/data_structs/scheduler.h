/*****************************************************************************
 * File name:   scheduler.h
 * Developer:   Yaron Meister
 
 * Reviewer: 
 * Date:        2018-11-26 17:35:25
 * Description: 
 *****************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include <stddef.h>             /* size_t     */

#include "scheduler_enum.h"     /* Sched enum */
#include "uid.h"                /* UID        */

typedef struct scheduler_s scheduler_t;

typedef enum
{
    SCHEDULER_NO_FAILURES,
    SCHEDULER_ALLOCATION_FAILURE,
    SCHEDULER_USER_FAILURES
} scheduler_run_t;

scheduler_t *SchCreate(void);
void SchDestroy(scheduler_t *scheduler);

/*
 * Schedule a task
 * May fail
 * interval_s can't be zero. Passing interval_s = 0 results in returning BadUID
 *
 * Returns:
 * unique_id_t      - id of the task
 * May return BadUID in case of allocation failure or when interval_s is wrong
 */
unique_id_t SchAddTask(scheduler_t *scheduler,
        scheduler_return_t (*function)(void *data),
        void *data, time_t interval_s);

/*
 * Returns status:
 * 0        - successfully removed
 * non-zero - failed to remove - task not found
 *
 * The behavior is undefined when unique_id is BadUID
 */
int SchRemoveTask(scheduler_t *scheduler, unique_id_t uid);

/*
 * Start the scheduling loop (time = t0)
 * Every task added to the scheduler gets run the first time at
 * (t0 + interval_s)
 *
 * If the task returns SCHEDULER_REPEAT, the task will be rescheduled to be
 * run in interval_s seconds
 * If the task returns SCHEDULER_NOREPEAT or SCHEDULER_ERROR, it doesn't get
 * rescheduled
 *
 * SchRun() would run until the last task returns SCHEDULER_NOREPEAT or
 * SCHEDULER_ERROR, or until SchStop() is called
 *
 * If SchRun() is called after SchStop(), the call time is considered the new
 * t0 and the schedules are reset to (new_t0 + interval_s)
 *
 * Returns:
 * SCHEDULER_ALLOCATION_FAILURE - allocation failure during refresh
 * SCHEDULER_USER_FAILURES      - user function(s) returned SCHEDULER_ERROR
 * SCHEDULER_NO_FAILURES        - nothing of the above
 */
scheduler_run_t SchRun(scheduler_t *scheduler);

/*
 * Notify the running scheduler, that it should stop after executing the
 * current task
 */
void SchStop(scheduler_t *scheduler);

/*
 * Count unique tasks scheduled
 */
size_t SchTaskCount(const scheduler_t *scheduler);

/*
 * Check whether there are no tasks scheduled
 *
 * Returns:
 * 0        - in case there are tasks scheduled
 * non-zero - in case there are no tasks scheduled
 */
int SchIsEmpty(const scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */
