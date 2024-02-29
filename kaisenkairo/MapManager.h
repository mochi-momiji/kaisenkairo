#pragma once
#include "DxLib.h"
#include "Map.h"
#include"Color.h"
#include <unordered_map>

class MapManager {

	//マップチップ①
	int field_01[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0,11, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 5, 2, 2, 2, 2, 2,},
	{0, 9, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 9, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{14,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0,10, 0, 0,10, 0, 0, 0, 0, 0, 0, 0,10, 0, 0,10, 0,},
	{2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0,12, 0, 0, 1, 0, 0, 0, 0, 0,},
	};
	//マップチップ②
	int field_02[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	};
	std::vector<const char*> stage_id = { "Stage01", "Stage02", "Stage03", "Stage04", "Stage05", "Stage06", "Stage07" };
	std::unordered_map<const char*, CMap*> maps;
	std::unordered_map<const char*, int> stage_color;

	std::unordered_map<const char*, UpExit*> up_exits;
	std::unordered_map<const char*, DownExit*> down_exits;
	std::unordered_map<const char*, RightExit*> right_exits;
	std::unordered_map<const char*, LeftExit*> left_exits;

	CMap* current_stage = nullptr;

	int slid = SLIDE_LIMIT;	//ミニマップ開閉時の移動量
	bool is_close = true;	//ミニマップか閉じてあるかのフラグ
	bool is_sliding = false;//ミニマップが開閉中であるかのフラグ
	const char* current_stage_id = "Stage01";
	
//メンバ変数を書き換える関数の為、private関数とする

	//MapChipを線分クラスの配列に変換する関数
	std::vector<Ray2> LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH],const char* string, int stageNum);

	//マップチップを読み込むための関数--------------------------------------------------------------
	Ray2 GetStraightLine(int x, int y, int length, int lineColor, bool is_horizontal);//縦線・横線を作成
	void GetCornerLine(std::vector<Ray2>& lines, int x, int y,
		int length, int lineColor, bool is_up, bool is_right);					//角を作成
	void CreateMap(std::vector<Ray2>& lines, Chip_Kind kind,
				int pos_x, int pos_y, const char* stageId, int& stageNum);//マップチップごとの生成関数呼び出し

public:
	MapManager() {
		stage_color["Stage01"] = COLOR.WHITE;
		stage_color["Stage02"] = COLOR.YELLOW;
		stage_color["Stage03"] = COLOR.LIGHT_BLUE;
		stage_color["Stage04"] = COLOR.GREEN;
		stage_color["Stage05"] = COLOR.PURPLE;
		stage_color["Stage06"] = COLOR.RED;
		stage_color["Stage07"] = COLOR.BLUE;

		SetUpMap();
	}

	void SetUpMap();

	void Update();
	void ChangeMap();
	void UpdateLines();
	void UpdateCollider();
	bool IsExit();
	void SlidMap();
};