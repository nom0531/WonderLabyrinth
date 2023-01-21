#pragma once

class NowLoading;
class GameStop;

// �w���v
class Help:public IGameObject
{
public:
	Help();
	~Help();

	void Update();
	void Sprite();						// �摜����
	void SetSprite();
	void Render(RenderContext& rc);

	// �����o�ϐ�
	SpriteRender spriteRender_back;		// �w�i
	SpriteRender spriteRender;			// ���e

	NowLoading* nowLoading;
	GameStop* gameStop;

	bool DeleteFlag = false;

	float animTimer = 2.0f;
	int spriteState = 0;				// 0:�V�т��� 1:������� 2:�A�C�R���̐���
};

