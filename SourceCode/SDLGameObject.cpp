#include "SDLGameObject.h"

#include "Transform.h"
#include "Texture.h"
#include "Component.h"

SDLGameObject::SDLGameObject(string _name)
{
	transform = AddComponent<Transform>();
	name = _name;
}

SDLGameObject::~SDLGameObject()
{
	// 모든 컴포넌트 파기
	for (auto component : components)
	{
		if (component != NULL)
			delete component;
	}
	transform = NULL;
}

void SDLGameObject::Update(float deltaTime)
{
	// 모든 컴포넌트 Update
	for (auto component : components)
	{
		component->Update(deltaTime);
	}
}

void SDLGameObject::Render()
{
	// Component중 Texture component의 Render를 호출 하도록 한다.
	Texture* texture = GetComponent<Texture>();

	// Texture 컴포넌트 타입만 렌더
	if(texture != NULL) 
		texture->Render();
}

//void SDLGameObject::OnCollisionEnter(Collider * other)
//{
//	for (auto component : components)
//	{
//		component->OnCollisionEnter(other);
//	}
//}

//void SDLGameObject::OnCollisionStay(Collider * other)
//{
//	for (auto component : components)
//	{
//		component->OnCollisionStay(other);
//	}
//}

//void SDLGameObject::OnCollisionExit(Collider * other)
//{
//	for (auto component : components)
//	{
//		component->OnCollisionExit(other);
//	}
//}

void SDLGameObject::HandleEvent(SDL_Event * e)
{
	for (auto component : components)
	{
		// 각 Component 타입에 재정의된 HandleEvent가 호출된다.
		component->HandleEvent(e);
	}
}
