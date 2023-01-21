#pragma once
#include"sound/SoundSource.h"

class NowLoading;
class Stage;
class Num;
class BGM;
class GameStop;

// ステージセレクト
class StageSelect:public IGameObject
{
public:
	StageSelect();
	~StageSelect();

	void Update();
	void Select();						// 画像の切り替え
	void Transition();					// 画面の遷移を行う
	void Render(RenderContext& rc);

	bool Start();

	// メンバ変数
	SpriteRender spriteRender;
	SpriteRender spriteRender_text;
	SpriteRender spriteRender_sprite;
	SpriteRender spriteRender_button;	// ボタン

	SoundSource* selectBGM;				// BGM

	// NewGO
	NowLoading* nowloading;				// LOADING画面
	Stage* stage;						// ステージ
	BGM* bgm;							// BGM
	GameStop* gameStop;

	bool DeleteFlag = false;			// 削除するかどうか

	float alpha = 0.0f;					// 透明度

	int selectState = 0;				// 0:チュートリアル 1:草原 (洞窟は派生)
	int stageState = 0;					// 判別用ステート

	float animTimer = 2.0f;				// タイマー
};

