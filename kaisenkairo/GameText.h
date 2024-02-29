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

//ゲームテキストクラス
class CGameText : public CObject{

	VECTOR position;					//テキスト表示の座標
	VECTOR pos1 = VGet(50, 840, NULL);	//
	VECTOR pos2 = VGet(960, 840, NULL);
	std::unordered_map<const char*, int> font_color;//文字描画時の色

	const char* progress_log[LOG_LINE_VALUE] = {"a","b","c"};//プライヤーの進行ログ
	const char* tutorial[LOG_LINE_VALUE] =					//操作説明
	{
		"移動:Wキー(前方向)・Sキー(後方向)",
		"     Aキー(左方向)・Dキー(右方向)",
		"視点移動:マウス",
		"特殊ギミック:Eキー(ミニマップの開閉)",
		"             Rキー(ミニマップ内に敵を表示)"
	};
public:
	//コンストラクタ
	CGameText(VECTOR setPosition);

	virtual void Update();	//更新処理
	virtual void Draw();	//描画処理

	void SetProgressLog(const char* new_log);//進行ログの入れ替え
};