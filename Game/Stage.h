#pragma once

class Player;
class Enemy;
class Enemy2;
class Enemy3;
class Num;
// チュートリアル
class Stage :public IGameObject
{
public:
	Stage();
	~Stage();

	void Update();
	void SetUp();
	void Render(RenderContext& rc);
	void StageZero();								// チュートリアル用
	bool Start();

	// 静的物理オブジェクト
	PhysicsStaticObject physicsStaticObject;
	BoxCollider boxCollider;

	Player* player;
	Enemy* slime;
	Enemy2* mush;
	Num* num;

	// メンバ変数
	ModelRender modelRender[25];
	Vector3 position;
	Vector2 clearPosition2D = { 2.0f,0.0f };		// ゴールの座標

	int stageFlag[5][5] = { 0 };					// 0:通過可 1:通過不可
};