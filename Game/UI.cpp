#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "Stage.h"
#include "Stage2.h"
#include "Player.h"
#include "GameCamera.h"
#include "NowLoading.h"
#include "Num.h"
#include "Sum.h"

UI::UI()
{
	// �C���X�^���X��T��
	num = FindGO<Num>("num");
	player = FindGO<Player>("player");					
	gameCamera = FindGO<GameCamera>("gameCamera");
	stage = FindGO<Stage>("stage");
	stage2 = FindGO<Stage2>("stage2");

	itemSum = player->itemCount;		// �A�C�e�������i�[����

	// 8:5�ŃT�C�Y�w��
	// HP�o�[
	spriteRender_HP.Init("Assets/sprite/UI/HP_full.DDS", 1600, 1000);
	spriteRender_HP.SetPosition({ -580.0f, 450.0f, 0.0f });
	spriteRender_HP.Update();

	// �[�x�̕\�� (�f�t�H���g��01)
	spriteRender_turn.Init("Assets/sprite/UI/turncount.DDS", 800, 500);
	spriteRender_turn.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_turn.Update();
	// 1�̈�
	spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_1.DDS", 800, 500);
	spriteRender_countOne.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countOne.Update();
	// 10�̈�
	spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_00.DDS", 800, 500);
	spriteRender_countTen.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countTen.Update();

	// �w���v�A�C�R�� (�X�^�[�g�{�^��)
	spriteRender_help.Init("Assets/sprite/UI/aicon_help.DDS", 400, 250);
	spriteRender_help.SetPosition({ 870.0f,200.0f,0.0f });
	spriteRender_help.Update();

	// �J�����؂�ւ��iX�j
	spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_a.DDS", 400, 250);
	spriteRender_camera.SetPosition({ 870.0f,85.0f,0.0f });
	spriteRender_camera.Update();

	// �A�C�e���Q�[�W
	spriteRender_itemgage.Init("Assets/sprite/UI/item_gage.DDS", 800, 500);
	spriteRender_itemgage.SetPosition({ -600.0f, 310.0f, 0.0f });
	spriteRender_itemgage.Update();
	// �w�i
	spriteRender_itemback.Init("Assets/sprite/UI/item_back.DDS", 220, 50);
	spriteRender_itemback.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_itemback.SetPivot({ 0.0f,0.5f });	// �摜�̒��S�_
	spriteRender_itemback.Update();
	// �Q�[�W����
	spriteRender_item.Init("Assets/sprite/UI/item.DDS", 220, 50);
	spriteRender_item.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_item.SetPivot({ 0.0f,0.5f });		// �摜�̒��S�_
	spriteRender_item.Update();

	// �����p�L�����N�^�[
	spriteRender_chat.Init("Asettes/sprite/chara.DDS", 400, 800);	// �摜�̓ǂݍ���
	spriteRender_chat.SetPosition({ 0.0f, 0.0f, 0.0f });
	spriteRender_chat.Update();
}

UI::~UI()
{
}

void UI::Update()
{
	Camera();		// �J����
	Crear();		// �N���A����
	PlayerHP();		// HP

	// num�����݂��鎞�Ɏ��s����
	if (num != nullptr) {
		ItemGage();		// �A�C�e���Q�[�W
	}

	// player����e�����Ƃ�
	if (player->animState == 3) {
		UI_playerHP = player->HP;	// HP���Q��
	}
}

void UI::ItemGage()
{
	// ��~�����Ƃ��Q�[�W�ʂ����炳�Ȃ��悤�ɂ���
	if (stopFlag == true) {
		nowGage = nowGage;
	}

	// �A�C�e���Q�[�W��UI����
	spriteRender_item.SetPivot({ 0.0f,0.5f });	// �摜�̒��S�_

	// �X�P�[���ƈʒu��ݒ肷��
	spriteRender_item.SetScale({ nowGage, 1.0f, 1.0f });
	spriteRender_item.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_item.Update();
}

void UI::TurnCount()
{
	// �l��9�ȉ��̎�
	if (UI_stageNum >= 0 && UI_stageNum <= 9) {
		if (UI_stageNum == 0) {
			turn_one = 0;
		}
		// ���̂܂ܓn��
		turn_one = UI_stageNum;
	}
	// 10�ȏ�19�ȉ��̎�
	else if (UI_stageNum >= 10 && UI_stageNum <= 19) {
		if (UI_stageNum == 10) {
			turn_one = 0;
		}
		else {
			// 10��������1�̈ʂ�n��
			turn_one = UI_stageNum - 10;
		}
		// 10�̈ʂ�1�̈ʂ������ēn��
		turn_ten = 1;
	}
	// 20�ȏ�29�ȉ��̎�
	else if (UI_stageNum >= 20 && UI_stageNum <= 29) {
		if (UI_stageNum == 20) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 20;
		}
		turn_ten = 2;
	}
	// 30�ȏ�39�ȉ��̎�
	else if (UI_stageNum >= 30 && UI_stageNum <= 39) {
		if (UI_stageNum == 30) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 30;
		}
		turn_ten = 3;
	}
	// 40�ȏ�49�ȉ��̎�
	else if (UI_stageNum >= 40 && UI_stageNum <= 49) {
		if (UI_stageNum == 40) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 40;
		}
		turn_ten = 4;
	}
	// 50�ȏ�59�ȉ��̎�
	else if (UI_stageNum >= 50 && UI_stageNum <= 59) {
		if (UI_stageNum == 50) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 50;
		}
		turn_ten = 5;
	}
	// 60�ȏ�69�ȉ��̎�
	else if (UI_stageNum >= 60 && UI_stageNum <= 69) {
		if (UI_stageNum == 60) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 60;
		}
		turn_ten = 6;
	}
	// 70�ȏ�79�ȉ��̎�
	else if (UI_stageNum >= 70 && UI_stageNum <= 79) {
		if (UI_stageNum == 70) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 70;
		}
		turn_ten = 7;
	}
	// 80�ȏ�89�ȉ��̎�
	else if (UI_stageNum >= 80 && UI_stageNum <= 89) {
		if (UI_stageNum == 80) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 80;
		}
		turn_ten = 8;
	}
	// 90�ȏ�99�ȉ��̎�
	else if (UI_stageNum >= 90 && UI_stageNum <= 99) {
		if (UI_stageNum == 90) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 90;
		}
		turn_ten = 9;
	}
	else {
		turn_one = 0;
		turn_ten = 0;
	}

	// �X�e�[�W���N���A�����Ƃ��ɌĂяo��
	if (player->stageClear == true) {
		// �K�w�̕\��
		TurnOne();
		TurnTen();
	}

	// �^�[�����̃J�E���g
	//wchar_t Turntext[256];
	// �����̎w��
	//swprintf_s(Turntext, 256, L"%2d���", (int)UI_turn);
}

void UI::TurnOne()
{
	// 1�̈�
	switch (turn_one) {
	case 0:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_0.DDS", 800, 500);
		break;
	case 1:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_1.DDS", 800, 500);
		break;
	case 2:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_2.DDS", 800, 500);
		break;
	case 3:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_3.DDS", 800, 500);
		break;
	case 4:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_4.DDS", 800, 500);
		break;
	case 5:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_5.DDS", 800, 500);
		break;
	case 6:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_6.DDS", 800, 500);
		break;
	case 7:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_7.DDS", 800, 500);
		break;
	case 8:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_8.DDS", 800, 500);
		break;
	case 9:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_9.DDS", 800, 500);
		break;
	}

	spriteRender_countOne.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countOne.Update();
}

void UI::TurnTen()
{
	// 10�̈�
	switch (turn_ten) {
	case 0:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_00.DDS", 800, 500);
		break;
	case 1:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_10.DDS", 800, 500);
		break;
	case 2:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_20.DDS", 800, 500);
		break;
	case 3:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_30.DDS", 800, 500);
		break;
	case 4:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_40.DDS", 800, 500);
		break;
	case 5:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_50.DDS", 800, 500);
		break;
	case 6:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_60.DDS", 800, 500);
		break;
	case 7:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_70.DDS", 800, 500);
		break;
	case 8:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_80.DDS", 800, 500);
		break;
	case 9:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_90.DDS", 800, 500);
		break;
	}

	spriteRender_countTen.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countTen.Update();
}

void UI::PlayerHP()
{
	// �l���Q��
	UI_playerHP = player->HP;

	// HP�̏���
	switch (UI_playerHP) {
	case 0:
		// �c��HP:0
		spriteRender_HP.Init("Assets/sprite/UI/HP_3damege.DDS", 1600, 1000);
		num->clearFlag = true;
		break;
	case 1:
		// �c��HP:1
		spriteRender_HP.Init("Assets/sprite/UI/HP_2damege.DDS", 1600, 1000);
		break;
	case 2:
		// �c��HP:2
		spriteRender_HP.Init("Assets/sprite/UI/HP_1damege.DDS", 1600, 1000);
		break;
	}
	spriteRender_HP.SetPosition({ -580.0f, 450, 0.0f });
	spriteRender_HP.Update();
}

void UI::Camera()
{
	// �l���Q��
	UI_cameraState = gameCamera->cameraState;

	if (num->stopFlag == false) {
		// �A�C�R���̐؂�ւ�
		switch (UI_cameraState) {
		case 0:
			if (g_pad[0]->IsTrigger(enButtonX)) {
				spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_a.DDS", 400, 250);
			}
			break;
		case 1:
			if (g_pad[0]->IsTrigger(enButtonX)) {
				spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_b.DDS", 400, 250);
			}
			break;
		}
	}
	spriteRender_camera.SetPosition({ 870.0f,85.0f,0.0f });
	spriteRender_camera.Update();
}

void UI::Crear()
{
	//spriteRender.Init("Assets/")
}

void UI::Render(RenderContext& rc)
{
	// �`��
	spriteRender_HP.Draw(rc);
	spriteRender_help.Draw(rc);		// �w���v�A�C�R��
	spriteRender_camera.Draw(rc);	// �J�����A�C�R��

	spriteRender_turn.Draw(rc);		// �^�[����
	spriteRender_countOne.Draw(rc);
	spriteRender_countTen.Draw(rc);

	spriteRender_itemgage.Draw(rc);	// �A�C�e���Q�[�W
	spriteRender_itemback.Draw(rc);
	spriteRender_item.Draw(rc);

	spriteRender_chat.Draw(rc);		// �L�����N�^�[�̕\��
}