#pragma once
#include "Tile.h"
#include "Text.h"
class Player :
	public Character
{
private:

	float				elapsedTime;
	float				MoveFrameRate;					// �̵� ��� ������
	int					y;								// ������ ��Ʈ Y��ǥ
	int					TSCount;						// �ʿ��� ī��Ʈ
public:

	bool				MoveState;						// �̵� ����
	int					walkPace;						// �÷��̾ �̵��� �Ÿ�
	int					StayLoc;						// �÷��̾ �־��� ��ġ
	int					Lev;							// �÷��̾� ����
	bool				battlestate;					// ��Ʋ ����

	bool				PlayerStatusState;				// �÷��̾� �������ͽ� ����

	Item*				equipedItem[2] = { NULL, };		// ������ ����
	Tile*				map[24] = { NULL, };			// �� ������ �޾ƿ� Ÿ�������� �迭

	SDLGameObject*		HPFObj = NULL;					// ������ ��Ʈ ������Ʈ
	Text*				HPF = NULL;						// ������ ��Ʈ
	SDL_Color*			keyColor = NULL;

	Player();
	~Player();
	// �������� �޾ƿ��� �Լ�
	void SetMap(Tile* tile[]) { for (int i = 0; i < 24; ++i)map[i] = tile[i]; }
	// �÷��̾� ������ �޾ƿ��� �Լ�
	void SetStatus(const char* _name, int _hp, int _atk, int _def);

	void Move() override;									// �÷��̾� �̵��Լ�
	void MapCheck();										// �÷��̾ �̵��� �� �� üũ�Լ�
	void ItemEquip(EquipSlot slot, Item* item) override;	// ������ ���� �Լ�
	

	virtual void Init();
	void HandleEvent(SDL_Event* e);
	virtual void Update(float deltaTime);
};

