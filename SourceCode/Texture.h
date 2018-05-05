#pragma once
#include "Component.h"
class Texture :
	public Component
{
protected:
	// Texture Component
	SDL_Texture*		texture;
	int		textureWidth;
	int		textureHeight;

	unsigned int		horizonCount = 1;
	unsigned int		verticalCount = 1;
	float				frameRate;
	float				elapsedTime;
	unsigned int		frameCount;
	bool				isActiveAnimation = false;
public:

	Texture();
	~Texture();

	void Update(float deltaTime);

	//// Texture Component
	void SetTexutre(SDL_Texture* _tex);
	SDL_Texture* GetTexture() {
		return texture;
	}
	void SetBlendMode(SDL_BlendMode blendMode);
	void SetAlpha(Uint8 alpha);

	// Animation
	void SetFrameRate(float _frameRate) { frameRate = _frameRate; }
	void SetHorizonCount(unsigned int hCount) { horizonCount = hCount; }
	void SetVerticalCount(unsigned int vCount) { verticalCount = vCount; }
	void SetAnimationActive(bool activate) { isActiveAnimation = activate; }
	unsigned int GetHorizonCount() { return horizonCount; }
	unsigned int GetVerticalCount() { return verticalCount; }
	int GetTextureWidth() { return textureWidth; }
	int GettextureHeight() { return textureHeight; }
	void SetFrameCount(unsigned int a) { frameCount = a; }
	void Render();
};

