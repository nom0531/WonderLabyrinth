#pragma once
#include "sound/SoundSource.h"

// BGM�Đ��p
class BGM:public IGameObject
{
public:
	BGM();
	~BGM();

	void SetPlayBGM();					// BGM�̐ݒ�
	void ChangeBGM(int fileBank);		// BGM��ύX����
	void ChangeVolume();
	void Update();

	SoundSource* gameBGM;				// BGM

	/// <summary>
	/// BGM�����[�h����
	/// 0:title
	/// 1:choose
	/// 2:Tutorial
	/// 3:stage_1
	/// 4:stage_2
	/// 5:Result
	/// </summary>
	int BGMState = 0;

	bool ChangeBGMFlag = false;		// ���ʂ�ύX���邩�ǂ���

	float SetVolume = 0.8f;				// ���ʂ�ύX����ׂ̕ϐ�
	float addVolume = -0.05f;			// ���Z�E���Z�l

	const float maxVolume = 0.8f;		// ���ʂ̍ő�l
	const float minVolume = 0.0f;		// ���ʂ̍ŏ��l
};

