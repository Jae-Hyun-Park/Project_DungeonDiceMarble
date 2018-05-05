#pragma once
#include <string>
#include <iostream>

#include "Component.h"
#include "SDLFramework.h"

#include "Item.h"
#include "Scene.h"


// 아이템 슬롯
enum EquipSlot {
	WeaponSlot,
	ArmorSlot
};


class Character :
	public Component
{
protected:		
	// 캐릭터 스테이터스 (이름, 체력, 공격력, 방어력, 생존상태)
	char*				Name = NULL;
	int					Hp = 0;
	int					Atk = 0;
	int					Def = 0;
	bool				LifeState = false;

public:
	
	string					DamageFName;
	bool					AttackState = true;		// 공격 상태 변수
	int						Loc = 0;				// 캐릭터 위치
	bool					EffectState = true;		// 이펙트 스테이트
	Texture*				CharacTex = NULL;		// 캐릭터 텍스쳐
	int						Exp = 0;				// 캐릭터 경험치

	Character();
	virtual ~Character();
	
	virtual void Move() {};									// 이동 가상함수
	void Hpcheck(int* _hp, bool* _lifeState);				// HP체크 함수
	void attack(int* _hp, int _def, bool* _lifeState);		// 공격함수
	virtual void ItemEquip(EquipSlot slot, Item* item) {};	// 아이템 장착 가상함수
	bool* Isdead() { return &LifeState; }					// 죽음처리 함수
	char* getName() { return Name; }
	int* getHp() { return &Hp; }							// 체력을 가져오는 함수
	int getAtk() { return Atk; }							// 공격력을 가져오는 함수
	int getDef() { return Def; }							// 방어력력을 가져오는 함수
};

