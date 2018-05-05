#include "Player.h"
#include "GameManager.h"
Player::Player()
{
}


Player::~Player()
{
	if (Name != NULL) {
		delete[] Name;
		Name = NULL;
	}
	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}
}
void Player::MapCheck()
{	// �̵����� Ÿ�� üũ �Լ� (Ÿ�� Ÿ�Կ� ���� �ٸ� �̺�Ʈ)

	// ������ ���� �ؽ��ĸ� �̺�Ʈ�� ���� ����
	GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Common_face"));
	if (map[Loc]->type == TrapT) {					// Ʈ�� Ÿ���� ��� hp ����

		CharacTex->SetBlendMode(SDL_BLENDMODE_BLEND);
		CharacTex->SetAlpha(0xA0);
		GameManager::Instance()->scene->Destroy_SDLTexture(HPF->Name);
		keyColor->r = 0xFF;
		keyColor->g = keyColor->b = 0x00;
		HPFObj->transform->SetPosition((map[Loc]->x), map[Loc]->y + y);
		HPF->SetText(BMYEONSUNG, "-10", keyColor);   // ������ ��Ʈ�� ���
		GameManager::Instance()->scene->Register_SDLTexture(HPF->Name, HPF->GetTexture());
		HPFObj->active = true;

		map[Loc]->TrapTex->SetAnimationActive(true);

		Hp -= 10;

		GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Damage_face"));
		Hpcheck(&Hp, &LifeState);
	}
	else if (map[Loc]->type == MonsterT) {			// ���� Ÿ���� ��� ��Ʋ ���� ���� ���� (������ �ѹ��� �ְ����)
		
		CharacTex->SetBlendMode(SDL_BLENDMODE_BLEND);
		CharacTex->SetAlpha(0xA0);
		
		battlestate = true;
		
		attack(map[Loc]->monster->getHp(),
			map[Loc]->monster->getDef(),
			map[Loc]->monster->Isdead());
		
		if (*(map[Loc]->monster->Isdead()) == true)	// ���Ͱ� ���� ������ ���Ͱ� �ݰ�
		{
			map[Loc]->monster->attack(&Hp, Def, Isdead());
			keyColor->r = 0xFF;
			keyColor->g = keyColor->b = 0x00;
			GameManager::Instance()->scene->Destroy_SDLTexture(HPF->Name);
			HPFObj->transform->SetPosition((map[Loc]->x), map[Loc]->y + y);
			HPF->SetText(BMYEONSUNG, "-" + map[Loc]->monster->DamageFName, keyColor);
			GameManager::Instance()->scene->Register_SDLTexture(HPF->Name, HPF->GetTexture());
			HPFObj->active = true;
		}
	}

	else if (map[Loc]->type == ItemT) {					// ������ Ÿ���� ��� ������Ÿ�Կ� ���� ���Կ� ����
		GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Item_face"));
		
		if (map[Loc]->item->getType() == Weapon) {
			ItemEquip(WeaponSlot, map[Loc]->item);
		}else if (map[Loc]->item != NULL && map[Loc]->item->getType() == Armor)
			ItemEquip(ArmorSlot, map[Loc]->item);
	}

	else if (map[Loc]->type == endT) {              // ���� Ÿ���� ��� ���� ���������� �̵�
		GameManager::Instance()->gameState = false;
		GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Common_face.PNG"));
		GameManager::Instance()->ChangeScene(SceneName::Game);
		
	}
	return;
}

void Player::Init()
{
	keyColor = new SDL_Color();
	keyColor->r = 0xFF;
	keyColor->g = keyColor->b = 0x00;

	LifeState = true;

	Loc = 0;
	StayLoc = 0;
	walkPace = 0;
	MoveState = false;
	MoveFrameRate = 150.0f;
	Lev = 1;
	y = 50;
	TSCount = 0;
	elapsedTime = 0.0f;
	battlestate = false;
	PlayerStatusState = false;
}

void Player::SetStatus(const char * _name, int _hp, int _atk, int _def)
{
	Name = new char[strlen(_name) + 1];
	strcpy(Name, _name);
	Hp = _hp;
	Atk = _atk;
	Def = _def;
}

void Player::Move()
{ // �̵��Լ�
	Loc++;
	if (Loc >= 24) { // Ÿ���� ��ġ�� ��� ���
		Loc = 0;	 // ó����ġ�� ���ư���, hp�� ȸ���Ѵ�.
		keyColor->r = keyColor->b = 0x00;
		keyColor->g = 0xFF;
		GameManager::Instance()->scene->Destroy_SDLTexture(HPF->Name);
		HPFObj->transform->SetPosition((map[Loc]->x), (map[Loc]->y) + y);
		HPF->SetText(BMYEONSUNG, "+10", keyColor);
		GameManager::Instance()->scene->Register_SDLTexture(HPF->Name, HPF->GetTexture());
		HPFObj->active = true;
		Hp += 10;
		TSCount++;

		if (GameManager::Instance()->Stage != 2 && TSCount == 2) { // �������������� �ƴϰ�, ���� 2�������� ����Ÿ���� Ÿ���� ����
			map[12]->type = endT;
			map[12]->tile->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(map[12]->TileTexName[map[12]->type]));
			TSCount = 0;
		}
	}

}

void Player::ItemEquip(EquipSlot slot, Item * item)
{	// ������ ���� �Լ�
	if (equipedItem[(int)slot] != NULL) // �������� �����ϰ� ������ �������� �����, ���� �����Ѵ�.(������Ʈ ����)
	{
		Atk -= equipedItem[(int)slot]->getAtk();
		Def -= equipedItem[(int)slot]->getDef();
		for (int i = 0; i < 4; i++)
		{
			if (GameManager::Instance()->item[i] != NULL)
			{
				if (equipedItem[(int)slot]->getType() == GameManager::Instance()->item[i]->getType() &&
					equipedItem[(int)slot]->Ploc == GameManager::Instance()->item[i]->Ploc) {
					GameManager::Instance()->item[i] = NULL;
				}
			}
		}
		equipedItem[(int)slot]->ItemTex = NULL;
		if (equipedItem[(int)slot]->gameObject != NULL) {
			GameManager::Instance()->scene->DestroyGameObject(equipedItem[(int)slot]->gameObject->name);
			equipedItem[(int)slot]->gameObject = NULL;
		}
		equipedItem[(int)slot] = NULL;
	}
	equipedItem[(int)slot] = item;
	Atk += equipedItem[(int)slot]->getAtk();
	Def += equipedItem[(int)slot]->getDef();
	equipedItem[(int)slot]->Ploc = &Loc;

	map[Loc]->item->gameObject->active = false;
	map[Loc]->item = NULL;
	map[Loc]->type = RoadT;
	map[Loc]->tile->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(map[Loc]->TileTexName[map[Loc]->type]));
}

void Player::HandleEvent(SDL_Event * e)
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
			PlayerStatusState = false;
			return;
		}

		if (CharacTex == NULL)
			return;
		switch (e->type)
		{
		case SDL_MOUSEMOTION:		// �� Ÿ�Ͽ��ִ� ĳ���Ϳ� ���콺�� ��� ������ �������ͽ� â�� ������ ���
			PlayerStatusState = true;
			break;
		default:
			break;
		}
	}

}

void Player::Update(float deltaTime)
{
	if (MoveState == true)					// �̵� ���°� �ɶ� ĳ���� �ؽ��ĸ� �̵�
	{
		CharacTex->SetAlpha(0xFF);

		int resultLoc = StayLoc + walkPace; // ���� �̵��� ��ġ
		if (resultLoc >= 24)
			resultLoc -= 24;

		elapsedTime += deltaTime;
		if (elapsedTime > MoveFrameRate)
		{
			Move();
			elapsedTime = 0.0f;
		}
		if (resultLoc == Loc) {
			MapCheck();
			MoveState = false;
		}
	}										// �����Ӻ��� ���� ��ġ���� ĳ���͸� Ÿ�� ��ĭ�� �̵���Ų��.
	this->gameObject->transform->SetPosition((map[Loc]->x) + 25, (map[Loc]->y) + 25);
	
	if (HPFObj->active == true) {  // ��Ʈ ����
		HPFObj->transform->SetPosition((map[Loc]->x), map[Loc]->y + y--);
	}

	if (y == 0) { // ��Ʈ�� ������ġ�� �����ϸ� ��ġ�� �ʱ�ȭ�ϰ� �����.
		y = 50;
		HPFObj->active = false;
	}

	if (Exp >= 100) {  // ����ġ�� 100�̻��� �Ǹ� ������ �ø��� �ɷ�ġ�� ��½�Ų��.
		Lev++;
		Atk += 3;
		Def += 2;
		Hp += 5;
		Exp -= 100;
	}
	if (map[Loc]->type != TrapT) { // ĳ���Ͱ� Ʈ���� ������ �������� �����϶� Ʈ���� ������Ų��.
		for (int i = 0; i < 24; ++i) {
			if (map[i]->type == TrapT) {
				int maxX = ((map[i]->TrapTex->GetTextureWidth()) -
					(map[i]->TrapTex->GetTextureWidth() / map[i]->TrapTex->GetHorizonCount()));
				if (map[i]->TrapObj->transform->getClipRectX() >= maxX)
					map[i]->TrapTex->SetAnimationActive(false);
			}
		}
	}

}
