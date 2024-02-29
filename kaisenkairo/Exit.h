#pragma once
#include "DxLib.h"
#include "Methods.h"
#include "VirtualClass.h"
#include "Collider.h"
#include "DataBase.h"
#include "Color.h"
#include <vector>
#include <time.h>

#define NONE 0

//�o����
class Exit {
protected:
	LineCollider* collider = nullptr;		//�����蔻��
	const char* next_stage_id = "";
	int progress = 0;			//�i���x
	std::vector<Ray2> lines;	//����
	std::unordered_map<const char*, int> stage_colors;//�X�e�[�W���Ƃ̐F�̘A�z�z��
	VECTOR position;		//���W
	int thickness = 10;		//����
	int width = 30;			//��
	int color = COLOR.WHITE;//���݂̐F

public:
	//�R���X�g���N�^
	Exit(const char* exitStageId) {
		next_stage_id = exitStageId;
		stage_colors["Stage01"] = COLOR.WHITE;
		stage_colors["Stage02"] = COLOR.YELLOW;
		stage_colors["Stage03"] = COLOR.LIGHT_BLUE;
		stage_colors["Stage04"] = COLOR.GREEN;
		stage_colors["Stage05"] = COLOR.PURPLE;
		stage_colors["Stage06"] = COLOR.RED;
		stage_colors["Stage07"] = COLOR.BLUE;

		color = stage_colors[exitStageId];
	}
	//�Q�b�^�[
	inline LineCollider& getCollider() { return *collider; }	//�����蔻�����n��
	inline std::vector<Ray2> getLines() { return lines; }		//�����z���n��
	inline VECTOR getPosition() { return position; }	//���W��n��
	inline const char* getNextStage() { return next_stage_id; }
	//�������z�֐�
	virtual void PushLine(VECTOR root) = 0;	//���������Z�o�E�ۑ�

	//�v���C���[���o������ɐڐG�����ۂ̏���
	void Loop();
	void Draw();//�`�揈��
};

//��Ɍ������ׂ̏o����
class UpExit :public Exit {
public:
	//�R���X�g���N�^
	UpExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//�I�[�o�[���C�h�֐�
	virtual void PushLine(VECTOR root) override;//���������Z�o�E�ۑ�
};

//���Ɍ������ׂ̏o����
class DownExit :public Exit {
public:
	//�R���X�g���N�^
	DownExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//�I�[�o�[���C�h�֐�
	virtual void PushLine(VECTOR root) override;	//���������Z�o�E�ۑ�
};

//�E�Ɍ������ׂ̏o����
class RightExit :public Exit {
public:
	//�R���X�g���N�^
	RightExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//�I�[�o�[���C�h�֐�
	virtual void PushLine(VECTOR root) override;	//���������Z�o�E�ۑ�
};

//���Ɍ������ׂ̏o����
class LeftExit :public Exit {
public:
	//�R���X�g���N�^
	LeftExit(int x, int y, const char* exitStageId)
		:Exit(exitStageId) {
	}
	//�I�[�o�[���C�h�֐�
	virtual void PushLine(VECTOR root) override;	//���������Z�o�E�ۑ�
};
