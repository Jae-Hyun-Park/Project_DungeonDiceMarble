#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
class SCButton :
	public Component
{
public:
	bool ButtonRunState = false;					// ĳ���Ͱ� �����̴� ����
	bool GameStartState = false;					// ���� ���� ����

	// ��ư ũ�� �� ��ġ
	int x;											
	int y;											
	int w;
	int h;

	Texture* ButtonTex = NULL;						// ��ư �ؽ���

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

