#pragma once
#include "DxLib.h"
#include "VirtualClass.h"

//À‘•—\’è
class Enemy :CObject {
	VECTOR position;

public:
	//ƒQƒbƒ^[
	VECTOR GetPosition() { return position; }
	//ˆÚ“®ˆ—
	void Move();

};
