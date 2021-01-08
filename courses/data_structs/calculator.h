/*****************************************************************************
 * File name:   calculator.h
 * Developer:   HRD7
 * Version: 	1
 * Date:        2018-12-23 15:07:31
 * Description: A modul that calculates 
 *****************************************************************************/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

/*
 * Function returns the result of <exp> after calculation.
 * if <status> is not NULL, <status> will hold the exit status 
 * of the function:
 * 0 - success
 * 1 - memory allocation failure
 * 2 - <exp> has syntax error (not digits, operators or '()')
 * 3 - <exp> has mathematic errors
 */
double Calculate(const char *exp, int *status);

 
#endif     /* __CALCULATOR_H__ */

