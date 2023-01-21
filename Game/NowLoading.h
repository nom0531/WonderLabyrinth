#pragma once
class Title;
class Game;
class StageSelect;
class GameClear;
class Sum;
class Help;
class Num;
class BGM;
class GameStop;

// ロード
class NowLoading:public IGameObject
{
public:
	NowLoading();
	~NowLoading();

	void Update();
	void Render(RenderContext& rc);

	void NewScene();

	bool Start();

	// メンバ変数
	SpriteRender spriteRender_back;	// 背景

	// NewGO
	Title* title;				// タイトル
	Game* game;					// game本編
	StageSelect* stageselect;	// ステージセレクト
	GameClear* gameClear;		// リザルト
	Help* help;					// 説明書

	BGM* bgm;
	Sum* sum;
	Num* num;
	GameStop* gameStop;

	float LoadTimer = 2.0f;
	float  animTimer = 2.0f;
	float alpha = 0.0f;			// 背景のα値
	int loadState = 0;			// 1:ゲーム本編 2:タイトル 3:ステージ選択 4:説明書
	int stageState = 0;			// ステージの指定

	bool makeFlag = false;
	bool migrationToTitleFlag = false;		// 説明以外から移行したときにタイトルのBGMを減らす
	bool NOTchangeBGMFlag = false;		// BGMを変更しない

	// スコア格納用
	float Cleartime = 0.0f;

	// スコア用変数
	int Itemnum = 0;
	int Stagenum = 0;
	int HPnum = 0;

	bool waitFlag = false;
	int waitFlame = 2;
};

