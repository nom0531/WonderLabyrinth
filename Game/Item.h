#pragma once

class Player;
class Sum;
class Num;
class Stage;
class Stage2;
// �A�C�e��
class Item :public IGameObject
{
public:
	Item();
	~Item();

	void Update();
	void Rot();					// ��]����
	void Get();					// �l������
	void Render(RenderContext& rc);

	// �����o�ϐ�
	ModelRender modelRender;

	Quaternion rot;
	Vector3 position;			// ���W

	Player* player;				// �v���C���[
	Sum* sum;					// �v�Z�p
	Num* num;					// ���l�Ǘ��p
	Stage* stage;				// �X�e�[�W
	Stage2* stage2;
};

