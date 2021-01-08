/*****************************************************************************
 * Project:     WS3                                                           *
 * Date:        18.10.18                                                      *
 * Written by:  Yaron                                                         *
 * Reviewer:    Yael                                                          *
 *                                                                            *
 *****************************************************************************/
 
 /* It's the responsibility of the user to suplly enough memory!!!!!!!!! */


#ifndef _WS2_H_
#define _WS2_H_


/* A function that prints all the environment variables */
void EnvPrint(char *env[]);

/* A function that copys all the environment variables to lower case */
void EnvCopy(char *env[]);

/* A function that calculates THE LAST SURVIVOR OF NAPOLEON */
int NapLast(int size_of_circle);

/* A function that prints THE SIZE OF EACH VARIABLE TYPE */
void SizeOfType(void);


#endif
