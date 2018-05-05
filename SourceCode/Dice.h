#pragma once
#include <random>
#include "Component.h"
#include "Player.h"
using namespace std;

class Dice :
	public Component
{
public:

	int Step = 0;						// ���̽� �����
	int randomDice();					// ���̽� ���� �Լ�
	Texture* DiceTex = NULL;			// ���̽� �ؽ���

	string DiceTName[7] = {
		"Dice1.png",
		"Dice2.png",
		"Dice3.png",
		"Dice4.png",
		"Dice5.png",
		"Dice6.png",
		"DiceS.png",
	};
	Dice();
	~Dice();
};

