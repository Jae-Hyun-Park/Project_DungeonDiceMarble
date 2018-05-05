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
{	// 이동한후 타일 체크 함수 (타일 타입에 따라 다른 이벤트)

	// 오른쪽 컷인 텍스쳐를 이벤트에 따라 변경
	GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Common_face"));
	if (map[Loc]->type == TrapT) {					// 트랩 타입일 경우 hp 감소

		CharacTex->SetBlendMode(SDL_BLENDMODE_BLEND);
		CharacTex->SetAlpha(0xA0);
		GameManager::Instance()->scene->Destroy_SDLTexture(HPF->Name);
		keyColor->r = 0xFF;
		keyColor->g = keyColor->b = 0x00;
		HPFObj->transform->SetPosition((map[Loc]->x), map[Loc]->y + y);
		HPF->SetText(BMYEONSUNG, "-10", keyColor);   // 데미지 폰트를 띄움
		GameManager::Instance()->scene->Register_SDLTexture(HPF->Name, HPF->GetTexture());
		HPFObj->active = true;

		map[Loc]->TrapTex->SetAnimationActive(true);

		Hp -= 10;

		GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Damage_face"));
		Hpcheck(&Hp, &LifeState);
	}
	else if (map[Loc]->type == MonsterT) {			// 몬스터 타입일 경우 배틀 씬을 띄우고 공격 (공격은 한번씩 주고받음)
		
		CharacTex->SetBlendMode(SDL_BLENDMODE_BLEND);
		CharacTex->SetAlpha(0xA0);
		
		battlestate = true;
		
		attack(map[Loc]->monster->getHp(),
			map[Loc]->monster->getDef(),
			map[Loc]->monster->Isdead());
		
		if (*(map[Loc]->monster->Isdead()) == true)	// 몬스터가 죽지 않으면 몬스터가 반격
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

	else if (map[Loc]->type == ItemT) {					// 아이템 타입일 경우 아이템타입에 따라 슬롯에 장착
		GameManager::Instance()->STView->CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Item_face"));
		
		if (map[Loc]->item->getType() == Weapon) {
			ItemEquip(WeaponSlot, map[Loc]->item);
		}else if (map[Loc]->item != NULL && map[Loc]->item->getType() == Armor)
			ItemEquip(ArmorSlot, map[Loc]->item);
	}

	else if (map[Loc]->type == endT) {              // 엔드 타입일 경우 다음 스테이지로 이동
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
{ // 이동함수
	Loc++;
	if (Loc >= 24) { // 타일의 위치를 벗어날 경우
		Loc = 0;	 // 처음위치로 돌아가고, hp를 회복한다.
		keyColor->r = keyColor->b = 0x00;
		keyColor->g = 0xFF;
		GameManager::Instance()->scene->Destroy_SDLTexture(HPF->Name);
		HPFObj->transform->SetPosition((map[Loc]->x), (map[Loc]->y) + y);
		HPF->SetText(BMYEONSUNG, "+10", keyColor);
		GameManager::Instance()->scene->Register_SDLTexture(HPF->Name, HPF->GetTexture());
		HPFObj->active = true;
		Hp += 10;
		TSCount++;

		if (GameManager::Instance()->Stage != 2 && TSCount == 2) { // 보스스테이지가 아니고, 맵을 2바퀴돌면 엔드타입의 타일을 설정
			map[12]->type = endT;
			map[12]->tile->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(map[12]->TileTexName[map[12]->type]));
			TSCount = 0;
		}
	}

}

void Player::ItemEquip(EquipSlot slot, Item * item)
{	// 아이템 장착 함수
	if (equipedItem[(int)slot] != NULL) // 아이템을 장착하고 있으면 아이템을 지우고, 새로 장착한다.(오브젝트 삭제)
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
		case SDL_MOUSEMOTION:		// 맵 타일에있는 캐릭터에 마우스를 대면 오른쪽 스테이터스 창에 정보를 띄움
			PlayerStatusState = true;
			break;
		default:
			break;
		}
	}

}

void Player::Update(float deltaTime)
{
	if (MoveState == true)					// 이동 상태가 될때 캐릭터 텍스쳐를 이동
	{
		CharacTex->SetAlpha(0xFF);

		int resultLoc = StayLoc + walkPace; // 최종 이동할 위치
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
	}										// 프레임별로 최종 위치까지 캐릭터를 타일 한칸씩 이동시킨다.
	this->gameObject->transform->SetPosition((map[Loc]->x) + 25, (map[Loc]->y) + 25);
	
	if (HPFObj->active == true) {  // 폰트 설정
		HPFObj->transform->SetPosition((map[Loc]->x), map[Loc]->y + y--);
	}

	if (y == 0) { // 폰트가 일정위치에 도달하면 위치를 초기화하고 숨긴다.
		y = 50;
		HPFObj->active = false;
	}

	if (Exp >= 100) {  // 경험치가 100이상이 되면 래벨을 올리고 능력치를 상승시킨다.
		Lev++;
		Atk += 3;
		Def += 2;
		Hp += 5;
		Exp -= 100;
	}
	if (map[Loc]->type != TrapT) { // 캐릭터가 트랩을 밟은후 다음으로 움직일때 트랩을 정지시킨다.
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
