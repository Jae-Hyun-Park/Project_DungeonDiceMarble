#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::Hpcheck(int * _hp, bool* _lifeState)   // hp 체크 함수
{
	if (*_hp <= 0) {			// hp가 0이면 생명상태를 false로
		*_lifeState = false;
		return;
	}
	return;
}

void Character::attack(int * _hp, int _def, bool* _lifeState)
{  // 공격 함수
	int damage = (Atk - _def);
		
	if (damage <= 0)
		damage = 0;
	DamageFName = to_string(damage);
	*_hp -= (Atk - _def);
	return Hpcheck(_hp, _lifeState);
}
