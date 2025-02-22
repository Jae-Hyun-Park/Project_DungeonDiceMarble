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
	SDL_Rect			clipRect;		// Render시에 Texture를 실제 클리핑 할 영역
	SDL_Rect			projRect;		// 실제 위치와 크기를 나타내는 영역
	double				angle;			// 시계방향으로의 회전 각도
	SDL_Point			centerPoint;	// 회전 시킬 기준 위치
	SDL_RendererFlip	flipMode;		// flip 시킬 모드

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

