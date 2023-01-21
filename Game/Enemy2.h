#pragma once

class Player;
class Game;
class Item;
class Num;
class Stage;
class Stage2;
class Enemy;
class Sum;

// �}�b�V�����[��
class Enemy2:public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	bool Start();

	void Update();
	void m_Mush();						// �G�l�~�[�̈ړ�����
	void m_ItemNewGO();
	void m_Rot();						// ��]
	void m_Damege();					// �_���[�W�v�Z
	void m_Attack();					// �U���v�Z
	bool m_IsMove(Vector2 movePos);
	bool m_IsJoin();					// �אڂ����Ƃ��̏���
	bool Search();						// �G�Ώ���
	void Chase(float moveSpeed);		// �ǔ�
	void NowPosition();					// 0:�}�b�v�S�� 1:���݂̈ʒu
	void PlayAnimation();				// �A�j���[�V����
	void Render(RenderContext& rc);

	// �����o�ϐ�
	ModelRender m_modelRender;
	Vector3 m_position;							// ���W
	Vector2 m_forward;							// ����
	Vector2 m_position2D;
	Quaternion m_rotation = Quaternion::Identity;	// �N�H�[�^�j�I��
	SpotLight m_spotLight;						// �X�|�b�g���C�g

	Player* player;								// �v���C���[
	Game* game;
	Item* item;									// �A�C�e��
	Num* num;									// ���l�Ǘ��p
	Stage* stage;								// �X�e�[�W
	Stage2* stage2;
	Sum* sum;									// �v�Z�p
	Enemy* slime;

	// mushroomMan
	enum mush_AnimationClip {
		mush_AnimationClip_Idle,				// �ҋ@
		mush_AnimationClip_Walk,				// ����
		mush_AnimationClip_Attack,				// �U��
		mush_AnimationClip_Damege,				// ����
		mush_AnimationClip_Dead,				// ����
		mush_AnimationClip_Num,
	};
	AnimationClip m_animationClips[mush_AnimationClip_Num];


	bool moveFlag = false;						// �ړ��t���O
	bool searchFlag = false;					// ���G�t���O
	bool positionFlag = false;					// ���W�t���O
	bool attackFlag = false;					// �U���t���O
	bool attackWaitFlag = false;				// �U������̂�҂�

	bool nowTurnEnd = false;					// ���݂̃^�[�����I���������ǂ���

	int m_enemy_Attack = 1;						// �U����
	int m_HP = 2;								// HP
	/// <summary>
	/// enemy�̏��
	/// 0:�ҋ@
	/// 1:����
	/// 2:�U��
	/// 3:���S
	/// 4:��e
	/// </summary>
	int m_State = 0;
	int m_moveCount = 0;						// �ړ��J�E���g

	int m_position_stage[9][9] = { 0 };			// ���݂̍��W
	int m_MoveState = 0;						// 1:��ړ� 2:�E�ړ� 3:���ړ� 4:���ړ�
	int m_ForwardState = 0;						// 1:����� 2:�E���� 3:������ 4:������
	int m_RotState = 0;							// 1:���] 2:�E��] 3:����] 4:����]
};

