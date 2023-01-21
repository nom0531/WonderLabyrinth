#pragma once

class Player;
class Enemy;
class Enemy2;
class Enemy3;
class Num;
// �`���[�g���A��
class Stage :public IGameObject
{
public:
	Stage();
	~Stage();

	void Update();
	void SetUp();
	void Render(RenderContext& rc);
	void StageZero();								// �`���[�g���A���p
	bool Start();

	// �ÓI�����I�u�W�F�N�g
	PhysicsStaticObject physicsStaticObject;
	BoxCollider boxCollider;

	Player* player;
	Enemy* slime;
	Enemy2* mush;
	Num* num;

	// �����o�ϐ�
	ModelRender modelRender[25];
	Vector3 position;
	Vector2 clearPosition2D = { 2.0f,0.0f };		// �S�[���̍��W

	int stageFlag[5][5] = { 0 };					// 0:�ʉ߉� 1:�ʉߕs��
};