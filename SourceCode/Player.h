#pragma once
#include "Tile.h"
#include "Text.h"
class Player :
	public Character
{
private:

	float				elapsedTime;
	float				MoveFrameRate;					// 이동 모션 프레임
	int					y;								// 데미지 폰트 Y좌표
	int					TSCount;						// 맵완주 카운트
public:

	bool				MoveState;						// 이동 상태
	int					walkPace;						// 플레이어가 이동할 거리
	int					StayLoc;						// 플레이어가 있었던 위치
	int					Lev;							// 플레이어 레벨
	bool				battlestate;					// 배틀 상태

	bool				PlayerStatusState;				// 플레이어 스테이터스 상태

	Item*				equipedItem[2] = { NULL, };		// 아이템 슬롯
	Tile*				map[24] = { NULL, };			// 맵 정보를 받아올 타일포인터 배열

	SDLGameObject*		HPFObj = NULL;					// 데미지 폰트 오브젝트
	Text*				HPF = NULL;						// 데미지 폰트
	SDL_Color*			keyColor = NULL;

	Player();
	~Player();
	// 맵정보를 받아오는 함수
	void SetMap(Tile* tile[]) { for (int i = 0; i < 24; ++i)map[i] = tile[i]; }
	// 플레이어 정보를 받아오는 함수
	void SetStatus(const char* _name, int _hp, int _atk, int _def);

	void Move() override;									// 플레이어 이동함수
	void MapCheck();										// 플레이어가 이동한 후 맵 체크함수
	void ItemEquip(EquipSlot slot, Item* item) override;	// 아이템 장착 함수
	

	virtual void Init();
	void HandleEvent(SDL_Event* e);
	virtual void Update(float deltaTime);
};

