#pragma once

class Player;
class Game;
class Enemy;
class Enemy2;
class Enemy3;
class Num;
//ゲーム本編
class Stage2 :public IGameObject
{
public:
	Stage2();
	~Stage2();

	void Update();
	void Render(RenderContext& rc);
	void SetUp();
	void Stage();								// ステージ生成
	bool Start();

	// 静的物理オブジェクト
	PhysicsStaticObject physicsStaticObject;
	BoxCollider boxCollider;

	Player* player;
	Game* game;
	Enemy* slime;
	Enemy2* mush;

	Num* num;

	// メンバ変数
	ModelRender modelRender[81];
	Vector3 position;
	Vector2 clearPosition2D = { 4.0f,0.0f };	// クリア判定用
	Vector2 objPos2D ;							// 通過できるオブジェクトかどうか

	bool clearFlag = false;						// ステージのクリア判定
	int texState = 0;							// テクスチャの判別
	int stageState = 0;							// ステージ判別
	int stageFlag[9][9] = { 0 };				// 0:通過可 1:通過不可
};
