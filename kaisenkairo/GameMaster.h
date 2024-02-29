#pragma once
#include "DxLib.h"
#include "Color.h"
#include "Scene.h"
#include "VirtualClass.h"

class CPlayer;
class CGameText;
class MapManager;
class View;
//ゲームのメインループを行うクラス
class GameMaster {
	CPlayer* player;
	MapManager* map;
	CGameText* progress_text;
	StartScene* start_scene;
	PlayScene* main_scene;
	ClearScene* clear_scene;
public:
	//コンストラクタ
	GameMaster();
	//デストラクタ
	~GameMaster();

	void EntryClasses();	//クラス宣言処理

	void Update();	//更新処理
	void Drawing();	//描画処理

	void Run();	//メインループ処理

	void SetStartScene();	//タイトルシーンループ
	void SetMainScene();	//メインシーンループ
	void SetClearScene();	//クリアシーンループ

	virtual void Move();//移動を一括処理
	virtual void Draw();//描画を一括処理

	bool pause = false;	//ポーズフラグ
};

extern GameMaster* GM;

/*　定数　*/
//Game設定関係
#define SCREEN_WIDTH 1920
#define SCREEN_HIGHT 1080
#define SCREEN_COLOR 32