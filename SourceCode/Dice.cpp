#include "Dice.h"

int Dice::randomDice()
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_int_distribution<int> Step(1, 6);
	return Step(rnd);
}

Dice::Dice()
{
}


Dice::~Dice()
{
}
