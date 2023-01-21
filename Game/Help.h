#pragma once

class NowLoading;
class GameStop;

// ヘルプ
class Help:public IGameObject
{
public:
	Help();
	~Help();

	void Update();
	void Sprite();						// 画像処理
	void SetSprite();
	void Render(RenderContext& rc);

	// メンバ変数
	SpriteRender spriteRender_back;		// 背景
	SpriteRender spriteRender;			// 内容

	NowLoading* nowLoading;
	GameStop* gameStop;

	bool DeleteFlag = false;

	float animTimer = 2.0f;
	int spriteState = 0;				// 0:遊びかた 1:操作説明 2:アイコンの説明
};

