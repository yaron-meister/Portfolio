/*****************************************************************************
 * File name:   scheduler_test.c
 * Developer:   Yaron Meister
 * Date:        2018-11-26 17:35:25
 * Description:
 * Test Flow:
 *****************************************************************************/

#include  <functional>

#include "scheduler.h"
#include "tests.h"

/* Forward Declarations    */

CScheduler::CTask::ETaskRepetition printExampleFunc1(ParamsBase* pParams);
CScheduler::CTask::ETaskRepetition printExampleFunc2(ParamsBase* pParams);
CScheduler::CTask::ETaskRepetition printExampleFunc3(ParamsBase* pParams);
CScheduler::CTask::ETaskRepetition printExampleFunc4(ParamsBase* pParams);
CScheduler::CTask::ETaskRepetition stopFunc(ParamsBase* pParams);

class SchedulerTest : public Test
{
public:
  using TestActionFunc = std::function<CScheduler::CTask::ETaskRepetition(ParamsBase* pParams)>;

  void addTaskTest();
  void removeTaskTest();
  void runStopTest();
  void taskCountTest();
  void isEmptyTest();

  static void incrementFunc1Runs() { ++m_func1RunsNum; }
  static void incrementFunc2Runs() { ++m_func2RunsNum; }
  static unsigned short getFunc1Runs() { return (m_func1RunsNum); }
  static unsigned short getFunc2Runs() { return (m_func2RunsNum); }

private:
  static unsigned short m_func1RunsNum;
  static unsigned short m_func2RunsNum;
};

/*  Global/Static variables  */
unsigned short SchedulerTest::m_func1RunsNum = 0;
unsigned short SchedulerTest::m_func2RunsNum = 0;


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
  SchedulerTest schedulerTest;

  schedulerTest.addTaskTest();
  schedulerTest.removeTaskTest();
  schedulerTest.runStopTest();
  schedulerTest.taskCountTest();
  schedulerTest.isEmptyTest();

  return (EXIT_SUCCESS);
}

/******************************************************************************/
void SchedulerTest::addTaskTest()
{
  CScheduler scheduler;

  printf("\n******************* Add - TEST ******************************\n");

  time_t intervalS1(0);
  CUid uid = scheduler.addTask(TestActionFunc(printExampleFunc1), nullptr, intervalS1);
  equalityTest<bool>(uid.isBad(), true);

  time_t intervalS2(5);
  uid = scheduler.addTask(TestActionFunc(printExampleFunc2), nullptr, intervalS2);
  equalityTest<size_t>(uid.getCounter(), 3);

  
  time_t intervalS3(12);
  scheduler.addTask(TestActionFunc(printExampleFunc3), nullptr, intervalS3);
  equalityTest<size_t>(scheduler.taskCount(), 2);
}

/******************************************************************************/
void SchedulerTest::removeTaskTest()
{
  CScheduler scheduler;
  EStatus removeStatus(SUCCESS);
  time_t intervalS2(5);

  printf("\n******************* Remove - TEST ***************************\n");

  CUid uid;
  removeStatus = scheduler.removeTask(uid);
  equalityTest<EStatus>(removeStatus, FAILURE);
  
  time_t intervalS1(3);
  scheduler.addTask(TestActionFunc(printExampleFunc1), nullptr, intervalS1);
  removeStatus = scheduler.removeTask(uid);
  equalityTest<EStatus>(removeStatus, FAILURE);

  uid = scheduler.addTask(TestActionFunc(printExampleFunc2), nullptr, intervalS2);
  removeStatus = scheduler.removeTask(uid);
  equalityTest<EStatus>(removeStatus, SUCCESS);
  equalityTest<size_t>(scheduler.taskCount(), 1);
}

/******************************************************************************/
void SchedulerTest::runStopTest()
{
  CScheduler scheduler;

  printf("\n********************* Run/Stop - TEST ***********************\n");

  time_t intervalS1(4);
  time_t intervalS2(3);
  time_t intervalS3(10);
  scheduler.addTask(TestActionFunc(printExampleFunc1), nullptr, intervalS1);
  scheduler.addTask(TestActionFunc(printExampleFunc2), nullptr, intervalS2);
  scheduler.addTask(TestActionFunc(stopFunc), (ParamsBase*)&scheduler, intervalS3);
  scheduler.run();
  equalityTest<unsigned short>(SchedulerTest::getFunc1Runs(), 2);
  equalityTest<unsigned short>(SchedulerTest::getFunc2Runs(), 3);
}

/******************************************************************************/
void SchedulerTest::taskCountTest()
{
  CScheduler scheduler;

  printf("\n******************* Count - TEST ****************************\n");

  equalityTest<size_t>(scheduler.taskCount(), 0);
  
  time_t intervalS1(2);
  time_t intervalS2(5);
  time_t intervalS3(12);
  scheduler.addTask(TestActionFunc(printExampleFunc1), nullptr, intervalS1);
  scheduler.addTask(TestActionFunc(printExampleFunc2), nullptr, intervalS2);
  scheduler.addTask(TestActionFunc(printExampleFunc3), nullptr, intervalS3);
  equalityTest<size_t>(scheduler.taskCount(), 3);
}

/******************************************************************************/
void SchedulerTest::isEmptyTest()
{
  CScheduler scheduler;

  printf("\n******************* IsEmpty - TEST **************************\n");

  equalityTest<bool>(scheduler.isEmpty(), true);
  
  time_t intervalS1(2);
  time_t intervalS2(5);
  time_t intervalS3(12);
  CUid uid1 = scheduler.addTask(TestActionFunc(printExampleFunc1), nullptr, intervalS1);
  CUid uid2 = scheduler.addTask(TestActionFunc(printExampleFunc2), nullptr, intervalS2);
  CUid uid3 = scheduler.addTask(TestActionFunc(printExampleFunc3), nullptr, intervalS3);
  equalityTest<bool>(scheduler.isEmpty(), false);

  scheduler.removeTask(uid1);
  scheduler.removeTask(uid2);
  scheduler.removeTask(uid3);
  equalityTest<bool>(scheduler.isEmpty(), true);
}

/******************************************************************************/
CScheduler::CTask::ETaskRepetition printExampleFunc1(ParamsBase* pParams)
{
  UNUSED_VAR(pParams);
  cout << "\n\n***Function 1 is working***\n\n";
  SchedulerTest::incrementFunc1Runs();

  return (CScheduler::CTask::TASK_REPEAT);
}

/******************************************************************************/
CScheduler::CTask::ETaskRepetition printExampleFunc2(ParamsBase* pParams)
{
  UNUSED_VAR(pParams);
  cout << "\n\n***Function 2 is working***\n\n";
  SchedulerTest::incrementFunc2Runs();

  return (CScheduler::CTask::TASK_REPEAT);
}

/******************************************************************************/
CScheduler::CTask::ETaskRepetition printExampleFunc3(ParamsBase* pParams)
{
  UNUSED_VAR(pParams);
  cout << "\n\n***Function 3 is working***\n\n";

  return (CScheduler::CTask::TASK_ERROR);
}

/******************************************************************************/
CScheduler::CTask::ETaskRepetition printExampleFunc4(ParamsBase* pParams)
{
  UNUSED_VAR(pParams);
  cout << "\n\n***Function 3 is working***\n\n";

  return (CScheduler::CTask::TASK_ERROR);
}

/******************************************************************************/
CScheduler::CTask::ETaskRepetition stopFunc(ParamsBase* pParams)
{
  cout << "\n\n***StopFunc is working***\n\n";

  if (pParams)
  {
    ((CScheduler*)pParams)->stop();
  }

  return (CScheduler::CTask::TASK_NOREPEAT);
}
