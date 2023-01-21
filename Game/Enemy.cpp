#include "stdafx.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "Num.h"
#include "Stage.h"
#include "Stage2.h"
#include "Sum.h"
#include <iostream>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start() 
{
	// ���C�g���[�X��؂�
	s_modelRender.SetRaytracingWorld(false);

	// �C���X�^���X��T��
	player = FindGO<Player>("player");
	num = FindGO<Num>("num");
	sum = FindGO<Sum>("sum");

	// �X�e�[�W�̏��
	if (num->stageState == 0) {
		stage = FindGO<Stage>("stage");
	}
	else {
		stage2 = FindGO<Stage2>("stage2");
	}

	// slimeRabbit
	s_animationClips[slime_AnimationClip_Idle].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Idle.tka");		// �ҋ@
	s_animationClips[slime_AnimationClip_Idle].SetLoopFlag(true);													// ���[�v����
	s_animationClips[slime_AnimationClip_Walk].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Move.tka");		// ����
	s_animationClips[slime_AnimationClip_Walk].SetLoopFlag(true);													// ���[�v����
	s_animationClips[slime_AnimationClip_Damage].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Damage.tka");		// ����
	s_animationClips[slime_AnimationClip_Damage].SetLoopFlag(false);
	s_animationClips[slime_AnimationClip_Dead].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Death.tka");		// ����
	s_animationClips[slime_AnimationClip_Dead].SetLoopFlag(false);
	// ���f���̓ǂݍ���
	s_modelRender.Init("Assets/modelData/model/enemy/SlimeRabbit/SlimeRabbit.tkm", s_animationClips, slime_AnimationClip_Num, enModelUpAxisZ);
	s_modelRender.SetScale(2.0f, 2.0f, 2.0f);

	num->enemyNum++;	// �G�l�~�[�̐��𑝂₷

	return true;
}

void Enemy::Update()
{
	m_Slime();
	PlayAnimation();

	// ���S�������I��������deleteGO
	if (s_modelRender.IsPlayingAnimation() == false && s_State == 2) {
		num->enemyNum--;	// �|�ꂽ�̂Ő������炷
		s_ItemNewGO();		// �A�C�e���𐶐�
		DeleteGO(this);
	}

	s_modelRender.SetPosition(s_position);
	s_modelRender.Update();
}

bool Enemy::s_IsMove(Vector2 movePos)
{
	// �ړ���̍��W��player�Əd�Ȃ��Ă��邩�ǂ����v�Z����
	bool isMove = true;	// �ړ��ł���

	// �v���C���[�̎��̍��W
	// �ړ��ł���H		
	// �ړ��悪������false��Ԃ�
	if (player->position2D.x == movePos.x && player->position2D.y == movePos.y) {
		isMove = false;
	}

	// �G�l�~�[
	//QueryGOs<Enemy>("slime", [&](Enemy* slime) {
	//	// �ړ��ł���H
	//	Vector2 enemyNextPos = slime->s_position2D;
	//	// �ړ��悪�G�l�~�[�Ɠ���
	//	if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
	//		isMove = false;
	//	}

	//	enemyNextPos.x += slime->s_NextMove[slime->s_moveCount].x;
	//	enemyNextPos.y += slime->s_NextMove[slime->s_moveCount].y;
	//	// �ړ��悪�G�l�~�[�̈ړ���Ɠ���
	//	if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
	//		isMove = false;
	//	}

	//	return true;
	//	});

	QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
		// �ړ��ł���H
		Vector2 enemyNextPos = mush->m_position2D;
		// �ړ��悪�G�l�~�[�Ɠ���
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		//enemyNextPos.x += mush->m_NextMove[mush->m_moveCount].x;
		//enemyNextPos.y += mush->m_NextMove[mush->m_moveCount].y;
		// �ړ��悪�G�l�~�[�̈ړ���Ɠ���
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		return true;
		});

	// �n�`����
	// �͈͊O�������� false ��Ԃ�
	if (movePos.x < 0.0f) {
		isMove = false;
	}
	if (movePos.x > num->stageNum - 1) {
		isMove = false;
	}
	if (movePos.y < 0.0f) {
		isMove = false;
	}
	if (movePos.y > num->stageNum - 1) {
		isMove = false;
	}


	switch (num->stageState) {
	case 0:
		// �n�`
		if (stage->stageFlag[(int)movePos.y][(int)movePos.x] == 1) {
			isMove = false;
		}
		break;
	case 1:
	case 2:
		// �n�`
		if (stage2->stageFlag[(int)movePos.y][(int)movePos.x] == 1) {
			isMove = false;
		}
		break;
	}

	return isMove;
}

void Enemy::s_ItemNewGO()
{
	// ���g�Ɠ����ʒu�ɃA�C�e���𐶐�����
	item = NewGO<Item>(0, "item");
	item->position = s_position;
	item->position.y = 20.0f;
}

void Enemy::m_Slime()
{
	// ��e�A�j���[�V�������͂����艺�͎��s���Ȃ�
	if (s_modelRender.IsPlayingAnimation() == true && s_State == 3) {
		return;
	}
	// ���S�A�j���[�V�������͉������Ȃ�
	if (s_State == 2) {
		return;
	}
	if (nowTurnEnd == true) {
		return;
	}

	// �����̃^�[���̎��ȊO�͓����Ȃ��悤�ɂ���
	if (num->turn == 2) {
		moveFlag = true;
	}
	else {
		moveFlag = false;
	}

	float moveSpeed = 50.0f;	// �ړ����x
	float forward[8] = { 90.0f,90.0f, 180.0f,180.0f, -90.0f,-90.0f, 0.0f,0.0f };	// ��]

	// �����̃^�[���̎�
	if (moveFlag == true) {

		// �ړ��\��n�̌v�Z
		Vector2 move = s_position2D;
		move.x += s_NextMove[s_moveCount].x;
		move.y += s_NextMove[s_moveCount].y;

		// �ړ����player�������璆�f����
		if (s_IsMove(move) == false) {
			nowTurnEnd = true;	// �����̃^�[�����I���������Ƃ�m�点��
			return;
		}

		s_State = 1;

		//���W�̈ړ�
		s_position.x += s_NextMove[s_moveCount].x * moveSpeed;
		s_position.z += s_NextMove[s_moveCount].y * -moveSpeed;	// ���f���ł͉��s����+�̂��߃}�C�i�X����Z����
		// �����̎w��
		s_rotation.SetRotationDegY(forward[s_moveCount]);
		s_forward.Set(s_NextMove[s_moveCount].x, s_NextMove[s_moveCount].y);	// ����
			
		// ��
		if (s_NextMove[s_moveCount].y < 0.0f) {
			s_MoveState = 1;
		}
		// �E
		if (s_NextMove[s_moveCount].x > 0.0f) {
			s_MoveState = 2;
		}
		// ��
		if (s_NextMove[s_moveCount].x < 0.0f) {
			s_MoveState = 3;
		}
		// ��
		if (s_NextMove[s_moveCount].y > 0.0f) {
			s_MoveState = 4;
		}

		NowPosition();	// ���݈ʒu�̍X�V

		nowTurnEnd = true;
	}
	else {
		s_State = 0;
	}

	// �ړ�����
	if (moveFlag == true) {
		// �J�E���g�𑝂₷
		s_moveCount++;
		// �J�E���g�����Z�b�g
		if (s_moveCount >= ((int)sizeof(s_NextMove) / (int)sizeof(Vector2)))
		{
			s_moveCount = 0;
		}
	}

	s_modelRender.SetRotation(s_rotation);	// ��]��������
	s_modelRender.SetPosition(s_position);	// ���W��������
}

void Enemy::s_Damege() 
{
	s_HP -= player->player_Attack;
	s_State = 3;

	if (s_HP <= 0) {
		s_State = 2;
	}
}

void Enemy::NowPosition()
{
	// ���W�̍X�V
	switch (s_MoveState) {
	case 1:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j - 1] = 1;
				}
				// �`���[�g���A���ȊO
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j - 1] = 1;
				}

				s_position2D.y -= 1.0f;
				s_MoveState = 0;
				return;
			}
		}
		break;
	case 2:
		// �E
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j + 1] = 1;
				}
				// �`���[�g���A���ȊO
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j + 1] = 1;
				}

				s_position2D.x += 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	case 3:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j - 1] = 1;
				}
				// �`���[�g���A���ȊO
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j - 1] = 1;
				}

				s_position2D.x -= 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	case 4:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i + 1][j] = 1;
				}
				// �`���[�g���A���ȊO
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i + 1][j] = 1;
				}

				s_position2D.y += 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	default:
		// ��L�ȊO�̎��͉������Ȃ�
		break;
	}
}

void Enemy::PlayAnimation()
{
	switch (s_State) {
	case 0:
		s_modelRender.PlayAnimation(slime_AnimationClip_Idle);		// �ҋ@
		break;
	case 1:
		s_modelRender.PlayAnimation(slime_AnimationClip_Walk);		// ����
		break;
	case 2:
		s_modelRender.PlayAnimation(slime_AnimationClip_Dead);		// ���S
		break;
	case 3:
		s_modelRender.PlayAnimation(slime_AnimationClip_Damage);	// ����
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	// �`��
	s_modelRender.Draw(rc);
}