#include "GameManager.h"


StatusView::StatusView()
{
	SDL_Texture* Common_face = SDLFramework::LoadTexture("./media/Common_face.PNG");
	GameManager::Instance()->scene->Register_SDLTexture("Common_face", Common_face);

	SDL_Texture* Attack_face = SDLFramework::LoadTexture("./Media/Attack_face.PNG");
	GameManager::Instance()->scene->Register_SDLTexture("Attack_face", Attack_face);

	SDL_Texture* Damage_face = SDLFramework::LoadTexture("./media/Damage_face.PNG");
	GameManager::Instance()->scene->Register_SDLTexture("Damage_face", Damage_face);

	SDL_Texture* Item_face = SDLFramework::LoadTexture("./media/Item_face.PNG");
	GameManager::Instance()->scene->Register_SDLTexture("Item_face", Item_face);

	keyColor = new SDL_Color();
	keyColor->r = keyColor->g = keyColor->b = 0xFF;

	CutInObj = new SDLGameObject("CharacterCutIn");
	CutInObj->AddComponent<Texture>();
	CutInTex = CutInObj->GetComponent<Texture>();
	CutInTex->gameObject = CutInObj;
	CutInObj->transform->SetPosition(950, 2);
	CutInObj->transform->SetWidth(280);
	CutInObj->transform->SetHeight(80);
	CutInTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Common_face"));
	GameManager::Instance()->scene->RegisterGameObject(CutInObj);

	StatusObj = new SDLGameObject("CharacterS");
	StatusObj->AddComponent<Texture>();
	StatusTex = StatusObj->GetComponent<Texture>();
	StatusTex->gameObject = StatusObj;
	StatusObj->transform->SetPosition(990, 105);
	StatusObj->transform->SetWidth(250);
	StatusObj->transform->SetHeight(250);
	StatusTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("player"));
	GameManager::Instance()->scene->RegisterGameObject(StatusObj);

	int countx = -1;
	int county = 1;
	for (int i = 0; i < 8; ++i) {

		GameManager::Instance()->ObjName.append("CharacStat");
		GameManager::Instance()->ObjName.append(GameManager::Instance()->nameNumber, i, 1);
		StatusFObj[i] = new SDLGameObject(GameManager::Instance()->ObjName);
		StatusFObj[i]->AddComponent<Text>();
		StatusF[i] = StatusFObj[i]->GetComponent<Text>();
		StatusF[i]->gameObject = StatusFObj[i];

		StatusFObj[i]->transform->SetPosition(1000, 410 + (70 * i));
		StatusFObj[i]->transform->SetWidth(250);
		StatusFObj[i]->transform->SetHeight(70);

		if (i >= 1 && i <= 4) {
			StatusFObj[i]->transform->SetPosition(1130 + (130 * countx), 410 + (70 * county));
			if (i == 1 || i == 3)
				countx++;
			if (i == 2 || i == 4) {
				county++;
				countx = -1;
			}
			StatusFObj[i]->transform->SetWidth(100);
			StatusFObj[i]->transform->SetHeight(70);
		}
		if (i > 4) {
			StatusFObj[i]->transform->SetPosition(1000, 410 + (70 * county));
			county++;
		}
		StatusFObj[i]->active = false;
		GameManager::Instance()->scene->RegisterGameObject(StatusFObj[i]);
		GameManager::Instance()->ObjName.clear();
	}
	StatusF[0]->SetText(BMYEONSUNG, "a", keyColor);
	for (int i = 1; i < 8; ++i)
		StatusF[i]->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("a"));
}

void StatusView::ViewingPlayerStatus(Player* player) 
{
	string STAT;

	StatusTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("playerT"));
	StatusTex->SetHorizonCount(player->CharacTex->GetHorizonCount());
	StatusTex->SetVerticalCount(player->CharacTex->GetVerticalCount());
	StatusTex->SetFrameRate(80.0f);
	StatusTex->SetAnimationActive(true);

	
	for (int i = 0; i < 6; ++i) {
		if (GameManager::Instance()->scene->Get_SDLTexture(StatusF[i]->Name) == NULL) {
			switch (i)
			{
			case 0:
				STAT = player->getName();
				StatusF[i]->SetText(BMYEONSUNG, "NAME : " + STAT, keyColor);
				STAT.clear();
				break;
			case 1:
				STAT = to_string(player->Lev);
				StatusF[i]->SetText(BMYEONSUNG, "Level : " + STAT, keyColor);
				STAT.clear();
				break;
			case 2:
				STAT = to_string(*(player->getHp()));
				StatusF[i]->SetText(BMYEONSUNG, "HP : " + STAT, keyColor);
				STAT.clear();
				break;
			case 3:
				STAT = to_string(player->getAtk());
				StatusF[i]->SetText(BMYEONSUNG, "ATK : " + STAT, keyColor);
				STAT.clear();
				break;
			case 4:
				STAT = to_string(player->getDef());
				StatusF[i]->SetText(BMYEONSUNG, "DEF : " + STAT, keyColor);
				STAT.clear();
				break;
			case 5:
				STAT = to_string(player->Exp);
				StatusF[i]->SetText(BMYEONSUNG, "Exp : " + STAT + " / 100", keyColor);
				STAT.clear();
				break;
			default:
				break;
			}
			GameManager::Instance()->scene->Register_SDLTexture(StatusF[i]->Name, StatusF[i]->GetTexture());
		}
		StatusFObj[i]->active = true;
	}
	for (int i = 6; i < 8; ++i) {
		if (GameManager::Instance()->scene->Get_SDLTexture(StatusF[i]->Name) == NULL && 
			player->equipedItem[i - 6] != NULL)
		{
			STAT = player->equipedItem[i - 6]->getName();
			StatusF[i]->SetText(BMYEONSUNG, "Item : " + STAT, keyColor);
			STAT.clear();
			GameManager::Instance()->scene->Register_SDLTexture(StatusF[i]->Name, StatusF[i]->GetTexture());
			StatusFObj[i]->active = true;
		}
	}
	StatusObj->active = true;
}

void StatusView::ViewingMonStatus(Monster* mon)
{
	string STAT;
	StatusTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(mon->MonsterName[mon->monType]));
	StatusTex->SetHorizonCount(mon->CharacTex->GetHorizonCount());
	StatusTex->SetVerticalCount(mon->CharacTex->GetVerticalCount());
	StatusTex->SetFrameRate(200.0f);
	StatusTex->SetAnimationActive(true);

	for (int i = 0; i < 4; ++i) {
		if (GameManager::Instance()->scene->Get_SDLTexture(StatusF[i]->Name) == NULL) {
			switch (i)
			{
			case 0:
				STAT = mon->getName();
				StatusF[i]->SetText(BMYEONSUNG, "NAME : " + STAT, keyColor);
				STAT.clear();
				break;
			case 1:
				STAT = to_string(*(mon->getHp()));
				StatusF[i]->SetText(BMYEONSUNG, "HP : " + STAT, keyColor);
				STAT.clear();
				break;
			case 2:
				STAT = to_string(mon->getAtk());
				StatusF[i]->SetText(BMYEONSUNG, "ATK : " + STAT, keyColor);
				STAT.clear();
				break;
			case 3:
				STAT = to_string(mon->getDef());
				StatusF[i]->SetText(BMYEONSUNG, "DEF : " + STAT, keyColor);
				STAT.clear();
				break;
			default:
				break;
			}
			GameManager::Instance()->scene->Register_SDLTexture(StatusF[i]->Name, StatusF[i]->GetTexture());
		}
		StatusFObj[i]->active = true;
	}
	StatusObj->active = true;
}


StatusView::~StatusView()
{
	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}
}
