#pragma once
#include"sound/SoundSource.h"

class BackGround;
class Stage;
class Stage2;		//����
//Player�֘A
class Player;
class GameCamera;
class Enemy;		//slime
class Enemy2;		//mushroom
class Item;
//UI�֘A
class UI;
class GameCrear;
class GameClear;
class NowLoading;
class Help;
class Chat;
class BGM;

class Sum;
class Num;
//�Q�[��
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void s_Light();			//�X�|�b�g���C�g
	void p_Light();			//�|�C���g���C�g
	void TurnCount();		//�^�[����
	void Crear();			//CLEAR�̏���
	void StageZero();		//�z�u�@
	void StageOne();		//�z�u�A
	void StageTwo();		//�z�u�B
	void Render(RenderContext& rc);

	// �Q�[����{���ɏI���Ƃ��p
	void GameEnd();

	void GameDelete();

	// �����o�ϐ�
	FontRender fontRender;
	SpotLight spotLight;		// �X�|�b�g���C�g
	SpotLight spotLight_enemy;	// �X�|�b�g���C�g
	SpotLight spotLight_item;	// �X�|�b�g���C�g
	PointLight pointLight;		// �|�C���g���C�g
	Vector3 player_position;	// player�̍��W

	SkyCube* skyCube;		// �X�J�C�L���[�u
	SoundSource* gameBGM;	// BGM

	// NewGO�p
	BackGround* backGround;	// �w�i
	Stage* stage;			// �X�e�[�W
	Stage2* stage2;			// �X�e�[�W
	Player* player=nullptr;			// �v���C���[
	GameCamera* gameCamera;	// �J����
	UI* ui;					// UI
	Help* help;				// �w���v
	GameCrear* gamecrear;	// �Q�[���N���A
	GameClear* gameClear;	// �N���A���
	NowLoading* nowLoading;
	Chat* chat;

	BGM* bgm;

	Sum* sum;				// �v�Z�p
	Num* num;				// ���l�Ǘ��p

	/// <summary>
	/// Chat�N���X�̉摜��\���������ǂ�����x�������ʂ���
	/// ������ bool�^
	/// </summary>
	/// <param name="false">�\�����Ă��Ȃ�</param>
	/// <param name="true">�\�����Ă���</param>
	void setDrawFlag(bool a) {
		drawFlag = a;
	}

	// �V�X�e���p
	float animTimer = 1.0f;

	bool drawFlag = false;				// ��b�p�摜��\���������ǂ���
	bool TitleNewGO = false;			// �^�C�g���𐶐��������ǂ���
	bool ResultNewGO = false;			// ���U���g�𐶐��������ǂ���
	bool CountFlag = false;				// �K�w�̃J�E���g�𐧌䂷��

	// �Q�[�������l
	float Timer = 0.0f;					// �N���A�^�C��
	bool DeleteFlag = false;			// �폜���邩�ǂ���

	float p_scale = 50.0f;				// �|�C���g���C�g�̑傫��
	bool nowLoadingMake = false;
};