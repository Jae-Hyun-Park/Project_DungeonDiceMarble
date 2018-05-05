#pragma once
#include "Monster.h"
#include "Item.h"
#include "SDLFramework.h"

// Ÿ�Ͽ�����Ʈ Ÿ��
enum TileObjType {
	RoadT,
	StartT,
	MonsterT,
	ItemT,
	TrapT,
	endT
};

class Tile : public Component				
{   // �� Ÿ�� ������Ʈ�� �ڽ��� ��ǥ�� �ڽžȿ��ִ� ��ü ����(������, ����)�� �������ִ�.
private:
	// Ÿ�� ���� (������, ��ġ�� �� �ִ� �ּ� ��ǥ�� �ִ� ��ǥ)
	int FloorSide = 130;
	int PosMin = 25;
	int PosMax = 805;
	
public:
	// Ÿ�� ��ǥ(x, y)
	int x = 0;
	int y = 0;

	Texture *		tile;						// Ÿ�� �ؽ���
	Monster*		monster;					// ���� ��ü
	Item*			item;						// ������ ��ü
	TileObjType		type = RoadT;				// Ÿ�� Ÿ��

	SDLGameObject*	TrapObj = NULL;
	Texture*		TrapTex = NULL;

	string TileTexName[6] = {					// Ÿ�� �ؽ��� �̸�
		"map_Road.png",
		"map_StartRoad.png",
		"map_MonsterRoad.png",
		"map_ItemRoad.png",
		"map_TrapRoad.png",
		"map_EndRoad.png",
	};

	// ���� ��ü �����͸� �������� �Լ�
	void insertMType(TileObjType _type, Monster* _mon) { type = _type; monster = _mon; }	
	// ������ ��ü �����͸� �������� �Լ�
	void insertIType(TileObjType _type, Item* _item) { type = _type; item = _item; }		
	int getFloorSide() { return FloorSide; }							// �ڽ��� ����� ��ȯ�ϴ� �Լ�
	int getPosMin() { return PosMin; }									// �ڽ��� ��ġ�� �ּ���ǥ�� ��ȯ�ϴ� �Լ�
	int getPosMax() { return PosMax; }									// �ڽ��� ��ġ�� �ִ���ǥ�� ��ȯ�ϴ� �Լ�

	void init(SDLGameObject* obj);

	Tile();
	~Tile();
};

