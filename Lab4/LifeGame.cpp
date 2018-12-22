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

#include "LifeGame.h"

/** @brief A Constructor.
*    @param[in] size the size of the matrix.
*/
LifeGame::LifeGame(int size)
{
	_size = size;
	_state = new int *[size];
	for (int i = 0; i < _size; i++)
		_state[i] = new int[_size];

	_neigh = new int *[size];
	for (int i = 0; i < _size; i++)
		_neigh[i] = new int[_size];

	InitValue();
}

/** @brief A Constructor.
*    @param[in] size the size of the matrix.
*    @param[in] a the source matrix.
*/
LifeGame::LifeGame(int size, int a[][MATRIX_SIZE_LIFEGAME])
{
	_size = size;
	_state = new int *[size];
	for (int i = 0; i < _size; i++)
		_state[i] = new int[_size];

	_neigh = new int *[size];
	for (int i = 0; i < _size; i++)
		_neigh[i] = new int[_size];

	InitValue();

	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_state[i][j] = a[i][j];
}

/** @brief  A Deconstructor. */
LifeGame::~LifeGame()
{
	for (int i = 0; i < _size; i++)
	{
		delete[] _state[i];
		delete[] _neigh[i];
	}
	delete[] _state;
	delete[] _neigh;
}

/** @brief  Assign zero to  _state & _neigh . */
void LifeGame::InitValue()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			_state[i][j] = 0;
			_neigh[i][j] = 0;
		}
}

/** @brief  Assign zero to  _neigh . */
void LifeGame::ClearNeigh()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_neigh[i][j] = 0;
}

/** @brief  Display the content of _state & _neigh,  empty: ☉  populated: ■.
*    @param[in] type 1: display _state only 2: display _neigh only 3: display _state & _neigh
*/
void LifeGame::Display(int type)
{
	switch (type)
	{
		case 1:
		{
			cout << "The contents of _state:" << endl;
			for (int i = 0; i < _size; i++)
			{
				for (int j = 0; j < _size; j++)
					if (_state[i][j] == 1)
						cout << "■";
					else if (_state[i][j] == 0) //  ★ ☉ □  ■
						cout << "□";
				cout << endl;
			}
		}break;
		case 2:
		{
			cout << "The contents of _neigh:" << endl;
			for (int i = 0; i < _size; i++)
			{
				for (int j = 0; j < _size; j++)
					cout << _neigh[i][j] << " ";
				cout << endl;
			}
		}break;
		case 3:
		{
			cout << "The contents of _state & _neigh:" << endl;
			for (int i = 0; i < _size; i++)
			{
				for (int j = 0; j < _size; j++)
					if (_state[i][j] == 1)
						cout << "■";
					else if (_state[i][j] == 0) //  ★ ☉ □  ■
						cout << "□";
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i < _size; i++)
			{
				for (int j = 0; j < _size; j++)
					cout << _neigh[i][j] << " ";
				cout << endl;
			}
			system("pause");
			system("cls");

		}break;
		default: cout << "Input the right type (1、2、3) :" << endl;
	}
}

/** @brief  Assign aim to _state[x][y].
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*    @param[in] aim the source value.
*/
void LifeGame::ChangeState(int x, int y, int aim)
{
	_state[x][y] = aim;
}

/** @brief  Whether x inside the bound or not.
*    @param[in] x the value to be judged.
*    @return 0: outside the bound, 1: inside the bound
*/
bool LifeGame::InBound(int x)
{
	return (x >= 0 && x < _size);
}

/** @brief Count the number of _state[x][y]'s neighbourhood.
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*    @param[in] type 1: without torus, 2: with torus.
*/
void LifeGame::CountNeighbour(int x, int y, int type)
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
			if (!InBound(tempX))
				continue;
		}

		for (int j = 0; j <= 2; j++)
		{
			int tempY = y - 1;
			tempY += j;
			if (type == 1)
			{
				if (!InBound(tempY))
					continue;
				if (_state[tempX][tempY])//1: 有人；0: 没人
					_neigh[x][y]++;
			}
			else if (type == 2)
			{
				if (tempY == -1)
					tempY = _size - 1;
				else if (tempY == _size)
					tempY = 0;
				if (!InBound(tempY))
					continue;
				if (_state[tempX][tempY])//1: 有人；0: 没人
					_neigh[x][y]++;

			}
		}
	}
	if(_state[x][y])
		_neigh[x][y]--; //除去自己
}

/** @brief Update _state[x][y].
*    @param[in] x the x_index of _state.
*    @param[in] y the y_index of _state.
*/
void LifeGame::UpdateState(int x, int y)
{
	_state[x][y] = CalculateState(x, y);
}

/** @brief According the neighbourhood number of (x,y) to change  _state[x][y] .
*    @param[in] x the x_index of _neigh.
*    @param[in] y the y_index of _neigh.
*/
int LifeGame::CalculateState(int x, int y)
{
	if (_state[x][y])
		return _neigh[x][y] >= 2 && _neigh[x][y] <= 3 ? 1 : 0;
	else if (!_state[x][y])
		return _neigh[x][y] == 3;
}

/** @brief  Apply CountNeighbour function to the whole of _state metirx.
*    @param[in] type 1: without torus, 2: with torus.
*/
void LifeGame::ChangeNeighbourWhole(int type)
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			CountNeighbour(i, j, type);
}

/** @brief  Update_state. */
void LifeGame::UpdateStateWhole()
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
void LifeGame::Simulation(int times, int type, int typeOfDis)
{
	for (int i = 0; i < times; i++)
	{
		ClearNeigh();
		ChangeNeighbourWhole(type);
		UpdateStateWhole();
		cout << i + 1 << "th :";
		Display(typeOfDis);
	}
}




