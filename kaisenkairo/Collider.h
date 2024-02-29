#pragma once
#include "DxLib.h"
#include "Methods.h"
#include <unordered_map>
#include <vector>
//オブジェクトの役割
enum class ObjectType {
	NON,
	PLAYER,
	ENEMY,
	WALL,
	UP_EXIT,
	DOWN_EXIT,
	RIGHT_EXIT,
	LEFT_EXIT,
};
//当たり判定の基本情報
class ColliderBase {
	ObjectType type;
	ObjectType hit_type = ObjectType::NON;
	bool is_hit_circle = false;
	bool is_hit_line = false;
public:
	ColliderBase(ObjectType setType = ObjectType::NON) {
		type = setType;
	}

	ObjectType getType() { return type; }
	ObjectType getHitType() {return hit_type; }
	bool getIsHitCircle() { return is_hit_circle; }
	bool getIsHitLine() { return is_hit_line; }

	void ChangeCircleFlag(ObjectType otherType) {
		is_hit_circle = true;
		hit_type = otherType;
	}
	void ChangeLineFlag(ObjectType otherType) {
		is_hit_line = true;
		hit_type = otherType;
	}

	void Reset() {
		is_hit_circle = false;
		is_hit_line = false; 
		hit_type = ObjectType::NON;
	}
};
//円の当たり判定コライダー
class CircleCollider : public ColliderBase {
	VECTOR position = VGet(0,0,0);	//中心座標
	int radius = 0;			//半径
public:
	//コンストラクタ
	CircleCollider(){}
	CircleCollider(VECTOR setPos, int setRad, ObjectType setType = ObjectType::NON)
		: ColliderBase(setType)
	{
		position = setPos;
		radius = setRad;
	}

	void UpdatePosition(VECTOR newPos) {
		position = newPos;
	}

	inline VECTOR getPosition()const  { return position; }
	inline int getRadius() const { return radius; }
};
//線の当たり判定コライダー
class LineCollider : public ColliderBase {
	std::vector<Ray2> lines;	//線分情報(始点・終点・色)
public:
	//コンストラクタ
	LineCollider(){}
	LineCollider(std::vector<Ray2> setLines,ObjectType setType = ObjectType::NON)
		: ColliderBase(setType) 
	{
		lines = setLines;
	}

	void UpdateLines(std::vector<Ray2> newLines){
		lines = newLines;
	}

	inline std::vector<Ray2> getLines() const { return lines; }
};

class ColliderManager {
	friend CircleCollider;
	friend LineCollider;
private:
	CircleCollider *player_collider, *enemy_collider;
	std::unordered_map<ObjectType, LineCollider*> line_colliders;
	
public:
	void GetCollider(CircleCollider *collider);	//オブジェクトの円コライダを配列に保存
	void GetCollider(LineCollider *collider);	//オブジェクトの線コライダを配列に保存
	void Update();								//各コライダの更新処理
	void UpdateFlag(CircleCollider* collider01, CircleCollider* collider02);//円と円の衝突フラグのチェック
	
	void UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider);	//円と線の衝突フラグのチェック
	//円と円の当たり判定処理
	bool CheckCollision(const CircleCollider& collider01, const CircleCollider& collider02);
	//円と線の当たり判定
	bool CheckCollision(const CircleCollider& circleCollider, const LineCollider& lineCollider);
};

extern ColliderManager collider_manager;