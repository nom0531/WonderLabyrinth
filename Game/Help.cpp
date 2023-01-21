#include "stdafx.h"
#include "Help.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "NowLoading.h"
#include "GameStop.h"

Help::Help()
{
	gameStop = FindGO<GameStop>("gameStop");

	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/Pluse_ButtonToHelpOnly.wav");

	spriteRender.Init("Aseets/sprite/UI/option_0.DDS", 1920, 1080);
}

Help::~Help()
{
}

void Help::Update()
{
	// ����s�\�ɂȂ��Ă��Ȃ��Ƃ�
	if (gameStop->StopFlag == false) {
		Sprite();	// �摜�̑J��

		// A�{�^�����������Ƃ��߂�
		if (g_pad[0]->IsTrigger(enButtonA)) {
			nowLoading = NewGO<NowLoading>(5, "nowLoading");
			nowLoading->loadState = 2;

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);					// A�{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������

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

		// �Q�[���̂����ѕ�
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			spriteState = 1;

			SetSprite();

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// �\���{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������
		}
		break;
	case 1:
		// �������
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			spriteState = 0;

			SetSprite();

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// �\���{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������
		}
		else if (g_pad[0]->IsTrigger(enButtonRight)) {
			spriteState = 2;

			SetSprite();

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// �\���{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������
		}
		break;
	case 2:
		// �A�C�R���̐���
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			spriteState = 1;

			SetSprite();

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(14);					// �\���{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������
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