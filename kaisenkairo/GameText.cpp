#include "GameText.h"

CGameText::CGameText(VECTOR setPosition)
	:CObject(setPosition)
{
	const char* string[] = { "White","Green","Yellow","Red" };
	font_color[string[0]] = GetColor(255, 255, 255);
	font_color[string[1]] = GetColor(0, 255, 0);
	font_color[string[2]] = GetColor(255, 255, 0);
	font_color[string[3]] = GetColor(0, 0, 255);
}

void CGameText::Update() {
	if (DB.getMoveLength() == 200) {
		SetProgressLog("ザザァ....");
	}
}

void CGameText::Draw()
{
	VECTOR sentence_pos;
	for (int i = 0; i < LOG_LINE_VALUE; i++) {
		sentence_pos = VAdd(pos1, VGet(NONE, NEXT_LINE * i, NULL));
		DrawFormatString(sentence_pos.x, sentence_pos.y, font_color["White"], 
							"%s", (TCHAR*)progress_log[i]);

		sentence_pos = VAdd(pos2, VGet(NONE, NEXT_LINE * i, NULL));
		DrawFormatString(sentence_pos.x, sentence_pos.y, font_color["Yellow"],
							"%s", (TCHAR*)tutorial[i]);
	}

	//ログ01表示の外枠
	DrawLineAA(50, 800, 900, 800, COLOR.WHITE);
	DrawLineAA(900, 800, 900, 1080, COLOR.WHITE);
	DrawLineAA(50, 800, 50, 1080, COLOR.WHITE);
	DrawString(50, 800, "ログ01", COLOR.WHITE);

	//ログ02表示の外枠
	DrawLineAA(960, 800, 1910, 800, COLOR.WHITE);
	DrawLineAA(1910, 800, 1910, 1080, COLOR.WHITE);
	DrawLineAA(960, 800, 960, 1080, COLOR.WHITE);
	DrawString(960, 800, "ログ02", COLOR.WHITE);
}

void CGameText::SetProgressLog(const char* new_log) {
	const char* tmp1 = progress_log[0];
	progress_log[0] = new_log;
	const char* tmp2 = progress_log[1];

	progress_log[1] = tmp1;
	progress_log[2] = tmp2;
}