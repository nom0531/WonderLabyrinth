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
	// nullptr���̐����Ɏg�p
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(BGMState);				// BGM�̎w��
	gameBGM->SetVolume(SetVolume);			// ����
	gameBGM->Play(true);					// ���[�v
}

void BGM::ChangeBGM(int fileBank)
{
	// gameBGM�����݂��Ă��鎞�̂ݍ폜����
	if (gameBGM != nullptr) {
		DeleteGO(gameBGM);
	}
	
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(fileBank);
	gameBGM->Play(true);					// ���[�v

	return;
}

void BGM::Update()
{
	// BGM��ύX����t���O��true�̎�
	if (ChangeBGMFlag == true) {
		// �{�����[����ύX����
		SetVolume += addVolume;				// �����̓}�C�i�X�̒l�����Z

		// 0.0f�ȉ��ɂȂ�����؂�ւ���
		if (SetVolume <= minVolume) {
			SetVolume = minVolume;			// �l��0.0f�ɂ���
			ChangeBGM(BGMState);			// BGM��؂�ւ���
			addVolume *= -1.0f;				// �{�����[�������Z���邽�߂Ƀv���X�̒l�ɂ���
		}

		// �؂�ւ������{�����[�����グ��
		// ���̒l�ɂȂ�����t���O���~�낵�Č��ɖ߂�
		if (SetVolume >= maxVolume) {
			SetVolume = maxVolume;			// �l��0.8f�ɂ���
			addVolume *= -1.0f;				// �{�����[�������Z���邽�߂Ƀv���X�̒l�ɂ���
			ChangeBGMFlag = false;			// �t���O���~�낷
		}

		gameBGM->SetVolume(SetVolume);		// ����
	}
}

BGM::~BGM()
{
	DeleteGO(gameBGM);
}