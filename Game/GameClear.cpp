#include "stdafx.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Sum.h"
#include "NowLoading.h"
#include "BGM.h"
#include "GameStop.h"

GameClear::GameClear()
{
	gameStop = FindGO<GameStop>("gameStop");

	// BGM
	bgm = FindGO<BGM>("bgm");
	// ��������Ă��Ȃ���������������
	if (bgm == nullptr) {
		bgm = NewGO<BGM>(0, "bgm");
		bgm->BGMState = 5;
		bgm->SetPlayBGM();
	}

	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/A_Button.wav");

	// �摜�̓ǂݍ���
	spriteRender.Init("Assets/sprite/UI/gameClear.DDS",1920.0f, 1080.0f);
	spriteRender_hpSaved.Init("Assets/sprite/UI/result_hp.DDS", 92.0f, 106.0f);
	spriteRender_itemGet.Init("Assets/sprite/UI/result_item.DDS", 92.0f, 106.0f);
	spriteRender_passStage.Init("Assets/sprite/UI/result_stage.DDS", 92.0f, 106.0f);

	// �X�R�A�̌v�Z���s��
	sum = NewGO<Sum>(0, "sum");
	sum->clearFlag = true;		// �A�C�e���Q�[�W�̌v�Z���s��Ȃ��悤�Ɏ~�߂Ă���
								// game�̃f�X�g���N�^���ł��w�肵�Ă��邪�O�̂��ߍēx�s��
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
	Font();						// ���U���g��ʂ̐���

	// ����s�\�łȂ��Ƃ�
	if (gameStop->StopFlag == false) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(11);					// A�{�^��
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������

			// �X�e�[�W�Z���N�g�ɖ߂�
			nowLoading = NewGO<NowLoading>(5, "nowLoading");
			nowLoading->loadState = 3;
			nowLoading->migrationToTitleFlag = true;

			deleteFlag = true;
		}
	}

	// ���g���폜����
	if (deleteFlag == true) {
		waitTimer -= g_gameTime->GetFrameDeltaTime();
		if (waitTimer <= 0.0f) {
			DeleteGO(this);
		}
	}

	// �X�V
	spriteRender_itemGet.Update();
	spriteRender_hpSaved.Update();
	spriteRender_passStage.Update();
}

void GameClear::Font()
{
	// �X�R�A���v�Z����
	Score = sum->CrearScore(itemSum, clearStage, HP);

	// �ʉ߃X�e�[�W��
	{
		// STAGE
		fontRender_stage.SetText(L"PASS STAGE");
		fontRender_stage.SetPosition(-300.0f, 350.0f, 0.0f);
		fontRender_stage.SetScale(0.8f);
		fontRender_stage.SetColor(g_vec4Black);

		// �ʉ߃X�e�[�W���̕\��
		wchar_t stage[256];
		//�����̎w��
		swprintf_s(stage, 256, L"x %d", clearStage);
		fontRender_Sumstage.SetText(stage);
		fontRender_Sumstage.SetPosition(100.0f, 360.0f, 0.0f);
		fontRender_Sumstage.SetScale(1.0f);
		fontRender_Sumstage.SetColor(g_vec4Black);

		spriteRender_passStage.SetPosition({ 50.0f, 330.0f, 0.0f });
		spriteRender_passStage.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// �擾�A�C�e����
	{
		// Score
		fontRender_item.SetText(L"GET ITEM");
		fontRender_item.SetPosition(-300.0f, 240.0f, 0.0f);
		fontRender_item.SetScale(0.8f);
		fontRender_item.SetColor(g_vec4Black);

		// �ʉ߃X�e�[�W���̕\��
		wchar_t stage[256];
		//�����̎w��
		swprintf_s(stage, 256, L"x %d", itemSum);
		fontRender_Sumitem.SetText(stage);
		fontRender_Sumitem.SetPosition(100.0f, 250.0f, 0.0f);
		fontRender_Sumitem.SetScale(1.0f);
		fontRender_Sumitem.SetColor(g_vec4Black);

		spriteRender_itemGet.SetPosition({ 50.0f, 220.0f, 0.0f });
		spriteRender_itemGet.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// �c��HP (�{�[�i�X�X�R�A)
	{
		// Score
		fontRender_hp.SetText(L"SAVED HP");
		fontRender_hp.SetPosition(-300.0f, 140.0f, 0.0f);
		fontRender_hp.SetScale(0.8f);
		fontRender_hp.SetColor(g_vec4Black);

		// �ʉ߃X�e�[�W���̕\��
		wchar_t stage[256];
		//�����̎w��
		swprintf_s(stage, 256, L"x %d", HP);
		fontRender_Sumhp.SetText(stage);
		fontRender_Sumhp.SetPosition(100.0f, 150.0f, 0.0f);
		fontRender_Sumhp.SetScale(1.0f);
		fontRender_Sumhp.SetColor(g_vec4Black);

		spriteRender_hpSaved.SetPosition({ 50.0f, 120.0f, 0.0f });
		spriteRender_hpSaved.SetScale({ 0.5f, 0.5f,0.0f });
	}

	// ��������
	{
		// CLEAR TIME
		fontRender_time.SetText(L"CLEAR TIME");
		fontRender_time.SetPosition(-450.0f, -240.0f, 0.0f);
		fontRender_time.SetScale(1.0f);
		fontRender_time.SetColor(g_vec4Black);

		// �L�^�̕\��
		wchar_t time[256];
		//�����̎w��
		swprintf_s(time, 256, L"%4.2fs", (float)clearTimer);
		fontRender_Cleartime.SetText(time);
		fontRender_Cleartime.SetPosition(150.0f, -200.0f, 0.0f);
		fontRender_Cleartime.SetScale(2.5f);
		fontRender_Cleartime.SetColor(g_vec4Black);
	}

	// �����X�R�A
	{
		// Score
		fontRender_score.SetText(L"YOUR SCORE");
		fontRender_score.SetPosition(-450.0f, -80.0f, 0.0f);
		fontRender_score.SetScale(1.0f);
		fontRender_score.SetColor(g_vec4Black);

		// �����X�R�A�̕\��
		wchar_t score[256];
		//�����̎w��
		swprintf_s(score, 256, L"%d", Score);
		fontRender_Sumscore.SetText(score);
		fontRender_Sumscore.SetPosition(150.0f, -40.0f, 0.0f);
		fontRender_Sumscore.SetScale(2.5f);
		fontRender_Sumscore.SetColor(g_vec4Black); 
	}
}

void GameClear::Render(RenderContext& rc)
{
	// �`��
	spriteRender.Draw(rc);
	spriteRender_hpSaved.Draw(rc);
	spriteRender_itemGet.Draw(rc);
	spriteRender_passStage.Draw(rc);
	// �^�C��
	fontRender_time.Draw(rc);
	fontRender_Cleartime.Draw(rc);
	// �X�R�A
	fontRender_score.Draw(rc);
	fontRender_Sumscore.Draw(rc);
	// �����킯
	fontRender_stage.Draw(rc);
	fontRender_Sumstage.Draw(rc);
	fontRender_item.Draw(rc);
	fontRender_Sumitem.Draw(rc);
	fontRender_hp.Draw(rc);
	fontRender_Sumhp.Draw(rc);
}