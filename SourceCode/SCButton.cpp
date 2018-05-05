#include "SCButton.h"
#include "GameManager.h"


SCButton::SCButton()
{
}


SCButton::~SCButton()
{
}

void SCButton::Init()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

void SCButton::HandleEvent(SDL_Event * e)
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

		if (ButtonTex == NULL)
			return;
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:			// 이동중이 아니거나 게임 스타트상태가 아닐때 버튼을 누르면 캐릭터가 움직인다
			if (ButtonRunState == false && GameStartState == false)
			{
				if (GameManager::Instance()->GetCurrentSceneName() == GameOver) // 게임오버 씬일경우 SDLTexture 생성 및 위치, 크기 재설정
				{
					SDL_Texture* playerTex = SDLFramework::LoadTexture("./Media/player.png");
					GameManager::Instance()->scene->Register_SDLTexture("Splayer", playerTex);
					SetX(500);
					SetY(500);
					SetW(200);
					SetH(200);
				}
				ButtonTex->SetTexutre(GameManager::Instance()->scene->Get_SDLTexture("Splayer"));
				this->gameObject->transform->SetWidth(w);
				this->gameObject->transform->SetHeight(h);
				ButtonTex->SetHorizonCount(4);
				ButtonTex->SetVerticalCount(1);
				ButtonTex->SetFrameRate(80.0f);
				ButtonTex->SetAnimationActive(true);

				ButtonRunState = true; 
			}
			break;
		default:
			break;
		}
	}
}

void SCButton::Update(float deltaTime)
{
	if (ButtonRunState == true) { // 매프레임 별로 캐릭터를 이동시킨다.
		this->gameObject->transform->SetPosition(x, y);
		x+=4;
	}
	if (x == 980) { // 캐릭터가 일정 위치에 도달하면 멈추고 게임 시작 씬으로 이동한다.
		ButtonTex->SetAnimationActive(false);
		ButtonRunState = false;
		GameStartState = true;
	}
}
