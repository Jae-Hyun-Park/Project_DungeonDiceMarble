#pragma once
#include <map>
#include <vector>

#include "Transform.h"
#include "DiceButton.h"
#include "StatusView.h"
#include "BattleView.h"
#include "SCButton.h"

// 씬이름
enum SceneName {
	StartScene,
	Game,
	GameOver,
};

// 폰트 등록 열거형 키
enum RegisteredFont
{
	BMYEONSUNG,
};

// 오브젝트 데이터 관리 구조체
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

	int Loc;										//  오브젝트 생성시 맵 배열을 가르키는 변수
	int MapCount;									//  맵 배열을 카르키는 변수
	int mapLineCount;								//  맵 배열을 라인별로 이동시키는 변수2
	int MonDCount = 0;								//  몬스터 죽음카운트
	int count = 0;
	int SVCount = 0;
	bool GameWinState;						//  게임 승리상태

	SCButton*			scb = NULL;					//  스타트버튼

	FILE*				fp = NULL;					//  캐릭터 스텟을 가져올 파일포인터
	vector<Stat*> SV;							//  오브젝트 데이터 관리 벡터
	SceneName			currentSceneName;			//  씬네임 변수
	BattleView*			BTView = NULL;				//  배틀 뷰

	SDLGameObject*		Floor[24] = { NULL, };		//	맵타일 오브젝트
	Tile*				mapTile[24] = { NULL, };	//  타일

	SDLGameObject*		bgObj = NULL;				//  배경화면 오브젝트	
	Texture*			bgTexture = NULL;			//	배경화면 텍스쳐

	SDLGameObject*		DiceButtonObj = NULL;		//  주사위버튼 오브젝트
	DiceButton*			dicebutton = NULL;			//  주사위버튼

	SDLGameObject*		PlayerObj = NULL;			//  플레이어 오브젝트
	Player*				player = NULL;				//  플레이어 캐릭터

	SDLGameObject*		ItemObj[4] = { NULL, };		//  아이템 오브젝트

	SDLGameObject*		MonsterObj[4] = { NULL, };	//  몬스터 오브젝트
	Monster*			mon[4] = { NULL, };			//  몬스터 배열

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

	bool gameState;									//  게임 상태 변수
	int Stage;

	Scene*				scene = NULL;				//  씬
	StatusView*			STView = NULL;				//	스테이터스 뷰
	Item*				item[4] = { NULL, };		//  아이템 배열

	string ObjName;
	string nameNumber;

	GameManager();
	~GameManager();

	void Drawing();							//  게임에대한 모든것을 그릴 함수
	void DrawingMap();						//  맵을 그리는 함수
	void MapSetting();						//  맵 셋팅
	void ItemSetting();						//  아이템 생성 및 셋팅
	void MonsterSetting();					//  몬스터 생성 및 셋팅
	void ButtonSetting();					//  버튼 생성 및 셋팅
	void TrapSetting();						//  트랩 셋팅
	void createPlayer();					//  플레이어 생성
	void DrawingMonster();					//  몬스터 그리기
	void DrawingItem();						//  아이템 그리기
	void DrawingPlayer();					//  플레이어 그리기
	void Init();
	void Update(float deltaTime);

	// 게임 종료시 해제 할 것들을 해제
	void Release();

	void ChangeScene(SceneName sceneName);								// 씬변경
	SceneName GetCurrentSceneName() { return currentSceneName; }		

private:
	void SetStartScene();
	void SetGameScene();
	void SetGameOverScene();
};

