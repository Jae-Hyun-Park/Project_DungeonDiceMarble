#include "GameManager.h"


int getRandomNumber(int min, int max) {
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_int_distribution<int> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}

void GameManager::Drawing()                    // 게임의 판을 그리는함수
{
	DrawingMap();
	DrawingMonster();
	DrawingItem();
	DrawingPlayer();
}

void GameManager::DrawingMap()					// 맵을 그리는 함수
{
	bool mapCountStatex = true;				// x축으로 그리는 상태
	bool mapCountStatey = false;			// y축으로 그리는 상태
	int count = 0;

	for (int i = 0; i < 24; ++i, ++count) {
		mapTile[i]->tile->SetTexutre(scene->Get_SDLTexture(mapTile[i]->TileTexName[mapTile[i]->type]));  // 타일 타입에 맞춰 텍스쳐 설정
		Floor[i]->transform->SetHeight(mapTile[i]->getFloorSide());
		Floor[i]->transform->SetWidth(mapTile[i]->getFloorSide());

		// ㅁ자 모양으로 그려간다.
		if (mapCountStatex == true) {																	// x축으로 그림 
			if (i < 7) {																				// 오른쪽으로 그려가는 경우
				mapTile[i]->x = mapTile[i]->getPosMin() + ((mapTile[i]->getFloorSide()) * count);
				mapTile[i]->y = mapTile[i]->getPosMin();
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
			else if (i > 12 && i < 19) {																// 왼쪽으로 그려가는 경우
				mapTile[i]->x = mapTile[i]->getPosMax() - ((mapTile[i]->getFloorSide()) * count);
				mapTile[i]->y = mapTile[i]->getPosMax();
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
		}
		else if (mapCountStatey == true) {																// y축으로 그림
			if (i > 6 && i < 13) {																		// 아래로 그려가는 경우
				mapTile[i]->x = mapTile[i]->getPosMax();
				mapTile[i]->y = mapTile[i]->getPosMin() + ((mapTile[i]->getFloorSide()) * count);
				Floor[i]->transform->SetPosition(mapTile[i]->x, mapTile[i]->y);
			}
			else if (i > 18) {																			// 위로 그려가는 경우
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

void GameManager::MapSetting()	// 맵 오브젝트 셋팅
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
	
	// 타일 타입수 만큼 생성 및 타입별로 색깔을 입힘

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
	mapTile[0]->type = StartT;    // 스타트 지점 설정
}

void GameManager::ItemSetting()                     // 아이템을 셋팅하는 함수
{
	
	if (Stage == 1)
	{
		SDL_Texture* ItemTex = SDLFramework::LoadTexture("./Media/item.png");
		scene->Register_SDLTexture("item", ItemTex);
	}

	for (int i = 0; i < 4; ++i, ++MapCount) {
		while (item[i] == NULL)
		{
			Loc = getRandomNumber(1, 5);			// 각 라인별로 랜덤 생성
			if (mapTile[Loc + (mapLineCount * MapCount)]->type != MonsterT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != ItemT
				&& mapTile[Loc + (mapLineCount * MapCount)]->type != TrapT) {		
				// 해당위치에 몬스터나 아이템, 트랩이 없을경우 아이템 생성
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
	MapCount = 0;											// 생성종료후 라인카운트 초기화
	return;
}

void GameManager::MonsterSetting()	// 몬스터 오브젝트 셋팅
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
				// 해당위치에 몬스터나 아이템, 트랩이 없을경우 몬스터 생성
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
		if (count == 0) { // 몬스터 타입이 겹치는게 없으면 텍스쳐 리소스를 가져온다.
			MonTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterName[mon[i]->monType]);
			MonAttackTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterAttackName[mon[i]->monType]);
			MonDamageTex[i] = SDLFramework::LoadTexture("./Media/" + mon[i]->MonsterDamageName[mon[i]->monType]);
			scene->Register_SDLTexture(mon[i]->MonsterName[mon[i]->monType], MonTex[i]);
			scene->Register_SDLTexture(mon[i]->MonsterAttackName[mon[i]->monType], MonAttackTex[i]);
			scene->Register_SDLTexture(mon[i]->MonsterDamageName[mon[i]->monType], MonDamageTex[i]);
		}
	}

	MapCount = 0;											// 생성종료후 라인카운트 초기화
	return;
}

void GameManager::ButtonSetting()							// 버튼 오브젝트 셋팅
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
		Loc = getRandomNumber(1, 5);				// 맵의 각 라인별로 랜덤 생성

		if (mapTile[Loc + (mapLineCount * MapCount)]->type != ItemT
			&& mapTile[Loc + (mapLineCount * MapCount)]->type != MonsterT
			&& mapTile[Loc + (mapLineCount * MapCount)]->type != TrapT) {
			// 해당위치에 몬스터나 아이템, 트랩이 없을경우 트랩 생성
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
	MapCount = 0;									// 생성종료후 라인카운트 초기화
}

void GameManager::createPlayer()							// 플레이어 생성
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

void GameManager::DrawingMonster()					// 몬스터를 그리는 함수
{
	for (int i = 0; i < 4; i++)
	{
		MonsterObj[i]->transform->SetWidth(100);	
		MonsterObj[i]->transform->SetHeight(100);
		mon[i]->CharacTex->SetAnimationActive(true);
		scene->RegisterGameObject(MonsterObj[i]);
		// 각 타일은 자신의 좌표를 가지고 있으므로 그것을 이용하여 그린다.
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

void GameManager::DrawingItem()				// 아이템을 그리는 함수
{
	for (int i = 0; i < 4; ++i) {
		item[i]->ItemTex->SetTexutre(scene->Get_SDLTexture("item"));

		// 각 타일은 자신의 좌표를 가지고 있으므로 그것을 이용하여 그린다.
		ItemObj[i]->transform->SetPosition((mapTile[*(item[i]->Ploc)]->x) + 25
			, (mapTile[*(item[i]->Ploc)]->y) + 25);
		ItemObj[i]->transform->SetWidth(70);
		ItemObj[i]->transform->SetHeight(70);
	}
}

void GameManager::DrawingPlayer()			// 플레이어를 그리는 함수
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
	// 폰트 로드
	SDLFramework::Instance()->RegisterFont("./Media/Font/BMYEONSUNG.ttf", 48);
	// 이곳에 게임에 필요한 오브젝트 또는 Scene 들을 초기 배치 및 등록합니다.
	ChangeScene(SceneName::Game);
}

void GameManager::Update(float deltaTime)
{
	if ((currentSceneName == StartScene || currentSceneName == GameOver) && scb != NULL) { // 시작버튼을 누를때 게임스타트씬으로 넘어간다.
		if (scb->GameStartState == true) {
			ChangeScene(SceneName::Game);
			return;
		}
	}
	if (currentSceneName == Game && gameState == true)
	{
		DiceButtonObj->active = player->battlestate ? false : true;					// 배틀 상태일 경우 버튼과 다이스를 숨긴다.
		dicebutton->DiceObj->active = player->battlestate ? false : true;

		if (!(*player->Isdead())) {			// 플레이어가 죽었을시 게임오버씬으로
			gameState = false;
			ChangeScene(SceneName::GameOver);
			return;
		}
		for (int i = 0; i < 24; i++)
		{
			if (MonDCount == 4 && mapTile[i]->type == endT) {	// 몬스터가 모두 죽었을시 다음 스테이지 타일로 이동
				player->walkPace = 12 + (24 - player->Loc);
				player->StayLoc = player->Loc;
				player->MoveState = true;
				return;
			}
		}

		// 마우스가 플레이어나 몬스터위치 밖에 있을경우 스테이터스 텍스쳐를 숨김
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

		if (player->battlestate == true && BTView != NULL) { // 배틀로 넘어갈 경우
			if (BTView->BattleTexState == false) { // 배틀이 시작될경우
				BTView->Battle(mapTile[player->Loc]->monster); // 배틀 세팅
				STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Attack_face"));
			}
			if (BTView->PAtkMotion == true) {
				BTView->PlayerAttack(deltaTime, mapTile[player->Loc]->monster, player);

				if (BTView->PAtkMotion == false && !(*(mapTile[player->Loc]->monster->Isdead()))) { // 몬스터가 죽었을경우 배틀 종료 및 경험치 획득, 몬스터오브젝트 제거

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
							if (count == 0) { // 살아있는 몬스터중 타입이 같은 몬스터가 없으면 리소스 제거
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
			else if (BTView->PAtkMotion == false && mapTile[player->Loc]->monster != NULL) { // 몬스터가 살아있고 캐릭터 모션이 끝나면 몬스터 공격
				BTView->MonsterAttack(deltaTime, mapTile[player->Loc]->monster);
				STView->CutInTex->SetTexutre(scene->Get_SDLTexture("Damage_face"));

				if (BTView->MAtkMotion == false) { // 몬스터 모션이 끝나면 배틀 종료
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
		if (sceneName == Game) { // 다음 스테이지로 넘어갈 경우 캐릭터, 맵, 스테이터스뷰, 배틀뷰를 제외한 모든 오브젝트를 초기화
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

	// scene이 들고있는 모든 오브젝트들을 파기
	scene->DestroyAll();

	SV.clear();

	// scene 전환
	currentSceneName = sceneName;
	switch (currentSceneName)
	{
	case StartScene:
		SetStartScene();
		break;
	case Game:
		SetGameScene();
		break;
	case GameOver: // 게임오버일경우 오브젝트가 아닌 BTview와 STview를 초기화
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
void GameManager::SetGameScene()			// 게임 Scene
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
void GameManager::SetGameOverScene()		// 게임오버 Scene
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
	if (GameWinState == false) // 플레이어가 죽었을 경우
		gameOverF->SetText(BMYEONSUNG, "GAME OVER", keyColor);
	else if (GameWinState == true) // 게임을 클리어 했을 경우
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

	if (GameWinState == false) // 플레이어가 죽었을 경우
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
	else if (GameWinState == true) { // 게임을 클리어 했을 경우
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
