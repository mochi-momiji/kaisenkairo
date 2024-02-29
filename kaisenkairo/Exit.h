#pragma once
#include "DxLib.h"
#include "Methods.h"
#include "VirtualClass.h"
#include "Collider.h"
#include "DataBase.h"
#include "Color.h"
#include <vector>
#include <time.h>

#define NONE 0

//出入口
class Exit {
protected:
	LineCollider* collider = nullptr;		//あたり判定
	const char* next_stage_id = "";
	int progress = 0;			//進捗度
	std::vector<Ray2> lines;	//線分
	std::unordered_map<const char*, int> stage_colors;//ステージごとの色の連想配列
	VECTOR position;		//座標
	int thickness = 10;		//厚さ
	int width = 30;			//幅
	int color = COLOR.WHITE;//現在の色

public:
	//コンストラクタ
	Exit(const char* exitStageId) {
		next_stage_id = exitStageId;
		stage_colors["Stage01"] = COLOR.WHITE;
		stage_colors["Stage02"] = COLOR.YELLOW;
		stage_colors["Stage03"] = COLOR.LIGHT_BLUE;
		stage_colors["Stage04"] = COLOR.GREEN;
		stage_colors["Stage05"] = COLOR.PURPLE;
		stage_colors["Stage06"] = COLOR.RED;
		stage_colors["Stage07"] = COLOR.BLUE;

		color = stage_colors[exitStageId];
	}
	//ゲッター
	inline LineCollider& getCollider() { return *collider; }	//あたり判定情報を渡す
	inline std::vector<Ray2> getLines() { return lines; }		//線分配列を渡す
	inline VECTOR getPosition() { return position; }	//座標を渡す
	inline const char* getNextStage() { return next_stage_id; }
	//純粋仮想関数
	virtual void PushLine(VECTOR root) = 0;	//線分情報を算出・保存

	//プレイヤーが出入り口に接触した際の処理
	void Loop();
	void Draw();//描画処理
};

//上に向かう為の出入口
class UpExit :public Exit {
public:
	//コンストラクタ
	UpExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//オーバーライド関数
	virtual void PushLine(VECTOR root) override;//線分情報を算出・保存
};

//下に向かう為の出入口
class DownExit :public Exit {
public:
	//コンストラクタ
	DownExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//オーバーライド関数
	virtual void PushLine(VECTOR root) override;	//線分情報を算出・保存
};

//右に向かう為の出入口
class RightExit :public Exit {
public:
	//コンストラクタ
	RightExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//オーバーライド関数
	virtual void PushLine(VECTOR root) override;	//線分情報を算出・保存
};

//左に向かう為の出入口
class LeftExit :public Exit {
public:
	//コンストラクタ
	LeftExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//オーバーライド関数
	virtual void PushLine(VECTOR root) override;	//線分情報を算出・保存
};
