#pragma once
class Title;
class Game;
class StageSelect;
class GameClear;
class Sum;
class Help;
class Num;
class BGM;
class GameStop;

// ���[�h
class NowLoading:public IGameObject
{
public:
	NowLoading();
	~NowLoading();

	void Update();
	void Render(RenderContext& rc);

	void NewScene();

	bool Start();

	// �����o�ϐ�
	SpriteRender spriteRender_back;	// �w�i

	// NewGO
	Title* title;				// �^�C�g��
	Game* game;					// game�{��
	StageSelect* stageselect;	// �X�e�[�W�Z���N�g
	GameClear* gameClear;		// ���U���g
	Help* help;					// ������

	BGM* bgm;
	Sum* sum;
	Num* num;
	GameStop* gameStop;

	float LoadTimer = 2.0f;
	float  animTimer = 2.0f;
	float alpha = 0.0f;			// �w�i�̃��l
	int loadState = 0;			// 1:�Q�[���{�� 2:�^�C�g�� 3:�X�e�[�W�I�� 4:������
	int stageState = 0;			// �X�e�[�W�̎w��

	bool makeFlag = false;
	bool migrationToTitleFlag = false;		// �����ȊO����ڍs�����Ƃ��Ƀ^�C�g����BGM�����炷
	bool NOTchangeBGMFlag = false;		// BGM��ύX���Ȃ�

	// �X�R�A�i�[�p
	float Cleartime = 0.0f;

	// �X�R�A�p�ϐ�
	int Itemnum = 0;
	int Stagenum = 0;
	int HPnum = 0;

	bool waitFlag = false;
	int waitFlame = 2;
};

