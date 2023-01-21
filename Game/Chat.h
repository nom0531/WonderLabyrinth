#pragma once

class Num;
class Sum;
class UI;

// ��b�p�N���X
class Chat:public IGameObject
{
public:
	Chat();
	~Chat();

	void Update();
	void Name();						// �\�����̔���
	void RundumChat();					// �����_���`���b�g
	void RundumUpdate();				// �����_���`���b�g�p�̏���
	void Button_SinMove();		// �X�v���C�g���㉺������
	void EventChat();					// �`���[�g���A���p��b
	void EventUpdate();					// �`���[�g���A���p�̏���
	void Render(RenderContext& rc);

	// �����_���Ȓl��n��
	int getRundumNum() {
		// 1�`10�̒l�������_���ɕԂ�
		return rand() % 10 + 1;
	}

	// �����o�ϐ�
	SpriteRender spriteRender_npc;		// �L�����N�^�[
	SpriteRender spriteRender_textbox;	// �e�L�X�g�{�b�N�X
	SpriteRender spriteRender_button;	// �{�^��

	FontRender fontRender_name;			// �L�����N�^�[���i�[�p
	FontRender* fontRender = nullptr;	// ��b���e

	Num* num;							// �l�i�[�p
	Sum* sum;							// �v�Z�p

	UI* ui;

	// ����
	float waitTimer = 1.0f;				// �\������܂ł̑҂�����
	float chatSpeed = 0.02;				// �����̕\�����x

	bool StopDrawFlag = false;			// �������ꎞ�I�ɔ�\���ɂ���
	bool drawChatFlag = false;			// ������\�����I�������ǂ���
	bool NextchatFlag = false;			// ���̕�����\�����邩�ǂ���
	bool playToSeFlag = true;			// �L�����N�^�[�̉������Đ����邩�ǂ���

	bool eventFlag = false;				// �C�x���g�������_�����̔��ʁ@true�ŃC�x���g��
	bool rundumChatStart = false;		// �����_���`���b�g���J�n����
	bool eveneStartFlag = false;		// true:�����_����b�E�C�x���g���J�n����

	// ��b�����p
	int chatState = 0;					// �`���[�g���A���̓��e�̎w��
	int chatState_end = 20;				// ��b�I�����̒l

	int rundumState = 0;				// �����_���e�L�X�g�̓��e�̎w��
	int clearState = 0;					// �����B���X�e�[�g 1:������ 2:�A�C�e���̊l�� 3:�Q�[���N���A 4:�Q�[���I��

	// ���̈ړ������p
	float movePos = 1.0f;				// ���Z����ړ��l (y��)
	float sumPos = 0.0f;
	int moveState = 0;					// 0:�������Ɉړ��@1:������Ɉړ�
};

