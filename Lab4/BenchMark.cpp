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
#include "MTRandom.h"

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
	/*
	double arr[MRX_SIZE_RULE][MRX_SIZE_RULE] = { 0.0 };
	//arr[0][0] = -1;

	for (int i = 1; i < 5; i++)
		for (int j = 1; j < 5 && j < MRX_SIZE_RULE - i; j++)
			arr[i][j] = (double)j / (double)(i + j) + 0.1;
	Display(arr);
	*/
	MTRandom r ;
	for(int i = 0; i < 10; i++)
		cout << r.GenrandInt100() << endl;
	system("pause");
	return 0;
}