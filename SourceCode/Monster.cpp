#include "Monster.h"

Monster::Monster()
{
}


Monster::~Monster()
{
	if (Name != NULL) {
		delete[] Name;
		Name = NULL;
	}
}

void Monster::Init()
{
	Loc = 0;
	LifeState = true;
	MonStatusState = false;
}

void Monster::SetStatus(const char * _name, MonsterType _type, int _hp, int _atk, int _def, int _Exp)
{
	Name = new char[strlen(_name) + 1];
	strcpy(Name, _name);
	monType = _type;
	Hp = _hp;
	Atk = _atk;
	Def = _def;
	Exp = _Exp;
}

void Monster::HandleEvent(SDL_Event * e)
{
	if (this->gameObject->transform == NULL)
		return;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < this->gameObject->transform->projRect.x || x > this->gameObject->transform->projRect.x + this->gameObject->transform->projRect.w ||
			y < this->gameObject->transform->projRect.y || y > this->gameObject->transform->projRect.y + this->gameObject->transform->projRect.h)
			inside = false;
		if (inside == false) {
			MonStatusState = false;
			return;
		}

		if (CharacTex == NULL)
			return;
		switch (e->type)
		{
		case SDL_MOUSEMOTION: // 맵 타일에있는 몬스터에 마우스를 대면 오른쪽 스테이터스 창에 정보를 띄움
			MonStatusState = true;
			break;
		default:
			break;
		}
	}

}

