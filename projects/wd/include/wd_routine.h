/*****************************************************************************
 * File name:   wd_routine.h
 * Developer:   Yaron Meister
 * Date:        2019-02-10 13:08:07
 * Description: Header of wd_routine.c
 *****************************************************************************/

#ifndef __WD_ROUTINE_H__
#define __WD_ROUTINE_H__

#include <stddef.h>      /* size_t */


enum sched_flag
{
	OFF,
	ON
};

/******************************* Structs **************************************/
typedef struct thread_arg
{
	int argc;
	char **argv;
	char **env;
	time_t interval;
}thread_arg_t;
  
 
int WDRoutine(thread_arg_t input_st);
 
#endif     /* __WD_ROUTINE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
