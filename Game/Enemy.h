#pragma once

class Player;
class Game;
class Item;
class Num;
class Stage;
class Stage2;
class Sum;
class Enemy2;

// スライム
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
	void NowPosition();					// 0:マップ全体 1:現在の位置
	void PlayAnimation();				// アニメーション
	void Render(RenderContext& rc);

	// メンバ変数
	ModelRender s_modelRender;
	Vector3 s_position;							// 座標
	Vector2 s_position2D;
	Vector2 s_NextMove[8] = { {1.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{0.0f,1.0f},{-1.0f,0.0f},{-1.0f,0.0f},{0.0f,-1.0f},{0.0f,-1.0f} };
	//Vector2 s_NextMove[1] = { {0.0f,0.0f}};
	Vector2 s_forward;							// 正面
	Quaternion s_rotation = Quaternion::Identity;	// クォータニオン
	SpotLight s_spotLight;						// スポットライト

	Player* player;								// プレイヤー
	Game* game;
	Item* item;									// アイテム
	Num* num;									// 数値管理用クラス
	Stage* stage;								// ステージ
	Stage2* stage2;
	Sum* sum;									// 計算用
	Enemy2* mush;

	// slimeRabbit
	enum slime_AnimationClip {
		slime_AnimationClip_Idle,				// 待機
		slime_AnimationClip_Walk,				// 歩く
		slime_AnimationClip_Damage,				// 被弾
		slime_AnimationClip_Dead,				// やられ
		slime_AnimationClip_Num,
	};

	AnimationClip s_animationClips[slime_AnimationClip_Num];

	bool moveFlag = false;						// 移動フラグ
	bool ssearchFlag = false;					// 索敵フラグ
	int s_HP = 2;
	/// <summary>
	/// enemyの状態
	/// 0:待機
	/// 1:歩く
	/// 2:死亡
	/// 3:被弾
	/// </summary>
	int s_State = 0;							
	int s_moveCount = 0;						// 移動カウント

	int s_position_stage[5][5] = { 0 };			// 現在の座標
	int s_position_stage2[9][9] = { 0 };		// 現在の座標
	int s_MoveState = 0;						// 1:上 2:右 3:左 4:下

	bool nowTurnEnd = false;
};