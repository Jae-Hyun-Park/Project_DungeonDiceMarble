#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
class SCButton :
	public Component
{
public:
	bool ButtonRunState = false;					// 캐릭터가 움직이는 상태
	bool GameStartState = false;					// 게임 시작 상태

	// 버튼 크기 및 위치
	int x;											
	int y;											
	int w;
	int h;

	Texture* ButtonTex = NULL;						// 버튼 텍스쳐

	SCButton();
	~SCButton();

	void Init();
	void HandleEvent(SDL_Event* e);
	void Update(float deltaTime);
	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; }
	void SetW(int _w) { w = _w; }
	void SetH(int _h) { h = _h; }
};

