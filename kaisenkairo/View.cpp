#include "View.h"


VECTOR View::CheckMinDistanceWall(Ray2 viewRay, VECTOR playerPos, int& color) {
	std::vector<Ray2> map_lines = DB.getMapLine();	//mapの線分情報のコピー
	VECTOR min_dist_cross = VGet(NULL, NULL, NULL);//最短距離の交点の座標
	float min_dist = 0;//最短距離
	float is_first = true;//一つ目の交点かのフラグ
	//mapの線分情報をfor文で一本ずつ確認して行く
	for (int i = 0; i < map_lines.size(); i++) {
		VECTOR cross_pos = Intersection(map_lines[i], viewRay);//視界判定の線分mapの線分との交点
		VECTOR distance_vec = VSub(cross_pos, playerPos);//Player=>交点のベクトル
		float distance //Player=>交点の距離
			= sqrt(distance_vec.x * distance_vec.x + distance_vec.y * distance_vec.y);
		//交点が発生していたなら
		if (cross_pos.x != NULL && cross_pos.y != NULL) {
			//一個目の交点なら
			if (is_first) {
				min_dist = distance;	//基準とするために距離の最小値の値に代入する
				min_dist_cross = cross_pos;//基準とするために最短距離の交点の値に代入する
				color = map_lines[i].getColor();//一番近い交点が更新されたら描画する線分の色を更新
				is_first = false;	//以降の交点は一つ目ではないのでフラグを切る
			}
			//二つ目以降の交点 かつ　保存された最短距離より短いなら
			else if (!is_first && distance < min_dist) {
				min_dist_cross = cross_pos;//最短距離の交点の座標を更新
				min_dist = distance;	//最短距離の値を更新
				color = map_lines[i].getColor();//一番近い交点が更新されたら描画する線分の色を更新
			}
		}
	}
	return min_dist_cross;
}


void View::Draw(const VECTOR& playerPos, const double& playerAngle) {
	double left_angle = playerAngle - M_PI_4;	//扇形の左端の角度
	double right_angle = playerAngle + M_PI_4;	//扇形の右端の角度
	int line_num = FIRST_INDEX;					//処理中の線が何本目なのかを保存
	//扇形の視野範囲を展開
	for (double angle = left_angle; angle < right_angle; angle += M_PI_2 / ray_num) {
		//視野の線分の終点を算出
		VECTOR end_pos = VAdd(playerPos, VGet(cos(angle) * range, sin(angle) * range, 0));
		Ray2 view_ray(playerPos, end_pos);//視野判定の線分
		int color = COLOR.WHITE;			//描画時の色
		//最も近い交点を算出
		VECTOR min_dist_cross = CheckMinDistanceWall(view_ray, playerPos, color);
		//交点がないなら
		if (min_dist_cross.x == NULL && min_dist_cross.y == NULL) {
			min_dist_cross = view_ray.getEnd();//視野の線分の終点を代入
		}
		//交点があるなら
		else {
			VECTOR distance_vec = VSub(min_dist_cross, playerPos);//Player => 最短距離の交点のベクトル
			float distance = VSize(distance_vec) * cos(angle - playerAngle);//上記のベクトルの長さ
			float view_height = Clump(8000 / distance, NONE, 700);//描画する線の長さ
			//一人称視点の描画処理
			DrawFPSView(line_num, color,view_height);
		}
		//Playerの視野の線分の描画処理
		DrawViewRenge(playerPos, min_dist_cross);
		line_num++;
	}
}

void View::DrawViewRenge(VECTOR playerPos, VECTOR crossPos) {
	Ray2 sight(playerPos, crossPos, COLOR.WHITE);
	int slid_pos = DB.getSlidPosition();

	//視野を線で描画
	DrawLineAA(sight.getBegin().x + slid_pos, sight.getBegin().y,
		sight.getEnd().x + slid_pos, sight.getEnd().y,
		sight.getColor());
}

void View::DrawFPSView(int lineNum, int color, float viewHeight) {;

	VECTOR view_root = VGet(50, 380, NONE);//描画線分の座標の基準
	VECTOR line_begin = VAdd(view_root, VGet(4 * lineNum, -viewHeight / 2, NONE));//始点
	VECTOR line_end = VAdd(line_begin, VGet(NONE, viewHeight, NONE));//終点
	//線分の描画関数
	DrawLineAA(line_begin.x, line_begin.y, line_end.x, line_end.y, color);
}