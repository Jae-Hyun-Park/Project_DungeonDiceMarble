#pragma once
#include "Player.h"
class BattleView
{
private :

	float				elapsedTime;
	float				AttackFrameRate;						// 공격 모션 프레임

	Texture*			playerbattleTex = NULL;					// 플레이어 배틀 텍스쳐
	Texture*			playereffectTex = NULL;					// 플레이어 배틀 이펙트 텍스쳐


	Texture*			monsterbattleTex = NULL;				// 몬스터 배틀 텍스쳐
	
	Texture*			MonsterEffectTex;						// 몬스터 이펙트 텍스쳐
	Text*				DamageF = NULL;							// 데미지 폰트
	SDL_Color*			keyColor = NULL;

	int					maxX;									// 스프라이트 최대 X좌표
	int					maxY;									// 스프라이트 최대 Y좌표
	int					fontY;									// 데미지 폰트 Y좌표
public:

	SDLGameObject*		PlayerbattleObj = NULL;					// 플레이어 배틀 오브젝트
	SDLGameObject*		PlayereffectObj = NULL;					// 플레이어 배틀 이펙트오브젝트

	SDLGameObject*		MonsterbattleObj = NULL;				// 몬스터 배틀 오브젝트
	SDLGameObject*		MonsterEffectObj;						// 몬스터 이펙트 오브젝트

	SDLGameObject*		DamageFObj = NULL;						// 데미지 폰트 오브젝트

	bool				BattleTexState;							// 배틀 씬텍스쳐 상태
	bool				PAtkMotion;								// 플레이어 어택 모션상태
	bool				MAtkMotion;								// 몬스터 어택 모션 상태

	BattleView();
	~BattleView();

	void Battle(Monster* mon);											// 배틀 전 셋팅
	void PlayerAttack(float deltaTime, Monster* mon, Player* player);	// 플레이어 공격
	void MonsterAttack(float deltaTime, Monster* mon);					// 몬스터 공격
	void BattleOff();													// 배틀종료 셋팅
};

