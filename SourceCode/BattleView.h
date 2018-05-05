#pragma once
#include "Player.h"
class BattleView
{
private :

	float				elapsedTime;
	float				AttackFrameRate;						// ���� ��� ������

	Texture*			playerbattleTex = NULL;					// �÷��̾� ��Ʋ �ؽ���
	Texture*			playereffectTex = NULL;					// �÷��̾� ��Ʋ ����Ʈ �ؽ���


	Texture*			monsterbattleTex = NULL;				// ���� ��Ʋ �ؽ���
	
	Texture*			MonsterEffectTex;						// ���� ����Ʈ �ؽ���
	Text*				DamageF = NULL;							// ������ ��Ʈ
	SDL_Color*			keyColor = NULL;

	int					maxX;									// ��������Ʈ �ִ� X��ǥ
	int					maxY;									// ��������Ʈ �ִ� Y��ǥ
	int					fontY;									// ������ ��Ʈ Y��ǥ
public:

	SDLGameObject*		PlayerbattleObj = NULL;					// �÷��̾� ��Ʋ ������Ʈ
	SDLGameObject*		PlayereffectObj = NULL;					// �÷��̾� ��Ʋ ����Ʈ������Ʈ

	SDLGameObject*		MonsterbattleObj = NULL;				// ���� ��Ʋ ������Ʈ
	SDLGameObject*		MonsterEffectObj;						// ���� ����Ʈ ������Ʈ

	SDLGameObject*		DamageFObj = NULL;						// ������ ��Ʈ ������Ʈ

	bool				BattleTexState;							// ��Ʋ ���ؽ��� ����
	bool				PAtkMotion;								// �÷��̾� ���� ��ǻ���
	bool				MAtkMotion;								// ���� ���� ��� ����

	BattleView();
	~BattleView();

	void Battle(Monster* mon);											// ��Ʋ �� ����
	void PlayerAttack(float deltaTime, Monster* mon, Player* player);	// �÷��̾� ����
	void MonsterAttack(float deltaTime, Monster* mon);					// ���� ����
	void BattleOff();													// ��Ʋ���� ����
};

