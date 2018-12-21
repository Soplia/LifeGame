/**
* @file
*
* @author Created by Jiarui XIE on 2018/12/19
*
* @version 1.00 2018/12/19 Creation
*
* @note This .cpp file is used to testing.
*	     Github: https://github.com/Soplia/LifeGame
*           Copyright  2018 Jiarui XIE. All rights reserved.
*/
#include "AgentGame.h"

void Display(double arr[][MRX_SIZE_RULE])
{
	for (int i = 0; i < MRX_SIZE_RULE; i++)
	{
		for (int j = 0; j < MRX_SIZE_RULE; j++)
			printf("%5.2f,", arr[i][j]);
		cout << endl;
	}
}

int main()
{
	int initArr[][MRX_SIZE_AGENTGAME] =
	{
		0, 2, 0, 0, 1,
		0, 0, 1, 0, 0,
		2, 0, 0, 2, 0,
		0, 1, 2, 0, 0,
		0, 0, 0, 0, 2,
	};

	AgentGame *t = new  AgentGame(MRX_SIZE_AGENTGAME, initArr);
	cout << "The inital state :" << endl;
	t->Display(3);
	cout << endl;
	//不能连接时到8不会再改变
	//能够连接时到20为一个周期
	t->Simulation(10, 2, 3);
	system("pause");
	return 0;
}