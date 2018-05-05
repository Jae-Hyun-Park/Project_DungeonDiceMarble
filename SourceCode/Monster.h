#pragma once
#include "Character.h"

// ���� Ÿ��
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
	
	MonsterType monType;							// ���� Ÿ�� ����
	
	string MonsterName[4] = {						// ���� �̸� �迭
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
	bool MonStatusState;							// ���� �������ͽ�����

	Monster();
	~Monster();
	// ���� ������ �޾ƿ��� �Լ�
	void SetStatus(const char * _name, MonsterType _type, int _hp, int _atk, int _def, int _Exp);
	virtual void Init();
	void HandleEvent(SDL_Event* e);
};

