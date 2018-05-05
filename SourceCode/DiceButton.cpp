#include "DiceButton.h"
#include "GameManager.h"


DiceButton::DiceButton()
{
}


DiceButton::~DiceButton()
{
}

void DiceButton::Init()
{
	DiceObj = new SDLGameObject("Dice");
	DiceObj->AddComponent<Dice>();
	DiceObj->AddComponent<Texture>();
	dice = DiceObj->GetComponent<Dice>();
	dice->gameObject = DiceObj;
	dice->DiceTex = DiceObj->GetComponent<Texture>();
	dice->DiceTex->gameObject = DiceObj;
	DiceObj->transform->SetPosition(400, 300);
	DiceObj->transform->SetWidth(200);
	DiceObj->transform->SetHeight(200);

	elapsedTime = 0.0f;
	DiceFrameRate = 720.0f;
}

void DiceButton::HandleEvent(SDL_Event * e)
{
	if (this->gameObject->transform == NULL)
		return;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;  // 안에 들어왔는지 확인하는 변수

		// 영역안에 없으면 false
		if (x < this->gameObject->transform->projRect.x || x > this->gameObject->transform->projRect.x + this->gameObject->transform->projRect.w ||
			y < this->gameObject->transform->projRect.y || y > this->gameObject->transform->projRect.y + this->gameObject->transform->projRect.h)
			inside = false;
		if (inside == false) {
			return;
		}
		if (this->ButtonTex == NULL)
			return;
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:			// 배틀중이나 움직이는 중이 아닐때 버튼을 누르면 다이스를 굴린다
			if (player != NULL)
			{
				if (player->battlestate == false && player->MoveState == false)
				{
					diceState = true;
				}
			}
			break;
		default:
			break;
		}
	}
}

void DiceButton::Update(float deltaTime)
{
	if (diceState == true && diceSpState == true) {
		elapsedTime += deltaTime;
		dice->DiceTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(dice->DiceTName[6]));
		DiceObj->transform->SetPosition(380, 280);
		DiceObj->transform->SetWidth(250);
		DiceObj->transform->SetHeight(250);
		dice->DiceTex->SetHorizonCount(16);
		dice->DiceTex->SetVerticalCount(1);
		dice->DiceTex->SetFrameRate(16.0f);
		dice->DiceTex->SetAnimationActive(true);
		if (elapsedTime > DiceFrameRate) // 다이스를 굴리고 일정시간 이후 다이스를 멈춤
		{
			diceSpState = false;
			elapsedTime = 0.0f;
		}
	}
	else if (diceSpState == false) { // 다이스가 멈추면 캐릭터를 해당 위치로 이동시킴
		
		int step = dice->randomDice();
		player->walkPace = step;
		player->StayLoc = player->Loc;
		player->MoveState = true;
		
		dice->DiceTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture(dice->DiceTName[step - 1]));
		DiceObj->transform->SetPosition(400, 300);
		DiceObj->transform->SetWidth(200);
		DiceObj->transform->SetHeight(200);
		dice->DiceTex->SetHorizonCount(1);
		dice->DiceTex->SetVerticalCount(1);
		dice->DiceTex->SetAnimationActive(false);
		
		diceState = false;
		diceSpState = true;
	}
}
