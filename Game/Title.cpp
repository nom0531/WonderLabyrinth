#include "stdafx.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "NowLoading.h"
#include "BGM.h"
#include "GameStop.h"

Title::Title()
{
	// 操作停止用クラスを作成
	gameStop = FindGO<GameStop>("gameStop");
	// nullptrの時に生成する
	if (gameStop == nullptr) {
		gameStop = NewGO<GameStop>(0, "gameStop");
	}

	// BGM
	bgm = FindGO<BGM>("bgm");

	if (bgm == nullptr) {
		bgm = NewGO<BGM>(0, "bgm");
		bgm->BGMState = 0;
		bgm->SetPlayBGM();
	}

	// 効果音
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/Pluse_Button.wav");

	// 初期画像
	spriteRender.Init("Assets/sprite/UI/title.DDS", 1920.0f, 1080.0f);

	spriteRender_button.Init("Assets/sprite/UI/button_black.DDS", 56.0f, 48.0f);
	spriteRender_button.SetPosition({ -400.0f, -100.0f, 0.0f });
}

Title::~Title()
{
}

void Title::Update()
{
	Anim();
	
	if (DeleteFlag == true) {
		animTimer -= g_gameTime->GetFrameDeltaTime();
		if (animTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	spriteRender.Update();
	spriteRender_button.Update();
}

void Title::Anim()
{
	switch (animState) {
	case 0:
		// ステージセレクト
		spriteRender_button.SetPosition({ -300.0f, -70.0f, 0.0f });
		// 操作不能になっていないとき
		if (gameStop->StopFlag == false) {
			// ↓キーを押したとき
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				animState = 1;

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// 十字キー
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする
			}

			// Bボタンを押したとき
			if (g_pad[0]->IsTrigger(enButtonB)) {
				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// Bボタン
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする

				// ロード
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 3;

				DeleteFlag = true;
			}
		}
		break;
	case 1:
		// 操作説明
		spriteRender_button.SetPosition({ -300.0f, -250.0f, 0.0f });
		// 操作不能になっていないとき
		if (gameStop->StopFlag == false) {
			// ↑キーを押したとき
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				animState = 0;
					
				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// 十字キー
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする
			}

			// Bボタンを押したとき
			if (g_pad[0]->IsTrigger(enButtonB)) {
				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// Bボタン
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする

				// ロード
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 4;

				DeleteFlag = true;
			}
		}
		break;
	}
}

void Title::Render(RenderContext& rc) 
{
	spriteRender.Draw(rc);
	spriteRender_button.Draw(rc);
}