#include "stdafx.h"
#include "Item.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Player.h"
#include "Sum.h"
#include "Stage.h"
#include "Stage2.h"
#include "Num.h"

Item::Item()
{
	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(23, "Assets/sound/Get_Item.wav");

	modelRender.Init("Assets/modelData/model/stage/item.tkm");
	modelRender.SetScale(1.0f, 1.3f, 1.0f);

	// �C���X�^���X��T��
	player = FindGO<Player>("player");
	sum = FindGO<Sum>("sum");
	num = FindGO<Num>("num");

	// �X�e�[�W�̏��
	if (num->stageState == 0) {
		stage = FindGO<Stage>("stage");
	}
	else {
		stage2 = FindGO<Stage2>("stage2");
	}
}

Item::~Item()
{
}

void Item::Update()
{
	Rot();		// ��]����
	Get();		// �A�C�e���̊l������

	// �{�҂̎�
	if (num->stageState == 2) {
		// �X�e�[�W���N���A������
		if (stage2->clearFlag == true) {
			DeleteGO(this);
		}
	}

	// �Q�[�����N���A�����Ƃ�
	if (num->clearFlag == true) {
		DeleteGO(this);
	}

	modelRender.SetPosition(position);
	modelRender.Update();
}

void Item::Rot()
{
	rot.AddRotationDegY(2.0f);
	modelRender.SetRotation(rot);
}

void Item::Get()
{
	// �v���C���[�ƃA�C�e���̍��W�̍������߂�
	Vector3 itemGet = player->position - position;
	// ������20.0f�ȉ�
	if (itemGet.Length() <= 10.0f) {
		// SE

		player->itemCount++;	// �J�E���g

		if (num->stageState == 0) {
			num->getItem = true;	// �C�x���g�p�t���O
		}

		// ���ʉ����Đ�
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(23);					// get_item
		se->Play(false);				// ���[�v���Ȃ�
		se->SetVolume(3.5f);			// ���ʂ̐ݒ������

		DeleteGO(this);
	}
}

void Item::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}