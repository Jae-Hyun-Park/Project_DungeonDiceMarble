#pragma once
#include "Text.h"

#include "Player.h"

class StatusView
{
private:
	Texture*			StatusTex;					// �������ͽ� �ؽ���
	SDLGameObject*		CutInObj;					// ���� �̹��� ������Ʈ
	SDL_Color*			keyColor;

public:
	SDLGameObject *		StatusObj;					// �������ͽ� ������Ʈ
	SDLGameObject*		StatusFObj[8] = { NULL, };	// �������ͽ� ��Ʈ ������Ʈ
	Text*				StatusF[8] = { NULL, };		// �������ͽ� ��Ʈ

	Texture*			CutInTex;					// ���� �̹��� �ؽ���

	StatusView();
	void ViewingPlayerStatus(Player* player);		// �÷��̾� �������ͽ��� �����ִ� �Լ�
	void ViewingMonStatus(Monster* mon);			// ���� �������ͽ��� �����ִ� �Լ�
	~StatusView();
};

