#pragma once
#include "DxLib.h"
#include "VirtualClass.h"

//�����\��
class Enemy :CObject {
	VECTOR position;

public:
	//�Q�b�^�[
	VECTOR GetPosition() { return position; }
	//�ړ�����
	void Move();

};
