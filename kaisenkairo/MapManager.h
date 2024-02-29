#pragma once
#include "DxLib.h"
#include "Map.h"
#include"Color.h"
#include <unordered_map>

class MapManager {

	//�}�b�v�`�b�v�@
	int field_01[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0,11, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 5, 2, 2, 2, 2, 2,},
	{0, 9, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 9, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{14,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0,10, 0, 0,10, 0, 0, 0, 0, 0, 0, 0,10, 0, 0,10, 0,},
	{2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0,12, 0, 0, 1, 0, 0, 0, 0, 0,},
	};
	//�}�b�v�`�b�v�A
	int field_02[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
	};
	std::vector<const char*> stage_id = { "Stage01", "Stage02", "Stage03", "Stage04", "Stage05", "Stage06", "Stage07" };
	std::unordered_map<const char*, CMap*> maps;
	std::unordered_map<const char*, int> stage_color;

	std::unordered_map<const char*, UpExit*> up_exits;
	std::unordered_map<const char*, DownExit*> down_exits;
	std::unordered_map<const char*, RightExit*> right_exits;
	std::unordered_map<const char*, LeftExit*> left_exits;

	CMap* current_stage = nullptr;

	int slid = SLIDE_LIMIT;	//�~�j�}�b�v�J���̈ړ���
	bool is_close = true;	//�~�j�}�b�v�����Ă��邩�̃t���O
	bool is_sliding = false;//�~�j�}�b�v���J���ł��邩�̃t���O
	const char* current_stage_id = "Stage01";
	
//�����o�ϐ�������������֐��ׁ̈Aprivate�֐��Ƃ���

	//MapChip������N���X�̔z��ɕϊ�����֐�
	std::vector<Ray2> LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH],const char* string, int stageNum);

	//�}�b�v�`�b�v��ǂݍ��ނ��߂̊֐�--------------------------------------------------------------
	Ray2 GetStraightLine(int x, int y, int length, int lineColor, bool is_horizontal);//�c���E�������쐬
	void GetCornerLine(std::vector<Ray2>& lines, int x, int y,
		int length, int lineColor, bool is_up, bool is_right);					//�p���쐬
	void CreateMap(std::vector<Ray2>& lines, Chip_Kind kind,
				int pos_x, int pos_y, const char* stageId, int& stageNum);//�}�b�v�`�b�v���Ƃ̐����֐��Ăяo��

public:
	MapManager() {
		stage_color["Stage01"] = COLOR.WHITE;
		stage_color["Stage02"] = COLOR.YELLOW;
		stage_color["Stage03"] = COLOR.LIGHT_BLUE;
		stage_color["Stage04"] = COLOR.GREEN;
		stage_color["Stage05"] = COLOR.PURPLE;
		stage_color["Stage06"] = COLOR.RED;
		stage_color["Stage07"] = COLOR.BLUE;

		SetUpMap();
	}

	void SetUpMap();

	void Update();
	void ChangeMap();
	void UpdateLines();
	void UpdateCollider();
	bool IsExit();
	void SlidMap();
};