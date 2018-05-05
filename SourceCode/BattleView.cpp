#include "GameManager.h"


BattleView::BattleView()
{
	SDL_Texture* PlayerbattleT = SDLFramework::LoadTexture("./media/playerattack.png");
	GameManager::Instance()->scene->Register_SDLTexture("PlayerBattleScene", PlayerbattleT);
	
	SDL_Texture* playerDieT = SDLFramework::LoadTexture("./Media/playerDie.png");
	GameManager::Instance()->scene->Register_SDLTexture("playerDie", playerDieT);

	SDL_Texture* PlayerEffectT = SDLFramework::LoadTexture("./Media/PlayerEffect.png");
	GameManager::Instance()->scene->Register_SDLTexture("PlayerEffect", PlayerEffectT);
	
	SDL_Texture* MonsterEffectT = SDLFramework::LoadTexture("./media/MonsterEffect.png");
	GameManager::Instance()->scene->Register_SDLTexture("MonsterEffect", MonsterEffectT);

	keyColor = new SDL_Color();
	keyColor->r = 0xFF;
	keyColor->g = keyColor->b = 0x00;

	PlayerbattleObj = new SDLGameObject("PlayerBattleSceneObj");
	PlayerbattleObj->AddComponent<Texture>();
	playerbattleTex = PlayerbattleObj->GetComponent<Texture>();
	playerbattleTex->gameObject = PlayerbattleObj;
	playerbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("playerT"));
	PlayerbattleObj->transform->SetPosition(210, 285);
	PlayerbattleObj->transform->SetWidth(260);
	PlayerbattleObj->transform->SetHeight(300);
	playerbattleTex->SetHorizonCount(4);
	playerbattleTex->SetVerticalCount(1);
	playerbattleTex->SetAnimationActive(false);
	GameManager::Instance()->scene->RegisterGameObject(PlayerbattleObj);
	PlayerbattleObj->active = false;

	MonsterbattleObj = new SDLGameObject("MonsterBattleSceneObj");
	MonsterbattleObj->AddComponent<Texture>();
	monsterbattleTex = MonsterbattleObj->GetComponent<Texture>();
	monsterbattleTex->gameObject = MonsterbattleObj;
	monsterbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("playerT"));
	MonsterbattleObj->transform->SetPosition(490, 285);
	MonsterbattleObj->transform->SetWidth(260);
	MonsterbattleObj->transform->SetHeight(300);
	monsterbattleTex->SetFrameRate(200.0f);
	monsterbattleTex->SetAnimationActive(false);
	GameManager::Instance()->scene->RegisterGameObject(MonsterbattleObj);
	MonsterbattleObj->active = false;

	PlayereffectObj = new SDLGameObject("PlayerEffectObj");
	PlayereffectObj->AddComponent<Texture>();
	playereffectTex = PlayereffectObj->GetComponent<Texture>();
	playereffectTex->gameObject = PlayereffectObj;
	playereffectTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("PlayerEffect"));
	PlayereffectObj->transform->SetPosition(490, 320);
	PlayereffectObj->transform->SetWidth(200);
	PlayereffectObj->transform->SetHeight(200);
	playereffectTex->SetHorizonCount(5);
	playereffectTex->SetVerticalCount(1);
	playereffectTex->SetFrameRate(215.0f);
	playereffectTex->SetAnimationActive(false);
	PlayereffectObj->active = false;
	GameManager::Instance()->scene->RegisterGameObject(PlayereffectObj);

	MonsterEffectObj = new SDLGameObject("MonsterEffectObj");
	MonsterEffectObj->AddComponent<Texture>();
	MonsterEffectTex = MonsterEffectObj->GetComponent<Texture>();
	MonsterEffectTex->gameObject = MonsterEffectObj;
	MonsterEffectTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("MonsterEffect"));
	MonsterEffectObj->transform->SetPosition(210, 355);
	MonsterEffectObj->transform->SetWidth(200);
	MonsterEffectObj->transform->SetHeight(200);
	MonsterEffectTex->SetHorizonCount(5);
	MonsterEffectTex->SetVerticalCount(1);
	MonsterEffectTex->SetFrameRate(100.0f);
	MonsterEffectTex->SetAnimationActive(false);
	MonsterEffectObj->active = false;
	GameManager::Instance()->scene->RegisterGameObject(MonsterEffectObj);

	DamageFObj = new SDLGameObject("DamageFObj");
	DamageFObj->AddComponent<Text>();
	DamageF = DamageFObj->GetComponent<Text>();
	DamageF->gameObject = DamageFObj;
	DamageFObj->transform->SetWidth(120);
	DamageFObj->transform->SetHeight(60);
	DamageFObj->active = false;
	GameManager::Instance()->scene->RegisterGameObject(DamageFObj);

	AttackFrameRate = 560.0f;
	elapsedTime = 0.0f;
	BattleTexState = false;
	MAtkMotion = true;
	PAtkMotion = true;
	maxX = 0;
	maxY = 0;
	fontY = 405;
}

BattleView::~BattleView()
{
	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}
}

void BattleView::Battle(Monster* mon)
{
	// ��Ʋ �� ����
	BattleTexState = true;
	MAtkMotion = true;
	PAtkMotion = true;

	playerbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("playerT"));
	monsterbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(mon->MonsterName[mon->monType]));
	monsterbattleTex->SetHorizonCount(mon->CharacTex->GetHorizonCount());
	monsterbattleTex->SetVerticalCount(mon->CharacTex->GetVerticalCount());

	// ��������Ʈ cliprect x, y��ǥ �ʱ�ȭ
	playereffectTex->SetFrameCount(0);
	playerbattleTex->SetFrameCount(0);
	monsterbattleTex->SetFrameCount(0);
	MonsterEffectTex->SetFrameCount(0);

	PlayerbattleObj->active = true;
	MonsterbattleObj->active = true;
}

void BattleView::PlayerAttack(float deltaTime, Monster* mon, Player* player)
{
	elapsedTime += deltaTime;

	// �������� ��Ʈ�� ����
	if (GameManager::Instance()->scene->Get_SDLTexture("-" + player->DamageFName) == NULL)
	{
		DamageF->SetText(BMYEONSUNG, "-" + player->DamageFName, keyColor);
		GameManager::Instance()->scene->Register_SDLTexture(DamageF->Name, DamageF->GetTexture());
	}
	else {
		DamageF->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("-" + player->DamageFName));
		DamageF->Name = "-" + player->DamageFName;
	}

	playerbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("PlayerBattleScene"));
	PlayerbattleObj->transform->SetPosition(210, 285);
	PlayerbattleObj->transform->SetWidth(260);
	PlayerbattleObj->transform->SetHeight(300);
	playerbattleTex->SetHorizonCount(7);
	playerbattleTex->SetVerticalCount(2);
	playerbattleTex->SetFrameRate(100.0f);

	maxX = ((playereffectTex->GetTextureWidth()) -
		(playereffectTex->GetTextureWidth() / playereffectTex->GetHorizonCount()));
	maxY = ((playereffectTex->GettextureHeight()) -
		(playereffectTex->GettextureHeight() / playereffectTex->GetVerticalCount()));

	monsterbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(mon->MonsterDamageName[mon->monType]));
	switch (mon->monType)  // Ÿ�Կ����� �ٸ� ������ ���ش�.
	{
	case Skull:
		MonsterbattleObj->transform->SetPosition(490, 285);
		monsterbattleTex->SetHorizonCount(4);
		monsterbattleTex->SetVerticalCount(2);
		MonsterbattleObj->transform->SetWidth(260);
		MonsterbattleObj->transform->SetHeight(300);
		monsterbattleTex->SetFrameRate(100.0f);
		break;
	case mermaid:
		monsterbattleTex->SetHorizonCount(7);
		monsterbattleTex->SetVerticalCount(1);
		MonsterbattleObj->transform->SetPosition(490, 285);
		MonsterbattleObj->transform->SetWidth(260);
		MonsterbattleObj->transform->SetHeight(300);
		monsterbattleTex->SetFrameRate(100.0f);
		break;
	case Angel:
		MonsterbattleObj->transform->SetPosition(440, 200);
		MonsterbattleObj->transform->SetWidth(360);
		MonsterbattleObj->transform->SetHeight(400);
		monsterbattleTex->SetHorizonCount(6);
		monsterbattleTex->SetVerticalCount(1);
		monsterbattleTex->SetFrameRate(100.0f);
		break;
	case GaruKasa:
		MonsterbattleObj->transform->SetPosition(440, 200);
		MonsterbattleObj->transform->SetWidth(360);
		MonsterbattleObj->transform->SetHeight(400);
		monsterbattleTex->SetHorizonCount(7);
		monsterbattleTex->SetVerticalCount(1);
		monsterbattleTex->SetFrameRate(100.0f);
		break;
	default:
		return;
	}

	playerbattleTex->SetAnimationActive(true);

	DamageFObj->transform->SetPosition(470, fontY);

	// ��Ʈ�� ��Ÿ���� ���� �����̱� �����Ѵ�
	if (DamageFObj->active == true)
		fontY -= 2;

	// �÷��̾ �����̰� �����ð� ���� ����Ʈ�� ���Ͱ� �´� ���, ��Ʈ�� �����δ�.
	if (elapsedTime > AttackFrameRate) {
		playereffectTex->SetAnimationActive(true);
		PlayereffectObj->active = true;
		monsterbattleTex->SetAnimationActive(true);
		DamageFObj->active = true;
		elapsedTime = 0.0f;
		AttackFrameRate = 16.0f;

		// ����Ʈ�� ������ ���� ���߰� �����.
		if (PlayereffectObj->transform->getClipRectX() == maxX && PlayereffectObj->transform->getClipRectY() == maxY) {
			playereffectTex->SetAnimationActive(false);
			PlayereffectObj->active = false;
		}

		// ��Ʈ�� ���� ��ġ�� �����ϸ� ������ �����ϰ� �ʱ�ȭ
		if (fontY <= 351)
		{
			playereffectTex->SetFrameCount(0);
			playerbattleTex->SetFrameCount(0);
			monsterbattleTex->SetFrameCount(0);
			MonsterEffectTex->SetFrameCount(0);
			PAtkMotion = false;
			DamageFObj->active = false;
			if (GameManager::Instance()->scene->Get_SDLTexture(DamageF->Name) != GameManager::Instance()->scene->Get_SDLTexture(mon->DamageFName))
				GameManager::Instance()->scene->Destroy_SDLTexture(DamageF->Name);
			fontY = 405;
			playerbattleTex->SetAnimationActive(false);
			playereffectTex->SetAnimationActive(false);
			PlayereffectObj->active = false;
			AttackFrameRate = 560.0f;
			return;
		}
	}
}

void BattleView::MonsterAttack(float deltaTime, Monster* mon)
{
	elapsedTime += deltaTime;

	// �������� ��Ʈ�� ����
	if (GameManager::Instance()->scene->Get_SDLTexture("-" + mon->DamageFName) == NULL)
	{
		DamageF->SetText(BMYEONSUNG, "-" + mon->DamageFName, keyColor);
		GameManager::Instance()->scene->Register_SDLTexture(DamageF->Name, DamageF->GetTexture());
	}
	else {
		DamageF->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("-" + mon->DamageFName));
		DamageF->Name = "-" + mon->DamageFName;
	}

	playerbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("playerDie"));
	playerbattleTex->SetHorizonCount(7);
	playerbattleTex->SetVerticalCount(1);
	PlayerbattleObj->transform->SetPosition(210, 355);
	PlayerbattleObj->transform->SetWidth(250);
	PlayerbattleObj->transform->SetHeight(250);
	playerbattleTex->SetFrameRate(120.0f);

	monsterbattleTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(mon->MonsterAttackName[mon->monType]));

	switch (mon->monType)  // Ÿ�Կ����� �ٸ� �ؽ��ĸ� �׸���.
	{
	case Skull:
		MonsterbattleObj->transform->SetPosition(390, 235);
		MonsterbattleObj->transform->SetWidth(400);
		MonsterbattleObj->transform->SetHeight(440);
		monsterbattleTex->SetHorizonCount(8);
		monsterbattleTex->SetVerticalCount(4);
		monsterbattleTex->SetFrameRate(80.0f);
		break;
	case mermaid:
		MonsterbattleObj->transform->SetWidth(260);
		MonsterbattleObj->transform->SetHeight(300);
		monsterbattleTex->SetHorizonCount(9);
		monsterbattleTex->SetVerticalCount(3);
		monsterbattleTex->SetFrameRate(80.0f);
		break;
	case Angel:
		MonsterbattleObj->transform->SetPosition(390, 235);
		MonsterbattleObj->transform->SetWidth(400);
		MonsterbattleObj->transform->SetHeight(440);
		monsterbattleTex->SetHorizonCount(8);
		monsterbattleTex->SetVerticalCount(5);
		monsterbattleTex->SetFrameRate(60.0f);
		break;
	case GaruKasa:
		MonsterbattleObj->transform->SetPosition(390, 235);
		MonsterbattleObj->transform->SetWidth(400);
		MonsterbattleObj->transform->SetHeight(440);
		monsterbattleTex->SetHorizonCount(6);
		monsterbattleTex->SetVerticalCount(6);
		monsterbattleTex->SetFrameRate(60.0f);
		break;
	default:
		return;
	}

	monsterbattleTex->SetAnimationActive(true);
	
	DamageFObj->transform->SetPosition(320, fontY);
	// ��Ʈ�� ��Ÿ���� ���� �����̱� �����Ѵ�
	if (DamageFObj->active == true)
		fontY -= 2;

	// ���Ͱ� �����̰� �����ð� ���� ����Ʈ�� �÷��̾ �´� ���, ��Ʈ�� �����δ�.
	if (elapsedTime > AttackFrameRate) {
		DamageFObj->active = true;
		MonsterEffectTex->SetAnimationActive(true);
		MonsterEffectObj->active = true;
		playerbattleTex->SetAnimationActive(true);
		elapsedTime = 0.0f;
		AttackFrameRate = 16.0f;

		// ��Ʈ�� ���� ��ġ�� �����ϸ� ������ �����ϰ� �ʱ�ȭ
		if (fontY <= 351)
		{
			playereffectTex->SetFrameCount(0);
			playerbattleTex->SetFrameCount(0);
			monsterbattleTex->SetFrameCount(0);
			MonsterEffectTex->SetFrameCount(0);
			playerbattleTex->SetAnimationActive(false);
			MonsterEffectObj->active = false;
			MAtkMotion = false;
			monsterbattleTex->SetAnimationActive(false);
			DamageFObj->active = false;
			GameManager::Instance()->scene->Destroy_SDLTexture(DamageF->Name);
			AttackFrameRate = 560.0f;
			fontY = 405;
			return;
		}
	}
	
}

void BattleView::BattleOff()
{
	// ��Ʋ ������ ��� �ʱ�ȭ�� �ؽ��ĸ� ����
	playereffectTex->SetAnimationActive(false);
	playerbattleTex->SetAnimationActive(false);
	PlayereffectObj->active = false;
	PlayerbattleObj->active = false;

	monsterbattleTex->SetAnimationActive(false);
	MonsterEffectTex->SetAnimationActive(false);
	MonsterEffectObj->active = false;
	MonsterbattleObj->active = false;
	DamageFObj->active = false;
	BattleTexState = false;

	playereffectTex->SetFrameCount(0);
	playerbattleTex->SetFrameCount(0);
	monsterbattleTex->SetFrameCount(0);
	MonsterEffectTex->SetFrameCount(0);
}
