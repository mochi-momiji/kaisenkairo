#include "Collider.h"
#include "DataBase.h"

extern ColliderManager collider_manager;

void ColliderManager::GetCollider(CircleCollider* collider) {
	switch (collider->getType()) {
	case ObjectType::PLAYER:
		player_collider = &*collider;
		break;
	case ObjectType::ENEMY:
		break;
	}
}

void ColliderManager::GetCollider(LineCollider *collider) {
	switch (collider->getType()) {
	case ObjectType::WALL:
		line_colliders[ObjectType::WALL] = &*collider;
		break;
	case ObjectType::UP_EXIT:
		line_colliders[ObjectType::UP_EXIT] = &*collider;
		break;
	case ObjectType::DOWN_EXIT:
		line_colliders[ObjectType::DOWN_EXIT] = &*collider;
		break;
	case ObjectType::RIGHT_EXIT:
		line_colliders[ObjectType::RIGHT_EXIT] = &*collider;
		break;
	case ObjectType::LEFT_EXIT:
		line_colliders[ObjectType::LEFT_EXIT] = &*collider;
		break;
	}
}

void ColliderManager::Update() {
	UpdateFlag(player_collider, line_colliders[ObjectType::UP_EXIT]); 
	UpdateFlag(player_collider, line_colliders[ObjectType::DOWN_EXIT]); 
	UpdateFlag(player_collider, line_colliders[ObjectType::RIGHT_EXIT]); 
	UpdateFlag(player_collider, line_colliders[ObjectType::LEFT_EXIT]); 
	UpdateFlag(player_collider, line_colliders[ObjectType::WALL]);
}




void ColliderManager::UpdateFlag(CircleCollider* collider01, CircleCollider* collider02) {
	if (CheckCollision(*collider01, *collider02)) {
		collider01->ChangeCircleFlag(collider02->getType());
		collider02->ChangeCircleFlag(collider01->getType());
		
	}
}

void ColliderManager::UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider) {
	if (CheckCollision(*cCollider, *lCollider)) {
		cCollider->ChangeLineFlag(lCollider->getType());
		lCollider->ChangeLineFlag(cCollider->getType());
		DrawCircle(500, 10, 30, COLOR.BLUE, TRUE);
	}
}

//�~�Ɖ~�̓����蔻��
bool ColliderManager::CheckCollision(const CircleCollider& collider01, const CircleCollider& collider02)
{
	VECTOR distance_vec = VSub(collider01.getPosition(), collider02.getPosition());
	float distance = VSize(distance_vec);

	if (distance < collider01.getRadius() + collider02.getRadius()) {
		return true;
	}
	return false;
}

//�~�Ɛ��̓����蔻��
bool ColliderManager::CheckCollision(const CircleCollider& circleCollider, const LineCollider& lineCollider){

	int circle_radius = circleCollider.getRadius();
	for (int i = 0; i < lineCollider.getLines().size(); i++) {
		Ray2 line = lineCollider.getLines()[i];
		VECTOR begin_to_center = VSub(circleCollider.getPosition(), line.getBegin());
		VECTOR end_to_centor = VSub(circleCollider.getPosition(), line.getEnd());
		VECTOR begin_to_end = VSub(line.getEnd(), line.getBegin());

		VECTOR normal_begin_to_end = VNorm(begin_to_end);
		VECTOR normal_begin_to_center = VNorm(begin_to_center);
		
		float cross = normal_begin_to_end.x * begin_to_center.y
					- normal_begin_to_end.y * begin_to_center.x;
		//��Βl�Ƃ��Ĉ����������߁A���̒l�Ȃ�}�C�i�X���|���Đ��̐��ɂ���
		cross = cross < 0 ? -cross : cross;
		
		//�O�ς̒l�����a�̒l�ȏ�̂Ƃ�
		if (cross >= circle_radius) {
			DrawCircle(430, 10, 30, COLOR.RED, TRUE);
			//�Փ˂��ĂȂ��̂Ŏ��̃��[�v�ɍs��
			continue;
		}

		float dot_01 = begin_to_center.x * begin_to_end.x + begin_to_center.y * begin_to_end.y;
		float dot_02 = end_to_centor.x * begin_to_end.x + end_to_centor.y * begin_to_end.y;
		
		//�n�_=>�~�̓��ςƏI�_=>�~�̓��ς��|�����l�����̒l�̂Ƃ�
		if (dot_01 * dot_02 <= NONE) {
			DrawCircle(460, 10, 30, COLOR.GREEN, TRUE);
			//�Փ˂��Ă���̂�true��Ԃ�
			return true;
		}

		//�n�_=>�~�̃x�N�g���̒����ƏI�_=>�~�̃x�N�g���̒����̂ǂ��炩���~�̔��a�ȏ�̂Ƃ�
		if (VSize(begin_to_center) > circle_radius
			|| VSize(end_to_centor) > circle_radius) {
			DrawCircle(490, 10, 30, COLOR.BLUE, TRUE);
			//�Փ˂��Ă��Ȃ��̂Ŏ��̃��[�v�ɍs��
			continue;
		}
		DrawCircle(520, 10, 30, COLOR.PURPLE, TRUE);
		return true;
	}
	DrawCircle(400, 10, 30, COLOR.YELLOW, TRUE);
	return false;
}
