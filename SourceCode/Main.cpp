//SDL�� ǥ������� ����
#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"

#include "GameManager.h"


using namespace std;

SDLFramework* SDLFramework::instance = NULL;
GameManager* GameManager::instance = NULL;

int main(int argc, char* args[])
{
#if defined(DEBUG) | defined (_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//_CrtSetBreakAlloc(236);
	int now, last = 0;			// now : ���� �����ӿ����� �ð��� ����� ����
								// last : ���� �����ӿ����� �ð��� ����� ����
	int deltaTime = 0;		// ���� �����ӿ��� ���� ���� �����ӱ��� �ɸ� �ð�

	if (!SDLFramework::Instance()->Init())				// SDL �����ӿ�ũ �ʱ�ȭ
	{
		cout << "Failed to initialized!!" << endl;
		return 0;
	}

	GameManager::Instance()->Init();					// ���� ������ ������ �ʱ�ȭ

	bool quit = false;						// ���α׷� ������°� �Ǹ� true�� �ٲ� ����

	float elapsedTime = 0.0f;
	const float Frame = 60.0f;

	// ���� �������� ó���� Event 
	SDL_Event e;

	while (!quit)
	{
		// Tick�� Time ���
		now = SDL_GetTicks();
		if (now > last)
		{
			deltaTime = now - last;
			elapsedTime += deltaTime;
			last = now;
		}

		SDLFramework::Instance()->DelayDestroyObjects();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// Event �ڵ鷯

			SDLFramework::Instance()->HandleEvent(&e);
		}

		if (elapsedTime > ((1.0f / Frame) * 1000.0f))
		{
			// ������Ʈ
			GameManager::Instance()->Update(elapsedTime);
			SDLFramework::Instance()->Update(elapsedTime);
			// ����
			SDLFramework::Instance()->Render();
			elapsedTime = 0.0f;
			deltaTime = 0;
		}
	}

	GameManager::Instance()->Release();

	// ����
	SDLFramework::Instance()->Close();
	if (SDLFramework::Instance() != NULL) {
		delete SDLFramework::Instance();
	}
	return 0;
}