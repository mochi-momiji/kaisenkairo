#pragma once
#include "DxLib.h"
#include "Methods.h"
#include <unordered_map>
#include <vector>
//�I�u�W�F�N�g�̖���
enum class ObjectType {
	NON,
	PLAYER,
	ENEMY,
	WALL,
	UP_EXIT,
	DOWN_EXIT,
	RIGHT_EXIT,
	LEFT_EXIT,
};
//�����蔻��̊�{���
class ColliderBase {
	ObjectType type;
	ObjectType hit_type = ObjectType::NON;
	bool is_hit_circle = false;
	bool is_hit_line = false;
public:
	ColliderBase(ObjectType setType = ObjectType::NON) {
		type = setType;
	}

	ObjectType getType() { return type; }
	ObjectType getHitType() {return hit_type; }
	bool getIsHitCircle() { return is_hit_circle; }
	bool getIsHitLine() { return is_hit_line; }

	void ChangeCircleFlag(ObjectType otherType) {
		is_hit_circle = true;
		hit_type = otherType;
	}
	void ChangeLineFlag(ObjectType otherType) {
		is_hit_line = true;
		hit_type = otherType;
	}

	void Reset() {
		is_hit_circle = false;
		is_hit_line = false; 
		hit_type = ObjectType::NON;
	}
};
//�~�̓����蔻��R���C�_�[
class CircleCollider : public ColliderBase {
	VECTOR position = VGet(0,0,0);	//���S���W
	int radius = 0;			//���a
public:
	//�R���X�g���N�^
	CircleCollider(){}
	CircleCollider(VECTOR setPos, int setRad, ObjectType setType = ObjectType::NON)
		: ColliderBase(setType)
	{
		position = setPos;
		radius = setRad;
	}

	void UpdatePosition(VECTOR newPos) {
		position = newPos;
	}

	inline VECTOR getPosition()const  { return position; }
	inline int getRadius() const { return radius; }
};
//���̓����蔻��R���C�_�[
class LineCollider : public ColliderBase {
	std::vector<Ray2> lines;	//�������(�n�_�E�I�_�E�F)
public:
	//�R���X�g���N�^
	LineCollider(){}
	LineCollider(std::vector<Ray2> setLines,ObjectType setType = ObjectType::NON)
		: ColliderBase(setType) 
	{
		lines = setLines;
	}

	void UpdateLines(std::vector<Ray2> newLines){
		lines = newLines;
	}

	inline std::vector<Ray2> getLines() const { return lines; }
};

class ColliderManager {
	friend CircleCollider;
	friend LineCollider;
private:
	CircleCollider *player_collider, *enemy_collider;
	std::unordered_map<ObjectType, LineCollider*> line_colliders;
	
public:
	void GetCollider(CircleCollider *collider);	//�I�u�W�F�N�g�̉~�R���C�_��z��ɕۑ�
	void GetCollider(LineCollider *collider);	//�I�u�W�F�N�g�̐��R���C�_��z��ɕۑ�
	void Update();								//�e�R���C�_�̍X�V����
	void UpdateFlag(CircleCollider* collider01, CircleCollider* collider02);//�~�Ɖ~�̏Փ˃t���O�̃`�F�b�N
	
	void UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider);	//�~�Ɛ��̏Փ˃t���O�̃`�F�b�N
	//�~�Ɖ~�̓����蔻�菈��
	bool CheckCollision(const CircleCollider& collider01, const CircleCollider& collider02);
	//�~�Ɛ��̓����蔻��
	bool CheckCollision(const CircleCollider& circleCollider, const LineCollider& lineCollider);
};

extern ColliderManager collider_manager;