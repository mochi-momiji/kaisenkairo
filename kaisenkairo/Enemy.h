#pragma once
#include "DxLib.h"
#include "VirtualClass.h"

//実装予定
class Enemy :CObject {
	VECTOR position;

public:
	//ゲッター
	VECTOR GetPosition() { return position; }
	//移動処理
	void Move();

};
