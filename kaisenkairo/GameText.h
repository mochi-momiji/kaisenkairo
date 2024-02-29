#pragma once
#include "DxLib.h"
#include "Color.h"
#include "VirtualClass.h"
#include <unordered_map>

#define NONE 0
#define NEXT_LINE 40
#define LOG_LINE_VALUE 5

//class TutorialText :CGameText {
//
//};
//
//class ProgressText :CGameText {
//	
//	ProgressText(VECTOR setPos)
//		:CGameText(setPos) {}
//
//	virtual void Draw();
//};

//�Q�[���e�L�X�g�N���X
class CGameText : public CObject{

	VECTOR position;					//�e�L�X�g�\���̍��W
	VECTOR pos1 = VGet(50, 840, NULL);	//
	VECTOR pos2 = VGet(960, 840, NULL);
	std::unordered_map<const char*, int> font_color;//�����`�掞�̐F

	const char* progress_log[LOG_LINE_VALUE] = {"a","b","c"};//�v���C���[�̐i�s���O
	const char* tutorial[LOG_LINE_VALUE] =					//�������
	{
		"�ړ�:W�L�[(�O����)�ES�L�[(�����)",
		"     A�L�[(������)�ED�L�[(�E����)",
		"���_�ړ�:�}�E�X",
		"����M�~�b�N:E�L�[(�~�j�}�b�v�̊J��)",
		"             R�L�[(�~�j�}�b�v���ɓG��\��)"
	};
public:
	//�R���X�g���N�^
	CGameText(VECTOR setPosition);

	virtual void Update();	//�X�V����
	virtual void Draw();	//�`�揈��

	void SetProgressLog(const char* new_log);//�i�s���O�̓���ւ�
};