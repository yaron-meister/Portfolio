/*****************************************************************************
 * File name:   scheduler.h
 * Developer:   Yaron Meister
 * Date:        2018-11-26 17:35:25
 * Description: Header file for Scheduler
 *****************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <cstddef>            // size_t 
#include <ctime>              // time_t
#include <functional>

#include "priority_queue.h"   // CPriorityQ
#include "uid.h"              // CUid        

class CScheduler
{
public:
  enum ERunStatus
  {
    RUN_SUCCESS,
    RUN_SCHEDULER_FAILURE,
    RUN_USER_FAILURE
  };

  class CTask
  {
  public:

    enum ETaskRepetition
    {
      TASK_REPEAT,
      TASK_NOREPEAT,
      TASK_ERROR
    };

    class TaskParams : public ParamsBase
    {
    public:
      TaskParams(CUid id) : m_id(id) {}

      CUid m_id;
    };

    using ActionFunc = std::function<ETaskRepetition(ParamsBase*)>;

    // CTor
    CTask(ActionFunc actionFunc, ParamsBase* params, time_t interval);

    //Operators
    bool operator==(const CTask& other) const;
    bool operator!=(const CTask& other) const;
    bool operator>(const CTask& other) const;
    bool operator<(const CTask& other) const;
    bool operator<=(const CTask& other) const;
    bool operator>=(const CTask& other) const;

    /*
     * Returns the ID of the Task
     */
    CUid getUID() const;

    /*
     * Runs the Action function
     */
    ETaskRepetition run();

    /*
     * Update Task's schedule time to interval seconds from *now*
     */
    void updateScheduledTime();

    /*
     * Peek on Task's schedule time
     */
    time_t getScheduledTime() const;

    /*
     * Check whether the lhs's uid and 'uid' are the same
     */
    bool isSame(CUid& uid) const;

  private:
    CUid m_id;
    ActionFunc m_actionFunc;
    ParamsBase* m_params;
    time_t m_interval;        // in [s]
    time_t m_scheduledTime;     // in [s]
  };

  // CTor
  CScheduler();

  // DTor
  ~CScheduler();

  /*
   * Schedule a task
   * May fail
   * interval can't be zero. Passing interval = 0 results in returning BadUID
   *
   * Returns:
   * CUid - id of the task
   * May return BadUID 
   */
  CUid addTask(CTask::ActionFunc actionFunc, ParamsBase* params, time_t interval);

  /*
   * Returns status:
   * 0        - successfully removed
   * non-zero - failed to remove - task not found
   *
   * The behavior is undefined when unique_id is BadUID
   */
  EStatus removeTask(CUid id);

  /*
   * Start the scheduling loop (time = t0)
   * Every task added to the scheduler gets run the first time at
   * (t0 + interval)
   *
   * If the task returns SCH_REPEAT, the task will be rescheduled to be
   * run in interval seconds
   * If the task returns SCH_NOREPEAT or SCH_ERROR, it doesn't get
   * rescheduled
   *
   * run() would run until the last task returns SCH_NOREPEAT or
   * SCH_ERROR, or until stop() is called
   *
   * If run() is called after stop(), the call time is considered the new
   * t0 and the schedules are reset to (new_t0 + interval)
   *
   * Returns:
   * RUN_SCHEDULER_FAILURE  - Scheduler fails
   * RUN_USER_FAILURE       - user function(s) returned SCH_ERROR
   * RUN_SUCCESS            - nothing of the above
   */
  ERunStatus run();

  /*
   * Notify the running scheduler, that it should stop after executing the
   * current task
   */
  void stop();

  /*
   * Count unique tasks scheduled
   */
  size_t taskCount() const;

  /*
   * Check whether there are no tasks scheduled
   *
   * Returns:
   * false  - in case there are tasks scheduled
   * true   - in case there are no tasks scheduled
   */
  bool isEmpty();

private:
  void destroyTask(CTask* pTask);
  void destroyTaskQueue(CPriorityQ<CTask*>* pTaskQueue);

  CPriorityQ<CTask*>* m_pTaskQueue;
  bool m_shouldStop;
};


#endif /* __SCHEDULER_H__ */
