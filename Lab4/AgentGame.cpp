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

#include "AgentGame.h"

/** @brief A Constructor.
*    @param[in] size the size of the matrix.
*/
AgentGame::AgentGame(int size)
{
	_size = size;
	_state = new int *[size];
	for (int i = 0; i < _size; i++)
		_state[i] = new int[_size];

	_neighPrey = new int *[size];
	_neighPdator = new int *[size];
	for (int i = 0; i < _size; i++)
	{
		_neighPrey[i] = new int[_size];
		_neighPdator[i] = new int[_size];
	}
	InitValue();
}

/** @brief A Constructor.
*    @param[in] size the size of the matrix.
*    @param[in] a the source matrix.
*/
AgentGame::AgentGame(int size, int a[][MRX_SIZE_AGENTGAME])
{
	_size = size;
	_state = new int *[size];
	for (int i = 0; i < _size; i++)
		_state[i] = new int[_size];

	_neighPrey = new int *[size];
	_neighPdator = new int *[size];
	for (int i = 0; i < _size; i++)
	{
		_neighPrey[i] = new int[_size];
		_neighPdator[i] = new int[_size];
	}

	InitValue();

	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_state[i][j] = a[i][j];

	//控制每次都不一样的开关
	//_rdm.InitGenrand((unsigned long)time(NULL));
}

/** @brief  A Deconstructor. */
AgentGame::~AgentGame()
{
	for (int i = 0; i < _size; i++)
	{
		delete[] _state[i];
		delete[] _neighPrey[i];
		delete[] _neighPdator[i];
	}

	delete[] _state;
	delete[] _neighPrey;
	delete[] _neighPdator;
}

/** @brief  Assign zero to  _state & _neighPrey & _neighPdator . */
void AgentGame::InitValue()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			_state[i][j] = 0;
			_neighPrey[i][j] = 0;
			_neighPdator[i][j] = 0;
		}
	for (int i = 0; i < MRX_SIZE_AMOUNT; i++)
		_amount[i][0] = _amount[i][1] = _amount[i][2] = 0;
}

/** @brief  Assign zero to  _neighPrey & _neighPdator. */
void AgentGame::ClearNeigh()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			_neighPrey[i][j] = 0;
			_neighPdator[i][j] = 0;
		}
}

/** @brief  Assign aim to _state[x][y].
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*    @param[in] aim the source value.
*/
void AgentGame::SetState(int x, int y, int aim)
{
	_state[x][y] = aim;
}

/** @brief  Whether x inside the bound or not.
*    @param[in] x the value to be judged.
*    @return 0: outside the bound, 1: inside the bound
*/
bool AgentGame::InBound(int x)
{
	return (x >= 0 && x < _size);
}

/** @brief Count the number of _state[x][y]'s neighbourhood.
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*    @param[in] type 1: without torus, 2: with torus.
*/
void AgentGame::CountNeighbour(int x, int y, int type)
{
	for (int i = 0; i <= 2; i++)
	{
		int tempX = x - 1;
		tempX += i;
		if (type == 1)
		{
			//cout << "tempX = " << tempX << endl;
			if (!InBound(tempX))
				continue;
		}
		else if (type == 2)
		{
			if (tempX == -1)
				tempX = _size - 1;
			else if (tempX == _size)
				tempX = 0;
			//if (!InBound(tempX))
				//continue;
		}
		for (int j = 0; j <= 2; j++)
		{
			int tempY = y - 1;
			tempY += j;
			if (type == 1)
			{
				if (!InBound(tempY))
					continue;
				if (_state[tempX][tempY] == CELL_PDATOR)
					_neighPdator[x][y]++;
				else if (_state[tempX][tempY] == CELL_PREY)
					_neighPrey[x][y]++;
			}
			else if (type == 2)
			{
				if (tempY == -1)
					tempY = _size - 1;
				else if (tempY == _size)
					tempY = 0;
				//if (!InBound(tempY))
					//continue;
				if (_state[tempX][tempY] == CELL_PDATOR)
					_neighPdator[x][y]++;
				else if (_state[tempX][tempY] == CELL_PREY)
					_neighPrey[x][y]++;
			}
		}
	}

	if (_state[x][y] == CELL_PDATOR)
		_neighPdator[x][y]--;
	else if (_state[x][y] == CELL_PREY)
		_neighPrey[x][y]--;
}

/** @brief  Apply CountNeighbour function to the whole of _state metirx.
*    @param[in] type 1: without torus, 2: with torus.
*/
void AgentGame::UpdateNeighWhole(int type)
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			CountNeighbour(i, j, type);
}

/** @brief According the neighbourhood number of (x,y) to change  _state[x][y] .
*    @param[in] x the x_index of _neighPrey & _neighPdator.
*    @param[in] y the y_index of _neighPrey & _neighPdator.
*/
int AgentGame::CalculateState(int x, int y)
{
	// occupied by prey
	if (_state[x][y] == CELL_PREY)
	{
		int xIndex = _neighPrey[x][y];
		int yIndex = _neighPdator[x][y];
		int posibility = MRX_PREY[xIndex][yIndex] * 100;
		int temp = _rdm.GenrandInt100();
		/*
		cout << "_state[" << x << "][" << y << "] with posibility[" << xIndex << "]["\
			<< yIndex << "] = " << posibility << " ,Random number = " << temp << endl;
		return  temp <= posibility ? CELL_PREY : CELL_EMPTY;
		*/
		return _rdm.GenrandInt100() <= posibility ? CELL_PREY : CELL_EMPTY;
	}
	// occupied by predator
	else if (_state[x][y] == CELL_PDATOR)
	{
		int xIndex = _neighPrey[x][y];
		int yIndex = _neighPdator[x][y];
		int posibility = MRX_PDATOR[xIndex][yIndex] * 100;
		int temp = _rdm.GenrandInt100();
		/*
		cout << "_state[" << x << "][" << y << "] with posibility[" << xIndex << "]["\
			<< yIndex << "] = " << posibility << " ,Random number = " << temp << endl;
		return temp <= posibility ? CELL_PDATOR : CELL_EMPTY;
		*/
		return _rdm.GenrandInt100() <= posibility ? CELL_PDATOR : CELL_EMPTY;
	}
	// unoccupied
	else if(_state[x][y] == CELL_EMPTY)
	{
		int xIndex = _neighPrey[x][y];
		int yIndex = _neighPdator[x][y];
		int posibility = MRX_PREY_PDATOR[xIndex][yIndex] * 100;
		
		/*
		int temp = _rdm.GenrandInt100();
		cout << "_state[" << x << "][" << y << "] with posibility[" << xIndex << "]["\
			<< yIndex << "] = " << posibility << " ,Random number = " << temp << endl;
		if (xIndex == 0)
			return temp <= posibility ? CELL_PDATOR : CELL_EMPTY;
		else if (yIndex == 0)
			return temp <= posibility ? CELL_PREY : CELL_EMPTY;
		else
			return temp <= posibility ? CELL_PREY : CELL_PDATOR;
		*/

		if (xIndex == 0)
			return _rdm.GenrandInt100() <= posibility ? CELL_PDATOR : CELL_EMPTY;
		else if (yIndex == 0)
			return _rdm.GenrandInt100() <= posibility ? CELL_PREY : CELL_EMPTY;
		else
			return _rdm.GenrandInt100() <= posibility ? CELL_PREY : CELL_PDATOR;
	}
	//Error
	return -1;
}

/** @brief Update _state[x][y].
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*/
void AgentGame::UpdateState(int x, int y)
{
	int tempS = CalculateState(x, y);
	if (tempS != -1)
		SetState(x, y, tempS);
	else
		cout << "Error for Caculate new state of (" << x << " , " << y << ")" << endl;
}

/** @brief  Update_state. */
void AgentGame::UpdateStateWhole()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			UpdateState(i, j);
}

/** @brief Simulation.
*    @param[in] times simulation times.
*    @param[in] type 1: without torus, 2: with torus.
*    @param[in] typeOfDis display type.
*/
void AgentGame::Simulation(long int times, int type, int typeOfDis)
{
	for (long int i = 0; i < times && i < MRX_SIZE_AMOUNT; i++)
	{
		ClearNeigh();
		UpdateNeighWhole(type);
		UpdateStateWhole();
		AgentAmount(i);
		cout << i + 1 << "th :";
		Display(typeOfDis);
		DisplayAmount(i);
	}
}

/** @brief  Display the content of _state & _neighPrey,  empty: ☉  populated: ■.
*    @param[in] type 1: display _state only 2: display _neighPrey only 3: display _state & _neighPrey
*/
void AgentGame::Display(int type)
{
	switch (type)
	{
	case 1:
	{
		cout << "The contents of _state:" << endl;
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				if (_state[i][j] == CELL_PDATOR)
					cout << "■";
				else if (_state[i][j] == CELL_PREY)
					cout << "☉";
				else if (_state[i][j] == CELL_EMPTY)
					cout << "□";
			cout << endl;
		}
	}break;
	case 2:
	{
		cout << "The contents of _neighPrey & _neighPdator:" << endl;
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				cout << _neighPrey[i][j] << " ";
			cout << "    ";
			for (int k = 0; k < _size; k++)
				cout << _neighPdator[i][k] << " ";
			cout << endl;
		}
	}break;
	case 3:
	{
		cout << "The contents of _state & _neighPrey & _neighPdator:" << endl;
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
				if (_state[i][j] == CELL_PDATOR)
					cout << "■";
				else if (_state[i][j] == CELL_PREY)
					cout << "☉";
				else if (_state[i][j] == CELL_EMPTY)
					cout << "□";
			cout << "    ";
			for (int j = 0; j < _size; j++)
				cout << _neighPrey[i][j] << " ";
			cout << "    ";
			for (int k = 0; k < _size; k++)
				cout << _neighPdator[i][k] << " ";
			cout << endl;
		}
		//system("pause");
		//system("cls");
	}break;
	default: cout << "Input the right type (1、2、3) :" << endl;
	}
}

/** @brief  Display the amount of each agent.
*    @param[in] times simulation order
*/
void AgentGame::DisplayAmount(long int times)
{
	cout << "Predator : " << _amount[times][1] << " Prey : " << _amount[times][2] \
		<< " Empty : " << _amount[times][0] << endl;
}

/** @brief Count the a.
*    @param[in] times simulation order.
*/
void AgentGame::AgentAmount(long int times)
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_amount[times][_state[i][j]] ++;
}