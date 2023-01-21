#include "stdafx.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Sum.h"
#include "NowLoading.h"
#include "BGM.h"
#include "GameStop.h"

GameClear::GameClear()
{
	gameStop = FindGO<GameStop>("gameStop");

	// BGM
	bgm = FindGO<BGM>("bgm");
	// 生成されていなかった時生成する
	if (bgm == nullptr) {
		bgm = NewGO<BGM>(0, "bgm");
		bgm->BGMState = 5;
		bgm->SetPlayBGM();
	}

	// 効果音
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");

	// 画像の読み込み
	spriteRender.Init("Assets/sprite/UI/gameClear.DDS",1920.0f, 1080.0f);
	spriteRender_hpSaved.Init("Assets/sprite/UI/result_hp.DDS", 92.0f, 106.0f);
	spriteRender_itemGet.Init("Assets/sprite/UI/result_item.DDS", 92.0f, 106.0f);
	spriteRender_passStage.Init("Assets/sprite/UI/result_stage.DDS", 92.0f, 106.0f);

	// スコアの計算を行う
	sum = NewGO<Sum>(0, "sum");
	sum->clearFlag = true;		// アイテムゲージの計算を行わないように止めておく
								// gameのデストラクタ内でも指定しているが念のため再度行う
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
	Font();						// リザルト画面の生成

	// 操作不能でないとき
	if (gameStop->StopFlag == false) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);					// Aボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする

			// ステージセレクトに戻る
			nowLoading = NewGO<NowLoading>(5, "nowLoading");
			nowLoading->loadState = 3;
			nowLoading->migrationToTitleFlag = true;

			deleteFlag = true;
		}
	}

	// 自身を削除する
	if (deleteFlag == true) {
		waitTimer -= g_gameTime->GetFrameDeltaTime();
		if (waitTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	// 更新
	spriteRender_itemGet.Update();
	spriteRender_hpSaved.Update();
	spriteRender_passStage.Update();
}

void GameClear::Font()
{
	// スコアを計算する
	Score = sum->CrearScore(itemSum, clearStage, HP);

	// 通過ステージ数
	{
		// STAGE
		fontRender_stage.SetText(L"PASS STAGE");
		fontRender_stage.SetPosition(-300.0f, 350.0f, 0.0f);
		fontRender_stage.SetScale(0.8f);
		fontRender_stage.SetColor(g_vec4Black);

		// 通過ステージ数の表示
		wchar_t stage[256];
		//桁数の指定
		swprintf_s(stage, 256, L"x %d", clearStage);
		fontRender_Sumstage.SetText(stage);
		fontRender_Sumstage.SetPosition(100.0f, 360.0f, 0.0f);
		fontRender_Sumstage.SetScale(1.0f);
		fontRender_Sumstage.SetColor(g_vec4Black);

		spriteRender_passStage.SetPosition({ 50.0f, 330.0f, 0.0f });
		spriteRender_passStage.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// 取得アイテム数
	{
		// Score
		fontRender_item.SetText(L"GET ITEM");
		fontRender_item.SetPosition(-300.0f, 240.0f, 0.0f);
		fontRender_item.SetScale(0.8f);
		fontRender_item.SetColor(g_vec4Black);

		// 通過ステージ数の表示
		wchar_t stage[256];
		//桁数の指定
		swprintf_s(stage, 256, L"x %d", itemSum);
		fontRender_Sumitem.SetText(stage);
		fontRender_Sumitem.SetPosition(100.0f, 250.0f, 0.0f);
		fontRender_Sumitem.SetScale(1.0f);
		fontRender_Sumitem.SetColor(g_vec4Black);

		spriteRender_itemGet.SetPosition({ 50.0f, 220.0f, 0.0f });
		spriteRender_itemGet.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// 残りHP (ボーナススコア)
	{
		// Score
		fontRender_hp.SetText(L"SAVED HP");
		fontRender_hp.SetPosition(-300.0f, 140.0f, 0.0f);
		fontRender_hp.SetScale(0.8f);
		fontRender_hp.SetColor(g_vec4Black);

		// 通過ステージ数の表示
		wchar_t stage[256];
		//桁数の指定
		swprintf_s(stage, 256, L"x %d", HP);
		fontRender_Sumhp.SetText(stage);
		fontRender_Sumhp.SetPosition(100.0f, 150.0f, 0.0f);
		fontRender_Sumhp.SetScale(1.0f);
		fontRender_Sumhp.SetColor(g_vec4Black);

		spriteRender_hpSaved.SetPosition({ 50.0f, 120.0f, 0.0f });
		spriteRender_hpSaved.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// 生存時間
	{
		// CLEAR TIME
		fontRender_time.SetText(L"CLEAR TIME");
		fontRender_time.SetPosition(-450.0f, -240.0f, 0.0f);
		fontRender_time.SetScale(1.0f);
		fontRender_time.SetColor(g_vec4Black);

		// 記録の表示
		wchar_t time[256];
		//桁数の指定
		swprintf_s(time, 256, L"%4.2fs", (float)clearTimer);
		fontRender_Cleartime.SetText(time);
		fontRender_Cleartime.SetPosition(150.0f, -200.0f, 0.0f);
		fontRender_Cleartime.SetScale(2.5f);
		fontRender_Cleartime.SetColor(g_vec4Black);
	}

	// 総合スコア
	{
		// Score
		fontRender_score.SetText(L"YOUR SCORE");
		fontRender_score.SetPosition(-450.0f, -80.0f, 0.0f);
		fontRender_score.SetScale(1.0f);
		fontRender_score.SetColor(g_vec4Black);

		// 総合スコアの表示
		wchar_t score[256];
		//桁数の指定
		swprintf_s(score, 256, L"%d", Score);
		fontRender_Sumscore.SetText(score);
		fontRender_Sumscore.SetPosition(150.0f, -40.0f, 0.0f);
		fontRender_Sumscore.SetScale(2.5f);
		fontRender_Sumscore.SetColor(g_vec4Black); 
	}
}

void GameClear::Render(RenderContext& rc)
{
	// 描画
	spriteRender.Draw(rc);
	spriteRender_hpSaved.Draw(rc);
	spriteRender_itemGet.Draw(rc);
	spriteRender_passStage.Draw(rc);
	// タイム
	fontRender_time.Draw(rc);
	fontRender_Cleartime.Draw(rc);
	// スコア
	fontRender_score.Draw(rc);
	fontRender_Sumscore.Draw(rc);
	// うちわけ
	fontRender_stage.Draw(rc);
	fontRender_Sumstage.Draw(rc);
	fontRender_item.Draw(rc);
	fontRender_Sumitem.Draw(rc);
	fontRender_hp.Draw(rc);
	fontRender_Sumhp.Draw(rc);
}