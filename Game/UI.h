#pragma once
#include "Sum.h"

class Game;
class GameOver;
class Stage;
class Stage2;
class Player;
class GameCamera;
class NowLoading;
class Sum;
class Num;
// ユーザーインターフェース
class UI:public IGameObject 
{
public:
	UI();
	~UI();

	void Update();
	void Render(RenderContext& rc);
	void TurnCount();					// ターン数のカウント
	void TurnOne();
	void TurnTen();
	void ItemGage();
	void PlayerHP();					// HP
	void Camera();						// カメラ
	void Crear();						// ステージクリア

	// メンバ変数
	SpriteRender spriteRender_HP;		// HPバー
	SpriteRender spriteRender_help;		// ヘルプアイコン
	SpriteRender spriteRender_camera;	// カメラアイコン
	SpriteRender spriteRender_crear;	// クリア

	SpriteRender spriteRender_turn;		// 階層数
	SpriteRender spriteRender_countOne;
	SpriteRender spriteRender_countTen;

	SpriteRender spriteRender_itemgage;	// アイテムゲージ
	SpriteRender spriteRender_item;
	SpriteRender spriteRender_itemback;

	SpriteRender spriteRender_chat;		// キャラクターの画像
	FontRender fontRender_chat;			// テキスト


	Vector3 position_HP;				// HPバーの座標
	Vector3 position_help;				// ヘルプ
	Vector3 position_camera;			// カメラ
	Vector3 position_chat;				// 画像の位置

	Game* game;
	GameOver* gameover;
	Stage* stage;
	Stage2* stage2;
	Player* player;
	GameCamera* gameCamera;
	NowLoading* nowLoading;
	Sum* sum;
	Num* num;

	// スケール値を渡す
	void SetNowX(float x)
	{
		nowGage = x;
	}

	bool stopFlag = false;

	float i_Timer = 20.0f;				// アイテムゲージ用タイマー
	int UI_playerHP = 0;
	int UI_cameraState = 0;
	int UI_stageState = 0;
	int UI_stageNum = 1;				// ステージ数格納用
	int turn_one = 0;					// 1の位
	int turn_ten = 0;					// 10の位
	int itemSum = 0;					// 最終アイテム数
	int ChatState = 0;					// 会話ステート
	char chat[100];						// 会話内容
private:
	float nowGage = 0.0f;				// 現在のアイテムゲージ
};

