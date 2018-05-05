#include "GameManager.h"


int getRandomNumber(int min, int max) {
	//< 1�ܰ�. �õ� ����
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2�ܰ�. ���� ���� ( ���� )
	uniform_int_distribution<int> range(min, max);

	//< 3�ܰ�. �� ����
	return range(rnd);
}

void GameManager::Drawing()                    // ������ ���� �׸����Լ�
{
	DrawingMap();
	DrawingMonster();
	DrawingItem();
	DrawingPlayer();
}

void GameManager::DrawingMap()					// ���� �׸��� �Լ�
{
	bool mapCountStatex = true;				// x������ �׸��� ����
	bool mapCountStatey = false;			// y������ �׸��� ����
	int count = 0;

	for (int i = 0; i < 24; ++i, ++count) {
		mapTile[i]->tile->SetTexutre(scene->Get_SDLTexture(mapTile[i]->TileTexName[mapTile[i]->type]));  // Ÿ�� Ÿ�Կ� ���� �ؽ��� ����
		Floor[i]->transform->SetHeight(mapTile[i]->getFloorSide());
		Floor[i]->transform->SetWidth(mapTile[i]->getFloorSide());

		// ���� ������� �׷�����.
		if (mapCountStatex == true) {																	// x������ �׸� 
			if (i < 7) {																				// ���������� �׷����� ���
				mapTile[i]->x = mapTile[i]->getPosMin() + ((mapTile[i]->getFloorSide()) * count);
				mapTile[i]->y = mapTile[i]->getPosMin();
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
			else if (i > 12 && i < 19) {																// �������� �׷����� ���
				mapTile[i]->x = mapTile[i]->getPosMax() - ((mapTile[i]->getFloorSide()) * count);
				mapTile[i]->y = mapTile[i]->getPosMax();
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
		}
		else if (mapCountStatey == true) {																// y������ �׸�
			if (i > 6 && i < 13) {																		// �Ʒ��� �׷����� ���
				mapTile[i]->x = mapTile[i]->getPosMax();
				mapTile[i]->y = mapTile[i]->getPosMin() + ((mapTile[i]->getFloorSide()) * count);
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
			else if (i > 18) {																			// ���� �׷����� ���
				mapTile[i]->x = mapTile[i]->getPosMin();
				mapTile[i]->y = mapTile[i]->getPosMax() - ((mapTile[i]->getFloorSide()) * count);
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
		}
		if (i == 6 || i == 18) {
			mapCountStatex = false;
			mapCountStatey = true;
			count = 0;
		}
		else if (i == 12) {
			mapCountStatex = true;
			mapCountStatey = false;
			count = 0;
		}

		mapTile[i]->tile->SetBlendMode(SDL_BLENDMODE_BLEND);
		mapTile[i]->tile->SetAlpha(0xA0);
		if (mapTile[i]->type == TrapT)
			mapTile[i]->TrapObj->transform->SetPosition(mapTile[i]->x, mapTile[i]->y + 30);
	}
	return;
}

void GameManager::MapSetting()	// �� ������Ʈ ����
{
	for (int i = 0; i < 24; ++i) {
		ObjName.append("FLOOR");
		ObjName.append(nameNumber, i, 1);
		Floor[i] = new SDLGameObject(ObjName);
		Floor[i]->AddComponent<Texture>();
		Floor[i]->AddComponent<Tile>();
		mapTile[i] = Floor[i]->GetComponent<Tile>();
		mapTile[i]->gameObject = Floor[i];
		mapTile[i]->init(Floor[i]);
		ObjName.clear();
		scene->RegisterGameObject(Floor[i]);
		Floor[i]->active = true;
	}
	
	// Ÿ�� Ÿ�Լ� ��ŭ ���� �� Ÿ�Ժ��� ������ ����

	SDL_Texture* Road[5] = { NULL, };
	if (Stage == 1)
	{
		for (int i = 0; i < 5; ++i)
		{
			Road[i] = SDLFramework::LoadTexture("./Media/" + mapTile[0]->TileTexName[i]);
			scene->Register_SDLTexture(mapTile[0]->TileTexName[i], Road[i]);
		}
		SDL_Texture* end = SDLFramework::LoadTexture("./Media/" + mapTile[0]->TileTexName[5]);
		scene->Register_SDLTexture(mapTile[0]->TileTexName[5], end);

		SDL_Texture* TrapTex = SDLFramework::LoadTexture("./Media/SpikeTrap.png");
		scene->Register_SDLTexture("Trap", TrapTex);
	}
	mapTile[0]->type = StartT;    // ��ŸƮ ���� ����
}

void GameManager::ItemSetting()                     // �������� �����ϴ� �Լ�
{
	
	if (Stage == 1)
	{
		SDL_Texture* ItemTex = SDLFramework::LoadTexture("./Media/item.png");
		scene->Register_SDLTexture("item", ItemTex);
	}

	for (int i = 0; i < 4; ++i, ++MapCount) {
		while (item[i] == NULL)
		{
			Loc = getRandomNumber(1, 5);			// �� ���κ��� ���� ����
			if (mapTile[Loc + (mapLineCount * MapCount)]->type != MonsterT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != ItemT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != TrapT) {		
				// �ش���ġ�� ���ͳ� ������, Ʈ���� ������� ������ ����
				ObjName.append("Item");				
				ObjName.append(nameNumber, i, 1);
				
				ItemObj[i] = new SDLGameObject(ObjName);
				ItemObj[i]->AddComponent<Item>();			
				ItemObj[i]->AddComponent<Texture>();
				item[i] = ItemObj[i]->GetComponent<Item>();
				item[i]->gameObject = ItemObj[i];
				item[i]->ItemTex = ItemObj[i]->GetComponent<Texture>();
				item[i]->ItemTex->gameObject =ItemObj[i];

				item[i]->SetStatus(SV[i + 5 - SVCount]->Name, SV[i + 5 - SVCount]->itemType, 
					SV[i + 5 - SVCount]->Atk, SV[i + 5 - SVCount]->Def);
				*(item[i]->Ploc) = Loc + (mapLineCount * MapCount);
				mapTile[Loc + (mapLineCount * MapCount)]->insertIType(ItemT, item[i]);
				ObjName.clear();
				scene->RegisterGameObject(ItemObj[i]);
			}
		}
	}
	MapCount = 0;											// ���������� ����ī��Ʈ �ʱ�ȭ
	return;
}

void GameManager::MonsterSetting()	// ���� ������Ʈ ����
{
	SDL_Texture*		MonTex[4] = { NULL, };
	SDL_Texture*		MonAttackTex[4] = { NULL, };
	SDL_Texture*		MonDamageTex[4] = { NULL, };

	for (int i = 0; i < 4; ++i, ++MapCount)
	{
		while (mon[i] == NULL)
		{
			Loc = getRandomNumber(1, 5);

			if (mapTile[Loc + (mapLineCount * MapCount)]->type != ItemT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != MonsterT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != TrapT)
			{		
				// �ش���ġ�� ���ͳ� ������, Ʈ���� ������� ���� ����
				ObjName.append("Monster");
				ObjName.append(nameNumber, i, 1);

				MonsterObj[i] = new SDLGameObject(ObjName);
				MonsterObj[i]->AddComponent<Monster>();
				MonsterObj[i]->AddComponent<Texture>();
				mon[i] = MonsterObj[i]->GetComponent<Monster>();    
				mon[i]->gameObject = MonsterObj[i];
				mon[i]->CharacTex = MonsterObj[i]->GetComponent<Texture>();
				mon[i]->CharacTex->gameObject = MonsterObj[i];
				mon[i]->SetStatus(SV[i + 1 - SVCount]->Name, SV[i + 1 - SVCount]->monType, 
					SV[i + 1 - SVCount]->Hp, SV[i + 1 - SVCount]->Atk, SV[i + 1 - SVCount]->Def, SV[i + 1 - SVCount]->Exp);
				mon[i]->Loc = Loc + (mapLineCount * MapCount);
				mapTile[Loc + (mapLineCount * MapCount)]->insertMType(MonsterT, mon[i]);
				ObjName.clear();
			}
		}

		int count = 0;

		for (int j = 0; j < i; ++j) {
			if (mon[i]->monType == mon[j]->monType)
				count++;
		}
		if (count == 0) { // ���� Ÿ���� ��ġ�°� ������ �ؽ��� ���ҽ��� �����´�.
			MonTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterName[mon[i]->monType]);
			MonAttackTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterAttackName[mon[i]->monType]);
			MonDamageTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterDamageName[mon[i]->monType]);
			scene->Register_SDLTexture(mon[i]->MonsterName[mon[i]->monType], MonTex[i]);
			scene->Register_SDLTexture(mon[i]->MonsterAttackName[mon[i]->monType], MonAttackTex[i]);
			scene->Register_SDLTexture(mon[i]->MonsterDamageName[mon[i]->monType], MonDamageTex[i]);
		}
	}

	MapCount = 0;											// ���������� ����ī��Ʈ �ʱ�ȭ
	return;
}

void GameManager::ButtonSetting()							// ��ư ������Ʈ ����
{
	SDL_Texture* ButtonTex = SDLFramework::LoadTexture("./Media/DiceButton.png");
	scene->Register_SDLTexture("DBTTex", ButtonTex);

	DiceButtonObj = new SDLGameObject("DICBUTTON");
	DiceButtonObj->AddComponent<DiceButton>();
	DiceButtonObj->AddComponent<Texture>();
	dicebutton = DiceButtonObj->GetComponent<DiceButton>();
	dicebutton->gameObject = DiceButtonObj;
	dicebutton->ButtonTex = DiceButtonObj->GetComponent<Texture>();
	dicebutton->ButtonTex->gameObject = DiceButtonObj;
	dicebutton->ButtonTex->SetTexutre(scene->Get_SDLTexture("DBTTex"));
	DiceButtonObj->transform->SetPosition(350, 525);
	DiceButtonObj->transform->SetWidth(300);
	DiceButtonObj->transform->SetHeight(200);
	dicebutton->ButtonTex->SetAlpha(0xAA);
	dicebutton->player = player;
	
	for (int i = 0; i < 7; ++i) {
		dicebutton->diceT[i] = SDLFramework::LoadTexture("./Media/" + dicebutton->dice->DiceTName[i]);
		scene->Register_SDLTexture(dicebutton->dice->DiceTName[i], dicebutton->diceT[i]);
	}
	
	dicebutton->dice->DiceTex->SetTexutre(scene->Get_SDLTexture(dicebutton->dice->DiceTName[0]));
	scene->RegisterGameObject(DiceButtonObj);
	scene->RegisterGameObject(dicebutton->DiceObj);

}

void GameManager::TrapSetting()
{
	for (int i = 0; i < 4; ++i, ++MapCount) {
		Loc = getRandomNumber(1, 5);				// ���� �� ���κ��� ���� ����

		if (mapTile[Loc + (mapLineCount * MapCount)]->type != ItemT
			&& mapTile[Loc + (mapLineCount * MapCount)]->type != MonsterT
			&& mapTile[Loc + (mapLineCount * MapCount)]->type != TrapT) {
			// �ش���ġ�� ���ͳ� ������, Ʈ���� ������� Ʈ�� ����
			ObjName.append("Trap");
			ObjName.append(nameNumber, i, 1);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapObj = new SDLGameObject(ObjName);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapObj->AddComponent<Texture>();
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex = mapTile[Loc + (mapLineCount * MapCount)]->TrapObj->GetComponent<Texture>();
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->gameObject = mapTile[Loc + (mapLineCount * MapCount)]->TrapObj;
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->SetTexutre(scene->Get_SDLTexture("Trap"));
			mapTile[Loc + (mapLineCount * MapCount)]->TrapObj->transform->SetWidth(130);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapObj->transform->SetHeight(130);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->SetAnimationActive(false);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->SetHorizonCount(13);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->SetVerticalCount(1);
			mapTile[Loc + (mapLineCount * MapCount)]->TrapTex->SetFrameRate(200.0f);
			mapTile[Loc + (mapLineCount * MapCount)]->type = TrapT;
			ObjName.clear();
			scene->RegisterGameObject(mapTile[Loc + (mapLineCount * MapCount)]->TrapObj);
		}
	}
	MapCount = 0;									// ���������� ����ī��Ʈ �ʱ�ȭ
}

void GameManager::createPlayer()							// �÷��̾� ����
{

	SDL_Texture* playerTex = SDLFramework::LoadTexture("./Media/player.png");
	scene->Register_SDLTexture("playerT",playerTex);

	PlayerObj = new SDLGameObject("player");
	PlayerObj->AddComponent<Player>();
	PlayerObj->AddComponent<Texture>();
	player = PlayerObj->GetComponent<Player>();
	player->gameObject = PlayerObj;
	player->SetStatus(SV[0]->Name, SV[0]->Hp, SV[0]->Atk, SV[0]->Def);
	player->CharacTex = PlayerObj->GetComponent<Texture>();
	player->CharacTex->gameObject = PlayerObj;
	player->SetMap(mapTile);
	scene->RegisterGameObject(PlayerObj);
	player->HPFObj = new SDLGameObject("HpF");
	player->HPFObj->AddComponent<Text>();
	player->HPF = player->HPFObj->GetComponent<Text>();
	player->HPF->gameObject = player->HPFObj;
	player->HPFObj->transform->SetWidth(80);
	player->HPFObj->transform->SetHeight(40);
	player->HPFObj->active = false;
	scene->RegisterGameObject(player->HPFObj);
	return;
}

void GameManager::DrawingMonster()					// ���͸� �׸��� �Լ�
{
	for (int i = 0; i < 4; i++)
	{
		MonsterObj[i]->transform->SetWidth(100);	
		MonsterObj[i]->transform->SetHeight(100);
		mon[i]->CharacTex->SetAnimationActive(true);
		scene->RegisterGameObject(MonsterObj[i]);
		// �� Ÿ���� �ڽ��� ��ǥ�� ������ �����Ƿ� �װ��� �̿��Ͽ� �׸���.
		MonsterObj[i]->transform->SetPosition((mapTile[mon[i]->Loc]->x) + 20
			, (mapTile[mon[i]->Loc]->y) + 20);
		mon[i]->CharacTex->SetFrameRate(200.0f);
		mon[i]->CharacTex->SetTexutre(scene->Get_SDLTexture(mon[i]->MonsterName[mon[i]->monType]));
		mon[i]->CharacTex->SetHorizonCount(4);
		mon[i]->CharacTex->SetVerticalCount(1);
		if (mon[i]->monType == Angel || mon[i]->monType == GaruKasa) {
			MonsterObj[i]->transform->SetPosition((mapTile[mon[i]->Loc]->x)
				, (mapTile[mon[i]->Loc]->y));
			MonsterObj[i]->transform->SetWidth(150);
			MonsterObj[i]->transform->SetHeight(150);
			mon[i]->CharacTex->SetFrameRate(200.0f);
		}
	}
	
}

void GameManager::DrawingItem()				// �������� �׸��� �Լ�
{
	for (int i = 0; i < 4; ++i) {
		item[i]->ItemTex->SetTexutre(scene->Get_SDLTexture("item"));

		// �� Ÿ���� �ڽ��� ��ǥ�� ������ �����Ƿ� �װ��� �̿��Ͽ� �׸���.
		ItemObj[i]->transform->SetPosition((mapTile[*(item[i]->Ploc)]->x) + 25
			, (mapTile[*(item[i]->Ploc)]->y) + 25);
		ItemObj[i]->transform->SetWidth(70);
		ItemObj[i]->transform->SetHeight(70);
	}
}

void GameManager::DrawingPlayer()			// �÷��̾ �׸��� �Լ�
{
	player->CharacTex->SetTexutre(scene->Get_SDLTexture("playerT"));
	PlayerObj->transform->SetPosition((mapTile[Loc]->x) + 25
		, (mapTile[Loc]->y) + 25);
	PlayerObj->transform->SetWidth(100);
	PlayerObj->transform->SetHeight(100);
	player->CharacTex->SetHorizonCount(4);
	player->CharacTex->SetVerticalCount(1);
	player->CharacTex->SetFrameRate(80.0f);
	player->CharacTex->SetAnimationActive(true);
	return;
}

void GameManager::Init()
{	
	gameState = false;
	Loc = 0; 
	MapCount = 0;
	mapLineCount = 6;
	Stage = 1;
	GameWinState = false;

	scene = new Scene();
	// ��Ʈ �ε�
	SDLFramework::Instance()->RegisterFont("./Media/Font/BMYEONSUNG.ttf", 48);
	// �̰��� ���ӿ� �ʿ��� ������Ʈ �Ǵ� Scene ���� �ʱ� ��ġ �� ����մϴ�.
	ChangeScene(SceneName::Game);
}

void GameManager::Update(float deltaTime)
{
	if ((currentSceneName == StartScene || currentSceneName == GameOver) && scb != NULL) { // ���۹�ư�� ������ ���ӽ�ŸƮ������ �Ѿ��.
		if (scb->GameStartState == true) {
			ChangeScene(SceneName::Game);
			return;
		}
	}
	if (currentSceneName == Game && gameState == true)
	{
		DiceButtonObj->active = player->battlestate ? false : true;					// ��Ʋ ������ ��� ��ư�� ���̽��� �����.
		dicebutton->DiceObj->active = player->battlestate ? false : true;

		if (!(*player->Isdead())) {			// �÷��̾ �׾����� ���ӿ���������
			gameState = false;
			ChangeScene(SceneName::GameOver);
			return;
		}
		for (int i = 0; i < 24; i++)
		{
			if (MonDCount == 4 && mapTile[i]->type == endT) {	// ���Ͱ� ��� �׾����� ���� �������� Ÿ�Ϸ� �̵�
				player->walkPace = 12 + (24 - player->Loc);
				player->StayLoc = player->Loc;
				player->MoveState = true;
				return;
			}
		}

		// ���콺�� �÷��̾ ������ġ �ۿ� ������� �������ͽ� �ؽ��ĸ� ����
		if (STView != NULL)
		{
			if (player->PlayerStatusState == true)
				STView->ViewingPlayerStatus(player);
			else if (player->PlayerStatusState == false) {
				int msCount = 0;
				for (int i = 0; i < 4; ++i) {
					if (mon[i] != NULL) {
						if (mon[i]->MonStatusState == true) {
							STView->ViewingMonStatus(mon[i]);
							msCount++;
						}
					}
				}
				if (msCount == 0) {
					STView->StatusObj->active = false;
					for (int i = 0; i < 8; ++i) {
						STView->StatusFObj[i]->active = false;
						scene->Destroy_SDLTexture(STView->StatusF[i]->Name);
					}
				}
			}
		}

		if (player->battlestate == true && BTView != NULL) { // ��Ʋ�� �Ѿ ���
			if (BTView->BattleTexState == false) { // ��Ʋ�� ���۵ɰ��
				BTView->Battle(mapTile[player->Loc]->monster); // ��Ʋ ����
				STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Attack_face"));
			}
			if (BTView->PAtkMotion == true) {
				BTView->PlayerAttack(deltaTime, mapTile[player->Loc]->monster, player);

				if (BTView->PAtkMotion == false && !(*(mapTile[player->Loc]->monster->Isdead()))) { // ���Ͱ� �׾������ ��Ʋ ���� �� ����ġ ȹ��, ���Ϳ�����Ʈ ����

					BTView->BattleOff();
					player->battlestate = false;

					player->Exp += mapTile[player->Loc]->monster->Exp;
					player->DamageFName = to_string(mapTile[player->Loc]->monster->Exp);
					player->keyColor->r = player->keyColor->b = 0x00;
					player->keyColor->g = 0xFF;
					scene->Destroy_SDLTexture(player->HPF->Name);
					player->HPFObj->transform->SetPosition((player->map[Loc]->x), (player->map[Loc]->y) + 50);
					player->HPF->SetText(BMYEONSUNG, "Exp +" + player->DamageFName, player->keyColor);
					GameManager::Instance()->scene->Register_SDLTexture(player->HPF->Name, player->HPF->GetTexture());
					player->HPFObj->active = true;

					STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Item_face"));
					player->CharacTex->SetAlpha(0xFF);

					mapTile[player->Loc]->monster = NULL;
					mapTile[player->Loc]->type = RoadT;
					mapTile[player->Loc]->tile->SetTexutre(scene->Get_SDLTexture(mapTile[player->Loc]->TileTexName[mapTile[player->Loc]->type]));

					for (int i = 0; i < 4; ++i) {
						if (mon[i] != NULL && mon[i]->Loc == player->Loc) {
							if (mon[i]->monType == GaruKasa) {
								gameState = false;
								GameWinState = true;
								ChangeScene(SceneName::GameOver);
								return;
							}
							int count = 0;
							for (int j = 0; j < 4; ++j) {
								if (mon[j] != NULL && i != j)
								{
									if (mon[i]->monType == mon[j]->monType)
										count++;
								}
							}
							if (count == 0) { // ����ִ� ������ Ÿ���� ���� ���Ͱ� ������ ���ҽ� ����
								scene->Destroy_SDLTexture(mon[i]->MonsterName[mon[i]->monType]);
								scene->Destroy_SDLTexture(mon[i]->MonsterAttackName[mon[i]->monType]);
								scene->Destroy_SDLTexture(mon[i]->MonsterDamageName[mon[i]->monType]);
							}
							mon[i]->CharacTex = NULL;
							mon[i] = NULL;
							if (MonsterObj[i] != NULL) {
								
								scene->DestroyGameObject(MonsterObj[i]->name);
								MonDCount++;
								return;
							}
						}
					}
				}
				return;
			}
			else if (BTView->PAtkMotion == false && mapTile[player->Loc]->monster != NULL) { // ���Ͱ� ����ְ� ĳ���� ����� ������ ���� ����
				BTView->MonsterAttack(deltaTime, mapTile[player->Loc]->monster);
				STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Damage_face"));

				if (BTView->MAtkMotion == false) { // ���� ����� ������ ��Ʋ ����
					BTView->BattleOff();
					player->battlestate = false;
				}
			}
		}
	}

	if (gameState == false && currentSceneName == GameOver && scb->ButtonRunState == false) {
		int maxX = (scb->ButtonTex->GetTextureWidth()) - (scb->ButtonTex->GetTextureWidth() / scb->ButtonTex->GetHorizonCount());
		if (PlayerObj->transform->getClipRectX() == maxX)
			scb->ButtonTex->SetAnimationActive(false);
	}
}

void GameManager::Release()
{
	scene->Close();
	if (STView != NULL) {
		delete STView;
		STView = NULL;
	}
	if (BTView != NULL) {
		delete BTView;
		BTView = NULL;
	}
	if (scene != NULL) {
		delete scene;
		scene = NULL;
	}
	SV.clear();
	delete instance;
}

void GameManager::ChangeScene(SceneName sceneName)
{
	if (currentSceneName == sceneName) {
		if (sceneName == Game) { // ���� ���������� �Ѿ ��� ĳ����, ��, �������ͽ���, ��Ʋ�並 ������ ��� ������Ʈ�� �ʱ�ȭ
			Stage++;
			MonDCount = 0;
			scene->Destroy_SDLTexture("BGTex");

			for (int i = 0; i < SV.size(); ++i) {
				if (SV[i] != NULL) {
					delete SV[i];
					SV[i] = NULL;
				}
			}

			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (mapTile[j]->type == TrapT) {
						mapTile[j]->type = RoadT;
						scene->DestroyGameObject(mapTile[j]->TrapObj->name);
						mapTile[j]->TrapObj = NULL;
						mapTile[j]->TrapTex = NULL;
						break;
					}
					if (mapTile[j]->type == endT) {
						mapTile[j]->type = RoadT;
					}
				}
				if (mon[i] != NULL)
				{
					scene->Destroy_SDLTexture(mon[i]->MonsterName[mon[i]->monType]);
					scene->Destroy_SDLTexture(mon[i]->MonsterAttackName[mon[i]->monType]);
					scene->Destroy_SDLTexture(mon[i]->MonsterDamageName[mon[i]->monType]);
					
					mapTile[mon[i]->Loc]->monster = NULL;
					mapTile[mon[i]->Loc]->type = RoadT;
					scene->DestroyGameObject(MonsterObj[i]->name);
					mon[i] = NULL;
				}
				if (item[i] != NULL)
				{
					if (item[i]->Ploc != &(player->Loc))
					{
						mapTile[*(item[i]->Ploc)]->item = NULL;
						mapTile[*(item[i]->Ploc)]->type = RoadT;
						scene->DestroyGameObject(ItemObj[i]->name);
						item[i] = NULL;
					}
				}
			}

			SetGameScene();
			return;
		}
		return;
	}

	// scene�� ����ִ� ��� ������Ʈ���� �ı�
	scene->DestroyAll();

	SV.clear();

	// scene ��ȯ
	currentSceneName = sceneName;
	switch (currentSceneName)
	{
	case StartScene:
		SetStartScene();
		break;
	case Game:
		SetGameScene();
		break;
	case GameOver: // ���ӿ����ϰ�� ������Ʈ�� �ƴ� BTview�� STview�� �ʱ�ȭ
		if (BTView != NULL)
		{
			delete BTView;
			BTView = NULL;
		}
		if (STView != NULL)
		{
			delete STView;
			STView = NULL;
		}
		SetGameOverScene();
		break;
	}
}
void GameManager::SetStartScene()
{
	SDL_Texture* bgTex = SDLFramework::LoadTexture("./Media/StartImage.png");
	scene->Register_SDLTexture("BGTex", bgTex);
	bgObj = new SDLGameObject("BackGround");
	bgObj->AddComponent<Texture>();
	bgTexture = bgObj->GetComponent<Texture>();
	bgTexture->gameObject = bgObj;
	bgTexture->SetTexutre(scene->Get_SDLTexture("BGTex"));
	bgObj->transform->SetPosition(0, 0);
	bgObj->transform->SetWidth(1280);
	bgObj->transform->SetHeight(960);
	scene->RegisterGameObject(bgObj);

	SDL_Color* keyColor = new SDL_Color();

	SDLGameObject* TitleFObj = new SDLGameObject("TitleFont");
	TitleFObj->AddComponent<Text>();
	Text* TitleF = TitleFObj->GetComponent<Text>();
	TitleF->gameObject = TitleFObj;
	TitleFObj->transform->SetPosition(100, 30);

	keyColor->r = keyColor->g = keyColor->b = 0x22;
	TitleF->SetText(BMYEONSUNG, "Dungeon Dice Marble", keyColor);
	scene->Register_SDLTexture(TitleF->Name, TitleF->GetTexture());
	TitleFObj->transform->SetWidth(1100);
	TitleFObj->transform->SetHeight(400);
	scene->RegisterGameObject(TitleFObj);

	SDLGameObject* startFObj = new SDLGameObject("startFont");
	startFObj->AddComponent<Text>();
	Text* startF = startFObj->GetComponent<Text>();
	startF->gameObject = startFObj;
	startFObj->transform->SetPosition(320, 450);

	keyColor->r = keyColor->g = keyColor->b = 0xFF;
	startF->SetText(BMYEONSUNG, "please click on the character", keyColor);
	scene->Register_SDLTexture(startF->Name, startF->GetTexture());
	startFObj->transform->SetWidth(600);
	startFObj->transform->SetHeight(100);
	scene->RegisterGameObject(startFObj);

	SDL_Texture* playerTex = SDLFramework::LoadTexture("./Media/player.png");
	GameManager::Instance()->scene->Register_SDLTexture("Splayer", playerTex);

	PlayerObj = new SDLGameObject("startButton");
	PlayerObj->AddComponent<SCButton>();
	PlayerObj->AddComponent<Texture>();

	scb = PlayerObj->GetComponent<SCButton>();
	scb->gameObject = PlayerObj;
	scb->ButtonTex = PlayerObj->GetComponent<Texture>();
	scb->ButtonTex->gameObject = PlayerObj;
	scb->ButtonTex->SetTexutre(scene->Get_SDLTexture("Splayer"));

	scb->SetX(500);
	scb->SetY(680);
	scb->SetW(200);
	scb->SetH(200);

	PlayerObj->transform->SetPosition(scb->x, scb->y);
	PlayerObj->transform->SetWidth(scb->w);
	PlayerObj->transform->SetHeight(scb->h);
	scb->ButtonTex->SetHorizonCount(4);
	scb->ButtonTex->SetVerticalCount(1);
	scb->ButtonTex->SetFrameRate(80.0f);
	scb->ButtonTex->SetAnimationActive(true);

	scene->RegisterGameObject(PlayerObj);
	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}
}
void GameManager::SetGameScene()			// ���� Scene
{

	gameState = true;
	char SVBuffer[256] = { NULL, };
	if (Stage > 1) {
		SVCount = 1;
	}
	if (Stage == 1)
	{
		SV.push_back(new Stat());
		fp = fopen("./GameInfoTxt/Player.txt", "rt");
		if (fp == NULL) {
			std::cout << "File open Error!" << endl;
		}
		fscanf(fp, "%s %d %d %d", SVBuffer, &(SV[0]->Hp), &(SV[0]->Atk), &(SV[0]->Def));
		SV[0]->Name = new char[strlen(SVBuffer) + 1];
		strcpy(SV[0]->Name, SVBuffer);
		fclose(fp);
		for (int i = 0; i < 256; ++i) {
			SVBuffer[i] = NULL;
		}

		SDL_Texture* bgTex = SDLFramework::LoadTexture("./Media/" + BGName[getRandomNumber(0, 3)]);
		scene->Register_SDLTexture("BGTex", bgTex);
		bgObj = new SDLGameObject("BackGround");
		bgObj->AddComponent<Texture>();
		bgTexture = bgObj->GetComponent<Texture>();
		bgTexture->gameObject = bgObj;
		bgTexture->SetTexutre(scene->Get_SDLTexture("BGTex"));
		bgObj->transform->SetPosition(0, 0);
		bgObj->transform->SetWidth(1280);
		bgObj->transform->SetHeight(960);
		scene->RegisterGameObject(bgObj);
	}
	
	for (int i = 0; i < 8; ++i) {
		SV.push_back(new Stat());
	}

	if (Stage != 2)
	{
		fp = fopen("./GameInfoTxt/NomalStage.txt", "rt");
		if (fp == NULL) {
			std::cout << "File open Error!" << endl;
			return;
		}
		for (int i = 0; i < 4; ++i) {
			fscanf(fp, "%s %d %d %d %d %d", SVBuffer, &(SV[i + 1 - SVCount]->monType), &(SV[i + 1 - SVCount]->Hp),
				&(SV[i + 1 - SVCount]->Atk), &(SV[i + 1 - SVCount]->Def), &(SV[i + 1 - SVCount]->Exp));
			SV[i + 1 - SVCount]->Name = new char[strlen(SVBuffer) + 1];
			strcpy(SV[i + 1 - SVCount]->Name, SVBuffer);
			for (int i = 0; i < 256; ++i) {
				SVBuffer[i] = NULL;
			}
		}
		for (int i = 0; i < 4; ++i) {
			fscanf(fp, "%s %d %d %d", SVBuffer, &(SV[i + 5 - SVCount]->itemType), &(SV[i + 5 - SVCount]->Atk), &(SV[i + 5 - SVCount]->Def));
			SV[i + 5 - SVCount]->Name = new char[strlen(SVBuffer) + 1];
			strcpy(SV[i + 5 - SVCount]->Name, SVBuffer);
			for (int i = 0; i < 256; ++i) {
				SVBuffer[i] = NULL;
			}
		}
		fclose(fp);
	}
	else if (Stage == 2)
	{
		fp = fopen("./GameInfoTxt/BossStage.txt", "rt");
		if (fp == NULL) {
			std::cout << "File open Error!" << endl;
			return;
		}
		for (int i = 0; i < 4; ++i) {
			fscanf(fp, "%s %d %d %d %d %d", SV[i + 1 - SVCount]->Name, &(SV[i + 1 - SVCount]->monType), &(SV[i + 1 - SVCount]->Hp),
				&(SV[i + 1 - SVCount]->Atk), &(SV[i + 1 - SVCount]->Def), &(SV[i + 1 - SVCount]->Exp));
			SV[i + 1 - SVCount]->Name = new char[strlen(SVBuffer) + 1];
			strcpy(SV[i + 1 - SVCount]->Name, SVBuffer);
			for (int i = 0; i < 256; ++i) {
				SVBuffer[i] = NULL;
			}
		}
		for (int i = 0; i < 4; ++i) {
			fscanf(fp, "%s %d %d %d", SV[i + 5 - SVCount]->Name, &(SV[i + 5 - SVCount]->itemType), &(SV[i + 5 - SVCount]->Atk), &(SV[i + 5 - SVCount]->Def));
			SV[i + 5 - SVCount]->Name = new char[strlen(SVBuffer) + 1];
			strcpy(SV[i + 5 - SVCount]->Name, SVBuffer);
			for (int i = 0; i < 256; ++i) {
				SVBuffer[i] = NULL;
			}
		}
		fclose(fp);

		SDL_Texture* bgTex = SDLFramework::LoadTexture("./Media/" + BGName[4]);
		scene->Register_SDLTexture("BGTex", bgTex);
		bgTexture->SetTexutre(scene->Get_SDLTexture("BGTex"));
	}
	if (Stage != 1 && Stage != 2) {
		SDL_Texture* bgTex = SDLFramework::LoadTexture("./Media/" + BGName[getRandomNumber(0, 3)]);
		scene->Register_SDLTexture("BGTex", bgTex);
		bgTexture->SetTexutre(scene->Get_SDLTexture("BGTex"));
	}

	if (mapTile[0] == NULL)
		MapSetting();
	if (player == NULL)
		createPlayer();

	TrapSetting();
	ItemSetting();
	MonsterSetting();

	if (dicebutton == NULL)
		ButtonSetting();

	Drawing();

	if (STView == NULL)
		STView = new StatusView();
	if (BTView == NULL)
		BTView = new BattleView();

	STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Common_face"));

	for (auto sv : SV) {
		if (sv != NULL) {
			delete sv;
		}
	}
	SV.clear();
}
void GameManager::SetGameOverScene()		// ���ӿ��� Scene
{
	Stage = 1;
	SVCount = 0;
	MonDCount = 0;
	if (player != NULL)
	{
		player = NULL;
		dicebutton->dice = NULL;
		dicebutton = NULL;
	}
	for (int i = 0; i < 4; ++i) {
		mon[i] = NULL;
		item[i] = NULL;
	}
	for (int i = 0; i < 24; ++i) {
		mapTile[i] = NULL;
	}
	if (STView != NULL) {
		delete STView;
		STView = NULL;
	}
	if (BTView != NULL) {
		delete BTView;
		BTView = NULL;
	}
	SDL_Texture* bgTex = SDLFramework::LoadTexture("./Media/GameOverImage.png");
	scene->Register_SDLTexture("BGTex", bgTex);
	bgObj = new SDLGameObject("BackGround");
	bgObj->AddComponent<Texture>();
	bgTexture = bgObj->GetComponent<Texture>();
	bgTexture->gameObject = bgObj;
	bgTexture->SetTexutre(scene->Get_SDLTexture("BGTex"));
	bgObj->transform->SetPosition(0, 0);
	bgObj->transform->SetWidth(1280);
	bgObj->transform->SetHeight(960);
	scene->RegisterGameObject(bgObj);

	SDLGameObject* GameOverFObj = new SDLGameObject("GameOverFont");
	GameOverFObj->AddComponent<Text>();
	Text* gameOverF = GameOverFObj->GetComponent<Text>();
	gameOverF->gameObject = GameOverFObj;
	GameOverFObj->transform->SetPosition(300, 100);

	SDL_Color* keyColor = new SDL_Color();
	keyColor->r = 0xAA;
	keyColor->g = keyColor->b = 0x00;
	if (GameWinState == false) // �÷��̾ �׾��� ���
		gameOverF->SetText(BMYEONSUNG, "GAME OVER", keyColor);
	else if (GameWinState == true) // ������ Ŭ���� ���� ���
		gameOverF->SetText(BMYEONSUNG, "VICTORY!", keyColor);
	scene->Register_SDLTexture(gameOverF->Name, gameOverF->GetTexture());
	GameOverFObj->transform->SetWidth(700);
	GameOverFObj->transform->SetHeight(350);
	scene->RegisterGameObject(GameOverFObj);

	SDLGameObject* RestartFObj = new SDLGameObject("RestartFont");
	RestartFObj->AddComponent<Text>();
	Text* RestartF = RestartFObj->GetComponent<Text>();
	RestartF->gameObject = RestartFObj;
	RestartFObj->transform->SetPosition(150, 350);
	keyColor->r = keyColor->g = keyColor->b = 0xFF;
	RestartF->SetText(BMYEONSUNG, "please click on the character", keyColor);
	scene->Register_SDLTexture(RestartF->Name, RestartF->GetTexture());
	RestartFObj->transform->SetWidth(1000);
	RestartFObj->transform->SetHeight(150);
	scene->RegisterGameObject(RestartFObj);

	PlayerObj = new SDLGameObject("startButton");
	PlayerObj->AddComponent<SCButton>();
	PlayerObj->AddComponent<Texture>();

	scb = PlayerObj->GetComponent<SCButton>();
	scb->gameObject = PlayerObj;
	scb->ButtonTex = PlayerObj->GetComponent<Texture>();
	scb->ButtonTex->gameObject = PlayerObj;

	if (GameWinState == false) // �÷��̾ �׾��� ���
	{
		SDL_Texture* playerDieT = SDLFramework::LoadTexture("./Media/playerDie.png");
		scene->Register_SDLTexture("playerDie", playerDieT);
		scb->ButtonTex->SetTexutre(scene->Get_SDLTexture("playerDie"));
		scb->SetX(500);
		scb->SetY(500);
		scb->SetW(200);
		scb->SetH(200);
		PlayerObj->transform->SetPosition(scb->x, scb->y);
		PlayerObj->transform->SetWidth(scb->w);
		PlayerObj->transform->SetHeight(scb->h);
		
	}
	else if (GameWinState == true) { // ������ Ŭ���� ���� ���
		SDL_Texture* playerDieT = SDLFramework::LoadTexture("./Media/GaruKasaDamage.PNG");
		scene->Register_SDLTexture("playerDie", playerDieT);
		scb->ButtonTex->SetTexutre(scene->Get_SDLTexture("playerDie"));
		scb->SetX(450);
		scb->SetY(400);
		scb->SetW(300);
		scb->SetH(300);
		PlayerObj->transform->SetPosition(scb->x, scb->y);
		PlayerObj->transform->SetWidth(scb->w);
		PlayerObj->transform->SetHeight(scb->h);
	}
	scb->ButtonTex->SetHorizonCount(7);
	scb->ButtonTex->SetVerticalCount(1);
	scb->ButtonTex->SetFrameRate(200.0f);
	scb->ButtonTex->SetAnimationActive(true);
	scene->RegisterGameObject(PlayerObj);

	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}
}
GameManager::GameManager()
{
	nameNumber = "abcdefghijklmnopqrstuvwxyz";
}

GameManager::~GameManager()
{
}
