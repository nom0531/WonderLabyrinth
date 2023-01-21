#include "stdafx.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Stage2.h"
#include "UI.h"
#include "Item.h"
#include "Enemy.h"		// slimerabbit
#include "Enemy2.h"		// mushroom
#include "GameClear.h"
#include "NowLoading.h"
#include "Help.h"
#include "Sum.h"		// �v�Z�p�N���X
#include "Num.h"		// ��Ԋi�[�p
#include "Chat.h"
#include "BGM.h"

#define CHANGETOSTAGE 5	// �X�L���EBGM��ύX����K�w���̒l

Game::Game()
{
	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/X_Button.wav");
	g_soundEngine->ResistWaveFileBank(24, "Assets/sound/Aru_ChatStart.wav");

	skyCube = NewGO<SkyCube>(0);

	g_renderingEngine->DisableTonemap();

	num = FindGO<Num>("num");
	if (num == nullptr) {
		num = NewGO<Num>(0, "num");
	}
	num->stopFlag = false;						// �O�̂��߃t���O�����Z�b�g���Ă���
	num->turn = 1;								// player�̃^�[������J�n
	num->enemyNum = 0;
	num->clearFlag = false;

	// �X�L���ύX
	ui = FindGO<UI>("ui");
	if (ui != nullptr) {
		// ���̊K�w���ŃX�L����ύX����
		if (ui->UI_stageNum % CHANGETOSTAGE == 0) {
			// ���݂̃X�e�[�W�̃X�L���� 1 �̎�
			if (num->stageState == 1) {
				num->stageState = 2;	// �X�L���� 2 �ɕύX

				bgm = FindGO<BGM>("bgm");
				bgm->ChangeBGMFlag = true;
				bgm->BGMState = 4;
			}
			// ���݂̃X�e�[�W�̃X�L���� 2 �̎�
			else if (num->stageState == 2) {
				num->stageState = 1;	// �X�L���� 1 �ɕύX

				bgm = FindGO<BGM>("bgm");
				bgm->ChangeBGMFlag = true;
				bgm->BGMState = 3;
			}
		}
	}

	// stage
	switch (num->stageState) {
	case 0:
		// �`���[�g���A��
		stage = NewGO<Stage>(0, "stage");
		num->stageNum = 5;

		// BGM
		bgm = FindGO<BGM>("bgm");
		// ��������Ă��Ȃ��Ƃ���������
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 2;
			bgm->SetPlayBGM();
		}

		break;
	case 1:
		// ����ȊO
		stage2 = NewGO<Stage2>(0, "stage2");
		stage2->texState = 1;					// �e�N�X�`�����w�肷��
		stage2->clearFlag = false;
		stage2->SetUp();
		num->stageNum = 9;						// �X�e�[�W�̃}�X����n��

		// BGM
		bgm = FindGO<BGM>("bgm");
		// ��������Ă��Ȃ��Ƃ���������
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 3;
			bgm->SetPlayBGM();
		}

		break;
	case 2:
		// ����ȊO
		stage2 = NewGO<Stage2>(0, "stage2");
		stage2->texState = 2;					// �e�N�X�`�����w�肷��
		stage2->clearFlag = false;
		stage2->SetUp();
		num->stageNum = 9;						// �X�e�[�W�̃}�X����n��

		// BGM
		bgm = FindGO<BGM>("bgm");
		// ��������Ă��Ȃ��Ƃ���������
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 4;
			bgm->SetPlayBGM();
		}

		break;
	}

	// player
	player = FindGO<Player>("player");
	// �v���C���[���������̎�
	if (player == nullptr) {
		player = NewGO<Player>(0, "player");
		player->p_stageState = num->stageState;
		player->Playermodel(false);					// player�̃��f�����X�V
	}
	// �X�e�[�W�N���A�̃t���O�������Ă���Ƃ�
	if (player->stageClear == true) {
		// �K�w���ύX�����̂ł��낢�냊�Z�b�g����
		// ���W�̍Đݒ�
		player->position = { 200.0f,11.0f,2.0f };
		player->position_stage2[8][4] = 1;
		player->position2D = { 4.0f,8.0f };

		player->modelRender.SetPosition(player->position);
		player->p_stageState = num->stageState;

		player->animState = 0;
		player->Playermodel(true);			// player�̃��f�����X�V

		// �t���O��������
		player->moveFlag = false;			// �ړ��ł��邩�ǂ���
		player->posFlag = false;			// �ړ��ł���I�u�W�F�N�g���ǂ���
		player->AttackFlag = false;			// �U���������ǂ���
	}

	// player�ɒl��n��
	player_position = player->position;

	// camera
	gameCamera = FindGO<GameCamera>("gameCamera");
	if (gameCamera == nullptr) {
		gameCamera = NewGO<GameCamera>(0, "gameCamera");
	}
	gameCamera->c_stageState = num->stageState;

	// sistem
	if (ui == nullptr) {
		ui = NewGO<UI>(0, "ui");
	}

	// �Q�[�W�̌������~���Ă���Ƃ�
	if (ui->stopFlag = true) {
		// ��������
		ui->stopFlag = false;
	}

	ui->UI_stageState = num->stageState;
	
	// stage
	backGround = NewGO<BackGround>(0);

	sum = NewGO<Sum>(0, "sum");
	sum->clearFlag = false;

	// �v���C���[���̃|�C���^������
	if (player->stageClear == true) {
		player->stage = stage;
		player->stage2 = stage2;

		player->num = num;
		player->sum = sum;
		
		ui->num = num;
		ui->stage = stage;
		ui->stage2 = stage2;

		gameCamera->num = num;

		player->stageClear = false;			// �X�e�[�W���N���A�������ǂ���
	}

	switch (num->stageState) {
	case 0:
		skyCube->SetType(enSkyCubeType_DayToon);
		skyCube->SetLuminance(1.0f);
		skyCube->SetScale(300.0f);

		s_Light();	// �X�|�b�g���C�g
		StageZero();// �z�u

		// �f�B���N�V�������C�g(���s����)
		g_renderingEngine->SetDirectionLight(
			0,					// ���C�g�̔ԍ�
			{ 0.2f,-1.0f,0.5f },			// ����(X Y Z)
			{ 0.8f,0.8f,0.8f }			// ���C�g�̃J���[(R G B)
		);
		// ����
		g_renderingEngine->SetAmbient({ 0.7f,0.7f,0.7f });
		break;
	case 1:
		skyCube->SetType(enSkyCubeType_DayToon);
		skyCube->SetLuminance(1.0f);
		skyCube->SetScale(300.0f);

		StageOne();	// �z�u

		// �f�B���N�V�������C�g(���s����)
		g_renderingEngine->SetDirectionLight(
			0,					// ���C�g�̔ԍ�
			{ 0.2f,-1.0f,0.5f },			// ����(X Y Z)
			{ 0.8f,0.8f,0.8f }			// ���C�g�̃J���[(R G B)
		);
		// ����
		g_renderingEngine->SetAmbient({ 0.7f,0.7f,0.7f });
		break;
	case 2:
		skyCube->SetType(enSkyCubeType_NightToon);
		skyCube->SetLuminance(0.2f);
		skyCube->SetScale(300.0f);

		p_Light();	// �|�C���g���C�g
		StageTwo();	// �z�u

		// �f�B���N�V�������C�g(���s����)
		g_renderingEngine->SetDirectionLight(
			0,					// ���C�g�̔ԍ�
			{ 0.2f,-1.0f,0.5f },			// ����(X Y Z)
			{ 0.2f,0.2f,0.2f }		// ���C�g�̃J���[(R G B)
		);
		// ����
		g_renderingEngine->SetAmbient({ 0.2f,0.2f,0.2f });
		break;
	}
}

void Game::s_Light()
{
	// �X�|�b�g���C�g
	spotLight.Init();
	// ���C�g�̉e��������ݒ�B
	spotLight.SetRange(1200.0f);
	// ���C�g�̉e���p�x��ݒ�B(�傫��)
	spotLight.SetAngle(Math::DegToRad(3.5f));
	// ���C�g�̋�����������ݒ�B
	spotLight.SetRangeAffectPowParam(1.0f);
	// ���C�g�̊p�x��������ݒ�B(�ڂ����H�j
	spotLight.SetAngleAffectPowParam(0.2f);
	// ���C�g�̐F��ݒ�B
	spotLight.SetColor(5.0f, 5.0f, 4.5f);
	// ���C�g�̕�����ݒ�B
	spotLight.SetDirection({ 0.0f,-10.0f,0.0f });
}

void Game::p_Light()
{
	// �|�C���g���C�g
	pointLight.Init();
	// �ʒu
	pointLight.SetPosition(100.0f, 10.0f, 8.0f);
	// �J���[
	pointLight.SetColor(Vector3(3.0f, 3.0f, 2.5f));
	// �e�����̗ݏ�i�H�j
	pointLight.SetAffectPowParam(0.1f);
	// �͈�
	pointLight.SetRange(p_scale);
}

void Game::StageZero()
{	
	// �g�p����G�l�~�[���쐬
	Enemy* slime = NewGO<Enemy>(0, "slime");
	slime->s_position = { 50.0f,2.0f,150.0f };
	slime->s_position_stage[1][1] = 1;
	slime->s_position2D = { 1.0f,1.0f };

	// �A�C�e���̓`���[�g���A���̂ݎg�p����
	Item* item = NewGO<Item>(0, "item");
	item->position = { 100.0f,20.0f,100.0f };
}

void Game::StageOne()
{
	// �g�p����G�l�~�[���쐬
	Enemy* slime = NewGO<Enemy>(0, "slime");
	Enemy* slime2 = NewGO<Enemy>(0, "slime");
	Enemy* slime3 = NewGO<Enemy>(0, "slime");

	Enemy2* mush = NewGO<Enemy2>(0, "mush");
	Enemy2* mush2 = NewGO<Enemy2>(0, "mush");
	Enemy2* mush3 = NewGO<Enemy2>(0, "mush");

	// �X�e�[�W�ɉ����ēG�̔z�u��ύX����
	switch (num->Rundum_StageNum) {
	case 0:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);
		DeleteGO(mush3);

		// ���W��ݒ�
		slime->s_position = { 200.0f,2.0f,200.0f };
		slime->s_position_stage2[4][4] = 1;
		slime->s_position2D = { 4.0f,4.0f };

		slime2->s_position = { 0.0f,2.0f,350.0f };
		slime2->s_position_stage2[1][0] = 1;
		slime2->s_position2D = { 0.0f,1.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		break;
	case 1:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);

		// ���W��ݒ�
		slime->s_position = { 0.0f,2.0f,300.0f };
		slime->s_position_stage2[2][0] = 1;
		slime->s_position2D = { 0.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,150.0f };
		slime2->s_position_stage2[5][5] = 1;
		slime2->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 200.0f,2.0f,200.0f };
		mush->m_position_stage[4][4] = 1;
		mush->m_position2D = { 4.0f,4.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		mush3->m_position = { 50.0f,2.0f,50.0f };
		mush3->m_position_stage[7][1] = 1;
		mush3->m_position2D = { 1.0f,7.0f };

		break;
	case 2:

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,200.0f };
		slime->s_position_stage2[4][1] = 1;
		slime->s_position2D = { 1.0f,4.0f };

		slime2->s_position = { 200.0f,2.0f,300.0f };
		slime2->s_position_stage2[2][4] = 1;
		slime2->s_position2D = { 4.0f,2.0f };
		
		slime3->s_position = { 250.0f,2.0f,150.0f };
		slime3->s_position_stage2[5][5] = 1;
		slime3->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 400.0f,2.0f,350.0f };
		mush->m_position_stage[1][8] = 1;
		mush->m_position2D = { 8.0f,1.0f };

		mush2->m_position = { 50.0f,2.0f,50.0f };
		mush2->m_position_stage[7][1] = 1;
		mush2->m_position2D = { 1.0f,7.0f };

		mush3->m_position = { 50.0f,2.0f,350.0f };
		mush3->m_position_stage[1][1] = 1;
		mush3->m_position2D = { 1.0f,1.0f };

		break;
	case 3:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);
		DeleteGO(mush3);

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,300.0f };
		slime->s_position_stage2[2][1] = 1;
		slime->s_position2D = { 1.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,100.0f };
		slime2->s_position_stage2[6][5] = 1;
		slime2->s_position2D = { 5.0f,6.0f };

		mush->m_position = { 0.0f,2.0f,50.0f };
		mush->m_position_stage[7][0] = 1;
		mush->m_position2D = { 0.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };

		break;
	case 4:
		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(mush3);
		DeleteGO(slime3);

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,350.0f };
		slime->s_position_stage2[1][1] = 1;
		slime->s_position2D = { 1.0f,1.0f };

		slime2->s_position = { 250.0f,2.0f,200.0f };
		slime2->s_position_stage2[4][5] = 1;
		slime2->s_position2D = { 5.0f,4.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };
		break;
	}
}

void Game::StageTwo()
{
	// �g�p����G�l�~�[���쐬
	Enemy* slime = NewGO<Enemy>(0, "slime");
	Enemy* slime2 = NewGO<Enemy>(0, "slime");
	Enemy* slime3 = NewGO<Enemy>(0, "slime");

	Enemy2* mush = NewGO<Enemy2>(0, "mush");
	Enemy2* mush2 = NewGO<Enemy2>(0, "mush");
	Enemy2* mush3 = NewGO<Enemy2>(0, "mush");

	// �X�e�[�W�ɉ����ēG�̔z�u��ύX����
	switch (num->Rundum_StageNum) {
	case 0:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);
		DeleteGO(mush3);

		// ���W��ݒ�
		slime->s_position = { 200.0f,2.0f,200.0f };
		slime->s_position_stage2[4][4] = 1;
		slime->s_position2D = { 4.0f,4.0f };

		slime2->s_position = { 0.0f,2.0f,350.0f };
		slime2->s_position_stage2[1][0] = 1;
		slime2->s_position2D = { 0.0f,1.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		break;
	case 1:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);

		// ���W��ݒ�
		slime->s_position = { 0.0f,2.0f,300.0f };
		slime->s_position_stage2[2][0] = 1;
		slime->s_position2D = { 0.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,150.0f };
		slime2->s_position_stage2[5][5] = 1;
		slime2->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 200.0f,2.0f,200.0f };
		mush->m_position_stage[4][4] = 1;
		mush->m_position2D = { 4.0f,4.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		mush3->m_position = { 50.0f,2.0f,50.0f };
		mush3->m_position_stage[7][1] = 1;
		mush3->m_position2D = { 1.0f,7.0f };

		break;
	case 2:

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,200.0f };
		slime->s_position_stage2[4][1] = 1;
		slime->s_position2D = { 1.0f,4.0f };

		slime2->s_position = { 200.0f,2.0f,300.0f };
		slime2->s_position_stage2[2][4] = 1;
		slime2->s_position2D = { 4.0f,2.0f };

		slime3->s_position = { 250.0f,2.0f,150.0f };
		slime3->s_position_stage2[5][5] = 1;
		slime3->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 400.0f,2.0f,350.0f };
		mush->m_position_stage[1][8] = 1;
		mush->m_position2D = { 8.0f,1.0f };

		mush2->m_position = { 50.0f,2.0f,50.0f };
		mush2->m_position_stage[7][1] = 1;
		mush2->m_position2D = { 1.0f,7.0f };

		mush3->m_position = { 50.0f,2.0f,350.0f };
		mush3->m_position_stage[1][1] = 1;
		mush3->m_position2D = { 1.0f,1.0f };

		break;
	case 3:

		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(slime3);
		DeleteGO(mush3);

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,300.0f };
		slime->s_position_stage2[2][1] = 1;
		slime->s_position2D = { 1.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,100.0f };
		slime2->s_position_stage2[6][5] = 1;
		slime2->s_position2D = { 5.0f,6.0f };

		mush->m_position = { 0.0f,2.0f,50.0f };
		mush->m_position_stage[7][0] = 1;
		mush->m_position2D = { 0.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };

		break;
	case 4:
		// �g�p���Ȃ��G�l�~�[�͍폜����
		DeleteGO(mush3);
		DeleteGO(slime3);

		// ���W��ݒ�
		slime->s_position = { 50.0f,2.0f,350.0f };
		slime->s_position_stage2[1][1] = 1;
		slime->s_position2D = { 1.0f,1.0f };

		slime2->s_position = { 250.0f,2.0f,200.0f };
		slime2->s_position_stage2[4][5] = 1;
		slime2->s_position2D = { 5.0f,4.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };
		break;
	}
}

Game::~Game()
{
	// sistem
	DeleteGO(help);
	DeleteGO(gameClear);
	DeleteGO(num);
	DeleteGO(sum);
	DeleteGO(gameBGM);
	// game
	DeleteGO(chat);
	DeleteGO(stage);
	DeleteGO(stage2);
	DeleteGO(backGround);
	DeleteGO(skyCube);
}

void Game::GameEnd() {
	DeleteGO(ui);
	DeleteGO(bgm);
	DeleteGO(player);
	DeleteGO(gameCamera);
	sum->clearFlag = true;
}

bool Game::Start()
{	
	return true;
}

void Game::Update()
{
	// �X�|�b�g���C�g
	if (num->stageState == 0) {
		Vector3 spot_position = player->position;
		spot_position.y = 500.0f;
		spotLight.SetPosition(spot_position);	// �X�|�b�g���C�g�̍��W
		spotLight.Update();						// ���W��������
	}

	// �|�C���g���C�g
	if (num->stageState == 2) {
		Vector3 point_position = player->position;
		point_position.y = 45.0;				// player�̑̂̈ʒu�Ɏ����Ă���
		pointLight.SetPosition(point_position);	// �|�C���g���C�g�̍��W
		pointLight.Update();					// ���W��������
	}

	if (num->turn == 2) {

		bool end = true;	// �G�l�~�[�̃^�[�����I���������ǂ���

		// �G�l�~�[
		QueryGOs<Enemy>("slime", [&](Enemy* slime) {
			// 1�̂ł��I�����Ă��Ȃ��Ƃ�
			if (slime->nowTurnEnd == false) {
				end = false;
			}
			// �I�����Ă���Ƃ���true��Ԃ�
			return true;
			});
		QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
			// 1�̂ł��I�����Ă��Ȃ��Ƃ�
			if (mush->nowTurnEnd == false) {
				end = false;
			}
			// �I�����Ă���Ƃ���true��Ԃ�
			return true;
			});

		// �I�����Ă���Ƃ�
		if (end == true) {
			num->turn = 1;	// player�̃^�[����

			// �t���O��߂�
			QueryGOs<Enemy>("slime", [&](Enemy* slime) {
				slime->nowTurnEnd = false;
				return true;
				});
			QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
				mush->nowTurnEnd = false;
				return true;
				});
		}
	}

	// �G�l�~�[�����Ȃ��@���@�G�l�~�[�̃^�[���̎�
	if (num->enemyNum == 0 && num->turn == 2) {
		num->turn = 1;	// player�̃^�[���ɕύX����
	}

	// �`��t���O��false�̎�
	if (drawFlag == false) {
		// �`���[�g���A���̎�
		if (num->stageState == 0) {
			// �������𖞂������Ƃ�
			if (num->NewGoFlag == false && num->movePlayer == false && num->getItem == false) {

				num->stopFlag = true;
				// �C�x���g���Đ�
				chat = NewGO<Chat>(0, "chat");
				chat->eventFlag = true;					// �C�x���g�t���O��true�ɂ���
				chat->eveneStartFlag = true;			// ��b���J�n
				chat->Name();

				num->drawChatFlag = true;				// �摜��`�悵���̂�true�ɂ���
			}
			num->NewGoFlag = true;						// ����ȍ~���̃t���O�͖����Ȃ̂�true�ɂ���
		}
		else {
			// ��b���\�� ���� �X�^�[�g�{�^�����������Ƃ�
			if (num->drawChatFlag == false && g_pad[0]->IsTrigger(enButtonStart)) {

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(24);
				se->Play(false);				// ���[�v���Ȃ�
				se->SetVolume(3.5f);			// ���ʂ̐ݒ������

				num->stopFlag = true;
				// �����_���`���b�g���Đ�
				chat = NewGO<Chat>(0, "chat");
				chat->rundumChatStart = true;			// �����_���`���b�g���J�n
				chat->eveneStartFlag = true;			// ��b���J�n
				chat->Name();

				num->drawChatFlag = true;				// �摜��`�悵���̂�true�ɂ���
			}
		}
	}

	Crear();											// �N���A����

	// �Q�[�W�ʂ�0�ȉ��@�܂��́@HP��0�̎��I��
	if (sum->nowGage == sum->minGage ||
		player->HP == 0) {
		num->clearFlag = true;
	}

	// �w���v��\�����Ă���Ƃ��͎~�߂�
	if (num->stopFlag == true) {
		sum->nowGage = sum->nowGage;
	}

	// �`���[�g���A���ȊO�@���@�`�悵�I�������
	if (num->stageState != 0 && num->drawChatFlag == false) {
		// �ēx�`��ł���悤�ɂ���
		drawFlag = false;
	}

	// �X�e�[�W���N���A�������A�s���ł��Ȃ��悤�ɂ���
	if (player->animState == 5) {
		num->stopFlag = true;
		num->turn = 0;					// �ǂ���������Ȃ��悤�ɂ���
		num->drawChatFlag = true;		// �w���v��`��ł��Ȃ��悤�ɂ���
	}
}

void Game::TurnCount()
{
	// �v���C���[���������Ƃ�
	if (player_position.x != player->position.x && player_position.z != player_position.z) {
		player->position = player_position;
		num->turn = 2;
		player->moveFlag = false;
	}
	// �����łȂ��Ƃ�
	else {
		num->turn = 1;
		player->moveFlag = true;
	}
}

void Game::Crear()
{
	//�X�e�[�W�N���A
	{
		// �������[�V�����̍Đ���Ɏ��s����
		if (player->modelRender.IsPlayingAnimation() == false && player->animState == 5) {

			player->stageClear = true;

			// �X�e�[�W�N���A
			// ���̃X�e�[�W�𐶐�����
			if (stage2->clearFlag == true) {

				// �ēx�Q�[���𐶐����鏈��
				if (nowLoadingMake == false) {
					nowLoading = NewGO<NowLoading>(5, "nowLoading");
					nowLoading->loadState = 1;					// �Q�[�������[�h
					nowLoading->stageState = num->stageState;	// �X�e�[�W�̏���n��

					// ���̊K�w���̂Ƃ�
					if (ui->UI_stageNum % CHANGETOSTAGE == 0) {
						// �ύX���Ȃ��t���O��false�ɂ���
						nowLoading->NOTchangeBGMFlag = false;
					}
					// ���̊K�w���łȂ��Ƃ�
					else {
						// �ύX���Ȃ��t���O��true�ɂ���
						nowLoading->NOTchangeBGMFlag = true;
					}

					nowLoadingMake = true;						// ���x���������Ȃ��悤�ɂ���
				}
			}
		}
	}

	// �Q�[���N���A�łȂ��Ƃ��̓^�C�}�[�����Z����
	Timer += g_gameTime->GetFrameDeltaTime();

	// �Q�[���N���A
	{
		// �N���A�t���O��true�̎�
		if (num->clearFlag == true) {
			sum->clearFlag = true;	// �N���A�����̂�true��n��

			num->turn = 0;			// �����Ȃ��悤�ɂ���
			num->stopFlag = true;

			if (num->stageState == 0) {
				// ��b���I�������Ƃ�
				if (chat->eveneStartFlag == false) {
					DeleteFlag = true;
				}
			}
			else if (num->stageState != 0) {
				if (ResultNewGO == false) {
					// ���U���g
					nowLoading = NewGO<NowLoading>(5, "nowLoading");
					nowLoading->loadState = 5;				// ���U���g�𐶐�

					ResultNewGO = true;						// ���x���������Ȃ��悤�ɂ���	
				}

				// ���U���g�p�̒l��n��
				nowLoading->Stagenum = ui->UI_stageNum;		// �ʉ߂����K�w��
				nowLoading->Itemnum = player->itemCount;	// �l���A�C�e����
				nowLoading->HPnum = player->HP;				// �c��HP
				nowLoading->Cleartime = Timer;				// �N���A�^�C��

				animTimer -= g_gameTime->GetFrameDeltaTime();
				if (animTimer <= 0.0f) {

					// �G�l�~�[���폜����
					QueryGOs<Enemy>("slime", [&](Enemy* slime) {
						DeleteGO(slime);
						return true;
						});
					// �G�l�~�[���폜����
					QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
						DeleteGO(mush);
						return true;
						});

					// ���g���폜����
					GameEnd();
					DeleteGO(this);
				}
			}
		}

		// �`���[�g���A�����̎������폜���鏈��
		if (DeleteFlag == true) {

			// �^�C�g���𐶐����Ă��Ȃ��Ƃ�
			if (TitleNewGO == false) {
				nowLoading = NewGO<NowLoading>(5, "nowLoading");
				nowLoading->loadState = 3;		// �^�C�g���𐶐�

				TitleNewGO = true;				// �^�C�g�������x���������Ȃ��悤�ɂ���
			}

			// �^�C�}�[������������
			animTimer -= g_gameTime->GetFrameDeltaTime();
			// 0�ɂȂ����Ƃ�
			if (animTimer <= 0.0f) {

				// �G�l�~�[���폜����
				QueryGOs<Enemy>("slime", [&](Enemy* slime) {
					DeleteGO(slime);
					return true;
					});
				// �G�l�~�[���폜����
				QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
					DeleteGO(mush);
					return true;
					});

				// ���g���폜����
				GameEnd();
				DeleteGO(this);
			}
		}
	}
}

// �{�҂ł̊K�w�̈ړ��p
void Game::GameDelete() {

	// ��x���J�E���g���Ă��Ȃ��Ƃ�
	if (CountFlag == false) {

		ui->stopFlag = true;	// �Q�[�W�̌������~

		ui->UI_stageNum++;		// �J�E���g����
		ui->TurnCount();		// �K�w��������

		CountFlag = true;		// ������J�E���g���Ȃ��悤�ɂ���
	}

	// �폜����
	QueryGOs<Enemy>("slime", [&](Enemy* slime) {
		DeleteGO(slime);
		return true;
		});
	QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
		DeleteGO(mush);
		return true;
		});

	DeleteGO(this);			// ���g���폜
}

void Game::Render(RenderContext& rc)
{
	// �`��
	fontRender.Draw(rc);
}