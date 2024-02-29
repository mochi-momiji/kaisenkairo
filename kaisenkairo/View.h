#pragma once
#include "DxLib.h"
#include "Collider.h"
#include "Methods.h"
#include "DataBase.h"

class View {
private:
	LineCollider collider;
	int ray_num = 300;
	int range = 700;
public:
	View(){}
	VECTOR CheckMinDistanceWall(Ray2 ray,VECTOR playerPos, int& color);
	void Draw(const VECTOR& playerPos, const double& playerAngle);
	void DrawViewRenge(VECTOR playerPos, VECTOR crossPos);
	void DrawFPSView(int lineNum, int color, float viewHeight);
};