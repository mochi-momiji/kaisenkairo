#include "Player.h"
#include "GameText.h"
#include "Map.h"

void CPlayer::Move()
{
	VECTOR move_pos = position;
	bool is_moving = false;
	//�ړ�����
	if (CheckHitKey(KEY_INPUT_A)) {
		is_moving = true;
		//�ړ��������v�Z
		VECTOR left = VGet(cos(angle - M_PI_2) * SPEED, sin(angle - M_PI_2) * SPEED, NULL);

		move_pos.x -= left.x;
		move_pos.y -= left.y;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		is_moving = true;
		//�ړ��������v�Z
		VECTOR right = VGet(cos(angle + M_PI_2) * SPEED, sin(angle + M_PI_2) * SPEED, NULL);

		move_pos.x -= right.x;
		move_pos.y -= right.y;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		is_moving = true;
		//�ړ��������v�Z
		VECTOR forward = VGet(cos(angle) * SPEED, sin(angle) * SPEED, NULL);

		move_pos.x -= forward.x;
		move_pos.y -= forward.y;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		is_moving = true;
		//�ړ��������v�Z
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

	//�R���C�_�[�Ɉړ���̍��W����
	collider->UpdatePosition(move_pos);
}

void CPlayer::Rotate()
{
	//�}�E�X�J�[�\���̈ʒu���擾
	GetMousePoint(&new_cursor_x, &new_cursor_y);

	/*	1�t���[���O�̈ʒu�Ɣ�r���� */
	//x�������傫��==�E����
	if (old_cursor_x < new_cursor_x) {
		//�E��U�����
		angle += M_PI_4 / ANGLE_SPEED;
	}
	//x������������==������
	else if (old_cursor_x > new_cursor_x) {
		//����U�����
		angle -= M_PI_4 / ANGLE_SPEED;
	}

	if (angle > M_PI * 2) {
		angle -= M_PI * 2;
	}

	//�J�[�\������ʒ[�t�߂ɒB�����ꍇ
	if (new_cursor_x == SCREEN_WIDTH - 1) {
		SetMousePoint(0, new_cursor_y);//���΂̉�ʒ[�Ɉړ�������
	}
	else if (new_cursor_x == 0) {
		SetMousePoint(SCREEN_WIDTH, new_cursor_y);

	}

	old_cursor_x = new_cursor_x;
	old_cursor_y = new_cursor_y;
}

void CPlayer::EnterRoom(VECTOR enterPos, VECTOR direction) {
	float melt_value = 1.5f;
	//���̃X�e�[�W�Ɉړ���������ƐڐG������ԂŃX�^�[�g���Ȃ��悤�Ɉړ��ʂ̃x�N�g����{�ɂ��邷��
	VECTOR enter_direction = VGet(direction.x * melt_value, direction.y * melt_value, direction.z * melt_value);
	position = VAdd(enterPos, enter_direction);
}

void CPlayer::Update() {
	Move();
	Rotate();
}

void CPlayer::Draw()
{
	//�ړ���̍��W�ŕǂɓ������Ă��Ȃ��Ȃ�ړ��������s��
	if (!collider->getIsHitLine()) {
		position = collider->getPosition();
		DrawBox(100, 10, 110, 20, COLOR.GREEN, TRUE);
	}
	else {
		//�v���C���[�{���̍��W����
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