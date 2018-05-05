#pragma once
#include <string>
#include <iostream>

#include "Component.h"
#include "SDLFramework.h"

#include "Item.h"
#include "Scene.h"


// ������ ����
enum EquipSlot {
	WeaponSlot,
	ArmorSlot
};


class Character :
	public Component
{
protected:		
	// ĳ���� �������ͽ� (�̸�, ü��, ���ݷ�, ����, ��������)
	char*				Name = NULL;
	int					Hp = 0;
	int					Atk = 0;
	int					Def = 0;
	bool				LifeState = false;

public:
	
	string					DamageFName;
	bool					AttackState = true;		// ���� ���� ����
	int						Loc = 0;				// ĳ���� ��ġ
	bool					EffectState = true;		// ����Ʈ ������Ʈ
	Texture*				CharacTex = NULL;		// ĳ���� �ؽ���
	int						Exp = 0;				// ĳ���� ����ġ

	Character();
	virtual ~Character();
	
	virtual void Move() {};									// �̵� �����Լ�
	void Hpcheck(int* _hp, bool* _lifeState);				// HPüũ �Լ�
	void attack(int* _hp, int _def, bool* _lifeState);		// �����Լ�
	virtual void ItemEquip(EquipSlot slot, Item* item) {};	// ������ ���� �����Լ�
	bool* Isdead() { return &LifeState; }					// ����ó�� �Լ�
	char* getName() { return Name; }
	int* getHp() { return &Hp; }							// ü���� �������� �Լ�
	int getAtk() { return Atk; }							// ���ݷ��� �������� �Լ�
	int getDef() { return Def; }							// ���·��� �������� �Լ�
};

