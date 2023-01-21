#include "stdafx.h"
#include "StageSelect.h"
#include "NowLoading.h"
#include "BGM.h"
#include "GameStop.h"

StageSelect::StageSelect()
{
	gameStop = FindGO<GameStop>("gameStop");

	// BGM
	bgm = FindGO<BGM>("bgm");

	if (bgm == nullptr) {
		bgm = NewGO<BGM>(0, "bgm");
		bgm->BGMState = 1;
		bgm->SetPlayBGM();
	}

	// 効果音
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/Pluse_Button.wav");

	// 画像読み込み
	spriteRender.Init("Assets/sprite/UI/stageSelect.DDS", 1920.0f, 1080.0f);
	spriteRender_text.Init("Assets/sprite/UI/stageSelect_text1.DDS", 634.0f, 68.0f);
	spriteRender_button.Init("Assets/sprite/UI/button_black.DDS", 56.0f, 48.0f);

	// ステージ画像
	spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_a.DDS", 734.0f, 527.0f);

	// ボタンの初期位置
	spriteRender_button.SetPosition({ 200.0f,85.0f,0.0f });
}

bool StageSelect::Start()
{
	return true;
}

StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
	Select();	// 画像の切り替え

	// 自身を削除する
	if (DeleteFlag == true) {
		animTimer -= g_gameTime->GetFrameDeltaTime();
		// タイマーが 0 になったときに削除する
		if (animTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	// スプライトの座標を決定する
	spriteRender_sprite.SetPosition({ -350.0f, 70.0f, 0.0f });
	spriteRender_text.SetPosition({ -330.0f, -315.0f, 0.0f });
	// 更新
	spriteRender.Update();
	spriteRender_text.Update();
	spriteRender_sprite.Update();
	spriteRender_button.Update();
}

void StageSelect::Select()
{
	switch (stageState) {
	case 0:
		// 画像読み込み
		spriteRender_text.Init("Assets/sprite/UI/stageSelect_text1.DDS", 634.0f, 68.0f);
		// ステージ画像
		spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_a.DDS", 734.0f, 527.0f);

		// ボタンの位置設定
		spriteRender_button.SetPosition({ 200.0f,85.0f,0.0f });

		if (gameStop->StopFlag == false) {
			// 下ボタンを押したとき
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				stageState = 1;

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// 十字キー
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする
			}

			// チュートリアルを生成
			if (g_pad[0]->IsTrigger(enButtonB)) {
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 1;		// ゲーム画面をロードする
				nowloading->stageState = 0;		// チュートリアル

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// Bボタン
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする

				DeleteFlag = true;
			}
		}
		break;
	case 1:
		// 画像読み込み
		spriteRender_text.Init("Assets/sprite/UI/stageSelect_text2.DDS", 634.0f, 68.0f);
		// ステージ画像
		spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_b.DDS", 734.0f, 527.0f);
		// ボタンの位置設定
		spriteRender_button.SetPosition({ 200.0f,-90.0f,0.0f });

		if (gameStop->StopFlag == false) {
			// 上ボタンを押したとき
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				stageState = 0;

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// 十字キー
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする
			}

			// ゲーム本編を生成
			if (g_pad[0]->IsTrigger(enButtonB)) {
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 1;		// ゲーム画面をロードする
				nowloading->stageState = 1;		// ゲーム本編

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// Bボタン
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする

				DeleteFlag = true;
			}
		}
		break;
	}

	// 操作不能になっていないとき
	if (gameStop->StopFlag == false) {
		// タイトルに戻る
		if (g_pad[0]->IsTrigger(enButtonA)) {
			nowloading = NewGO<NowLoading>(5, "nowloading");
			nowloading->loadState = 2;

			// BGMを差し替える処理
			nowloading->migrationToTitleFlag = true;

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);						// Aボタン
			se->Play(false);					// ループしない
			se->SetVolume(3.5f);				// 音量の設定をする

			DeleteFlag = true;
		}
	}
}

void StageSelect::Transition()
{
	alpha += g_gameTime->GetFrameDeltaTime();		// 透明度を加算する
	spriteRender_sprite.SetMulColor({ 1.0f,1.0f,1.0f,alpha });
}

void StageSelect::Render(RenderContext& rc)
{
	// 描画
	spriteRender.Draw(rc);
	spriteRender_text.Draw(rc);
	spriteRender_sprite.Draw(rc);
	spriteRender_button.Draw(rc);
}