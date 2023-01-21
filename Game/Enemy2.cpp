#include "stdafx.h"
#include "Enemy2.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "Num.h"
#include "Stage.h"
#include "Stage2.h"
#include "Sum.h"

Enemy2::Enemy2()
{

}

Enemy2::~Enemy2()
{

}

bool Enemy2::Start() {
	// ���C�g���[�X��؂�
	m_modelRender.SetRaytracingWorld(false);

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

	// mushroomMan
	m_animationClips[mush_AnimationClip_Idle].Load("Assets/animData/MushroomManAnim/MushroomMonster_Idle.tka");		// �ҋ@
	m_animationClips[mush_AnimationClip_Idle].SetLoopFlag(true);													// ���[�v����
	m_animationClips[mush_AnimationClip_Walk].Load("Assets/animData/MushroomManAnim/MushroomMonster_Walk.tka");		// ����
	m_animationClips[mush_AnimationClip_Walk].SetLoopFlag(true);													// ���[�v����
	m_animationClips[mush_AnimationClip_Attack].Load("Assets/animData/MushroomManAnim/MushroomMonster_Attack.tka");	// �U��
	m_animationClips[mush_AnimationClip_Attack].SetLoopFlag(false);													// ���[�v�Ȃ�
	m_animationClips[mush_AnimationClip_Damege].Load("Assets/animData/MushroomManAnim/MushroomMonster_Damage.tka");	// ����
	m_animationClips[mush_AnimationClip_Damege].SetLoopFlag(false);
	m_animationClips[mush_AnimationClip_Dead].Load("Assets/animData/MushroomManAnim/MushroomMonster_Death.tka");	// ����
	m_animationClips[mush_AnimationClip_Dead].SetLoopFlag(false);
	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/model/enemy/MushroomMan/MushroomMan.tkm", m_animationClips, mush_AnimationClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(0.4f, 0.4f, 0.4f);

	num->enemyNum++;	// �G�l�~�[�̐��𑝂₷

	return true;
}

void Enemy2::Update()
{
	m_Mush();
	PlayAnimation();						// �A�j���[�V����

	// �U���A�j���[�V�������I�������Ƃ�
	if (m_modelRender.IsPlayingAnimation() == false && m_State == 2) {
		num->turn = 1;	// player�̃^�[���ɂ���
		m_State = 0;	// �ҋ@���[�V�����ɖ߂�
	}

	// ���S�������I��������deletego
	if (m_modelRender.IsPlayingAnimation() == false && m_State == 3) {
		num->enemyNum--;	// �|�ꂽ�̂Ő������炷
		m_ItemNewGO();		// �A�C�e���𐶐�
		DeleteGO(this);
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy2::PlayAnimation()
{
	switch (m_State) {
	case 0:
		m_modelRender.PlayAnimation(mush_AnimationClip_Idle);		// �ҋ@
		break;
	case 1:
		m_modelRender.PlayAnimation(mush_AnimationClip_Walk);		// ����
		break;
	case 2:
		m_modelRender.PlayAnimation(mush_AnimationClip_Attack);		// �U��
		break;
	case 3:
		m_modelRender.PlayAnimation(mush_AnimationClip_Dead);		// �|�ꂽ
		break;
	case 4:
		m_modelRender.PlayAnimation(mush_AnimationClip_Damege);		// ��e
		break;
	}
}

bool Enemy2::Search()
{
	bool flag = false;

	// �v���C���[�����g�̌����Ɠ�����ɂ���Ƃ�
	switch (m_ForwardState) {
	case 1:
		// �����
		if (player->position2D.x == m_position2D.x &&
			player->position2D.y <= m_position2D.y &&
			player->position2D.y >= m_position2D.y - 3.0f) {
			flag = true;
		}
		break;
	case 2:
		// �E����
		if (player->position2D.y == m_position2D.y &&
			player->position2D.x >= m_position2D.x &&
			player->position2D.x <= m_position2D.x + 3.0f) {
			flag = true;
		}
		break;
	case 3:
		// ������
		if (player->position2D.y == m_position2D.y &&
			player->position2D.x <= m_position2D.x &&
			player->position2D.x >= m_position2D.x - 3.0f) {
			flag = true;
		}
		break;
	case 4:
		// ������
		if (player->position2D.x == m_position2D.x &&
			player->position2D.y >= m_position2D.y &&
			player->position2D.y <= m_position2D.y + 3.0f) {
			flag = true;
		}
		break;
	}

	return flag;
}

void Enemy2::m_ItemNewGO()
{
	// ���g�Ɠ����ʒu�ɃA�C�e���𐶐�����
	item = NewGO<Item>(0, "item");
	item->position = m_position;
	item->position.y = 20.0f;
}

void Enemy2::m_Mush()
{
	// ���쓙���~����悤�ɂ��Ă���Ƃ��͈ȉ��̏����͍s��Ȃ�
	if (num->stopFlag == true) {
		return;
	}

	// ��e�A�j���[�V�������͂����艺�͎��s���Ȃ�
	if (m_modelRender.IsPlayingAnimation() == true && m_State == 4) {
		return;
	}
	// ���S�A�j���[�V�������͉������Ȃ�
	if (m_State == 3) {
		return;
	}
	// ���g�̃^�[�����I�����Ă���Ƃ��������Ȃ�
	if (nowTurnEnd == true) {
		return;
	}

	if (num->turn == 2) {
		moveFlag = true;
	}
	else {
		moveFlag = false;
	}

	float moveSpeed = 50.0f;		// �ړ����x

	// �����̃^�[���̎�
	if (moveFlag == true) {
		m_moveCount++;

		
		// �ʏ�p�^�[��
		if (searchFlag == false) {
			m_State = 0;
			m_MoveState = 0;
			// ���̏��2�^�[�����Ƃɉ�]����
			if (m_moveCount >= 0 && m_moveCount <= 2) {
				// �E��]
				m_RotState = 2;
			}
			else if (m_moveCount >= 3 && m_moveCount <= 5) {
				// ����]
				m_RotState = 4;
			}
			else if (m_moveCount >= 6 && m_moveCount <= 8) {
				// ����]
				m_RotState = 3;
			}
			else if (m_moveCount >= 9 && m_moveCount <= 11) {
				// ���]
				m_RotState = 1;

				if (m_moveCount == 10) {
					// �J�E���g�����Z�b�g
					m_moveCount = 0;
				}
			}

			// ���G
			if (Search() == true) {
				searchFlag = true;
			}
		}
		// �v���C���[����������
		if (searchFlag == true) {
			m_State = 1;

			// �אڂ��Ă���Ƃ�
			if (m_IsJoin() == true) {
				if (attackWaitFlag == true) {
					attackWaitFlag = false;
				}
				else {
					m_Attack();		// �U������
				}
			}
			else {

				Chase(moveSpeed);

			}
		}

		m_Rot();					// ��]�̌v�Z�����s����
		NowPosition();							// �񎟌��z���̍��W
		nowTurnEnd = true;
	}
	else {
		m_State = 0;
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
}

void Enemy2::Chase(float moveSpeed) {

	// player��ǂ�������
	Vector3 toPlayer = player->position - m_position;

	// ��Βl�ő召���v�Z����
	// x���߂��Ƃ�
	if (abs(toPlayer.x) > abs(toPlayer.z)) {
		// ���E�ǂ�����
		if (toPlayer.x > 0.0f) {
			// �E
			Vector2 movePos = m_position2D;
			movePos.x += 1.0f;

			if (m_IsMove(movePos) == true) {
				m_position.x += moveSpeed;
				m_MoveState = 2;

				m_RotState = 2;		// ��]������������

				return;
			}
		}
		else {
			// ��
			Vector2 movePos = m_position2D;
			movePos.x -= 1.0f;

			if (m_IsMove(movePos) == true) {
				m_position.x -= moveSpeed;
				m_MoveState = 3;

				m_RotState = 3;		// ��]������������

				return;
			}
		}
	}

	// z���߂��Ƃ�
	// �㉺�ǂ�����
	if (toPlayer.z > 0.0f) {
		// �O
		Vector2 movePos = m_position2D;
		movePos.y -= 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.z += moveSpeed;
			m_MoveState = 1;

			m_RotState = 1;		// ��]������������

			return;
		}

	}
	else if (toPlayer.z < 0.0f) {
		// ��
		Vector2 movePos = m_position2D;
		movePos.y += 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.z -= moveSpeed;
			m_MoveState = 4;

			m_RotState = 4;		// ��]������������

			return;
		}
	}

	// ���E�ǂ�����
	if (toPlayer.x > 0.0f) {
		// �E
		Vector2 movePos = m_position2D;
		movePos.x += 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.x += moveSpeed;
			m_MoveState = 2;

			m_RotState = 2;		// ��]������������

			return;
		}
	}
	else if (toPlayer.x < 0.0f) {
		// ��
		Vector2 movePos = m_position2D;
		movePos.x -= 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.x -= moveSpeed;
			m_MoveState = 3;

			m_RotState = 3;		// ��]������������

			return;
		}
	}

}

void Enemy2::m_Rot()
{
	switch (m_RotState) {
	case 1:
		// ���]
		m_rotation.SetRotationDegY(0.0f);
		m_forward.Set(0, -1);		// ���ʂ�ݒ�
		m_ForwardState = 1;			// ���ʂ̃X�e�[�g��ݒ�
		break;
	case 2:
		// �E��]
		m_rotation.SetRotationDegY(90.0f);
		m_forward.Set(1, 0);		// ���ʂ�ݒ�
		m_ForwardState = 2;			// ���ʂ̃X�e�[�g��ݒ�
		break;
	case 3:
		// ����]
		m_rotation.SetRotationDegY(-90.0f);
		m_forward.Set(-1, 0);		// ���ʂ�ݒ�
		m_ForwardState = 3;			// ���ʂ̃X�e�[�g��ݒ�
		break;
	case 4:
		// ����]
		m_rotation.SetRotationDegY(-180.0f);
		m_forward.Set(0, 1);		// ���ʂ�ݒ�
		m_ForwardState = 4;			// ���ʂ̃X�e�[�g��ݒ�
		break;
	}
}

void Enemy2::m_Attack()
{
	// �U������
	m_State = 2;

	player->Damege(m_enemy_Attack);



	// �U���ꏊ���v�Z
	Vector2 attackPos = m_position2D;		// �G�l�~�[�̑O�����v�Z����
	attackPos.x += m_forward.x;
	attackPos.y += m_forward.y;
}

bool Enemy2 :: m_IsJoin()
{
	bool flag = false;

	//�אڂ��Ă���true
	// �E����
	if (m_position2D.x + 1.0f == player->position2D.x &&
		m_position2D.y == player->position2D.y) {
		m_RotState = 2;		// ��]������������
		flag = true;
	}
	// ������
	if (m_position2D.x - 1.0f == player->position2D.x &&
		m_position2D.y == player->position2D.y) {
		m_RotState = 3;		// ��]������������
		flag = true;
	}
	// �O���� (��)
	if (m_position2D.y + 1.0f == player->position2D.y &&
		m_position2D.x == player->position2D.x) {
		m_RotState = 4;		// ��]������������
		flag = true;
	}
	// ������ (��O)
	if (m_position2D.y - 1.0f == player->position2D.y &&
		m_position2D.x == player->position2D.x) {
		m_RotState = 1;		// ��]������������
		flag = true;
	}

	return flag;
}

bool Enemy2::m_IsMove(Vector2 movePos)
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
	QueryGOs<Enemy>("slime", [&](Enemy* slime) {
		// �ړ��ł���H
		Vector2 enemyNextPos = slime->s_position2D;
		// �ړ��悪�G�l�~�[�Ɠ���
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		enemyNextPos.x += slime->s_NextMove[slime->s_moveCount].x;
		enemyNextPos.y += slime->s_NextMove[slime->s_moveCount].y;
		// �ړ��悪�G�l�~�[�̈ړ���Ɠ���
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		return true;
		});

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


void Enemy2 :: m_Damege()
{
	// player�ɍU�����ꂽ����e
	m_HP -= player->player_Attack;
	m_State = 4;

	if (searchFlag == false) {
		searchFlag = true;
		attackWaitFlag = true;
	}

	if (m_HP <= 0) {
		m_State = 3;
	}
}

void Enemy2::NowPosition()
{
	// ���W�̍X�V
	switch (m_MoveState) {
	case 1:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i - 1][j] = 1;

					m_position2D.y -= 1.0f;
					m_MoveState = 0;		// �ǂ̕����Ɉړ��������w�肷��ϐ������Z�b�g����

					return;
				}
			}
		}
		break;
	case 2:
		// �E
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i][j + 1] = 1;

					m_position2D.x += 1.0f;
					m_MoveState = 0;		// �ǂ̕����Ɉړ��������w�肷��ϐ������Z�b�g����

					return;
				}
			}
		}
		break;
	case 3:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i][j - 1] = 1;

					m_position2D.x -= 1.0f;
					m_MoveState = 0;		// �ǂ̕����Ɉړ��������w�肷��ϐ������Z�b�g����

					return;
				}
			}
		}
		break;
	case 4:
		// ��
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i + 1][j] = 1;

					m_position2D.y += 1.0f;
					m_MoveState = 0;		// �ǂ̕����Ɉړ��������w�肷��ϐ������Z�b�g����

					return;
				}
			}
		}
		break;
	default:
		// ��L�ȊO�̎��͉������Ȃ�
		break;
	}
}

void Enemy2::Render(RenderContext& rc)
{
	// �`��
	m_modelRender.Draw(rc);
}