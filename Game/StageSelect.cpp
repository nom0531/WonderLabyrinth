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

	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/Pluse_Button.wav");

	// �摜�ǂݍ���
	spriteRender.Init("Assets/sprite/UI/stageSelect.DDS", 1920.0f, 1080.0f);
	spriteRender_text.Init("Assets/sprite/UI/stageSelect_text1.DDS", 634.0f, 68.0f);
	spriteRender_button.Init("Assets/sprite/UI/button_black.DDS", 56.0f, 48.0f);

	// �X�e�[�W�摜
	spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_a.DDS", 734.0f, 527.0f);

	// �{�^���̏����ʒu
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
	Select();	// �摜�̐؂�ւ�

	// ���g���폜����
	if (DeleteFlag == true) {
		animTimer -= g_gameTime->GetFrameDeltaTime();
		// �^�C�}�[�� 0 �ɂȂ����Ƃ��ɍ폜����
		if (animTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	// �X�v���C�g�̍��W�����肷��
	spriteRender_sprite.SetPosition({ -350.0f, 70.0f, 0.0f });
	spriteRender_text.SetPosition({ -330.0f, -315.0f, 0.0f });
	// �X�V
	spriteRender.Update();
	spriteRender_text.Update();
	spriteRender_sprite.Update();
	spriteRender_button.Update();
}

void StageSelect::Select()
{
	switch (stageState) {
	case 0:
		// �摜�ǂݍ���
		spriteRender_text.Init("Assets/sprite/UI/stageSelect_text1.DDS", 634.0f, 68.0f);
		// �X�e�[�W�摜
		spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_a.DDS", 734.0f, 527.0f);

		// �{�^���̈ʒu�ݒ�
		spriteRender_button.SetPosition({ 200.0f,85.0f,0.0f });

		if (gameStop->StopFlag == false) {
			// ���{�^�����������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				stageState = 1;

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// �\���L�[
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������
			}

			// �`���[�g���A���𐶐�
			if (g_pad[0]->IsTrigger(enButtonB)) {
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 1;		// �Q�[����ʂ����[�h����
				nowloading->stageState = 0;		// �`���[�g���A��

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// B�{�^��
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������

				DeleteFlag = true;
			}
		}
		break;
	case 1:
		// �摜�ǂݍ���
		spriteRender_text.Init("Assets/sprite/UI/stageSelect_text2.DDS", 634.0f, 68.0f);
		// �X�e�[�W�摜
		spriteRender_sprite.Init("Assets/sprite/UI/stageSelect_b.DDS", 734.0f, 527.0f);
		// �{�^���̈ʒu�ݒ�
		spriteRender_button.SetPosition({ 200.0f,-90.0f,0.0f });

		if (gameStop->StopFlag == false) {
			// ��{�^�����������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				stageState = 0;

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);					// �\���L�[
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������
			}

			// �Q�[���{�҂𐶐�
			if (g_pad[0]->IsTrigger(enButtonB)) {
				nowloading = NewGO<NowLoading>(5, "nowloading");
				nowloading->loadState = 1;		// �Q�[����ʂ����[�h����
				nowloading->stageState = 1;		// �Q�[���{��

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);					// B�{�^��
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������

				DeleteFlag = true;
			}
		}
		break;
	}

	// ����s�\�ɂȂ��Ă��Ȃ��Ƃ�
	if (gameStop->StopFlag == false) {
		// �^�C�g���ɖ߂�
		if (g_pad[0]->IsTrigger(enButtonA)) {
			nowloading = NewGO<NowLoading>(5, "nowloading");
			nowloading->loadState = 2;

			// BGM�������ւ��鏈��
			nowloading->migrationToTitleFlag = true;

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);						// A�{�^��
			se->Play(false);					// ���[�v���Ȃ�
			se->SetVolume(3.5f);				// ���ʂ̐ݒ������

			DeleteFlag = true;
		}
	}
}

void StageSelect::Transition()
{
	alpha += g_gameTime->GetFrameDeltaTime();		// �����x�����Z����
	spriteRender_sprite.SetMulColor({ 1.0f,1.0f,1.0f,alpha });
}

void StageSelect::Render(RenderContext& rc)
{
	// �`��
	spriteRender.Draw(rc);
	spriteRender_text.Draw(rc);
	spriteRender_sprite.Draw(rc);
	spriteRender_button.Draw(rc);
}