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

		bool inside = true;  // �ȿ� ���Դ��� Ȯ���ϴ� ����

							 // �����ȿ� ������ false
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
		case SDL_MOUSEBUTTONDOWN:			// �̵����� �ƴϰų� ���� ��ŸƮ���°� �ƴҶ� ��ư�� ������ ĳ���Ͱ� �����δ�
			if (ButtonRunState == false && GameStartState == false)
			{
				if (GameManager::Instance()->GetCurrentSceneName() == GameOver) // ���ӿ��� ���ϰ�� SDLTexture ���� �� ��ġ, ũ�� �缳��
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
	if (ButtonRunState == true) { // �������� ���� ĳ���͸� �̵���Ų��.
		this->gameObject->transform->SetPosition(x, y);
		x+=4;
	}
	if (x == 980) { // ĳ���Ͱ� ���� ��ġ�� �����ϸ� ���߰� ���� ���� ������ �̵��Ѵ�.
		ButtonTex->SetAnimationActive(false);
		ButtonRunState = false;
		GameStartState = true;
	}
}
