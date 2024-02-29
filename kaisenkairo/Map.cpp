#include "Map.h"
#include "Player.h"

void CMap::Search()
{
	bool is_close = false;
	if (is_close == false) {
		if (CheckHitKeyDown(KEY_INPUT_R))
			is_search = true;

		if (is_search == true) {
			for (int i = 0; i < 2; i++) {
				//DrawCircleAA(obj[i].position.x, obj[i].position.y, 3, 32, red, TRUE);
				timer++;
				//DrawCircleAA(move_pos.x, move_pos.y, timer, 32, yellow, FALSE);
			}
			if (timer >= 300) {
				is_search = false;
				timer = 0;
			}
		}
	}
}

void CMap::Update()
{
	Search();
	collider.Reset();
}

//ミニマップの描画処理
void CMap::Draw()
{
	int slid_pos = DB.getSlidPosition();
	for (int i = 0; i < lines.size(); i++) {
		//マップを線で描画
		DrawLineAA(lines[i].getBegin().x + slid_pos, lines[i].getBegin().y,//始点 
			lines[i].getEnd().x + slid_pos, lines[i].getEnd().y,		//終点
			COLOR.WHITE);										//描画時の色
		DrawCircle(lines[i].getBegin().x, lines[i].getBegin().y, 5, COLOR.PURPLE);
	}
}