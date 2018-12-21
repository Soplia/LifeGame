/**
* @file
*
* @author Created by Jiarui XIE on 2018/12/19
*
* @version 1.00 2018/12/19 Creation
*
* @note Header of Random Generator
*/
#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Constant.h"
using namespace std;

class MTRandom
{
public:
	/** @brief  Initializes mt[N] with a seed.
	*    @param[in] s the seed.
	*/
	void InitGenrand(unsigned long s);

	/** @brief  Generates a random number on [0,0xffffffff]-interval.	
	*    @return The generated unsigned long number.
	*/
	unsigned long GenrandInt32(void);

	/** @brief  generates an integer number on [0,100] interval..
	*    @return The generated integer number.
	*/
	int GenrandInt100(void);
};