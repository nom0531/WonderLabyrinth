#pragma once

class Num;
// �Q�[���J����
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();
	void Normal();	// ����(�m�[�}���ݒ�)
	void Reverse();	// ����(���o�[�X�ݒ�)

	// �����o�ϐ�
	SpriteRender spriteRender;
	Vector3 cameraPos;		// �����_���王�_�ւ̃x�N�g��

	Num* num;

	int cameraState = 0;	// ��]�؂�ւ�
	int c_stageState = 0;	// �J�����̈ʒu�؂�ւ�
};

