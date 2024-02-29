#include "View.h"


VECTOR View::CheckMinDistanceWall(Ray2 viewRay, VECTOR playerPos, int& color) {
	std::vector<Ray2> map_lines = DB.getMapLine();	//map�̐������̃R�s�[
	VECTOR min_dist_cross = VGet(NULL, NULL, NULL);//�ŒZ�����̌�_�̍��W
	float min_dist = 0;//�ŒZ����
	float is_first = true;//��ڂ̌�_���̃t���O
	//map�̐�������for���ň�{���m�F���čs��
	for (int i = 0; i < map_lines.size(); i++) {
		VECTOR cross_pos = Intersection(map_lines[i], viewRay);//���E����̐���map�̐����Ƃ̌�_
		VECTOR distance_vec = VSub(cross_pos, playerPos);//Player=>��_�̃x�N�g��
		float distance //Player=>��_�̋���
			= sqrt(distance_vec.x * distance_vec.x + distance_vec.y * distance_vec.y);
		//��_���������Ă����Ȃ�
		if (cross_pos.x != NULL && cross_pos.y != NULL) {
			//��ڂ̌�_�Ȃ�
			if (is_first) {
				min_dist = distance;	//��Ƃ��邽�߂ɋ����̍ŏ��l�̒l�ɑ������
				min_dist_cross = cross_pos;//��Ƃ��邽�߂ɍŒZ�����̌�_�̒l�ɑ������
				color = map_lines[i].getColor();//��ԋ߂���_���X�V���ꂽ��`�悷������̐F���X�V
				is_first = false;	//�ȍ~�̌�_�͈�ڂł͂Ȃ��̂Ńt���O��؂�
			}
			//��ڈȍ~�̌�_ ���@�ۑ����ꂽ�ŒZ�������Z���Ȃ�
			else if (!is_first && distance < min_dist) {
				min_dist_cross = cross_pos;//�ŒZ�����̌�_�̍��W���X�V
				min_dist = distance;	//�ŒZ�����̒l���X�V
				color = map_lines[i].getColor();//��ԋ߂���_���X�V���ꂽ��`�悷������̐F���X�V
			}
		}
	}
	return min_dist_cross;
}


void View::Draw(const VECTOR& playerPos, const double& playerAngle) {
	double left_angle = playerAngle - M_PI_4;	//��`�̍��[�̊p�x
	double right_angle = playerAngle + M_PI_4;	//��`�̉E�[�̊p�x
	int line_num = FIRST_INDEX;					//�������̐������{�ڂȂ̂���ۑ�
	//��`�̎���͈͂�W�J
	for (double angle = left_angle; angle < right_angle; angle += M_PI_2 / ray_num) {
		//����̐����̏I�_���Z�o
		VECTOR end_pos = VAdd(playerPos, VGet(cos(angle) * range, sin(angle) * range, 0));
		Ray2 view_ray(playerPos, end_pos);//���씻��̐���
		int color = COLOR.WHITE;			//�`�掞�̐F
		//�ł��߂���_���Z�o
		VECTOR min_dist_cross = CheckMinDistanceWall(view_ray, playerPos, color);
		//��_���Ȃ��Ȃ�
		if (min_dist_cross.x == NULL && min_dist_cross.y == NULL) {
			min_dist_cross = view_ray.getEnd();//����̐����̏I�_����
		}
		//��_������Ȃ�
		else {
			VECTOR distance_vec = VSub(min_dist_cross, playerPos);//Player => �ŒZ�����̌�_�̃x�N�g��
			float distance = VSize(distance_vec) * cos(angle - playerAngle);//��L�̃x�N�g���̒���
			float view_height = Clump(8000 / distance, NONE, 700);//�`�悷����̒���
			//��l�̎��_�̕`�揈��
			DrawFPSView(line_num, color,view_height);
		}
		//Player�̎���̐����̕`�揈��
		DrawViewRenge(playerPos, min_dist_cross);
		line_num++;
	}
}

void View::DrawViewRenge(VECTOR playerPos, VECTOR crossPos) {
	Ray2 sight(playerPos, crossPos, COLOR.WHITE);
	int slid_pos = DB.getSlidPosition();

	//�������ŕ`��
	DrawLineAA(sight.getBegin().x + slid_pos, sight.getBegin().y,
		sight.getEnd().x + slid_pos, sight.getEnd().y,
		sight.getColor());
}

void View::DrawFPSView(int lineNum, int color, float viewHeight) {;

	VECTOR view_root = VGet(50, 380, NONE);//�`������̍��W�̊
	VECTOR line_begin = VAdd(view_root, VGet(4 * lineNum, -viewHeight / 2, NONE));//�n�_
	VECTOR line_end = VAdd(line_begin, VGet(NONE, viewHeight, NONE));//�I�_
	//�����̕`��֐�
	DrawLineAA(line_begin.x, line_begin.y, line_end.x, line_end.y, color);
}