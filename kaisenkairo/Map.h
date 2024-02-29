#pragma once
#include "DxLib.h"
#include "DataBase.h"
#include "Color.h"
#include "Methods.h"
#include "VirtualClass.h"
#include "Exit.h"
#include "Collider.h"
#include <vector>

#define MAP_ROOT VGet(1400, 30, 0)
#define WALL_INDEX 4
#define FIELD_WIDTH 17
#define FIELD_HIGHT 25
#define UP_LIMIT 30
#define DOWN_LIMIT 780
#define RIGHT_LIMIT 1910
#define LEFT_LIMIT 1400
#define GRID_LENGTH 30
#define LENGTH 90
#define OBJECT_VALUE 15
#define SLIDE_LIMIT 540
#define NONE 0

//Player�̏���ۑ�����N���X
class CPlayer;
//class Collision;

enum Chip_Kind {
	NONE_LINE,			//�}�b�v�`�b�v����
	VARTICAL,			//�c��
	HORIZONTAL,			//����
	LEFT_UP_CORNER,		//����̊p
	RIGHT_UP_CORNER,	//�E��̊p
	LEFT_DOWN_CORNER,	//�����̊p
	RIGHT_DOWN_CORNER,	//�E���̊p
	UP_EXIT,			//�o��(��̕�)
	DOWN_EXIT,			//�o��(���̕�)
	RIGHT_EXIT,			//�o��(�E�̕�)
	LEFT_EXIT,			//�o��(���̕�)
};

class CMap : public CObject {
	//friend Collision;
	friend CPlayer;
	
	LineCollider collider;	//�ǂ̓����蔻��

	//map�̐������̔z��
	std::vector<Ray2> lines;

	bool is_search = false;//�T�[�`�@�\���g�p���Ă��邩�̃t���O
	int timer = 0;			//�T�[�`���̌o�ߎ��Ԃ��v��
	int radius = 0;			//�T�[�`�͈͂̔��a

public:
	//�R���X�g���N�^
	CMap(std::vector<Ray2> setLines, int setColor, VECTOR setPos = MAP_ROOT)
		:CObject(setPos), collider(setLines, ObjectType::WALL)
	{
		lines = setLines;
		color = setColor;
		collider_manager.GetCollider(&collider);
	}
	//�Q�b�^�[
	inline int getSize() { return lines.size(); }			//�����z��̗v�f����n��
	inline LineCollider* getCollider() { return &collider; }//map�̓����蔻�����n��
	inline std::vector<Ray2> getLines() { return lines; }

	//�~�j�}�b�v�̃}�b�v�M�~�b�N
	void Search();

	//�}�b�v�̍X�V����
	virtual void Update();
	//�~�j�}�b�v�̕`�揈��
	virtual void Draw();
};