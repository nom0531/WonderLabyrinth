#include "stdafx.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "NowLoading.h"
#include "BGM.h"
#include "GameStop.h"

Title::Title()
{
	// �����~�p�N���X���쐬
	gameStop = FindGO<GameStop>("gameStop");
	// nullptr�̎��ɐ�������
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

	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/Pluse_Button.wav");

	// �����摜
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
		// �X�e�[�W�Z���N�g
		spriteRender_button.SetPosition({ -300.0f, -70.0f, 0.0f });
		// ����s�\�ɂȂ��Ă��Ȃ��Ƃ�
		if (gameStop->StopFlag == false) {
			// ���L�[���������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				animState = 1;

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// �\���L�[
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������
			}

			// B�{�^�����������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonB)) {
				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// B�{�^��
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������

				// ���[�h
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 3;

				DeleteFlag = true;
			}
		}
		break;
	case 1:
		// �������
		spriteRender_button.SetPosition({ -300.0f, -250.0f, 0.0f });
		// ����s�\�ɂȂ��Ă��Ȃ��Ƃ�
		if (gameStop->StopFlag == false) {
			// ���L�[���������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				animState = 0;
					
				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// �\���L�[
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������
			}

			// B�{�^�����������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonB)) {
				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// B�{�^��
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������

				// ���[�h
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