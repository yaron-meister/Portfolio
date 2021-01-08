/*****************************************************************************
 * File name:   uid.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-25 11:59:11
 * Description: 
 *****************************************************************************/

#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>      /*     size_t     */
#include <sys/types.h>   /*     pid_t      */
#include <sys/time.h>    /* struct timeval */

typedef struct unique_id
{
	pid_t pid;             /* use getpid()       */
	struct timeval time;   /* use gettimeofday() */
	size_t counter; 
} unique_id_t;


/* 
 * The function creates the struct and generate unique number per process
 * the function return the struct by value.
 * In case of failure in timeofday() counter = 0
 *
 * note: the return value isn't a pointer.
 */ 
unique_id_t UIDCreate(void);

/* 
 * The function creates the struct and generate a bad UID 
 * the function return the struct by value.
 * A bad UID expressed with - counter = 0
 *
 * note: the return value isn't a pointer.
 */ 
unique_id_t UIDCreateBad(void);

/* 
 * The function get two uid and check if uid1 is equal to uid2.
 * return: 0 - false,
 *        !0 - true.
 * note: boolean function.
 */
int UIDIsSame(unique_id_t uid1, unique_id_t uid2);

/* 
 * The function get uid and check if uid is valid.
 * return: 0 - false,
 *        !0 - true (counter = 0).
 * note: boolean function.
 */
int UIDIsBad(unique_id_t uid);
 

 
#endif     /* __UID_H__ */

