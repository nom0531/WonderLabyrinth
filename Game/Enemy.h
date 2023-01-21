#pragma once

class Player;
class Game;
class Item;
class Num;
class Stage;
class Stage2;
class Sum;
class Enemy2;

// �X���C��
class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void m_Slime();
	void s_ItemNewGO();
	void s_Damege();
	bool s_IsMove(Vector2 movePos);
	void NowPosition();					// 0:�}�b�v�S�� 1:���݂̈ʒu
	void PlayAnimation();				// �A�j���[�V����
	void Render(RenderContext& rc);

	// �����o�ϐ�
	ModelRender s_modelRender;
	Vector3 s_position;							// ���W
	Vector2 s_position2D;
	Vector2 s_NextMove[8] = { {1.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{0.0f,1.0f},{-1.0f,0.0f},{-1.0f,0.0f},{0.0f,-1.0f},{0.0f,-1.0f} };
	//Vector2 s_NextMove[1] = { {0.0f,0.0f}};
	Vector2 s_forward;							// ����
	Quaternion s_rotation = Quaternion::Identity;	// �N�H�[�^�j�I��
	SpotLight s_spotLight;						// �X�|�b�g���C�g

	Player* player;								// �v���C���[
	Game* game;
	Item* item;									// �A�C�e��
	Num* num;									// ���l�Ǘ��p�N���X
	Stage* stage;								// �X�e�[�W
	Stage2* stage2;
	Sum* sum;									// �v�Z�p
	Enemy2* mush;

	// slimeRabbit
	enum slime_AnimationClip {
		slime_AnimationClip_Idle,				// �ҋ@
		slime_AnimationClip_Walk,				// ����
		slime_AnimationClip_Damage,				// ��e
		slime_AnimationClip_Dead,				// ����
		slime_AnimationClip_Num,
	};

	AnimationClip s_animationClips[slime_AnimationClip_Num];

	bool moveFlag = false;						// �ړ��t���O
	bool ssearchFlag = false;					// ���G�t���O
	int s_HP = 2;
	/// <summary>
	/// enemy�̏��
	/// 0:�ҋ@
	/// 1:����
	/// 2:���S
	/// 3:��e
	/// </summary>
	int s_State = 0;							
	int s_moveCount = 0;						// �ړ��J�E���g

	int s_position_stage[5][5] = { 0 };			// ���݂̍��W
	int s_position_stage2[9][9] = { 0 };		// ���݂̍��W
	int s_MoveState = 0;						// 1:�� 2:�E 3:�� 4:��

	bool nowTurnEnd = false;
};