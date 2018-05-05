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
	// ��� ������Ʈ �ı�
	for (auto component : components)
	{
		if (component != NULL)
			delete component;
	}
	transform = NULL;
}

void SDLGameObject::Update(float deltaTime)
{
	// ��� ������Ʈ Update
	for (auto component : components)
	{
		component->Update(deltaTime);
	}
}

void SDLGameObject::Render()
{
	// Component�� Texture component�� Render�� ȣ�� �ϵ��� �Ѵ�.
	Texture* texture = GetComponent<Texture>();

	// Texture ������Ʈ Ÿ�Ը� ����
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
		// �� Component Ÿ�Կ� �����ǵ� HandleEvent�� ȣ��ȴ�.
		component->HandleEvent(e);
	}
}
