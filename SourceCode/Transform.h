#pragma once
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "Component.h"

class Texture;

class Transform :
	public Component
{
public:
	// Transform Component
	SDL_Rect			clipRect;		// Render�ÿ� Texture�� ���� Ŭ���� �� ����
	SDL_Rect			projRect;		// ���� ��ġ�� ũ�⸦ ��Ÿ���� ����
	double				angle;			// �ð���������� ȸ�� ����
	SDL_Point			centerPoint;	// ȸ�� ��ų ���� ��ġ
	SDL_RendererFlip	flipMode;		// flip ��ų ���

public:
	Transform();
	~Transform();

	void Init();
	void Update(float deltaTime);

	// member Functions
	void SetPosition(int x, int y);
	void SetClipRect(int x, int y, int width, int height);
	int getClipRectX() { return clipRect.x; }
	int getClipRectY() { return clipRect.y; }
	void SetWidth(int width);
	void SetHeight(int height);
	void SetRotate(double _angle);
	void SetFlipMode(SDL_RendererFlip flip);
	void SetCenterPoint(int x, int y);

	void Move(int x, int y);
};

