/*****************************************************************************
 * File name:   knights_tour.h
 * Developer:   HRD7
 * version:		1 
 * Date:        2019-01-13 14:25:40
 * Description: Knights tour solution implementation
 *****************************************************************************/

#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

/*
 * Finds a solution for knight's tour from [row:starting_y, col: starting_x]
 *	 on a 8x8 chess board
 * x,y are between 0 - 7
 * <out_solution_array> is an out parameter that would contain the history
 *	 of knight's movements,
 * where cell's value is the number of turn on which the knight
 *   enters the cell. Numbering begins on 0ץ
 * <out_solution_array>'s size is 64 elements (8X8)
 */ 
void KnightsTour(const unsigned int starting_x, const unsigned int starting_y,
			     unsigned int *out_solution_array); 
 
#endif     /* __KNIGHTS_TOUR_H__ */
