#pragma once

class Player;
class Game;
class Enemy;
class Enemy2;
class Enemy3;
class Num;
//�Q�[���{��
class Stage2 :public IGameObject
{
public:
	Stage2();
	~Stage2();

	void Update();
	void Render(RenderContext& rc);
	void SetUp();
	void Stage();								// �X�e�[�W����
	bool Start();

	// �ÓI�����I�u�W�F�N�g
	PhysicsStaticObject physicsStaticObject;
	BoxCollider boxCollider;

	Player* player;
	Game* game;
	Enemy* slime;
	Enemy2* mush;

	Num* num;

	// �����o�ϐ�
	ModelRender modelRender[81];
	Vector3 position;
	Vector2 clearPosition2D = { 4.0f,0.0f };	// �N���A����p
	Vector2 objPos2D ;							// �ʉ߂ł���I�u�W�F�N�g���ǂ���

	bool clearFlag = false;						// �X�e�[�W�̃N���A����
	int texState = 0;							// �e�N�X�`���̔���
	int stageState = 0;							// �X�e�[�W����
	int stageFlag[9][9] = { 0 };				// 0:�ʉ߉� 1:�ʉߕs��
};
