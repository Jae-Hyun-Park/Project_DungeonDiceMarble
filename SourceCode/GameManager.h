#pragma once
#include <map>
#include <vector>

#include "Transform.h"
#include "DiceButton.h"
#include "StatusView.h"
#include "BattleView.h"
#include "SCButton.h"

// ���̸�
enum SceneName {
	StartScene,
	Game,
	GameOver,
};

// ��Ʈ ��� ������ Ű
enum RegisteredFont
{
	BMYEONSUNG,
};

// ������Ʈ ������ ���� ����ü
struct Stat {
	char*				Name;
	MonsterType			monType;
	ItemType			itemType;
	int					Hp;
	int					Atk;
	int					Def;
	int					Exp;
	~Stat() {
		if (Name != NULL) {
			delete[] Name;
			Name = NULL;
		}
	}
};

class GameManager
{
private:
	static GameManager* instance;

	int Loc;										//  ������Ʈ ������ �� �迭�� ����Ű�� ����
	int MapCount;									//  �� �迭�� ī��Ű�� ����
	int mapLineCount;								//  �� �迭�� ���κ��� �̵���Ű�� ����2
	int MonDCount = 0;								//  ���� ����ī��Ʈ
	int count = 0;
	int SVCount = 0;
	bool GameWinState;						//  ���� �¸�����

	SCButton*			scb = NULL;					//  ��ŸƮ��ư

	FILE*				fp = NULL;					//  ĳ���� ������ ������ ����������
	vector<Stat*> SV;							//  ������Ʈ ������ ���� ����
	SceneName			currentSceneName;			//  ������ ����
	BattleView*			BTView = NULL;				//  ��Ʋ ��

	SDLGameObject*		Floor[24] = { NULL, };		//	��Ÿ�� ������Ʈ
	Tile*				mapTile[24] = { NULL, };	//  Ÿ��

	SDLGameObject*		bgObj = NULL;				//  ���ȭ�� ������Ʈ	
	Texture*			bgTexture = NULL;			//	���ȭ�� �ؽ���

	SDLGameObject*		DiceButtonObj = NULL;		//  �ֻ�����ư ������Ʈ
	DiceButton*			dicebutton = NULL;			//  �ֻ�����ư

	SDLGameObject*		PlayerObj = NULL;			//  �÷��̾� ������Ʈ
	Player*				player = NULL;				//  �÷��̾� ĳ����

	SDLGameObject*		ItemObj[4] = { NULL, };		//  ������ ������Ʈ

	SDLGameObject*		MonsterObj[4] = { NULL, };	//  ���� ������Ʈ
	Monster*			mon[4] = { NULL, };			//  ���� �迭

	string BGName[5] = {
		"BackGround_Image.png",
		"BackGround_Image1.png",
		"BackGround_Image2.png",
		"BackGround_Image3.png",
		"BackGround_Image4.png",
	};
public:
	static GameManager* Instance()
	{
		if (instance == NULL)
			instance = new GameManager();
		return instance;
	}

	bool gameState;									//  ���� ���� ����
	int Stage;

	Scene*				scene = NULL;				//  ��
	StatusView*			STView = NULL;				//	�������ͽ� ��
	Item*				item[4] = { NULL, };		//  ������ �迭

	string ObjName;
	string nameNumber;

	GameManager();
	~GameManager();

	void Drawing();							//  ���ӿ����� ������ �׸� �Լ�
	void DrawingMap();						//  ���� �׸��� �Լ�
	void MapSetting();						//  �� ����
	void ItemSetting();						//  ������ ���� �� ����
	void MonsterSetting();					//  ���� ���� �� ����
	void ButtonSetting();					//  ��ư ���� �� ����
	void TrapSetting();						//  Ʈ�� ����
	void createPlayer();					//  �÷��̾� ����
	void DrawingMonster();					//  ���� �׸���
	void DrawingItem();						//  ������ �׸���
	void DrawingPlayer();					//  �÷��̾� �׸���
	void Init();
	void Update(float deltaTime);

	// ���� ����� ���� �� �͵��� ����
	void Release();

	void ChangeScene(SceneName sceneName);								// ������
	SceneName GetCurrentSceneName() { return currentSceneName; }		

private:
	void SetStartScene();
	void SetGameScene();
	void SetGameOverScene();
};

