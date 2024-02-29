#pragma once
#include "DxLib.h"
#include "Color.h"
#include "Scene.h"
#include "VirtualClass.h"

class CPlayer;
class CGameText;
class MapManager;
class View;
//�Q�[���̃��C�����[�v���s���N���X
class GameMaster {
	CPlayer* player;
	MapManager* map;
	CGameText* progress_text;
	StartScene* start_scene;
	PlayScene* main_scene;
	ClearScene* clear_scene;
public:
	//�R���X�g���N�^
	GameMaster();
	//�f�X�g���N�^
	~GameMaster();

	void EntryClasses();	//�N���X�錾����

	void Update();	//�X�V����
	void Drawing();	//�`�揈��

	void Run();	//���C�����[�v����

	void SetStartScene();	//�^�C�g���V�[�����[�v
	void SetMainScene();	//���C���V�[�����[�v
	void SetClearScene();	//�N���A�V�[�����[�v

	virtual void Move();//�ړ����ꊇ����
	virtual void Draw();//�`����ꊇ����

	bool pause = false;	//�|�[�Y�t���O
};

extern GameMaster* GM;

/*�@�萔�@*/
//Game�ݒ�֌W
#define SCREEN_WIDTH 1920
#define SCREEN_HIGHT 1080
#define SCREEN_COLOR 32