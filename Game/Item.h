#pragma once

class Player;
class Sum;
class Num;
class Stage;
class Stage2;
// アイテム
class Item :public IGameObject
{
public:
	Item();
	~Item();

	void Update();
	void Rot();					// 回転処理
	void Get();					// 獲得処理
	void Render(RenderContext& rc);

	// メンバ変数
	ModelRender modelRender;

	Quaternion rot;
	Vector3 position;			// 座標

	Player* player;				// プレイヤー
	Sum* sum;					// 計算用
	Num* num;					// 数値管理用
	Stage* stage;				// ステージ
	Stage2* stage2;
};

