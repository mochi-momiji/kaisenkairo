#pragma once
#include "DxLib.h"
#include "Methods.h"
#include "Collider.h"
#include "Color.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
//���N���X�ԂŎQ�Ƃ���f�[�^���Ǘ�����N���X
class DataBase {
private:
	VECTOR player_pos = VGet(0, 0, 0);	//�v���C���[�̍��W
	double player_angle = 0;			//�v���C���[�̌����Ă���p�x
	int slid_pos = 0;					//�~�j�}�b�v�̊J�ړ���
	const char* stage_id = "Stage01";	//���݂̃X�e�[�W�̕`�掞�̐F
	std::vector<Ray2> map_line;			//�}�b�v�̐������
	std::map<int, VECTOR> enemy_pos;	//�G�l�~�[�̍��W�̘A�z�z��(�X�e�[�W�ԍ�,���W)
	int move_length = 0;
	int stage_color = COLOR.WHITE;
	VECTOR delta_vec = VGet(0, 0, 0);
	VECTOR enter_exit_pos = VGet(0, 0, 0);

public:
	//�R���X�g���N�^
	DataBase() {}

	//�X�V����
	void UpdateMapData(const std::vector<Ray2>& newLine) { map_line = newLine; }//�}�b�v�f�[�^�̍X�V����
	void UpdateExit(const std::vector<Ray2>& newLine) {
		map_line.insert(map_line.end(), newLine.begin(), newLine.end());
	}
	void UpdateSlid(const int& new_pos) { slid_pos = new_pos; }					//�~�j�}�b�v�J�̈ړ��ʍX�V
	void UpdatePlayerPosition(const VECTOR& newPos) { player_pos = newPos; }	//�v���C���[�̍��W���X�V����
	void UpdateStageId(const char* stageId) { stage_id = stageId; }				//�X�e�[�W�̕`��F�̍X�V����
	void UpdateMoveLength(const int& newLenght) { move_length = newLenght; }
	void UpdateStageColor(const int& setColor) { stage_color = setColor; }
	void UpdateDelta(VECTOR setVec) { delta_vec = setVec; }
	void UpdateExitPosition(VECTOR setPos) { enter_exit_pos = setPos; }

	//�Q�b�^�[
	inline std::vector<Ray2> getMapLine() { return map_line; }//Map�̐������̃Q�b�^�[
	inline int getSlidPosition() { return slid_pos; }		//�J���̈ړ��ʂ̃Q�b�^�[
	inline VECTOR getPlayerPosition() { return player_pos; }//Player�̍��W�̃Q�b�^�[
	inline double getPlayerAngle() { return player_angle; }//Player�̊p�x�̃Q�b�^�[
	inline const char* getStageId() { return stage_id; }	//�X�e�[�W��(const char*�^)�̃Q�b�^�[
	inline int getMoveLength() { return move_length; }
	inline int getStageColor() { return stage_color; }
	inline VECTOR getDelta() { return delta_vec; }
	inline VECTOR getExitPosition() { return enter_exit_pos; }
};

extern DataBase DB;