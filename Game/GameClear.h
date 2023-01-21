#pragma once
#include "sound/SoundSource.h"

class Sum;
class NowLoading;
class BGM;
class GameStop;

// ゲームクリア
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();

	void Update();
	void Font();					// 文字の出力
	void Render(RenderContext& rc);

	// メンバ変数
	SpriteRender spriteRender;
	SpriteRender spriteRender_hpSaved;
	SpriteRender spriteRender_itemGet;
	SpriteRender spriteRender_passStage;
	// クリアタイム
	FontRender fontRender_time;
	FontRender fontRender_Cleartime;
	// ステージ数
	FontRender fontRender_stage;
	FontRender fontRender_Sumstage;
	// アイテム数
	FontRender fontRender_item;
	FontRender fontRender_Sumitem;
	// HP
	FontRender fontRender_hp;
	FontRender fontRender_Sumhp;
	// 総合スコア
	FontRender fontRender_score;
	FontRender fontRender_Sumscore;

	BGM* bgm;
	Sum* sum;
	GameStop* gameStop;
	NowLoading* nowLoading;

	// スコアを設定する (時間,ステージ数,アイテム数 残りHP)
	void setClearNum(float t, int s, int i,int h) {
		clearTimer = t;
		clearStage = s;
		itemSum = i;
		HP = h;
	}

	float waitTimer = 2.0f;		// タイマー
	bool deleteFlag = false;

	int Score = 0;					// スコア格納用変数

private:
	float clearTimer = 0.0f;	// クリアタイム
	int clearStage = 0;			// 通過ステージ数
	int itemSum = 0;			// アイテム数
	int HP = 0;					// 残りHP
};

