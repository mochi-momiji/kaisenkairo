#pragma once
#include "DxLib.h"
#include "Collider.h"
#include "Color.h"
#include "VirtualClass.h"
#include "Methods.h"
#include "View.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HIGHT 1080
#define SPEED 0.5
#define ANGLE_SPEED 30
#define RAY_INDEX 300
#define DEPTH 700
#define RADIUS 5
#define NONE 0

//��Class�ւ̎Q�Ɨp�N���X
class CMap;
class CGameText;
//class Collision;

class CPlayer : public CObject{
	//friend Collision;
	friend CMap;
	friend CGameText;

	View* fps_view = new View();

	CircleCollider* collider;	//�����蔻��(�~)
	
	int radius = 20;	//�`�掞�̉~�̔��a
	int color = COLOR.YELLOW;	//�`�掞�̐F

	float move_length = 0;	//�ړ�����

	//����������̃}�E�X�J�[�\���̍��W����
	int new_cursor_x = 0;
	int new_cursor_y = 0;

	//�������O�̃}�E�X�J�[�\���̍��W����
	int old_cursor_x = 0;
	int old_cursor_y = 0;

public:
	//�R���X�g���N�^
	CPlayer(VECTOR setPos = VGet(1600, 750, 0), int setAngle = 0)
		:CObject(setPos, setAngle)
	{
		collider = new CircleCollider(position, radius, ObjectType::PLAYER);
		collider_manager.GetCollider(collider);
	}
	~CPlayer() {
		delete collider;
	}

	//�Q�b�^�[
	inline VECTOR getPosition() { return position; }			//�v���C���[�̍��W��n��
	inline float getMoveLength() { return move_length; }		//�ړ�������n��
	inline CircleCollider& GetCollider() { return *collider; }	//�����蔻��̏���n��

	void Move();	//�ړ�����
	void Rotate();	//��]����
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	void EnterRoom(VECTOR exitPos,VECTOR direction);
};