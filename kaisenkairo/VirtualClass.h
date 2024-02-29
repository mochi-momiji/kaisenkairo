#pragma once
#include "DxLib.h"
#include "Color.h"
#include"DataBase.h"
#include <list>

//�ړ���O��Ƃ����I�u�W�F�N�g�̉��z�֐�
class CObject {
protected:
	VECTOR position;	//���S���W
	double angle = 0;	//�����Ă���p�x
	int color = COLOR.WHITE;//�`�掞�̐F
public:
	//�R���X�g���N�^
	CObject(VECTOR setPos, int setAngle = 0) {
		position = setPos;
		angle = setAngle;
	}
	//�f�X�g���N�^
	~CObject() {}

	int getColor() { return color; }

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class ObjectManager {

};
