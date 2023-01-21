#pragma once
#include "sound/SoundSource.h"

class Sum;
class NowLoading;
class BGM;
class GameStop;

// �Q�[���N���A
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();

	void Update();
	void Font();					// �����̏o��
	void Render(RenderContext& rc);

	// �����o�ϐ�
	SpriteRender spriteRender;
	SpriteRender spriteRender_hpSaved;
	SpriteRender spriteRender_itemGet;
	SpriteRender spriteRender_passStage;
	// �N���A�^�C��
	FontRender fontRender_time;
	FontRender fontRender_Cleartime;
	// �X�e�[�W��
	FontRender fontRender_stage;
	FontRender fontRender_Sumstage;
	// �A�C�e����
	FontRender fontRender_item;
	FontRender fontRender_Sumitem;
	// HP
	FontRender fontRender_hp;
	FontRender fontRender_Sumhp;
	// �����X�R�A
	FontRender fontRender_score;
	FontRender fontRender_Sumscore;

	BGM* bgm;
	Sum* sum;
	GameStop* gameStop;
	NowLoading* nowLoading;

	// �X�R�A��ݒ肷�� (����,�X�e�[�W��,�A�C�e���� �c��HP)
	void setClearNum(float t, int s, int i,int h) {
		clearTimer = t;
		clearStage = s;
		itemSum = i;
		HP = h;
	}

	float waitTimer = 2.0f;		// �^�C�}�[
	bool deleteFlag = false;

	int Score = 0;					// �X�R�A�i�[�p�ϐ�

private:
	float clearTimer = 0.0f;	// �N���A�^�C��
	int clearStage = 0;			// �ʉ߃X�e�[�W��
	int itemSum = 0;			// �A�C�e����
	int HP = 0;					// �c��HP
};

