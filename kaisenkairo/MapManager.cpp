#include "MapManager.h"

void MapManager::SlidMap()
{
	int count = 0;
	if (CheckHitKey(KEY_INPUT_E) && is_sliding == false) {
		is_close = !is_close;
		is_sliding = true;
	}
	if (is_sliding == true) {
		if (slid > NONE && is_close == false) {
			slid -= 20;
		}
		else if (slid < SLIDE_LIMIT && is_close == true) {
			slid += 20;
		}
		else {
			is_sliding = false;
		}
	}
	DB.UpdateSlid(slid);
}

void MapManager::SetUpMap() {
	int stage_num = FIRST_INDEX;
	std::vector<Ray2> lines = LoadMapInfo(field_01, "Stage01", stage_num++);
	maps["Stage01"] = new CMap(lines,stage_color["Stage01"]);
	lines = LoadMapInfo(field_01, "Stage02", stage_num++);
	maps["Stage02"] = new CMap(lines, stage_color["Stage02"]);
	lines = LoadMapInfo(field_01, "Stage03", stage_num++);
	maps["Stage03"] = new CMap(lines, stage_color["Stage03"]);
	lines = LoadMapInfo(field_01, "Stage04", stage_num++);
	maps["Stage04"] = new CMap(lines, stage_color["Stage04"]);
	lines = LoadMapInfo(field_01, "Stage05", stage_num++);
	maps["Stage05"] = new CMap(lines, stage_color["Stage05"]);
	lines = LoadMapInfo(field_01, "Stage06", stage_num++);
	maps["Stage06"] = new CMap(lines, stage_color["Stage06"]);
	lines = LoadMapInfo(field_01, "Stage07", stage_num);
	maps["Stage07"] = new CMap(lines, stage_color["Stage07"]);

	UpdateLines();
	UpdateCollider();
}

void MapManager::Update() {
	current_stage->Update();
  	current_stage->Draw();
	up_exits[current_stage_id]->Draw();
	down_exits[current_stage_id]->Draw();
	right_exits[current_stage_id]->Draw();
	left_exits[current_stage_id]->Draw();
	ChangeMap();
	SlidMap();
}

void MapManager::UpdateLines() {
	current_stage = maps[current_stage_id];//現在のステージ情報を更新
	DB.UpdateMapData(current_stage->getLines());//現在のステージ情報を保存
	collider_manager.GetCollider(maps[current_stage_id]->getCollider());//字ライダー情報を保存
	DB.UpdateExit(up_exits[current_stage_id]->getLines());
	DB.UpdateExit(down_exits[current_stage_id]->getLines());
	DB.UpdateExit(right_exits[current_stage_id]->getLines());
	DB.UpdateExit(left_exits[current_stage_id]->getLines());
	DB.UpdateStageId(current_stage_id);//現在のステージ寧を保存
	DB.UpdateStageColor(current_stage->getColor());//ステージの色を保存
}

void MapManager::ChangeMap() {
	if (up_exits[current_stage_id]->getCollider().getHitType() == ObjectType::PLAYER) {
		up_exits[current_stage_id]->Loop();
		current_stage_id = DB.getStageId();;//現在のステージ名の更新
		current_stage = maps[current_stage_id];//現在のステージ情報を更新
		UpdateCollider();//衝突判定をする出入口のコライダーを更新
		DB.UpdateExitPosition(down_exits[current_stage_id]->getPosition());
		UpdateLines();
	}
	else if (down_exits[current_stage_id]->getCollider().getHitType() == ObjectType::PLAYER) {
		down_exits[current_stage_id]->Loop();
		current_stage_id = DB.getStageId();
		current_stage = maps[current_stage_id];
		UpdateCollider();
		DB.UpdateExitPosition(up_exits[current_stage_id]->getPosition());
		UpdateLines();
	}
	else if (right_exits[current_stage_id]->getCollider().getHitType() == ObjectType::PLAYER) {
		right_exits[current_stage_id]->Loop();
		current_stage_id = DB.getStageId();
		current_stage = maps[current_stage_id];
		UpdateCollider();
		DB.UpdateExitPosition(left_exits[current_stage_id]->getPosition());
		UpdateLines();
	}
	else if (left_exits[current_stage_id]->getCollider().getHitType() == ObjectType::PLAYER) {
		left_exits[current_stage_id]->Loop();
		current_stage_id = DB.getStageId();
		current_stage = maps[current_stage_id];
		UpdateCollider();
		DB.UpdateExitPosition(right_exits[current_stage_id]->getPosition());
		UpdateLines();
	}
}

void MapManager::UpdateCollider() {
	collider_manager.GetCollider(current_stage->getCollider());
	collider_manager.GetCollider(&up_exits[current_stage_id]->getCollider());
	collider_manager.GetCollider(&down_exits[current_stage_id]->getCollider());
	collider_manager.GetCollider(&right_exits[current_stage_id]->getCollider());
	collider_manager.GetCollider(&left_exits[current_stage_id]->getCollider());
}

Ray2 MapManager::GetStraightLine(int x, int y, int length, int lineColor, bool is_horizontal)
{
	VECTOR MapPos = VGet(LEFT_LIMIT, UP_LIMIT, NONE);
	VECTOR root = VAdd(MapPos, VGet(length * x, length * y, NONE));
	VECTOR start, end;
	float offset = length / 2;
	if (is_horizontal == true) {
		start = VAdd(root, VGet(NONE, offset, NONE));
		end = VAdd(start, VGet(length, NONE, NONE));
	}
	else {
		start = VAdd(root, VGet(offset, NONE, NONE));
		end = VAdd(start, VGet(NONE, length, NONE));
	}
	Ray2 result(start, end, lineColor);
	return result;
}

void MapManager::GetCornerLine(std::vector<Ray2>& lines,int x, int y, int length,
	int lineColor, bool is_up, bool is_right)
{
	//基準点と壁の長さを保存
	float horizontal_offset = length / 2;
	float vartical_offset = length / 2;
	VECTOR MapPos = VGet(LEFT_LIMIT, UP_LIMIT, NONE);
	VECTOR root = VAdd(MapPos, VGet(length * x, length * y, NONE));
	VECTOR start = VAdd(root, VGet(horizontal_offset, horizontal_offset, NONE));

	//角の横線を計算
	horizontal_offset = is_right ? -horizontal_offset : horizontal_offset;
	VECTOR end = VAdd(start, VGet(horizontal_offset, NONE, NONE));
	//線を生成
	Ray2 horizontal_line(start, end, lineColor);
	//配列に保存
	lines.emplace_back(horizontal_line);

	//角の縦線の計算
	vartical_offset = is_up ? vartical_offset : -vartical_offset;
	end = VAdd(start, VGet(NONE, vartical_offset, NONE));
	Ray2 vertical_line(start, end, lineColor);
	lines.emplace_back(vertical_line);
}

void MapManager::CreateMap(std::vector<Ray2>& lines,Chip_Kind kind, 
		int pos_x, int pos_y, const char* stageId, int& stageNum)
{
	Ray2 line;
	int color = stage_color[stageId];
	VECTOR MapPos = VGet(LEFT_LIMIT, UP_LIMIT, NONE);
	VECTOR root = VAdd(MapPos, VGet(GRID_LENGTH * pos_x, GRID_LENGTH * pos_y, NONE));
	switch (kind) {
	case NONE_LINE:
		break;
	case VARTICAL:
		line = GetStraightLine(pos_x, pos_y, GRID_LENGTH, color, false);
		lines.emplace_back(line);
		break;
	case HORIZONTAL:
		line = GetStraightLine(pos_x, pos_y,  GRID_LENGTH, color, true);
		lines.emplace_back(line);
		break;
	case LEFT_UP_CORNER:
		GetCornerLine(lines, pos_x, pos_y,  GRID_LENGTH, color, true, false);
		break;
	case RIGHT_UP_CORNER:
		GetCornerLine(lines, pos_x, pos_y,  GRID_LENGTH, color, true, true);
		break;
	case LEFT_DOWN_CORNER:
		GetCornerLine(lines, pos_x, pos_y,  GRID_LENGTH, color, false, false);
		break;
	case RIGHT_DOWN_CORNER:
		GetCornerLine(lines, pos_x, pos_y,  GRID_LENGTH, color, false, true);
		break;
	case UP_EXIT:
		stageNum++;
		if (stageNum == stage_id.size()) {
			stageNum = 0;
		}
		up_exits[stageId] = new UpExit(root.x + GRID_LENGTH / 2, root.y + 10, stage_id[stageNum]);
		up_exits[stageId]->PushLine(root);
		break;
	case DOWN_EXIT:
		stageNum++;
		if (stageNum == stage_id.size()) {
			stageNum = 0;
		}
		down_exits[stageId] = new DownExit(root.x + GRID_LENGTH / 2, root.y + 10, stage_id[stageNum]);
		down_exits[stageId]->PushLine(root);
		break;
	case RIGHT_EXIT:
		stageNum++;
		if (stageNum == stage_id.size()) {
			stageNum = 0;
		}
		right_exits[stageId] = new RightExit(root.x + GRID_LENGTH / 2, root.y + 10, stage_id[stageNum]);
		right_exits[stageId]->PushLine(root);
		break;
	case LEFT_EXIT:
		stageNum++;
		if (stageNum == stage_id.size()) {
			stageNum = 0;
		}
		left_exits[stageId] = new LeftExit(root.x + GRID_LENGTH / 2, root.y + 10, stage_id[stageNum]);
		left_exits[stageId]->PushLine(root);
		break;
	}
}

std::vector<Ray2> MapManager::LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH],
	const char* stageId, int stageNum)
{
	std::vector<Ray2> lines;
	int wall_color = stage_color[stageId];
	for (int y = FIRST_INDEX; y < FIELD_HIGHT; y++) {
		for (int x = FIRST_INDEX; x < FIELD_WIDTH; x++) {
  			CreateMap(lines, (Chip_Kind)mapChips[y][x], x, y, stageId, stageNum);
		}
	}
	Ray2 line;
	line.With2p(VGet(LEFT_LIMIT, UP_LIMIT, NONE), VGet(RIGHT_LIMIT, UP_LIMIT, NONE), wall_color);
	lines.emplace_back(line);
	line.With2p(VGet(RIGHT_LIMIT, UP_LIMIT, NONE), VGet(RIGHT_LIMIT, DOWN_LIMIT, NONE), wall_color);
	lines.emplace_back(line);
	line.With2p(VGet(LEFT_LIMIT, DOWN_LIMIT, NONE), VGet(RIGHT_LIMIT, DOWN_LIMIT, NONE), wall_color);
	lines.emplace_back(line);
	line.With2p(VGet(LEFT_LIMIT, UP_LIMIT, NONE), VGet(LEFT_LIMIT, DOWN_LIMIT, NONE), wall_color);
	lines.emplace_back(line);

  	return lines;
}

bool MapManager::IsExit() {
	return up_exits[current_stage_id]->getCollider().getIsHitCircle()
		|| down_exits[current_stage_id]->getCollider().getIsHitCircle()
		|| right_exits[current_stage_id]->getCollider().getIsHitCircle()
		|| left_exits[current_stage_id]->getCollider().getIsHitCircle();
}
