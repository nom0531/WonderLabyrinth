#pragma once

// �X�e�[�g�i�[�N���X
class Num:public IGameObject
{
public:
	bool CameraAdjustmentFlag = false;		// �J�����̈ʒu�𒲐߂���t���O

	bool clearFlag = false;			// �Q�[���̃N���A����
	bool stopFlag = false;			// true :�Q�[�����̑���ȂǂȂǂ����ׂĒ�~����
	bool NewGoFlag = false;			// �C�x���g�p�t���O (����)
	bool movePlayer = false;		// �C�x���g�p�ړ��t���O
	bool getItem = false;			// �C�x���g�p�A�C�e���l���t���O

	int turn = 1;					// 1:�v���C���[�@2:MOB
	int stageState = 0;				// 0:�`���[�g���A���@1:�����@2:���A
	int stageNum = 0;				// �X�e�[�W�̃}�X��

	int enemyNum = 0;				// �G�l�~�[�̐�

	int Rundum_StageNum = 0;		// �X�e�[�W�̃����_�������̒l

	bool drawChatFlag = false;		// �`���b�g��`�悵�����ǂ���
};

