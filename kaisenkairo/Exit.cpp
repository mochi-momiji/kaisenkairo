#include "Exit.h"
//未実装

//描画処理
void Exit::Draw() {
	for (int i = 0; i < lines.size(); i++) {
		//DB.getSlidPosition() ==> ミニマップ開閉ギミックの移動量
		DrawLine(lines[i].getBegin().x + DB.getSlidPosition(), lines[i].getBegin().y,//始点座標
					lines[i].getEnd().x + DB.getSlidPosition(), lines[i].getEnd().y,//終点座標
					COLOR.WHITE	//線分を表示する際の色
		);
	}
	DrawCircle(position.x, position.y, 5, color, TRUE);
}

void Exit::Loop() {
	//Playerと衝突しているなら
	if (collider->getHitType() == ObjectType::PLAYER) {
		VECTOR player_pos = DB.getPlayerPosition();//Playerの座標を取得
		VECTOR delta = VSub(position, player_pos);//Player=>Exitのベクトルを生成(Map移動後の座標を算出時に使用)
		DB.UpdateDelta(delta);//Playerで参照するため、保存
		DB.UpdateStageId(next_stage_id);//移動先のステージ名を保存
	}
	collider->Reset();
}

//当たり判定・描画用の線分情報を生成
void UpExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(NONE, thickness, NONE));
	end = root;
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	end = VAdd(start, VGet(width, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(NONE, -thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	position = VAdd(end, VGet(-width / 2, NONE, NONE));
	collider = new LineCollider(lines,ObjectType::UP_EXIT);
}

void DownExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(NONE, width - thickness, NONE));
	end = VAdd(start, VGet(NONE, thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(width / 2, NONE, NONE));
	//
	end = VAdd(start, VGet(width, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(NONE, thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::DOWN_EXIT);
}

void RightExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(width - thickness, NONE, NONE));
	end = VAdd(start, VGet(thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(NONE, width / 2, NONE));
	//
	end = VAdd(start, VGet(NONE, width, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::RIGHT_EXIT);
}

void LeftExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(thickness, NONE, NONE));
	end = root;
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(NONE, width / 2, NONE));
	//
	end = VAdd(start, VGet(NONE, width, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(-thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::LEFT_EXIT);
}