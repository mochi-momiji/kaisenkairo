#include "Methods.h"

Ray2::Ray2(){}

Ray2::Ray2(VECTOR begin_, VECTOR end_)
{
	begin = begin_;
	end = end_;
}

Ray2::Ray2(VECTOR setBegin, VECTOR setEnd,int setColor)
{
	begin = setBegin;
	end = setEnd;
	color = setColor;
}

 void Ray2::With2p(VECTOR setBegin, VECTOR setEnd)
 {
	 begin = setBegin;
	 end = setEnd;
 }

 void Ray2::With2p(VECTOR setBegin, VECTOR setEnd,int setColor)
 {
	 begin = setBegin;
	 end = setEnd;
	 color = setColor;
 }

//��_����E�擾
VECTOR Intersection(Ray2 ray1, Ray2 ray2)
{
	//�e�����̎n�_�I�_����
	VECTOR A = VGet(ray1.getBegin().x, ray1.getBegin().y, NULL);
	VECTOR B = VGet(ray1.getEnd().x, ray1.getEnd().y, NULL);
	VECTOR C = VGet(ray2.getBegin().x, ray2.getBegin().y, NULL);
	VECTOR D = VGet(ray2.getEnd().x, ray2.getEnd().y, NULL);

	VECTOR clos = VGet(NULL, NULL, NULL);

	//---------��_���v�Z----------------------------------------------
	float cross = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	if (cross == 0.0f)
		return clos;

	float ACx = C.x - A.x;
	float ACy = C.y - A.y;


	float ABx = B.x - A.x;
	float ABy = B.y - A.y;

	//�}��ϐ����v�Z
	float t1 = ((D.y - C.y) * (C.x - A.x) - (D.x - C.x) * (C.y - A.y)) / cross;
	float t2 = ((B.y - A.y) * (A.x - C.x) - (B.x - A.x) * (A.y - C.y)) / cross;

	float x = A.x + t1 * ABx;
	float y = A.y + t1 * ABy;

	//��������
	if (t1 < MIN || t1 > MAX || t2 < MIN || t2 > MAX) {
		//�������ĂȂ��̂ŁA�l��Ԃ��Ȃ�
		return clos;
	}
	else {
		//�������Ă���̂Œl��Ԃ�
		return clos = VGet(x, y, NULL);
	}
}

//�l�̉����Ə���𐧌�
float Clump(float value, float min, float max)
{
	//�l�̉�����min�ɐ���
	if (value < min) {
		return min;
	}
	//�l�̏����max�ɐ���
	else if (value > max) {
		return max;
	}
	//���E�l�𒴂��ĂȂ���΂��̂܂܂̒l��Ԃ�
	else {
		return value;
	}
}

bool LineToCircle(VECTOR circle_center, Ray2 line, float circle_radius)
{
	VECTOR start_to_circle = VSub(circle_center, line.getBegin());
	VECTOR end_to_circle = VSub(circle_center, line.getEnd());
	VECTOR start_to_end = VSub(line.getBegin(), line.getEnd());

	float start_magnitude = sqrt(start_to_circle.x * start_to_circle.x
		+ start_to_circle.y * start_to_circle.y);

	float end_magnitude = sqrt(end_to_circle.x * end_to_circle.x + end_to_circle.y * end_to_circle.y);

	float line_magnitude = sqrt(start_to_end.x * start_to_end.x + start_to_end.y * start_to_end.y);

	if (start_magnitude < circle_radius || end_magnitude < circle_radius)
		return true;
	else
		return false;

	//�e�x�N�g����P�ʃx�N�g���ɂ���
	VECTOR normal_start = VGet(start_to_circle.x / start_magnitude,
		start_to_circle.y / start_magnitude,
		NULL);
	VECTOR normal_end = VGet(end_to_circle.x / end_magnitude
		, end_to_circle.y / end_magnitude,
		NULL);
	VECTOR normal_line = VGet(start_to_end.x / line_magnitude,
		start_to_end.y / line_magnitude,
		NULL);

	//�O�ς��v�Z
	float cross = normal_line.x * normal_start.y - normal_line.y * normal_start.x;

	//�O�ς̌��ʂ��~�̔��a��菬�����Ȃ�
	if (fabs(cross) < circle_radius)
		return true;
	else
		return false;

	float dot1 = normal_line.x * normal_start.x + normal_line.y * normal_start.y;
	float dot2 = normal_line.x * normal_end.x + normal_line.y * normal_end.y;

	if (dot1 * dot2 <= 0.0f) {
		return true;
	}
	return false;
}

int c = 0;

bool CheckHitKeyDown(int key_code) {
	if (CheckHitKey(key_code)) {
		c++;
		switch (c) {
		case 1:
			return true;
		default:
			return false;
		}
	}
	else {
		c = 0;
		return false;
	}
}