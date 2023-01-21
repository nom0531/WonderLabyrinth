#pragma once
#include "Sum.h"

class Game;
class GameOver;
class Stage;
class Stage2;
class Player;
class GameCamera;
class NowLoading;
class Sum;
class Num;
// ���[�U�[�C���^�[�t�F�[�X
class UI:public IGameObject 
{
public:
	UI();
	~UI();

	void Update();
	void Render(RenderContext& rc);
	void TurnCount();					// �^�[�����̃J�E���g
	void TurnOne();
	void TurnTen();
	void ItemGage();
	void PlayerHP();					// HP
	void Camera();						// �J����
	void Crear();						// �X�e�[�W�N���A

	// �����o�ϐ�
	SpriteRender spriteRender_HP;		// HP�o�[
	SpriteRender spriteRender_help;		// �w���v�A�C�R��
	SpriteRender spriteRender_camera;	// �J�����A�C�R��
	SpriteRender spriteRender_crear;	// �N���A

	SpriteRender spriteRender_turn;		// �K�w��
	SpriteRender spriteRender_countOne;
	SpriteRender spriteRender_countTen;

	SpriteRender spriteRender_itemgage;	// �A�C�e���Q�[�W
	SpriteRender spriteRender_item;
	SpriteRender spriteRender_itemback;

	SpriteRender spriteRender_chat;		// �L�����N�^�[�̉摜
	FontRender fontRender_chat;			// �e�L�X�g


	Vector3 position_HP;				// HP�o�[�̍��W
	Vector3 position_help;				// �w���v
	Vector3 position_camera;			// �J����
	Vector3 position_chat;				// �摜�̈ʒu

	Game* game;
	GameOver* gameover;
	Stage* stage;
	Stage2* stage2;
	Player* player;
	GameCamera* gameCamera;
	NowLoading* nowLoading;
	Sum* sum;
	Num* num;

	// �X�P�[���l��n��
	void SetNowX(float x)
	{
		nowGage = x;
	}

	bool stopFlag = false;

	float i_Timer = 20.0f;				// �A�C�e���Q�[�W�p�^�C�}�[
	int UI_playerHP = 0;
	int UI_cameraState = 0;
	int UI_stageState = 0;
	int UI_stageNum = 1;				// �X�e�[�W���i�[�p
	int turn_one = 0;					// 1�̈�
	int turn_ten = 0;					// 10�̈�
	int itemSum = 0;					// �ŏI�A�C�e����
	int ChatState = 0;					// ��b�X�e�[�g
	char chat[100];						// ��b���e
private:
	float nowGage = 0.0f;				// ���݂̃A�C�e���Q�[�W
};

