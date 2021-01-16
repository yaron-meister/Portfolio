/*****************************************************************************
 * File name:   scheduler.cpp
 * Developer:   Yaron Meister
 * Date:        2018-11-26 17:35:25
 * Description:	Source file for Scheduler
 *****************************************************************************/

#include <new>          // nothrow

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "scheduler.h"  

using namespace std;

// Global variables

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////

//**********//
//  CTask 
//**********//
/////////////////////////////////////////////////////////////////////////////
CScheduler::CTask::CTask(ActionFunc actionFunc, ParamsBase* params, time_t interval)  : m_id(CUid())
                                                                                      , m_actionFunc(actionFunc)
                                                                                      , m_params(params)
                                                                                      , m_interval(interval)
{
  updateScheduledTime();
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator==(const CTask& other) const
{
  return (m_id == other.m_id);
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator!=(const CTask& other) const
{
  return (!operator==(other));
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator>(const CTask& other) const
{
  return (m_scheduledTime > other.m_scheduledTime);
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator<(const CTask& other) const
{
  return (m_scheduledTime < other.m_scheduledTime);
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator<=(const CTask& other) const
{
  return (!operator>(other));
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::operator>=(const CTask& other) const
{
  return (!operator<(other));
}

/////////////////////////////////////////////////////////////////////////////
CUid CScheduler::CTask::getUID() const
{
  return (m_id);
}

/////////////////////////////////////////////////////////////////////////////
CScheduler::CTask::ETaskRepetition CScheduler::CTask::run()
{
  return (m_actionFunc(m_params));
}

/////////////////////////////////////////////////////////////////////////////
void CScheduler::CTask::updateScheduledTime()
{
  m_scheduledTime = time(nullptr) + m_interval;
}

/////////////////////////////////////////////////////////////////////////////
time_t CScheduler::CTask::getScheduledTime() const
{
  return (m_scheduledTime);
}

/////////////////////////////////////////////////////////////////////////////
bool CScheduler::CTask::isSame(CUid& uid) const
{
  return (m_id == uid);
}

//**************//
//  CScheduler 
//**************//
/////////////////////////////////////////////////////////////////////////////
CScheduler::CScheduler()  : m_pTaskQueue(nullptr)
                          , m_shouldStop(false)
{
  try
  {
    m_pTaskQueue = new CPriorityQ<CTask*>([](const CTask* lhs, const CTask* rhs, const ParamsBase* params) {return (*lhs < *rhs); }, nullptr);
  }
  catch (bad_alloc&)
  {
    cout << "m_pTaskQueue allocation failed" << endl;
  }
}

/////////////////////////////////////////////////////////////////////////////
CScheduler::~CScheduler()
{
  CTask* pTask(nullptr);

  while (!isEmpty())
  { 
    pTask = m_pTaskQueue->dequeue();
    destroyTask(pTask);
  }
}

/////////////////////////////////////////////////////////////////////////////
CUid CScheduler::addTask(CTask::ActionFunc actionFunc, ParamsBase* params, time_t interval)
{
  bool isBad = true;
  CUid uid(isBad);

  if (interval > 0)
  {
    CTask* pTask = new(nothrow) CTask(actionFunc, params, interval);

    if (nullptr != pTask && !pTask->getUID().isBad())
    {
      m_pTaskQueue->enqueue(pTask);
      uid = pTask->getUID();
    }
    else
    {
      destroyTask(pTask);
    }
  }

  return (uid);
}

/////////////////////////////////////////////////////////////////////////////
EStatus CScheduler::removeTask(CUid id)
{
  EStatus eraseStatus(FAILURE);
  CTask* erasedTask(nullptr);

  erasedTask = m_pTaskQueue->erase(nullptr, 
                                [](const CTask* lhs, const CTask* rhs, const ParamsBase* pParams) {return (rhs->isSame(*(CUid*)(pParams))); }, 
                                (ParamsBase*)&id);
  if (nullptr != erasedTask)
  {
    // User's responsibility to free the tasks 
    destroyTask(erasedTask);
    eraseStatus = SUCCESS;
  }

  return (eraseStatus);
}

/////////////////////////////////////////////////////////////////////////////
CScheduler::ERunStatus CScheduler::run()
{
  CTask* pTask(nullptr);
  ERunStatus runStatus(RUN_SUCCESS);

  m_shouldStop = false;

  // Refresh time of all tasks using new PQ
  CPriorityQ<CTask*>* pNewTaskQueue = 
    new (nothrow) CPriorityQ<CTask*>([](const CTask* lhs, const CTask* rhs, const ParamsBase* params) {return (*lhs < *rhs); }, nullptr);
  if (nullptr == pNewTaskQueue)
  {
    UT(cerr << "Scheduler run() failed #1, new task queue creation failed" << endl;)
    return(RUN_SCHEDULER_FAILURE);
  }

  while (!isEmpty())
  {
    pTask = m_pTaskQueue->dequeue();
    pTask->updateScheduledTime();

    if (SUCCESS != pNewTaskQueue->enqueue(pTask))
    {
      destroyTaskQueue(pNewTaskQueue);
      UT(stderr << "Scheduler run() failed #2, new task queue enqueue failed" << endl;)

      return(RUN_SCHEDULER_FAILURE);
    }
  }

  // Destroy the old PQ and assign to scheduler to time-updeted PQ 
  destroyTaskQueue(m_pTaskQueue);
  m_pTaskQueue = pNewTaskQueue;

  // Run all tasks in the new PQ 
  while (!isEmpty() && (false == m_shouldStop))
  {
    pTask = m_pTaskQueue->dequeue();

#ifdef _WIN32
    Sleep(static_cast<DWORD>(pTask->getScheduledTime() - time(NULL)) * SEC_TO_MS);
#else
    sleep(TaskGetScheduledTime(task) - time(NULL));
#endif

    switch (pTask->run())
    {
    case CTask::TASK_REPEAT:
      pTask->updateScheduledTime();

      if (SUCCESS != m_pTaskQueue->enqueue(pTask))
      {
        UT(stderr << "Scheduler run() failed #3, new task queue enqueue failed" << endl;)
        
        return(RUN_SCHEDULER_FAILURE);
      }
      break;
    case CTask::TASK_ERROR:
      runStatus = RUN_USER_FAILURE;
      destroyTask(pTask);
      break;
    case CTask::TASK_NOREPEAT:
      destroyTask(pTask);
      break;
    default:
      break;
    }
  }

  return (runStatus);
}

/////////////////////////////////////////////////////////////////////////////
void CScheduler::stop()
{
  m_shouldStop = true;
}

/******************************************************************************/
size_t CScheduler::taskCount() const
{
  return (m_pTaskQueue->size());
}


/////////////////////////////////////////////////////////////////////////////
bool CScheduler::isEmpty()
{
  return (m_pTaskQueue->isEmpty());
}


/////////////////////////////////////////////////////////////////////////////
void CScheduler::destroyTask(CTask* pTask)
{
  delete(pTask);
  pTask = nullptr;
}


/////////////////////////////////////////////////////////////////////////////
void CScheduler::destroyTaskQueue(CPriorityQ<CTask*>* pTaskQueue)
{
  if (nullptr != pTaskQueue)
  {
    while (!pTaskQueue->isEmpty())
    {
      destroyTask(pTaskQueue->dequeue());
    }

    delete (pTaskQueue);
    pTaskQueue = nullptr;
  }
}