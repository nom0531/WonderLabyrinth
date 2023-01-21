#pragma once
#include"sound/SoundSource.h"

class BackGround;
class Stage;
class Stage2;		//平原
//Player関連
class Player;
class GameCamera;
class Enemy;		//slime
class Enemy2;		//mushroom
class Item;
//UI関連
class UI;
class GameCrear;
class GameClear;
class NowLoading;
class Help;
class Chat;
class BGM;

class Sum;
class Num;
//ゲーム
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void s_Light();			//スポットライト
	void p_Light();			//ポイントライト
	void TurnCount();		//ターン数
	void Crear();			//CLEARの処理
	void StageZero();		//配置①
	void StageOne();		//配置②
	void StageTwo();		//配置③
	void Render(RenderContext& rc);

	// ゲームを本当に終わるとき用
	void GameEnd();

	void GameDelete();

	// メンバ変数
	FontRender fontRender;
	SpotLight spotLight;		// スポットライト
	SpotLight spotLight_enemy;	// スポットライト
	SpotLight spotLight_item;	// スポットライト
	PointLight pointLight;		// ポイントライト
	Vector3 player_position;	// playerの座標

	SkyCube* skyCube;		// スカイキューブ
	SoundSource* gameBGM;	// BGM

	// NewGO用
	BackGround* backGround;	// 背景
	Stage* stage;			// ステージ
	Stage2* stage2;			// ステージ
	Player* player=nullptr;			// プレイヤー
	GameCamera* gameCamera;	// カメラ
	UI* ui;					// UI
	Help* help;				// ヘルプ
	GameCrear* gamecrear;	// ゲームクリア
	GameClear* gameClear;	// クリア画面
	NowLoading* nowLoading;
	Chat* chat;

	BGM* bgm;

	Sum* sum;				// 計算用
	Num* num;				// 数値管理用

	/// <summary>
	/// Chatクラスの画像を表示したかどうか一度だけ判別する
	/// 引数は bool型
	/// </summary>
	/// <param name="false">表示していない</param>
	/// <param name="true">表示している</param>
	void setDrawFlag(bool a) {
		drawFlag = a;
	}

	// システム用
	float animTimer = 1.0f;

	bool drawFlag = false;				// 会話用画像を表示したかどうか
	bool TitleNewGO = false;			// タイトルを生成したかどうか
	bool ResultNewGO = false;			// リザルトを生成したかどうか
	bool CountFlag = false;				// 階層のカウントを制御する

	// ゲーム内数値
	float Timer = 0.0f;					// クリアタイム
	bool DeleteFlag = false;			// 削除するかどうか

	float p_scale = 50.0f;				// ポイントライトの大きさ
	bool nowLoadingMake = false;
};