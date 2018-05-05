#pragma once
#include <map>
#include "SDLGameObject.h"

class Scene
{
public:
	Scene();
	~Scene();

	map<string, SDLGameObject*>	contentObjects;
	map<string, SDL_Texture*>	textures;		// 미리 로딩해서 쓸 텍스쳐 목록, map으로 변경 할 예정

	bool RegisterGameObject(SDLGameObject* obj);
	SDLGameObject* GetObject(string name);
	void DestroyGameObject(string name);

	bool Register_SDLTexture(string name, SDL_Texture* texture);
	SDL_Texture* Get_SDLTexture(string name);
	void Destroy_SDLTexture(string name);

	void DestroyAll();
	void Close();
};