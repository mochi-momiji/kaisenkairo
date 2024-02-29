#include "DxLib.h"
#include "GameMaster.h"
#include "MapManager.h"
//#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Methods.h"
#include "GameText.h"
#include "Collider.h"
#include "View.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

	/*�@�萔�@*/
//Game�ݒ�֌W
#define SCREEN_WIDTH 1920
#define SCREEN_HIGHT 1080
#define SCREEN_COLOR 32

GameMaster* GM;
DataBase DB;
ColliderManager collider_manager;
Color COLOR;

//�Q�[���̏��
enum GameStatus {
	START_SCENE,
	MAIN_SCENE,
	CLEAR_SCENE,
};

GameStatus status = START_SCENE;

GameMaster::GameMaster() {
	SetGraphMode(SCREEN_WIDTH, SCREEN_HIGHT, SCREEN_COLOR);

	ChangeWindowMode(FALSE);
	DxLib_Init();

	//�}�E�X�J�[�\���̕\����OFF
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	SetFontSize(32);
	SetFontThickness(3);

	EntryClasses();
}

GameMaster::~GameMaster() {
	delete player;
	delete map;
	delete progress_text;
	DxLib_End();
}

void GameMaster::EntryClasses(){
	player = new CPlayer;
	map = new MapManager();
	progress_text = new CGameText(VGet(50, 800, NULL));
}

void GameMaster::Move() {

}

void GameMaster::Draw() {
	
}

//�X�^�[�g��ʂ�`��
void GameMaster::SetStartScene()
{
	DrawString(640, 540, "Input Space to Start Game", COLOR.WHITE);
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		status = MAIN_SCENE;
	}
}

void GameMaster::Update() {
	player->Update();
	progress_text->Update(); 
	DrawCircleAA(10, 20, 5, 32, COLOR.WHITE);
	collider_manager.Update();
	map->Update();
}

//��ʂ̘g��`��
void GameMaster::Drawing()
{
	player->Draw();
	
	progress_text->Draw();

	//3D�r���[�̊O�g
	DrawLineAA(50, 30, 1250, 30, COLOR.WHITE);
	DrawLineAA(1250, 30, 1250, 730, COLOR.WHITE);
	DrawLineAA(1250, 730, 50, 730, COLOR.WHITE);
	DrawLineAA(50, 730, 50, 30, COLOR.WHITE);
}

//�Q�[���̃��C����ʂ�`��
void GameMaster::SetMainScene()
{
	/*GM->Move();
	GM->Draw();*/
	GM->Update();
	Drawing();
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		status = CLEAR_SCENE;
	}
}

//�Q�[���̃N���A��ʂ�`��
void GameMaster::SetClearScene()
{
	DrawString(640, 540, "Clear", COLOR.WHITE);
	if (CheckHitKey(KEY_INPUT_T)) {
		status = START_SCENE;
	}
}

void GameMaster::Run() {
	while (!ProcessMessage()) {
		ClearDrawScreen();
		switch (status) {
		case START_SCENE:
			SetStartScene();
			break;
		case MAIN_SCENE:
			SetMainScene();
			break;
		case CLEAR_SCENE:
			SetClearScene();
			break;
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		ScreenFlip();
	}
}