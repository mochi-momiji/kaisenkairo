#pragma once
#include "DxLib.h"
#include "Color.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define FIRST_INDEX 0
#define NONE 0
#define MAX 1.0f
#define MIN 0.0f
#define HALF_DEG 180

//線分クラス
class Ray2 {
	VECTOR begin = VGet(0, 0, 0);	//始点座標
	VECTOR end = VGet(0, 0, 0);		//終点座標
	int color = GetColor(255, 255, 255);	//線分の色

public:
	//コンストラクタ
	Ray2();//値を指定しない場合
	Ray2(VECTOR setBegin, VECTOR setBnd);//初期価値を指定する場合
	Ray2(VECTOR setBegin, VECTOR setEnd, int setColor);

	//ゲッター
	inline VECTOR getBegin() { return begin; }	//始点を渡す
	inline VECTOR getEnd() { return end; }		//終点を渡す
	inline int getColor() { return color; }	//線分の色を渡す
	
	void With2p(VECTOR setBegin, VECTOR setEnd);//既に生成した線分の始点と主点を書き換える
	void With2p(VECTOR setBegin, VECTOR setEnd,int setColor);//既に生成した線分の始点と主点を書き換える
};

VECTOR Intersection(Ray2 ray1, Ray2 ray2);	//交点の座標を算出

float Clump(float value, float min, float max);//値の上限と下限で制限する

bool CheckHitKeyDown(int key_code);	//キーが押した瞬間だけを判定する