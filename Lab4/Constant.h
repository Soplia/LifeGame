/**
* @file
*
* @author Created by Jiarui XIE on 2018/12/19
*
* @version 1.00 2018/12/19 Creation
*
* @note Definations of constant values 
*/
#pragma once

/** @brief  Represent the size of _state & _neigh in LifeGame class. */
const int MATRIX_SIZE_LIFEGAME = 5;

/*************************************************************************************/
#define N 624
#define M 397
/** @brief  Constant vector A. */
#define MATRIX_A 0x9908b0dfUL 
/** @brief  Most significant w-r bits. */
#define UPPER_MASK 0x80000000UL
/** @brief  Least significant r bits. */
#define LOWER_MASK 0x7fffffffUL 
/** @brief  The array for the state vector. */
static unsigned long mt[N]; 
 /** @brief  mti==N+1 means mt[N] is not initialized. */
static int mti = N + 1; 

/*************************************************************************************/

/** @brief  Represent the size of _state & _neigh in AgentGame class. */
const int MRX_SIZE_AGENTGAME = 5;

/** @brief  Represent the size of  rule matrix. */
const int MRX_SIZE_RULE = 9;

/** @brief  Represent the empty cell space, ¡õ */
const int CELL_EMPTY = 0;

/** @brief  Represent the cell space is occupied by predator, ¡ö */
const int CELL_PDATOR = 1;

/** @brief  Represent the cell space is occupied by prey, ¨‘ */
const int CELL_PREY = 2;

/** @brief  The possibility of preys occupy the empty cell space, row: prey, column:predator. */
const double MRX_PREY_PDATOR[][MRX_SIZE_RULE] =
								{
	-1.0, 0.50, 0.60, 0.70, 0.80, 1.00, 1.00, 1.00, 1.00,
	0.50, 0.50, 0.33, 0.25, 0.20, 0.17, 0.14, 0.13, 0.00,
	0.60, 0.67, 0.50, 0.40, 0.33, 0.29, 0.25, 0.00, 0.00,
	0.70, 0.75, 0.60, 0.50, 0.43, 0.38, 0.00, 0.00, 0.00,
	0.80, 0.80, 0.67, 0.57, 0.50, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.83, 0.71, 0.63, 0.00, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.86, 0.75, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.88, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
								};

/** @brief  The possibility of preys when preys occupied the cell space, row: prey, column:predator. */
const double MRX_PREY[][MRX_SIZE_RULE] =
								{
	0.40, 0.40, 0.30, 0.20, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.70, 0.50, 0.33, 0.25, 0.00, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.67, 0.50, 0.40, 0.00, 0.00, 0.00, 0.00, 0.00,
	1.00, 0.75, 0.60, 0.50, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.60, 0.50, 0.37, 0.27, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.60, 0.43, 0.31, 0.23, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
								};

/** @brief  The possibility of predator when preys occupied the cell space, row: prey, column:predator. */
const double MRX_PDATOR[][MRX_SIZE_RULE] =
								{
	0.70, 0.70, 1.00, 1.00, 0.60, 0.00, 0.00, 0.00, 0.00,
	0.60, 0.60, 0.77, 0.85, 0.50, 0.00, 0.00, 0.00, 0.00,
	0.50, 0.43, 0.60, 0.70, 0.37, 0.00, 0.00, 0.00, 0.00,
	0.40, 0.35, 0.50, 0.60, 0.27, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.30, 0.43, 0.53, 0.20, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
								};