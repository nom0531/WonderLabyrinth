#pragma once

class Game;
class Player;
class UI;
class GameClear;
class Num;
class GameStop;

// �v�Z�p�N���X
class Sum:public IGameObject
{
public:
	Sum();
	~Sum();

	void Update();
	void ItemGage();										// �A�C�e���Q�[�W
	int CrearScore(int item,int stage,int hp);				// �N���A�X�R�A
	//void MoveSprite();									// �摜���㉺�ɓ������@�g�p���Ȃ�

	// �����o�ϐ�
	Player* player;
	UI* ui;
	GameClear* gameClear;
	Num* num;
	GameStop* gameStop;

	// <summary>
	// �����g�𗘗p���ĉ摜���㉺�ɓ�����
	// </summary>
	// <param name="int">���b�ň�����邩���w�肷�� (60�J�E���g/�b) </param>
	// <param name="float">�ړ��l�̕����w�肷��</param>
	//void setMoveFromSin(int a ,float b) {
	//	syuuki = a;
	//	moveMin_Max = b;
	//}
	// �����g�𗘗p�����v�Z��̒l���l������
	//float getMoveAfterFromSin() {
	//	return AfterPos;
	//}

	bool clearFlag = false;			// �N���A���Ă��邩�ǂ���

	// �A�C�e���Q�[�W�p
	int nowGage = 800;				// ���݂̃Q�[�W��(�f�t�H���g 600)
	const int maxGage = 800;		// �ő�l
	const int minGage = 0;			// �ŏ��l
	const int addGage = 200;		// �񕜗�
	float Scale_x = 0.0f;			// �X�P�[���̒l

	// �X�R�A�p
	const int addPoint_stage = 10;	// ���Z�X�R�A
	const int addPoint_item = 100;
	const int addPoint_hp = 1000;

	//int itemNum = 0;				// �l���A�C�e����
	//int stageNum = 0;				// �X�e�[�W�N���A��
	//int HPNum = 0;				// �c��HP

//private:
//
//	float AfterPos = 0.0f;			// �v�Z��̍��W
//
//	float PI = 3.141592654f;		// �~����
//	float Count = 0;				// ��b�ԂɃJ�E���g����J�E���^
//	int syuuki = 0;					// ����
//	float moveMin_Max = 0.0f;		// �ړ���
};

