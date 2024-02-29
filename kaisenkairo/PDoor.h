#pragma once
#include "DxLib.h"
#include "PVirtualClass.h"

class CPDoor: public Object {
public:
	int width = 0;
	int height = 0;
	bool is_visible = false;

	int all_handle = 0;
	int split_handle = 0;

	CPDoor() = default;

	CPDoor(VECTOR pos, int obj_width, int obj_height,int rad, float angle);

	void Init(VECTOR pos, float obj_width, float obj_height, int pas) {
		position = pos;
		width = obj_width;
		height = obj_height;
		all_handle = pas;
	}

	int GetIsVisible() { return is_visible; }
	int SetIsVisible(bool flg) { is_visible = flg; }
};