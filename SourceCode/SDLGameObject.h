#pragma once
#include <string>
#include <list>
#include "include\SDL_image.h"
using namespace std;

class Component;
class Transform;
// class Collider;

class SDLGameObject
{
private:
	list<Component*> components;

public:
	string name;
	Transform* transform = NULL;

	bool willBeDestroy = false;
	bool active = true;

	SDLGameObject(string _name);
	~SDLGameObject();

	template<class T>
	T* AddComponent()
	{
		T* pT = GetComponent<T>();

		// 해당 컴포넌트 타입이 존재하지 않는 경우에만 새로 추가 가능
		if (pT == NULL)
		{
			pT = new T();
			components.push_back(pT);
			components.back()->gameObject = this;
			components.back()->Init();
		}

		return pT;
	}

	template<typename T>
	T* GetComponent()
	{
		T* pT = NULL;
		for (auto component : components)
		{
			pT = dynamic_cast<T*>(component);
			if (pT == NULL)
				continue;
			else
				break;
		}

		return pT;
	}


	// EventHandle
	void HandleEvent(SDL_Event* e);

	// Update
	void Update(float deltaTime);

	// Render
	void Render();

	//void OnCollisionEnter(Collider* other);
	//void OnCollisionStay(Collider* other);
	//void OnCollisionExit(Collider* other);
};

