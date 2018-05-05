#pragma once
#include "Text.h"

#include "Player.h"

class StatusView
{
private:
	Texture*			StatusTex;					// 스테이터스 텍스쳐
	SDLGameObject*		CutInObj;					// 컷인 이미지 오브젝트
	SDL_Color*			keyColor;

public:
	SDLGameObject *		StatusObj;					// 스테이터스 오브젝트
	SDLGameObject*		StatusFObj[8] = { NULL, };	// 스테이터스 폰트 오브젝트
	Text*				StatusF[8] = { NULL, };		// 스테이터스 폰트

	Texture*			CutInTex;					// 컷인 이미지 텍스쳐

	StatusView();
	void ViewingPlayerStatus(Player* player);		// 플레이어 스테이터스를 보여주는 함수
	void ViewingMonStatus(Monster* mon);			// 몬스터 스테이터스를 보여주는 함수
	~StatusView();
};

