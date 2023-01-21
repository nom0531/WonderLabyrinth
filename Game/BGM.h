#pragma once
#include "sound/SoundSource.h"

// BGM再生用
class BGM:public IGameObject
{
public:
	BGM();
	~BGM();

	void SetPlayBGM();					// BGMの設定
	void ChangeBGM(int fileBank);		// BGMを変更する
	void ChangeVolume();
	void Update();

	SoundSource* gameBGM;				// BGM

	/// <summary>
	/// BGMをロードする
	/// 0:title
	/// 1:choose
	/// 2:Tutorial
	/// 3:stage_1
	/// 4:stage_2
	/// 5:Result
	/// </summary>
	int BGMState = 0;

	bool ChangeBGMFlag = false;		// 音量を変更するかどうか

	float SetVolume = 0.8f;				// 音量を変更する為の変数
	float addVolume = -0.05f;			// 加算・減算値

	const float maxVolume = 0.8f;		// 音量の最大値
	const float minVolume = 0.0f;		// 音量の最小値
};

