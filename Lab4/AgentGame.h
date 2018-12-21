/**
* @file
*
* @author Created by Jiarui XIE on 2018/12/19
*
* @version 1.00 2018/12/19 Creation
*
* @note Implement a game of life in "text" mode, test it with a glider.
*	     Github: https://github.com/Soplia/LifeGame
*           Copyright  2018 Jiarui XIE. All rights reserved.
*/
#pragma once

#include <iostream>
#include <cstdlib>
#include "Constant.h"
#include "MTRandom.h"
using namespace std;

/**
* @class AgentGame
* @brief  Implement a game of life in "text" mode, test it with a glider.
* @note
* Can be run under two modes: without torus neighbourhood and with a torus universe.
* There are three display formats: display status only / display the number of neighbourhood only and display
* them at the same time.
*/

class AgentGame
{
public:
	/** @brief A Constructor.
	*    @param[in] size the size of the matrix.
	*/
	AgentGame(int size);

	/** @brief A Constructor.
	*    @param[in] size the size of the matrix.
	*    @param[in] a the source matrix.
	*/
	AgentGame(int size, int  a[][MRX_SIZE_AGENTGAME]);

	/** @brief  A Deconstructor. */
	~AgentGame();

	/** @brief  Assign zero to  _state & _neighPrey & _neighPdator . */
	void InitValue();

	/** @brief  Assign zero to  _neighPrey & _neighPdator. */
	void ClearNeigh();

	/** @brief  Display the content of _state & _neigh,  empty: ¨‘  populated: ¡ö.
	*    @param[in] type 1: display _state only 2: display _neigh only 3: display _state & _neigh
	*/
	void Display(int type);

	/** @brief  Display the amount of each agent.
	*    @param[in] times simulation order
	*/
	void DisplayAmount(long int times);

	/** @brief  Assign aim to _state[x][y].
	*    @param[in] x the x_index of _state.
	*    @param[in] y the y_index of _state.
	*    @param[in] aim the source value.
	*/
	void SetState(int x, int y, int aim);

	/** @brief Count the number of _state[x][y]'s neighbourhood.
	*    @param[in] x the x_index of _state.
	*    @param[in] y the y_index of _state.
	*    @param[in] type 1: without torus, 2: with torus.
	*/
	void CountNeighbour(int x, int y, int type);

	/** @brief  Apply CountNeighbour function to the whole of _state metirx.
	*    @param[in] type 1: without torus, 2: with torus.
	*/
	void  UpdateNeighWhole(int type);

	/** @brief According the neighbourhood number of (x,y) to change  _state[x][y] .
	*    @param[in] x the x_index of _neighPrey & _neighPdator.
	*    @param[in] y the y_index of _neighPrey & _neighPdator.
	*/
	int CalculateState(int x, int y);

	/** @brief Update _state[x][y].
	*    @param[in] x the x_index of _state.
	*    @param[in] y the y_index of _state.
	*/
	void UpdateState(int x, int y);

	/** @brief  Update_state. */
	void UpdateStateWhole();

	/** @brief  Whether x inside the bound or not.
	*    @param[in] x the value to be judged.
	*    @return 0: outside the bound, 1: inside the bound
	*/
	bool InBound(int x);

	/** @brief Simulation.
	*    @param[in] times simulation times.
	*    @param[in] type 1: without torus, 2: with torus.
	*    @param[in] typeOfDis display type.
	*/
	void Simulation(long int times, int type, int typeOfDis);

	/** @brief Count the a.
	*    @param[in] times simulation order.
	*/
	void AgentAmount(long int times);
public:
	/** @brief  Stock for State . */
	int **_state;

	/** @brief  Stock for prey neighborhood number. */
	int **_neighPrey;

	/** @brief  Stock for predator neighborhood number. */
	int **_neighPdator;

	/** @brief  Stock for amount of each agent . */
	int _amount[MRX_SIZE_AMOUNT][3];

	/** @brief  Keep the size of  _state & _neigh. */
	int _size;

	/** @brief  Random numbers generator. */
	MTRandom _rdm;
};