#pragma once
#include <string>
#include <iostream>
#include "Texture.h"
#include "Component.h"
#include "Transform.h"

// 아이템 타입
enum ItemType {
	Weapon,
	Armor
};

class Item :
	public Component
{
private:
	// 아이템 정보 (이름, 타입, 공격력, 방어력, 위치)
	char* Name = NULL;							
	ItemType type;								
	int PlusAtk = 0;						
	int PlusDef = 0;						
	int loc = 0;

public:
	
	int* Ploc = NULL;							// 아이템 위치포인터
	Texture * ItemTex = NULL;					// 아이템 텍스쳐
	
	char* getName() { return Name; };			// 이름을 가져오는 함수
	int getAtk() { return PlusAtk; };			// 공격력을 가져오는 함수
	int getDef() { return PlusDef; };			// 방어력을 가져오는 함수
	ItemType getType() { return type; };		// 타입을 가져오는 함수
	// 아이템 정보를 받아오는 함수
	void SetStatus(const char * _name, ItemType _type, int _atk, int _def);

	virtual void Init();

	Item();
	~Item();
};

