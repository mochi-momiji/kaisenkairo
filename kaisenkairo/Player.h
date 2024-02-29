#pragma once
#include "DxLib.h"
#include "Collider.h"
#include "Color.h"
#include "VirtualClass.h"
#include "Methods.h"
#include "View.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HIGHT 1080
#define SPEED 0.5
#define ANGLE_SPEED 30
#define RAY_INDEX 300
#define DEPTH 700
#define RADIUS 5
#define NONE 0

//他Classへの参照用クラス
class CMap;
class CGameText;
//class Collision;

class CPlayer : public CObject{
	//friend Collision;
	friend CMap;
	friend CGameText;

	View* fps_view = new View();

	CircleCollider* collider;	//当たり判定(円)
	
	int radius = 20;	//描画時の円の半径
	int color = COLOR.YELLOW;	//描画時の色

	float move_length = 0;	//移動距離

	//動かした後のマウスカーソルの座標成分
	int new_cursor_x = 0;
	int new_cursor_y = 0;

	//動かす前のマウスカーソルの座標成分
	int old_cursor_x = 0;
	int old_cursor_y = 0;

public:
	//コンストラクタ
	CPlayer(VECTOR setPos = VGet(1600, 750, 0), int setAngle = 0)
		:CObject(setPos, setAngle)
	{
		collider = new CircleCollider(position, radius, ObjectType::PLAYER);
		collider_manager.GetCollider(collider);
	}
	~CPlayer() {
		delete collider;
	}

	//ゲッター
	inline VECTOR getPosition() { return position; }			//プレイヤーの座標を渡す
	inline float getMoveLength() { return move_length; }		//移動距離を渡す
	inline CircleCollider& GetCollider() { return *collider; }	//当たり判定の情報を渡す

	void Move();	//移動処理
	void Rotate();	//回転処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

	void EnterRoom(VECTOR exitPos,VECTOR direction);
};