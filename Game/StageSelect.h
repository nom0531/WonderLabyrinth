#pragma once
#include"sound/SoundSource.h"

class NowLoading;
class Stage;
class Num;
class BGM;
class GameStop;

// �X�e�[�W�Z���N�g
class StageSelect:public IGameObject
{
public:
	StageSelect();
	~StageSelect();

	void Update();
	void Select();						// �摜�̐؂�ւ�
	void Transition();					// ��ʂ̑J�ڂ��s��
	void Render(RenderContext& rc);

	bool Start();

	// �����o�ϐ�
	SpriteRender spriteRender;
	SpriteRender spriteRender_text;
	SpriteRender spriteRender_sprite;
	SpriteRender spriteRender_button;	// �{�^��

	SoundSource* selectBGM;				// BGM

	// NewGO
	NowLoading* nowloading;				// LOADING���
	Stage* stage;						// �X�e�[�W
	BGM* bgm;							// BGM
	GameStop* gameStop;

	bool DeleteFlag = false;			// �폜���邩�ǂ���

	float alpha = 0.0f;					// �����x

	int selectState = 0;				// 0:�`���[�g���A�� 1:���� (���A�͔h��)
	int stageState = 0;					// ���ʗp�X�e�[�g

	float animTimer = 2.0f;				// �^�C�}�[
};

