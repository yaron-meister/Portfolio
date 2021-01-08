/*******************************************************************************
 * File name:   thread_pool_test.cpp
 * Developer:   Aviv Nevo
 * Reviewer:    Alon
 * Date:        2019-04-14 14:50:48
 * Test Flow:   Test cases 
 ******************************************************************************/
 
#include <iostream>     // cout
#include <cstdlib>      // EXIT_SUCCESS
#include <unistd.h>     // sleep
#include <chrono>       // std::chrono
#include <ctime>        // std::time_t, std::time

#include "thread_pool.h"         // Declarations

using namespace std;
using namespace ilrd;
/********************************* Macros *************************************/
 
/**************************** Global Variables ********************************/

class TestTask : public Task
{
public:
    TestTask(Task::Priority priority) : Task(priority) {}
    ~TestTask() {}
    size_t GetHighPriorityCounter() { return (m_high_priority_counter);}
    size_t GetLowPriorityCounter() { return (m_low_priority_counter);}

private:
    void Execute() override;
    static std::atomic_size_t m_high_priority_counter;
    static std::atomic_size_t m_low_priority_counter;
};

std::atomic_size_t TestTask::m_high_priority_counter(0);
std::atomic_size_t TestTask::m_low_priority_counter(0);

class LongTask : public Task
{
public:
    LongTask(Task::Priority priority) : Task(priority) {}
    ~LongTask() {}

private:
    void Execute() override;
};


static int g_tests_passed  = 0;
static int g_tests_overall = 0;
 
/*************************** Forward Declarations *****************************/
static void AddTaskTest();
static void ThreadNumTest();
static void PauseResumeTest();
static void CombinedTest();

/* Test results print functions */
template<typename T>
void TestFunc(const char *test, T value, T expected_val);

static void PrintTestSummary(void); 

/******************************** M-A-I-N *************************************/
int main(/*int argc, char *argv[], char *env[]*/)
{
    ThreadNumTest();
    PauseResumeTest();
    AddTaskTest();
    CombinedTest();

    PrintTestSummary();
    return (EXIT_SUCCESS);
}

/************************** Function Definition *******************************/
static void AddTaskTest()
{
    size_t n_threads = 5;
    ThreadPool pool(n_threads);

  	cout <<"\n******************** AddTask Test *************************\n";

    TestFunc("Activate Check: ", n_threads, pool.GetNumOfThreads());

    shared_ptr<TestTask> task(new TestTask(Task::Priority::HIGH));

    pool.AddTask(task);
    pool.AddTask(task);
    pool.AddTask(task);

    // std::this_thread::sleep_for(chrono::milliseconds(30));
    sleep(1);
    TestFunc("Task DO Check: \t", true, 3 == task->GetHighPriorityCounter());

    shared_ptr<LongTask> long_task(new LongTask(Task::Priority::LOW));
    pool.AddTask(long_task);
}

/**************************************************************************/
static void ThreadNumTest()
{
  	cout <<"\n******************** Thread Num Test *************************\n";
    ThreadPool empty_pool(0);
    TestFunc("Empty Pool Check: ", (size_t)0, empty_pool.GetNumOfThreads());


    size_t n_threads = 5;
    ThreadPool pool(n_threads);
    TestFunc("Activate Check: ", n_threads, pool.GetNumOfThreads());

    size_t n_tests(10);
    size_t true_counter(0);
    for(size_t i = 0; i < (n_tests/2); i++)
    {
        pool.SetNumOfThreads(100);
        true_counter += (100 == pool.GetNumOfThreads()); 

        pool.SetNumOfThreads(1);
        true_counter += (1 == pool.GetNumOfThreads()); 
    }

    TestFunc("Set (loop) Check: ", n_tests, true_counter);
}

/**************************************************************************/
static void PauseResumeTest()
{
    cout <<"\n******************** Pause Resume Test ***********************\n";

    size_t n_threads = 5;
    ThreadPool pool(n_threads);
    TestFunc("Activate Check: ", n_threads, pool.GetNumOfThreads());

    pool.Pause();
    TestFunc("Pause Check: \t", n_threads, pool.GetNumOfThreads());

    std::chrono::duration<int> timeout(1);
    TestFunc("Pause (timeout) Check:", (size_t)0, pool.Pause(timeout));
    
    pool.Resume();
    TestFunc("Resume Check: \t", true, 0 < pool.Pause(timeout));
}

/**************************************************************************/
static void CombinedTest()
{
    cout <<"\n********************** Combined Test *************************\n";

    size_t n_threads = 5;
    ThreadPool pool(n_threads);
    TestFunc("Activate Check: ", n_threads, pool.GetNumOfThreads());

    shared_ptr<TestTask> task(new TestTask(Task::Priority::LOW));

    pool.AddTask(task);
    pool.AddTask(task);
    pool.AddTask(task);
    pool.AddTask(task);
    pool.AddTask(task);

    pool.Pause();
    TestFunc("Pause (tasks) Check#1: ", true, 5 > task->GetLowPriorityCounter());

    pool.Resume();
    sleep(2);
    TestFunc("Resume (tasks) Check: ", true, 5 == task->GetLowPriorityCounter());

    pool.Pause();
    pool.AddTask(task);
    pool.AddTask(task);
    pool.AddTask(task);
    TestFunc("Pause (tasks) Check#2: ", true, 5 == task->GetLowPriorityCounter());

}

/**************************************************************************/

void TestTask::Execute()
{
    if (GetPriority() < Task::Priority::MEDIUM) 
    {
        ++m_high_priority_counter;
    }
    else
    {
        sleep(1);
        ++m_low_priority_counter;
    }
}

void LongTask::Execute()
{
    TestFunc("Long Task DO Check: ", true, true);
    sleep(2);
}
/************************** Auxiliary Function *******************************/
const char* const green = "\033[1;32m";
const char* const red = "\033[1;32m";
const char* const yellow = "\033[1;33m";
const char* const cyan = "\033[1;36m";
const char* const reset = "\033[0m"; 

/**********************************************/
template<typename T>
void TestFunc(const char *test, T value, T expected_val)
{   
    ++g_tests_overall;

    std::cout<<test;
    
    if(value == expected_val)
    {
        ++g_tests_passed;
        cout<<cyan<<"\tSUCCESS\n"<<reset;
    }
    else
    {
        cout<<yellow<<"\t\tFAILURE\n"<<reset;
    }
}

/**********************************************/
static void PrintTestSummary(void)
{
    cout<<green;
    cout<<"=============================================================\n";
    cout<<"\t\tTests Summary: "<<g_tests_passed<<"/"<<g_tests_overall<<" passed\n";
    cout<<"=============================================================\n";
    cout<<reset;
}
