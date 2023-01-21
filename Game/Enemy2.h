#pragma once

class Player;
class Game;
class Item;
class Num;
class Stage;
class Stage2;
class Enemy;
class Sum;

// マッシュルーム
class Enemy2:public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	bool Start();

	void Update();
	void m_Mush();						// エネミーの移動処理
	void m_ItemNewGO();
	void m_Rot();						// 回転
	void m_Damege();					// ダメージ計算
	void m_Attack();					// 攻撃計算
	bool m_IsMove(Vector2 movePos);
	bool m_IsJoin();					// 隣接したときの処理
	bool Search();						// 敵対処理
	void Chase(float moveSpeed);		// 追尾
	void NowPosition();					// 0:マップ全体 1:現在の位置
	void PlayAnimation();				// アニメーション
	void Render(RenderContext& rc);

	// メンバ変数
	ModelRender m_modelRender;
	Vector3 m_position;							// 座標
	Vector2 m_forward;							// 正面
	Vector2 m_position2D;
	Quaternion m_rotation = Quaternion::Identity;	// クォータニオン
	SpotLight m_spotLight;						// スポットライト

	Player* player;								// プレイヤー
	Game* game;
	Item* item;									// アイテム
	Num* num;									// 数値管理用
	Stage* stage;								// ステージ
	Stage2* stage2;
	Sum* sum;									// 計算用
	Enemy* slime;

	// mushroomMan
	enum mush_AnimationClip {
		mush_AnimationClip_Idle,				// 待機
		mush_AnimationClip_Walk,				// 歩く
		mush_AnimationClip_Attack,				// 攻撃
		mush_AnimationClip_Damege,				// やられ
		mush_AnimationClip_Dead,				// やられ
		mush_AnimationClip_Num,
	};
	AnimationClip m_animationClips[mush_AnimationClip_Num];


	bool moveFlag = false;						// 移動フラグ
	bool searchFlag = false;					// 索敵フラグ
	bool positionFlag = false;					// 座標フラグ
	bool attackFlag = false;					// 攻撃フラグ
	bool attackWaitFlag = false;				// 攻撃するのを待つ

	bool nowTurnEnd = false;					// 現在のターンが終了したかどうか

	int m_enemy_Attack = 1;						// 攻撃力
	int m_HP = 2;								// HP
	/// <summary>
	/// enemyの状態
	/// 0:待機
	/// 1:歩く
	/// 2:攻撃
	/// 3:死亡
	/// 4:被弾
	/// </summary>
	int m_State = 0;
	int m_moveCount = 0;						// 移動カウント

	int m_position_stage[9][9] = { 0 };			// 現在の座標
	int m_MoveState = 0;						// 1:上移動 2:右移動 3:左移動 4:下移動
	int m_ForwardState = 0;						// 1:上方向 2:右方向 3:左方向 4:下方向
	int m_RotState = 0;							// 1:上回転 2:右回転 3:左回転 4:下回転
};

