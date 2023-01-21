#include "stdafx.h"
#include "NowLoading.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"
#include "GameClear.h"
#include "Sum.h"
#include "Num.h"
#include "Help.h"
#include "BGM.h"
#include "GameStop.h"

NowLoading::NowLoading()
{
	// �摜
	spriteRender_back.Init("Assets/sprite/UI/black.DDS", 1920, 1080);
	spriteRender_back.SetMulColor({ 1,1,1,0 });		// �������̃e�N�X�`��
}

bool NowLoading::Start()
{
	// �C���X�^���X��T��
	bgm = FindGO<BGM>("bgm");

	gameStop = FindGO<GameStop>("gameStop");
	gameStop->StopFlag = true;					// �������ꂽ�u�Ԃɑ���s�\�ɂ���

	return true;
}

NowLoading::~NowLoading()
{
}

void NowLoading::Update()
{
	spriteRender_back.SetMulColor({ 1.0f,1.0f,1.0f,alpha });	// �������̃e�N�X�`��

	// �A�j���[�V�����^�C�}�[������������
	animTimer -= g_gameTime->GetFrameDeltaTime();
	// 0�̎�
	if (animTimer <= 0.0f) {

		alpha -= g_gameTime->GetFrameDeltaTime();

		// �����x��0.0f�ȉ��̂Ƃ����g���폜����
		if (alpha <= 0.0f) {
			gameStop->StopFlag = false;	// �폜����̂Ńt���O���~�낷
			DeleteGO(this);
		}
	}
	else {
		alpha += g_gameTime->GetFrameDeltaTime();
	}
	
	// �w�肵���V�[���𐶐����Ă��Ȃ� ���� �����x��1.0f�ȏ�̎�
	if (makeFlag == false && alpha >= 1.0f) {
		NewScene();			// �V�[���̐���
		makeFlag = true;	// ���������̂Ńt���O���~�낷
	}

	// �ҋ@�t���O�������Ă���
	if (waitFlag)
	{
		waitFlame--;

		// �ҋ@�t���[���� 0 �ɂȂ����Ƃ�
		if (waitFlame < 0) {
			// num��game�𐶐�����
			num = NewGO<Num>(0, "num");
			num->stageState = stageState;		// �ǂ̃X�e�[�W���o�͂��邩�n��
			num->CameraAdjustmentFlag = true;	// �J�����̒��߂��s��

			// BGM�������ւ��鏈��
			switch (num->stageState) {
			case 0:
				bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
				bgm->BGMState = 2;				// �`���[�g���A��
				break;
			case 1:
				// �ύX���Ȃ��t���O��false�̎�
				if (NOTchangeBGMFlag == false) {
					bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
					bgm->BGMState = 3;				// �{��(����)
				}
				break;
			case 2:
				// �ύX���Ȃ��t���O��false�̎�
				if (NOTchangeBGMFlag == true) {
					bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
					bgm->BGMState = 4;				// �{��(���A)
				}
				break;
			}

			game = NewGO<Game>(0, "game");		// game�𐶐�����
			waitFlag = false;
		}
	}

	spriteRender_back.Update();
}

void NowLoading::NewScene() 
{
	// ���ʎ�
	switch (loadState) {
	// �Q�[�����o��
	case 1:
		// �C���X�^���X��T��
		game = FindGO<Game>("game");

		// �Q�[������������Ă���Ƃ�
		if (game != nullptr) {
			game->GameDelete();
		}

		waitFlag = true;					// �ҋ@�t���O�𗧂Ă�
		break;
	// �^�C�g��
	case 2:
		title = NewGO<Title>(0, "title");

		// ��������ȊO����^�C�g���ɖ߂�Ƃ�
		if (migrationToTitleFlag == true) {
			// BGM�������ւ��鏈��
			bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
			bgm->BGMState = 0;				// �^�C�g��
		}

		break;
	// �X�e�[�W�I��
	case 3:
		stageselect = NewGO<StageSelect>(0, "stageselect");

		// BGM�������ւ��鏈��
		bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
		bgm->BGMState = 1;				// �X�e�[�W�I��

		break;
	// ������
	case 4:
		help = NewGO<Help>(0, "help");
		break;
	// ���U���g���
	case 5:
		gameClear = NewGO<GameClear>(0, "gameClear");
		// �l��n��
		gameClear->setClearNum(
			Cleartime,					// �N���A�^�C��
			Stagenum,					// �ʉ߃X�e�[�W��
			Itemnum,					// �l���A�C�e����
			HPnum						// �c��HP
		);

		// BGM�������ւ��鏈��
		bgm->ChangeBGMFlag = true;		// ���ʂ�ύX����
		bgm->BGMState = 5;				// ���U���g

		break;
	}

	return;
}

void NowLoading::Render(RenderContext& rc)
{
	spriteRender_back.Draw(rc);
}