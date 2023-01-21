#include "stdafx.h"
#include "Help.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "NowLoading.h"
#include "GameStop.h"

Help::Help()
{
	gameStop = FindGO<GameStop>("gameStop");

	// 効果音
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/Pluse_ButtonToHelpOnly.wav");

	spriteRender.Init("Aseets/sprite/UI/option_0.DDS", 1920, 1080);
}

Help::~Help()
{
}

void Help::Update()
{
	// 操作不能になっていないとき
	if (gameStop->StopFlag == false) {
		Sprite();	// 画像の遷移

		// Aボタンを押したとき戻る
		if (g_pad[0]->IsTrigger(enButtonA)) {
			nowLoading = NewGO<NowLoading>(5, "nowLoading");
			nowLoading->loadState = 2;

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);					// Aボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする

			DeleteFlag = true;
		}
	}

	if (DeleteFlag == true) {
		animTimer -= g_gameTime->GetFrameDeltaTime();
		if (animTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	spriteRender.Update();
}

void Help::Sprite()
{
	switch (spriteState) {
	case 0:
		SetSprite();

		// ゲームのあそび方
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			spriteState = 1;

			SetSprite();

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// 十字ボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする
		}
		break;
	case 1:
		// 操作説明
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			spriteState = 0;

			SetSprite();

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// 十字ボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする
		}
		else if (g_pad[0]->IsTrigger(enButtonRight)) {
			spriteState = 2;

			SetSprite();

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// 十字ボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする
		}
		break;
	case 2:
		// アイコンの説明
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			spriteState = 1;

			SetSprite();

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// 十字ボタン
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする
		}
		break;
	}
}

void Help::SetSprite()
{
	switch (spriteState) {
	case 0:
		spriteRender.Init("Assets/sprite/UI/option_0.DDS", 1920, 1080);
		break;
	case 1:
		spriteRender.Init("Assets/sprite/UI/option_1.DDS", 1920, 1080);
		break;
	case 2:
		spriteRender.Init("Assets/sprite/UI/option_2.DDS", 1920, 1080);
		break;
	}

	return;
}

void Help::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}