#include "Player.h"
#include "GameText.h"
#include "Map.h"

void CPlayer::Move()
{
	VECTOR move_pos = position;
	bool is_moving = false;
	//移動処理
	if (CheckHitKey(KEY_INPUT_A)) {
		is_moving = true;
		//移動方向を計算
		VECTOR left = VGet(cos(angle - M_PI_2) * SPEED, sin(angle - M_PI_2) * SPEED, NULL);

		move_pos.x -= left.x;
		move_pos.y -= left.y;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		is_moving = true;
		//移動方向を計算
		VECTOR right = VGet(cos(angle + M_PI_2) * SPEED, sin(angle + M_PI_2) * SPEED, NULL);

		move_pos.x -= right.x;
		move_pos.y -= right.y;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		is_moving = true;
		//移動方向を計算
		VECTOR forward = VGet(cos(angle) * SPEED, sin(angle) * SPEED, NULL);

		move_pos.x -= forward.x;
		move_pos.y -= forward.y;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		is_moving = true;
		//移動方向を計算
		VECTOR back = VGet(cos(angle - M_PI) * SPEED, sin(angle - M_PI) * SPEED, NULL);

		move_pos.x -= back.x;
		move_pos.y -= back.y;
	}

	if (is_moving == true) {
		move_length++;
	}
	is_moving = false;

	DB.UpdateMoveLength(move_length);

	if (move_length > 200) {
		move_length = 0;
	}

	//コライダーに移動後の座標を代入
	collider->UpdatePosition(move_pos);
}

void CPlayer::Rotate()
{
	//マウスカーソルの位置を取得
	GetMousePoint(&new_cursor_x, &new_cursor_y);

	/*	1フレーム前の位置と比較して */
	//x成分が大きい==右入力
	if (old_cursor_x < new_cursor_x) {
		//右を振り向く
		angle += M_PI_4 / ANGLE_SPEED;
	}
	//x成分が小さい==左入力
	else if (old_cursor_x > new_cursor_x) {
		//左を振り向く
		angle -= M_PI_4 / ANGLE_SPEED;
	}

	if (angle > M_PI * 2) {
		angle -= M_PI * 2;
	}

	//カーソルが画面端付近に達した場合
	if (new_cursor_x == SCREEN_WIDTH - 1) {
		SetMousePoint(0, new_cursor_y);//反対の画面端に移動させる
	}
	else if (new_cursor_x == 0) {
		SetMousePoint(SCREEN_WIDTH, new_cursor_y);

	}

	old_cursor_x = new_cursor_x;
	old_cursor_y = new_cursor_y;
}

void CPlayer::EnterRoom(VECTOR enterPos, VECTOR direction) {
	float melt_value = 1.5f;
	//次のステージに移動時入り口と接触した状態でスタートしないように移動量のベクトルを倍にするする
	VECTOR enter_direction = VGet(direction.x * melt_value, direction.y * melt_value, direction.z * melt_value);
	position = VAdd(enterPos, enter_direction);
}

void CPlayer::Update() {
	Move();
	Rotate();
}

void CPlayer::Draw()
{
	//移動後の座標で壁に当たっていないなら移動処理を行う
	if (!collider->getIsHitLine()) {
		position = collider->getPosition();
		DrawBox(100, 10, 110, 20, COLOR.GREEN, TRUE);
	}
	else {
		//プレイヤー本来の座標を代入
		collider->UpdatePosition(position);
		DrawBox(90, 10, 100, 20, COLOR.RED, TRUE);
	}

	DB.UpdatePlayerPosition(position);

	const char* string = "";
	switch (collider->getHitType()) {
	case ObjectType::WALL:
		string = "WALL";
		break;
	case ObjectType::NON:
		string = "NULL";
		break;
	default:
		string = "EXIT";
		EnterRoom(DB.getExitPosition(), DB.getDelta());
		break;
	}
	DrawFormatString(400, 500, COLOR.BLUE, "%f, %f",position.x,position.y);
	DrawFormatString(400, 400, COLOR.RED, (const TCHAR*)string);

	collider->Reset();
	fps_view->Draw(position, angle);
	
	DrawCircle(position.x + DB.getSlidPosition(), position.y, radius, color, TRUE);
}