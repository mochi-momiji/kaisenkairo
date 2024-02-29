#pragma once
#include "DxLib.h"
#include "VirtualClass.h"

class Scene {
protected:
	//ÉQÅ[ÉÄÇÃèÛë‘
	static enum SceneStatus {
		START,
		PLAY,
		CLEAR,
	};
	static SceneStatus status;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class StartScene :public Scene {
private:
public:
	StartScene()
		:Scene()
	{}

	virtual void Update();
	virtual void Draw();
};

class PlayScene :public Scene {
public:
	PlayScene()
		:Scene()
	{}

	virtual void Update();
	virtual void Draw();
};

class ClearScene :public Scene {
public:
	ClearScene()
		:Scene()
	{}
	
	virtual void Update();
	virtual void Draw();
};