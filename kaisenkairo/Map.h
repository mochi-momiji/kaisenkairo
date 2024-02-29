#pragma once
#include "DxLib.h"
#include "DataBase.h"
#include "Color.h"
#include "Methods.h"
#include "VirtualClass.h"
#include "Exit.h"
#include "Collider.h"
#include <vector>

#define MAP_ROOT VGet(1400, 30, 0)
#define WALL_INDEX 4
#define FIELD_WIDTH 17
#define FIELD_HIGHT 25
#define UP_LIMIT 30
#define DOWN_LIMIT 780
#define RIGHT_LIMIT 1910
#define LEFT_LIMIT 1400
#define GRID_LENGTH 30
#define LENGTH 90
#define OBJECT_VALUE 15
#define SLIDE_LIMIT 540
#define NONE 0

//Playerの情報を保存するクラス
class CPlayer;
//class Collision;

enum Chip_Kind {
	NONE_LINE,			//マップチップ無し
	VARTICAL,			//縦線
	HORIZONTAL,			//横線
	LEFT_UP_CORNER,		//左上の角
	RIGHT_UP_CORNER,	//右上の角
	LEFT_DOWN_CORNER,	//左下の角
	RIGHT_DOWN_CORNER,	//右下の角
	UP_EXIT,			//出口(上の壁)
	DOWN_EXIT,			//出口(下の壁)
	RIGHT_EXIT,			//出口(右の壁)
	LEFT_EXIT,			//出口(左の壁)
};

class CMap : public CObject {
	//friend Collision;
	friend CPlayer;
	
	LineCollider collider;	//壁の当たり判定

	//mapの線分情報の配列
	std::vector<Ray2> lines;

	bool is_search = false;//サーチ機能を使用しているかのフラグ
	int timer = 0;			//サーチ中の経過時間を計測
	int radius = 0;			//サーチ範囲の半径

public:
	//コンストラクタ
	CMap(std::vector<Ray2> setLines, int setColor, VECTOR setPos = MAP_ROOT)
		:CObject(setPos), collider(setLines, ObjectType::WALL)
	{
		lines = setLines;
		color = setColor;
		collider_manager.GetCollider(&collider);
	}
	//ゲッター
	inline int getSize() { return lines.size(); }			//線分配列の要素数を渡す
	inline LineCollider* getCollider() { return &collider; }//mapの当たり判定情報を渡す
	inline std::vector<Ray2> getLines() { return lines; }

	//ミニマップのマップギミック
	void Search();

	//マップの更新処理
	virtual void Update();
	//ミニマップの描画処理
	virtual void Draw();
};