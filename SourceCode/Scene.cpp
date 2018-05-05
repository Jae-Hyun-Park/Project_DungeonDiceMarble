#include <iostream>
#include "SDLFramework.h"
#include "Scene.h"

using namespace std;

Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::RegisterGameObject(SDLGameObject* obj)  // ������Ʈ ���
{
	if (contentObjects.find(obj->name) != contentObjects.end())
	{
		cout << obj->name << " : �̹� ��ϵ� Ű�� �ֽ��ϴ�. Object ��Ͽ� ���� �Ͽ����ϴ�."
			<< endl;

		return false;
	}

	contentObjects.insert(pair<string, SDLGameObject*>(obj->name, obj));
	SDLFramework::Instance()->AddGameObject(obj);

	return true;
}

SDLGameObject * Scene::GetObject(string name) // ������Ʈ�� ������
{
	map<string, SDLGameObject*>::iterator iter = contentObjects.find(name);
	if (iter != contentObjects.end())
	{
		return iter->second;
	}

	return NULL;
}

void Scene::DestroyGameObject(string name)			// ������Ʈ ����
{
	map<string, SDLGameObject*>::iterator iter = contentObjects.find(name);
	if (iter != contentObjects.end())
	{
		if (iter->second != NULL)
		{
			SDLFramework::Instance()->RemoveGameObject(iter->second);
		}

		contentObjects.erase(iter);
	}
}

bool Scene::Register_SDLTexture(string name, SDL_Texture * texture)  // SDL_Texture ���(���ҽ�)
{
	if (textures.find(name) != textures.end())
	{
		cout << name << " : �̹� ��ϵ� Ű�� �ֽ��ϴ�. SDL_Texture ��Ͽ� ���� �Ͽ����ϴ�."
			<< endl;

		return false;
	}
	textures.insert(pair<string, SDL_Texture*>(name, texture));
	return true;
}

SDL_Texture * Scene::Get_SDLTexture(string name)						// SDL_Texture ��������(���ҽ�)
{
	map<string, SDL_Texture*>::iterator iter = textures.find(name);
	if (textures.find(name) != textures.end())
	{
		return iter->second;
	}

	return NULL;
}

void Scene::Destroy_SDLTexture(string name)								// SDL_Texture ����(���ҽ�)
{
	map<string, SDL_Texture*>::iterator iter = textures.find(name);
	if (textures.find(name) != textures.end())
	{
		if (iter->second != NULL)
		{
			SDL_DestroyTexture(iter->second);
		}

		textures.erase(iter);
	}
}

void Scene::DestroyAll()												// ��� ������Ʈ ����
{
	for (auto object : contentObjects)
	{
		if (object.second != NULL)
		{
			SDLFramework::Instance()->RemoveGameObject(object.second);
		}
	}
	contentObjects.clear();

	for (auto object : textures)
	{
		if (object.second != NULL)
			SDL_DestroyTexture(object.second);
	}
	textures.clear();
}

void Scene::Close() {
	for (auto object : contentObjects)
	{
		if (object.second != NULL)
		{
			SDLFramework::Instance()->RemoveGameObject(object.second);
		}
	}	
	contentObjects.clear();

	for (auto object : textures)
	{
		if (object.second != NULL)
			SDL_DestroyTexture(object.second);
	}
	textures.clear();

	SDLFramework::Instance()->DelayDestroyObjects();
}