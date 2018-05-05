#pragma once
#include <string>
#include <iostream>
#include "Texture.h"
#include "Component.h"
#include "Transform.h"

// ������ Ÿ��
enum ItemType {
	Weapon,
	Armor
};

class Item :
	public Component
{
private:
	// ������ ���� (�̸�, Ÿ��, ���ݷ�, ����, ��ġ)
	char* Name = NULL;							
	ItemType type;								
	int PlusAtk = 0;						
	int PlusDef = 0;						
	int loc = 0;

public:
	
	int* Ploc = NULL;							// ������ ��ġ������
	Texture * ItemTex = NULL;					// ������ �ؽ���
	
	char* getName() { return Name; };			// �̸��� �������� �Լ�
	int getAtk() { return PlusAtk; };			// ���ݷ��� �������� �Լ�
	int getDef() { return PlusDef; };			// ������ �������� �Լ�
	ItemType getType() { return type; };		// Ÿ���� �������� �Լ�
	// ������ ������ �޾ƿ��� �Լ�
	void SetStatus(const char * _name, ItemType _type, int _atk, int _def);

	virtual void Init();

	Item();
	~Item();
};

