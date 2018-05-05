#include <iostream>
#include <algorithm>
#include "SDLFramework.h"
//#include "CircleCollider.h"
//#include "RectangleCollider.h"

using namespace std;

void SDLFramework::AddGameObject(SDLGameObject * obj)
{
	gameObjects.push_back(obj);
}

void SDLFramework::RemoveGameObject(SDLGameObject * obj)
{
	list<SDLGameObject*>::iterator firstIter = gameObjects.begin();
	for (; firstIter != gameObjects.end(); ++firstIter)
	{
		SDLGameObject* currentObject = *firstIter;
		if (currentObject != NULL && currentObject == obj)
		{
			currentObject->willBeDestroy = true;
			currentObject->active = false;
			haveToRemoveObject = true;
			break;
		}
	}
}

SDLFramework::SDLFramework()
{
}


SDLFramework::~SDLFramework()
{
}

void SDLFramework::DelayDestroyObjects()
{
	list<SDLGameObject*>::iterator iter = gameObjects.begin();
	for (; iter != gameObjects.end(); )
	{
		if ((*iter)->willBeDestroy)
		{
			delete *iter;
			*iter = NULL;
			gameObjects.erase(iter++);
		}
		else
			iter++;
	}

	haveToRemoveObject = false;
}

bool SDLFramework::Init()
{
	bool success = true;
	//SDL 초기화
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)		// SDL 초기화 실패시
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else										// 초기화 성공시
	{
		//윈도우 생성
		window = SDL_CreateWindow(
			"SDL Tutorial",    //타이틀
			SDL_WINDOWPOS_UNDEFINED,  //x좌표
			SDL_WINDOWPOS_UNDEFINED,  //y좌표
			SCREEN_WIDTH,     //화면너비
			SCREEN_HEIGHT,     //화면높이
			SDL_WINDOW_SHOWN   //창 보이기
		);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create Renderer for Window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == NULL)
			{
				printf("Renderer Could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{

				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error : " << TTF_GetError() << endl;
					success = false;
				}

				// 백그라운드 색 채우기
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_Image Could not initialize! SDL_Error : " << SDL_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

void SDLFramework::HandleEvent(SDL_Event* e)
{
	list<SDLGameObject*>::iterator firstIter = gameObjects.begin();
	for (; firstIter != gameObjects.end(); ++firstIter)
	{
		if (haveToRemoveObject)
			return;

		SDLGameObject* currentObject = *firstIter;
		if (currentObject != NULL)
			currentObject->HandleEvent(e);
	}
}

void SDLFramework::Update(float deltaTime)
{
	// Event 관련 처리 및 게임 오브젝트 Update
	list<SDLGameObject*>::iterator firstIter = gameObjects.begin();
	for (; firstIter != gameObjects.end(); ++firstIter)
	{
		if (haveToRemoveObject)
			return;

		SDLGameObject* currentObject = *firstIter;
		if (currentObject != NULL && currentObject->active)
			currentObject->Update(deltaTime);
	}

//	CheckCollisionObjects();
}

//void SDLFramework::CheckCollisionObjects()
//{
//	list<SDLGameObject*>::iterator firstIter = gameObjects.begin();
//	for (; firstIter != gameObjects.end(); ++firstIter)
//	{
//		if (haveToRemoveObject)
//			return;
//
//		SDLGameObject* currentObject = *firstIter;
//		if (currentObject != NULL)
//		{
//			Collider* collider = currentObject->GetComponent<Collider>();
//			if (collider != NULL)
//			{
//				list<SDLGameObject*>::iterator secondIter = std::next(firstIter, 1);
//				for (; secondIter != gameObjects.end(); ++secondIter)
//				{
//					if (haveToRemoveObject)
//						return;
//
//					SDLGameObject* otherObject = *secondIter;
//					if (otherObject != NULL)
//					{
//						Collider* otherCollider = otherObject->GetComponent<Collider>();
//						if (otherCollider != NULL)
//						{
//							if (IsCollision(collider, otherCollider))
//							{
//								if (collider->FindEnteredCollider(otherCollider) == NULL)
//								{
//									collider->gameObject->OnCollisionEnter(otherCollider);
//									collider->enteredColliders.push_back(otherCollider);
//								}
//								else
//								{
//									collider->gameObject->OnCollisionStay(otherCollider);
//								}
//
//								if (otherCollider->FindEnteredCollider(collider) == NULL)
//								{
//									otherCollider->gameObject->OnCollisionEnter(collider);
//									otherCollider->enteredColliders.push_back(collider);
//								}
//								else
//								{
//									otherCollider->gameObject->OnCollisionStay(collider);
//								}
//							}
//							else
//							{
//								if (collider->FindEnteredCollider(otherCollider) != NULL)
//								{
//									collider->gameObject->OnCollisionExit(otherCollider);
//									collider->enteredColliders.remove(otherCollider);
//								}
//								if (otherCollider->FindEnteredCollider(collider) != NULL)
//								{
//									otherCollider->gameObject->OnCollisionExit(collider);
//									otherCollider->enteredColliders.remove(collider);
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}

void SDLFramework::Render()
{
	// 렌더러가 제대로 초기화 된경우에만 렌더
	if (renderer != NULL)
	{
		// 현재 백버퍼 (: 이전 프레임의 프론트버퍼)를 깨끗히 한다
		SDL_RenderClear(renderer);

		// 각 GameObject Render
		list<SDLGameObject*>::iterator firstIter = gameObjects.begin();
		for (; firstIter != gameObjects.end(); ++firstIter)
		{
			if (haveToRemoveObject)
				return;
			SDLGameObject* currentObject = *firstIter;
			if (currentObject != NULL && currentObject->active)
				currentObject->Render();
		}

		// UpdateScreen : 백 버퍼와 프론트 버퍼를 스왑하여 업데이트 된 화면을 보여준다. 
		SDL_RenderPresent(renderer);
	}
}

void SDLFramework::Close()
{
	// 게임 오브젝트들 해제
	for (auto object : gameObjects)
	{
		delete object;
	}
	gameObjects.clear();

	// 폰트 파기
	for (auto font : fonts)
	{
		TTF_CloseFont(font);
	}
	fonts.clear();

	// 렌더러 파기
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//창 파괴
	SDL_DestroyWindow(window);
	window = NULL;

	//SDL 하위시스템 끝내기
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDLFramework::RegisterFont(string filePath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
	if (font == NULL)
	{
		cout << "Failed to load Diablo font! SDL_ttf Error : " << TTF_GetError() << endl;
	}
	else
	{
		fonts.push_back(font);
	}
}

SDL_Texture* SDLFramework::LoadTexture(string filePath, SDL_Color * keyColor)
{
	if (keyColor == NULL)
	{
		keyColor = new SDL_Color();
		keyColor->r = 0xFF; keyColor->g = 0x00; keyColor->b = 0xFF;
	}

	// final Texture
	SDL_Texture* newTexture = NULL;

	// 이미지를 매개변수 filePath로 부터 로드
	SDL_Surface* surface = NULL; // 로드를 해서 바로 담을 Surface

	surface = IMG_Load(filePath.c_str()); // surface 에 로드

	if (surface == NULL)
	{
		cout << "Unable to load image " << filePath << "SDL_Error : " << SDL_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(
			surface,
			SDL_TRUE,
			SDL_MapRGB(surface->format, keyColor->r, keyColor->g, keyColor->b)
		);

		// 텍스처를 Surface 픽셀들로 부터 생성
		newTexture = SDL_CreateTextureFromSurface(instance->renderer, surface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from " << filePath << "SDL_Error : " << SDL_GetError() << endl;
		}

		// 필요없는 SDL_Surface* 를 해제
		SDL_FreeSurface(surface);
	}

	if (keyColor != NULL) {
		delete keyColor;
		keyColor = NULL;
	}

	return newTexture;
}

SDL_Texture * SDLFramework::LoadTextureFromFont(TTF_Font * font, string textureText, SDL_Color * textColor)
{
	{
		SDL_Texture* texture = NULL;

		SDL_Color color;
		if (textColor == NULL)
		{
			color.r = 0x00; color.g = 0x00; color.b = 0x00; color.a = 0xFF;
		}
		else
		{
			color = *textColor;
		}

		SDL_Surface* surface = TTF_RenderText_Solid(font, textureText.c_str(), color);

		if (surface == NULL)
		{
			cout << "Unable to render text surface! SDL_ttf Error : " << TTF_GetError() << endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(instance->renderer, surface);

			if (texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL Error : " << SDL_GetError() << endl;
			}

			SDL_FreeSurface(surface);
		}
		return texture;
	}
}

//bool SDLFramework::IsCollision(Collider* collider, Collider* other)
//{
//	switch (collider->type)
//	{
//	case Circle:
//		switch (other->type)
//		{
//		case Circle:
//			return CheckCollision((CircleCollider*)collider, (CircleCollider*)other);
//		case Rectangle:
//			return CheckCollision((CircleCollider*)collider, (RectangleCollider*)other);
//		}
//		break;
//	case Rectangle:
//		switch (other->type)
//		{
//		case Circle:
//			return CheckCollision((CircleCollider*)other, (RectangleCollider*)collider);
//		case Rectangle:
//			return CheckCollision((RectangleCollider*)collider, (RectangleCollider*)other);
//		}
//		break;
//	}
//	return false;
//}

//bool SDLFramework::IsPointInCircle(int px, int py, int cx, int cy, int radius)
//{
//	int xDelta = cx - px;
//	int yDelta = cy - py;
//
//	float distance = sqrtf((float)(xDelta * xDelta + yDelta * yDelta));
//
//	if (radius >= (int)distance)
//		return true;
//	else
//		return false;
//}

// 원과 사각형
//bool SDLFramework::CheckCollision(CircleCollider * circle, RectangleCollider* rect)
//{
//	SDL_Rect r = rect->collisionRect;
//
//	if ((r.x <= circle->centerX && circle->centerX <= r.x + r.w) ||
//		(r.y <= circle->centerY && circle->centerY <= r.y + r.h))
//	{
//		// 원의 반지름 만큼 확장된 사각형의 각 x, y 좌표를 구함
//		int left = r.x - circle->radius;
//		int top = r.y - circle->radius;
//		int right = r.x + r.w + circle->radius;
//		int bottom = r.y + r.h + circle->radius;
//
//		if ((left < circle->centerX && circle->centerX < right) &&
//			(top < circle->centerY && circle->centerY < bottom))
//		{
//			return true;
//		}
//	}
//	else
//	{
//		if (IsPointInCircle(r.x, r.y, circle->centerX, circle->centerY, circle->radius))
//			return true;
//
//		if (IsPointInCircle(r.x + r.w, r.y, circle->centerX, circle->centerY, circle->radius))
//			return true;
//
//		if (IsPointInCircle(r.x, r.y + r.h, circle->centerX, circle->centerY, circle->radius))
//			return true;
//
//		if (IsPointInCircle(r.x + r.w, r.y + r.h, circle->centerX, circle->centerY, circle->radius))
//			return true;
//	}
//
//	return false;
//}

//bool SDLFramework::CheckCollision(CircleCollider * circle, CircleCollider * other)
//{
//	float distance = sqrt(powf((float)(other->centerX - circle->centerX), 2) +
//		powf((float)(other->centerY - circle->centerY), 2));
//
//	if ((int)distance <= circle->radius + other->radius)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//bool SDLFramework::CheckCollision(RectangleCollider * rect, RectangleCollider * other)
//{
//	int left1 = rect->collisionRect.x;
//	int right1 = left1 + rect->collisionRect.w;
//	int top1 = rect->collisionRect.y;
//	int bottom1 = top1 + rect->collisionRect.h;
//
//	int left2 = other->collisionRect.x;
//	int right2 = left2 + other->collisionRect.w;
//	int top2 = other->collisionRect.y;
//	int bottom2 = top2 + other->collisionRect.h;
//
//	if (right1 <= left2 || left1 >= right2 ||
//		top1 >= bottom2 || bottom1 <= top2)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
