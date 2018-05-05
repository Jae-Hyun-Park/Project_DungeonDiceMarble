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
	static SDLFramework* instance;			// singleton �ν��Ͻ�
	SDL_Window* window;						// Window ��ü ������
	SDL_Renderer* renderer;					// Renderer   "
	vector<TTF_Font*> fonts;				// �̸� �ε��ؼ� �� ��Ʈ ���
	list<SDLGameObject*> gameObjects;		// ���� ���ư��� �ִ� ��� GameObject

	bool haveToRemoveObject = false;

public:
	static SDLFramework* Instance()			// Framework �ν��Ͻ� ������ �Լ�
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

	void AddGameObject(SDLGameObject* obj);				// ���� ������Ʈ ���
	void RemoveGameObject(SDLGameObject* obj);			// ���� ������Ʈ ����

	list<SDLGameObject*> GetObjectList() {
		return gameObjects;
	}

	//ȭ��ũ��
	const int SCREEN_WIDTH = WINDOWS_WIDTH;				// ȭ�� �ػ�
	const int SCREEN_HEIGHT = WINDOWS_HEIGHT;			// ȭ�� �ػ�

	SDLFramework();										// Framework ������
	~SDLFramework();

	// Private �Լ�
private:
	//void CheckCollisionObjects();

	// Public �Լ�
public:
	void DelayDestroyObjects();

	bool Init();										// SDL ���� �ʱ�ȭ
	void HandleEvent(SDL_Event* e);						// Event�� Object�� �� Component�� ������ �Լ�
	void Update(float deltaTime);						// GameObjects Update

	void Render();										// GameObjects Render
	void Close();										// SDL �� GameObjects ����

	void RegisterFont(string filePath, int fontSize);	// ��Ʈ ���;

														// private static �Լ���
private:
	//static bool CheckCollision(CircleCollider* circle, RectangleCollider* rect);
	//static bool CheckCollision(CircleCollider* circle, CircleCollider* other);
	//static bool CheckCollision(RectangleCollider* rect, RectangleCollider* other);

	// public static �Լ���
public:
	static SDL_Texture* LoadTexture(string filePath, SDL_Color* keyColor = NULL);
	static SDL_Texture* LoadTextureFromFont(TTF_Font* font, string textureText, SDL_Color* textColor = NULL);

	//static bool IsCollision(Collider* collider, Collider* other);
	//static bool IsPointInCircle(int px, int py, int cx, int cy, int radius);
};

