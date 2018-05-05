#pragma once
#include "Component.h"
#include "Dice.h"
class DiceButton :
	public Component
{
private:

	float				elapsedTime;
	float				DiceFrameRate;				// 다이스 모션 프레임
public:
	
	bool diceState = false;							//  다이스 상태
	bool diceSpState = true;						//  다이스 스프라이트 상태

	Texture* ButtonTex = NULL;						//  버튼텍스쳐
	SDL_Texture* diceT[7] = { NULL, };

	SDLGameObject * DiceObj = NULL;					//  주사위 오브젝트
	Dice * dice = NULL;								//  주사위

	Player * player = NULL;							//  플레이어

	DiceButton();
	~DiceButton();
	virtual void Init();
	void HandleEvent(SDL_Event* e);
	virtual void Update(float deltaTime);

};

