#pragma once
#include "Component.h"
#include "Dice.h"
class DiceButton :
	public Component
{
private:

	float				elapsedTime;
	float				DiceFrameRate;				// ���̽� ��� ������
public:
	
	bool diceState = false;							//  ���̽� ����
	bool diceSpState = true;						//  ���̽� ��������Ʈ ����

	Texture* ButtonTex = NULL;						//  ��ư�ؽ���
	SDL_Texture* diceT[7] = { NULL, };

	SDLGameObject * DiceObj = NULL;					//  �ֻ��� ������Ʈ
	Dice * dice = NULL;								//  �ֻ���

	Player * player = NULL;							//  �÷��̾�

	DiceButton();
	~DiceButton();
	virtual void Init();
	void HandleEvent(SDL_Event* e);
	virtual void Update(float deltaTime);

};

