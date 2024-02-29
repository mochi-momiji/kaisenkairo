#include "Scene.h"


void StartScene::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		status = PLAY;
	}
}

void StartScene::Draw() {
	DrawString(640, 540, "Input Space to Start Game", COLOR.WHITE);
}

void PlayScene::Update() {

}

void PlayScene::Draw() {

}

void ClearScene::Update() {

}

void ClearScene::Draw() {

}