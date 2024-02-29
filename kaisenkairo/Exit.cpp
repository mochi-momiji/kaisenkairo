#include "Exit.h"
//������

//�`�揈��
void Exit::Draw() {
	for (int i = 0; i < lines.size(); i++) {
		//DB.getSlidPosition() ==> �~�j�}�b�v�J�M�~�b�N�̈ړ���
		DrawLine(lines[i].getBegin().x + DB.getSlidPosition(), lines[i].getBegin().y,//�n�_���W
					lines[i].getEnd().x + DB.getSlidPosition(), lines[i].getEnd().y,//�I�_���W
					COLOR.WHITE	//������\������ۂ̐F
		);
	}
	DrawCircle(position.x, position.y, 5, color, TRUE);
}

void Exit::Loop() {
	//Player�ƏՓ˂��Ă���Ȃ�
	if (collider->getHitType() == ObjectType::PLAYER) {
		VECTOR player_pos = DB.getPlayerPosition();//Player�̍��W���擾
		VECTOR delta = VSub(position, player_pos);//Player=>Exit�̃x�N�g���𐶐�(Map�ړ���̍��W���Z�o���Ɏg�p)
		DB.UpdateDelta(delta);//Player�ŎQ�Ƃ��邽�߁A�ۑ�
		DB.UpdateStageId(next_stage_id);//�ړ���̃X�e�[�W����ۑ�
	}
	collider->Reset();
}

//�����蔻��E�`��p�̐������𐶐�
void UpExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(NONE, thickness, NONE));
	end = root;
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	end = VAdd(start, VGet(width, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(NONE, -thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	position = VAdd(end, VGet(-width / 2, NONE, NONE));
	collider = new LineCollider(lines,ObjectType::UP_EXIT);
}

void DownExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(NONE, width - thickness, NONE));
	end = VAdd(start, VGet(NONE, thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(width / 2, NONE, NONE));
	//
	end = VAdd(start, VGet(width, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(NONE, thickness, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::DOWN_EXIT);
}

void RightExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(width - thickness, NONE, NONE));
	end = VAdd(start, VGet(thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(NONE, width / 2, NONE));
	//
	end = VAdd(start, VGet(NONE, width, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::RIGHT_EXIT);
}

void LeftExit::PushLine(VECTOR root) {
	VECTOR start, end;
	Ray2 line;
	//
	start = VAdd(root, VGet(thickness, NONE, NONE));
	end = root;
	line.With2p(start, end, color);
	lines.emplace_back(line);
	position = VAdd(end, VGet(NONE, width / 2, NONE));
	//
	end = VAdd(start, VGet(NONE, width, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);
	//
	start = end;
	end = VAdd(start, VGet(-thickness, NONE, NONE));
	line.With2p(start, end, color);
	lines.emplace_back(line);

	collider = new LineCollider(lines, ObjectType::LEFT_EXIT);
}