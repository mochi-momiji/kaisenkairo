#pragma once
#include "DxLib.h"
#include "Methods.h"
#include "Collider.h"
#include "Color.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
//他クラス間で参照するデータを管理するクラス
class DataBase {
private:
	VECTOR player_pos = VGet(0, 0, 0);	//プレイヤーの座標
	double player_angle = 0;			//プレイヤーの向いている角度
	int slid_pos = 0;					//ミニマップの開閉移動量
	const char* stage_id = "Stage01";	//現在のステージの描画時の色
	std::vector<Ray2> map_line;			//マップの線分情報
	std::map<int, VECTOR> enemy_pos;	//エネミーの座標の連想配列(ステージ番号,座標)
	int move_length = 0;
	int stage_color = COLOR.WHITE;
	VECTOR delta_vec = VGet(0, 0, 0);
	VECTOR enter_exit_pos = VGet(0, 0, 0);

public:
	//コンストラクタ
	DataBase() {}

	//更新処理
	void UpdateMapData(const std::vector<Ray2>& newLine) { map_line = newLine; }//マップデータの更新処理
	void UpdateExit(const std::vector<Ray2>& newLine) {
		map_line.insert(map_line.end(), newLine.begin(), newLine.end());
	}
	void UpdateSlid(const int& new_pos) { slid_pos = new_pos; }					//ミニマップ開閉の移動量更新
	void UpdatePlayerPosition(const VECTOR& newPos) { player_pos = newPos; }	//プレイヤーの座標情報更新処理
	void UpdateStageId(const char* stageId) { stage_id = stageId; }				//ステージの描画色の更新処理
	void UpdateMoveLength(const int& newLenght) { move_length = newLenght; }
	void UpdateStageColor(const int& setColor) { stage_color = setColor; }
	void UpdateDelta(VECTOR setVec) { delta_vec = setVec; }
	void UpdateExitPosition(VECTOR setPos) { enter_exit_pos = setPos; }

	//ゲッター
	inline std::vector<Ray2> getMapLine() { return map_line; }//Mapの線分情報のゲッター
	inline int getSlidPosition() { return slid_pos; }		//開閉時の移動量のゲッター
	inline VECTOR getPlayerPosition() { return player_pos; }//Playerの座標のゲッター
	inline double getPlayerAngle() { return player_angle; }//Playerの角度のゲッター
	inline const char* getStageId() { return stage_id; }	//ステージ名(const char*型)のゲッター
	inline int getMoveLength() { return move_length; }
	inline int getStageColor() { return stage_color; }
	inline VECTOR getDelta() { return delta_vec; }
	inline VECTOR getExitPosition() { return enter_exit_pos; }
};

extern DataBase DB;