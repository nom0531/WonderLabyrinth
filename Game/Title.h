#pragma once
#include"sound/SoundSource.h"

class NowLoading;
class BGM;
class GameStop;

// タイトル
class Title :public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void Render(RenderContext& rc);
	void Anim();// アニメーション

	// メンバ変数
	SpriteRender spriteRender;
	SpriteRender spriteRender_button;	// ボタン

	// NewGO用
	NowLoading* nowloading;
	BGM* bgm;
	GameStop* gameStop;

	bool DeleteFlag = false;			// 削除するかどうか

	float animTimer = 2.0f;				// タイマー
	int animState = 0;					// 遷移
};

