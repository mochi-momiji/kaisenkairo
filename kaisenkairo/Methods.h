#pragma once
#include "DxLib.h"
#include "Color.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define FIRST_INDEX 0
#define NONE 0
#define MAX 1.0f
#define MIN 0.0f
#define HALF_DEG 180

//�����N���X
class Ray2 {
	VECTOR begin = VGet(0, 0, 0);	//�n�_���W
	VECTOR end = VGet(0, 0, 0);		//�I�_���W
	int color = GetColor(255, 255, 255);	//�����̐F

public:
	//�R���X�g���N�^
	Ray2();//�l���w�肵�Ȃ��ꍇ
	Ray2(VECTOR setBegin, VECTOR setBnd);//�������l���w�肷��ꍇ
	Ray2(VECTOR setBegin, VECTOR setEnd, int setColor);

	//�Q�b�^�[
	inline VECTOR getBegin() { return begin; }	//�n�_��n��
	inline VECTOR getEnd() { return end; }		//�I�_��n��
	inline int getColor() { return color; }	//�����̐F��n��
	
	void With2p(VECTOR setBegin, VECTOR setEnd);//���ɐ������������̎n�_�Ǝ�_������������
	void With2p(VECTOR setBegin, VECTOR setEnd,int setColor);//���ɐ������������̎n�_�Ǝ�_������������
};

VECTOR Intersection(Ray2 ray1, Ray2 ray2);	//��_�̍��W���Z�o

float Clump(float value, float min, float max);//�l�̏���Ɖ����Ő�������

bool CheckHitKeyDown(int key_code);	//�L�[���������u�Ԃ����𔻒肷��