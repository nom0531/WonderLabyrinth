#pragma once
#include"sound/SoundSource.h"

class NowLoading;
class BGM;
class GameStop;

// �^�C�g��
class Title :public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void Render(RenderContext& rc);
	void Anim();// �A�j���[�V����

	// �����o�ϐ�
	SpriteRender spriteRender;
	SpriteRender spriteRender_button;	// �{�^��

	// NewGO�p
	NowLoading* nowloading;
	BGM* bgm;
	GameStop* gameStop;

	bool DeleteFlag = false;			// �폜���邩�ǂ���

	float animTimer = 2.0f;				// �^�C�}�[
	int animState = 0;					// �J��
};

