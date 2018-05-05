#pragma once
#include "Monster.h"
#include "Item.h"
#include "SDLFramework.h"

// 타일오브젝트 타입
enum TileObjType {
	RoadT,
	StartT,
	MonsterT,
	ItemT,
	TrapT,
	endT
};

class Tile : public Component				
{   // 각 타일 오브젝트는 자신의 좌표와 자신안에있는 객체 정보(아이템, 몬스터)를 가지고있다.
private:
	// 타일 정보 (사이즈, 배치될 수 있는 최소 좌표와 최대 좌표)
	int FloorSide = 130;
	int PosMin = 25;
	int PosMax = 805;
	
public:
	// 타일 좌표(x, y)
	int x = 0;
	int y = 0;

	Texture *		tile;						// 타일 텍스쳐
	Monster*		monster;					// 몬스터 객체
	Item*			item;						// 아이템 객체
	TileObjType		type = RoadT;				// 타일 타입

	SDLGameObject*	TrapObj = NULL;
	Texture*		TrapTex = NULL;

	string TileTexName[6] = {					// 타일 텍스쳐 이름
		"map_Road.png",
		"map_StartRoad.png",
		"map_MonsterRoad.png",
		"map_ItemRoad.png",
		"map_TrapRoad.png",
		"map_EndRoad.png",
	};

	// 몬스터 객체 포인터를 가져오는 함수
	void insertMType(TileObjType _type, Monster* _mon) { type = _type; monster = _mon; }	
	// 아이템 객체 포인터를 가져오는 함수
	void insertIType(TileObjType _type, Item* _item) { type = _type; item = _item; }		
	int getFloorSide() { return FloorSide; }							// 자신의 사이즈를 반환하는 함수
	int getPosMin() { return PosMin; }									// 자신이 배치될 최소좌표를 반환하는 함수
	int getPosMax() { return PosMax; }									// 자신이 배치될 최대좌표를 반환하는 함수

	void init(SDLGameObject* obj);

	Tile();
	~Tile();
};

