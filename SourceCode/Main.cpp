//SDL과 표준입출력 포함
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
	int now, last = 0;			// now : 현재 프레임에서의 시각을 기록할 변수
								// last : 이전 프레임에서의 시각을 기록한 변수
	int deltaTime = 0;		// 이전 프레임에서 부터 현재 프레임까지 걸린 시간

	if (!SDLFramework::Instance()->Init())				// SDL 프레임워크 초기화
	{
		cout << "Failed to initialized!!" << endl;
		return 0;
	}

	GameManager::Instance()->Init();					// 게임 컨텐츠 관리자 초기화

	bool quit = false;						// 프로그램 종료상태가 되면 true로 바뀔 변수

	float elapsedTime = 0.0f;
	const float Frame = 60.0f;

	// 메인 루프에서 처리할 Event 
	SDL_Event e;

	while (!quit)
	{
		// Tick당 Time 계산
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

			// Event 핸들러

			SDLFramework::Instance()->HandleEvent(&e);
		}

		if (elapsedTime > ((1.0f / Frame) * 1000.0f))
		{
			// 업데이트
			GameManager::Instance()->Update(elapsedTime);
			SDLFramework::Instance()->Update(elapsedTime);
			// 렌더
			SDLFramework::Instance()->Render();
			elapsedTime = 0.0f;
			deltaTime = 0;
		}
	}

	GameManager::Instance()->Release();

	// 해제
	SDLFramework::Instance()->Close();
	if (SDLFramework::Instance() != NULL) {
		delete SDLFramework::Instance();
	}
	return 0;
}