#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::Hpcheck(int * _hp, bool* _lifeState)   // hp üũ �Լ�
{
	if (*_hp <= 0) {			// hp�� 0�̸� ������¸� false��
		*_lifeState = false;
		return;
	}
	return;
}

void Character::attack(int * _hp, int _def, bool* _lifeState)
{  // ���� �Լ�
	int damage = (Atk - _def);
		
	if (damage <= 0)
		damage = 0;
	DamageFName = to_string(damage);
	*_hp -= (Atk - _def);
	return Hpcheck(_hp, _lifeState);
}
