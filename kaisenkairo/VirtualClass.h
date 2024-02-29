#pragma once
#include "DxLib.h"
#include "Color.h"
#include"DataBase.h"
#include <list>

//移動を前提としたオブジェクトの仮想関数
class CObject {
protected:
	VECTOR position;	//中心座標
	double angle = 0;	//向いている角度
	int color = COLOR.WHITE;//描画時の色
public:
	//コンストラクタ
	CObject(VECTOR setPos, int setAngle = 0) {
		position = setPos;
		angle = setAngle;
	}
	//デストラクタ
	~CObject() {}

	int getColor() { return color; }

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class ObjectManager {

};
