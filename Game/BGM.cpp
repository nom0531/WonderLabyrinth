#include "stdafx.h"
#include "BGM.h"
#include "sound/SoundEngine.h"

BGM::BGM()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Chose_Stage.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Stage_0.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/Stage_1.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/Stage_2.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Result.wav");
}

void BGM::SetPlayBGM()
{
	// nullptr時の生成に使用
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(BGMState);				// BGMの指定
	gameBGM->SetVolume(SetVolume);			// 音量
	gameBGM->Play(true);					// ループ
}

void BGM::ChangeBGM(int fileBank)
{
	// gameBGMが存在している時のみ削除する
	if (gameBGM != nullptr) {
		DeleteGO(gameBGM);
	}
	
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(fileBank);
	gameBGM->Play(true);					// ループ

	return;
}

void BGM::Update()
{
	// BGMを変更するフラグがtrueの時
	if (ChangeBGMFlag == true) {
		// ボリュームを変更する
		SetVolume += addVolume;				// 初期はマイナスの値を加算

		// 0.0f以下になったら切り替える
		if (SetVolume <= minVolume) {
			SetVolume = minVolume;			// 値を0.0fにする
			ChangeBGM(BGMState);			// BGMを切り替える
			addVolume *= -1.0f;				// ボリュームを加算するためにプラスの値にする
		}

		// 切り替わったらボリュームを上げる
		// 一定の値になったらフラグを降ろして元に戻す
		if (SetVolume >= maxVolume) {
			SetVolume = maxVolume;			// 値を0.8fにする
			addVolume *= -1.0f;				// ボリュームを加算するためにプラスの値にする
			ChangeBGMFlag = false;			// フラグを降ろす
		}

		gameBGM->SetVolume(SetVolume);		// 音量
	}
}

BGM::~BGM()
{
	DeleteGO(gameBGM);
}