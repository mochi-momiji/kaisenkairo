#pragma once
#include "DxLib.h"
#include <unordered_map>

class Color {
public:
	const int WHITE = GetColor(255, 255, 255);	//”’
	const int RED = GetColor(255, 0, 0);		//Ô
	const int YELLOW = GetColor(255, 255, 0);	//‰©
	const int GREEN = GetColor(0, 255, 0);		//—Î
	const int BLUE = GetColor(0, 0, 255);		//Â
	const int LIGHT_BLUE = GetColor(0, 174, 239);//…F
	const int PURPLE = GetColor(255, 0, 255);	//‡F
};

extern Color COLOR;