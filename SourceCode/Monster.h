#pragma once
#include "Character.h"

// 몬스터 타입
enum MonsterType {
	Skull,
	mermaid,
	Angel,
	GaruKasa,
};

class Monster :
	public Character
{
public:
	
	MonsterType monType;							// 몬스터 타입 변수
	
	string MonsterName[4] = {						// 몬스터 이름 배열
		"skull.png",
		"mermaid.png",
		"angel.PNG",
		"GaruKasa.PNG",
	};
	string MonsterAttackName[4] = {
		"skullattack.png",
		"mermaidattack.png",
		"angelattack.png",
		"GaruKasaAttack.png",
	};
	string MonsterDamageName[4] = {
		"skullDamage.png",
		"mermaidDamage.png",
		"AngelDamage.PNG",
		"GaruKasaDamage.PNG"
	};
	bool MonStatusState;							// 몬스터 스테이터스상태

	Monster();
	~Monster();
	// 몬스터 정보를 받아오는 함수
	void SetStatus(const char * _name, MonsterType _type, int _hp, int _atk, int _def, int _Exp);
	virtual void Init();
	void HandleEvent(SDL_Event* e);
};

