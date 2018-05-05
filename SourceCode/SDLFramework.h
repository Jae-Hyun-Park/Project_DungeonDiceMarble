#pragma once
#include <vector>
#include <list>
#include <string>
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"
#include "SDLGameObject.h"

using namespace std;

#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 960

//class CircleCollider;
//class RectangleCollider;

class SDLFramework
{
private:
	static SDLFramework* instance;			// singleton 인스턴스
	SDL_Window* window;						// Window 객체 포인터
	SDL_Renderer* renderer;					// Renderer   "
	vector<TTF_Font*> fonts;				// 미리 로딩해서 쓸 폰트 목록
	list<SDLGameObject*> gameObjects;		// 현재 돌아가고 있는 모든 GameObject

	bool haveToRemoveObject = false;

public:
	static SDLFramework* Instance()			// Framework 인스턴스 가져올 함수
	{
		if (instance == NULL)
		{
			instance = new SDLFramework();
		}
		return instance;
	}

	SDL_Window* GetWindow() { return window; }			// Window Getter
	SDL_Renderer* GetRenderer() { return renderer; }	// Renderer Getter
	TTF_Font* GetFont(unsigned int index) { return fonts[index]; }	// Font Getter;

	void AddGameObject(SDLGameObject* obj);				// 게임 오브젝트 등록
	void RemoveGameObject(SDLGameObject* obj);			// 게임 오브젝트 제거

	list<SDLGameObject*> GetObjectList() {
		return gameObjects;
	}

	//화면크기
	const int SCREEN_WIDTH = WINDOWS_WIDTH;				// 화면 해상도
	const int SCREEN_HEIGHT = WINDOWS_HEIGHT;			// 화면 해상도

	SDLFramework();										// Framework 생성자
	~SDLFramework();

	// Private 함수
private:
	//void CheckCollisionObjects();

	// Public 함수
public:
	void DelayDestroyObjects();

	bool Init();										// SDL 관련 초기화
	void HandleEvent(SDL_Event* e);						// Event를 Object의 각 Component에 전달할 함수
	void Update(float deltaTime);						// GameObjects Update

	void Render();										// GameObjects Render
	void Close();										// SDL 및 GameObjects 해제

	void RegisterFont(string filePath, int fontSize);	// 폰트 등록;

														// private static 함수들
private:
	//static bool CheckCollision(CircleCollider* circle, RectangleCollider* rect);
	//static bool CheckCollision(CircleCollider* circle, CircleCollider* other);
	//static bool CheckCollision(RectangleCollider* rect, RectangleCollider* other);

	// public static 함수들
public:
	static SDL_Texture* LoadTexture(string filePath, SDL_Color* keyColor = NULL);
	static SDL_Texture* LoadTextureFromFont(TTF_Font* font, string textureText, SDL_Color* textColor = NULL);

	//static bool IsCollision(Collider* collider, Collider* other);
	//static bool IsPointInCircle(int px, int py, int cx, int cy, int radius);
};

