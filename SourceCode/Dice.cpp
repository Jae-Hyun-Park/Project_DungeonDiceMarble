#include "Dice.h"

int Dice::randomDice()
{
	//< 1�ܰ�. �õ� ����
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2�ܰ�. ���� ���� ( ���� )
	uniform_int_distribution<int> Step(1, 6);
	return Step(rnd);
}

Dice::Dice()
{
}


Dice::~Dice()
{
}
