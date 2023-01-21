#include "stdafx.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Num.h"

GameCamera::GameCamera()
{
	// near,far�̐ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// �����_���王�_�܂ł̃x�N�g��
	cameraPos.Set(0.0f, 125.0f, -250.0f);
	
	num = FindGO<Num>("num");		// �C���X�^���X��T��
	c_stageState = num->stageState;	// �X�e�[�W�̏��
	return true;
}

void GameCamera::Update()
{
	// ����s�\�łȂ��Ƃ�
	if (num->stopFlag == false) {
		// �J�����؂�ւ�
		switch (cameraState) {
		//�m�[�}����]
		case 0:Normal();
			break;
		// ���o�[�X��]
		case 1:Reverse();
			break;
		}
	}
	// �����̓J�����̒��߂�����悤�Ɏw������Ă���Ƃ�
	else if (num->CameraAdjustmentFlag == true) {
		// �J�����؂�ւ�
		switch (cameraState) {
			//�m�[�}����]
		case 0:Normal();
			break;
			// ���o�[�X��]
		case 1:Reverse();
			break;
		}
	}

	// �{�^�����������Ƃ�
	if (g_pad[0]->IsTrigger(enButtonX)) {
		// ���o�[�X�֐؂�ւ�
		if (cameraState == 0) {
			cameraState = 1;
		}
		// �m�[�}���֐؂�ւ�
		else if (cameraState == 1) {
			cameraState = 0;
		}
	}
}

void GameCamera::Normal()
{
	// �����_
	Vector3 c_position;				// �J�����̈ʒu
	switch (c_stageState) {
	case 0:
		// �`���[�g���A��
		c_position = {100.0f, 10.0f, 2.0f};

		break;
	case 1:
	case 2:
		// ����ȊO
		c_position = {200.0f, 10.0f, 2.0f};
		num->CameraAdjustmentFlag == false;
		break;
	}
	
	// �����_
	Vector3 target = c_position;
	//Vector3 target = Vector3::Zero;
	target.y += 50.0;
	target.z += 80.0;

	Vector3 cameraPosOld = cameraPos;

	// �p�b�h���͂ŃJ��������
	float x = g_pad[0]->GetLStickXF();
	float y = g_pad[0]->GetLStickYF();
	// Y��
	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, 0.1 * x);
	rot.Apply(cameraPos);
	// X��(Normal)
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, cameraPos);
	axisX.Normalize();
	rot.SetRotationDeg(axisX, -1.5f * y);
	rot.Apply(cameraPos);
	// �J�����̉�]�̏�����`�F�b�N����B
	// �����_���王�_�܂ł̃x�N�g���𐳋K������B
	// ���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	// �傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = cameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		// �J����������������B
		cameraPos = cameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		// �J�����������������B
		cameraPos = cameraPosOld;
	}

	// ���_���v�Z����B
	Vector3 pos = target + cameraPos;
	// ���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	// �J�����̍X�V�B
	g_camera3D->Update();

	//target = Vector3::Zero;		// �f�o�b�O�p
	//pos = { 0.0f,80.0f,-150.0f };	// �f�o�b�O�p
}

void GameCamera::Reverse()
{
	// �����_
	Vector3 c_position;				// �J�����̈ʒu
	switch (c_stageState) {
	case 0:
		c_position = { 100.0f, 10.0f, 2.0f };
		break;
	case 1:
	case 2:
		c_position = { 200.0f, 10.0f, 2.0f };
		num->CameraAdjustmentFlag == false;
		break;
	}

	Vector3 target = c_position; // �����_
	// Vector3 target = Vector3::Zero;
	target.y += 50.0;
	target.z += 80.0;

	Vector3 cameraPosOld = cameraPos;
	// �p�b�h���͂ŃJ��������
	float x = g_pad[0]->GetLStickXF();
	float y = g_pad[0]->GetLStickYF();
	// Y��
	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, 0.1 * x);
	rot.Apply(cameraPos);
	// X��(Reverse)
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, cameraPos);
	axisX.Normalize();
	rot.SetRotationDeg(axisX, 1.5f * y);
	rot.Apply(cameraPos);

	// �J�����̉�]�̏�����`�F�b�N����B
	// �����_���王�_�܂ł̃x�N�g���𐳋K������B
	// ���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	// �傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = cameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		// �J����������������B
		cameraPos = cameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		// �J�����������������B
		cameraPos = cameraPosOld;
	}

	// ���_���v�Z����B
	Vector3 pos = target + cameraPos;
	// ���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	// �J�����̍X�V�B
	g_camera3D->Update();
}