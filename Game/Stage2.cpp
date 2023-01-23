#include "stdafx.h"
#include "Stage2.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Num.h"

Stage2::Stage2()
{
}

void Stage2::Stage()
{
	// �C���X�^���X��T��
	num = FindGO<Num>("num");

	// ���C�g���[�X��؂�
	//modelRender.SetRaytracingWorld(false);

	int stage[9][9] = {
		{ 2,2,2,2,0,2,2,2,2 },
		{ 2,2,2,2,2,2,2,3,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,1,2,2,2,2 },
		};

	int stage_0[9][9] = {
		{ 2,2,5,2,0,2,2,2,4 },
		{ 2,2,2,2,2,2,2,3,2 },
		{ 2,4,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,3,2,2,2 },
		{ 3,2,2,2,2,2,2,5,2 },
		{ 2,2,2,4,2,2,2,2,2 },
		{ 2,2,5,2,2,2,2,4,2 },
		{ 3,2,2,2,2,2,3,2,2 },
		{ 4,3,2,2,1,2,2,2,2 },
	};

	int stage_1[9][9] = {
		{ 4,2,2,2,0,2,2,3,4 },
		{ 3,2,2,2,2,2,4,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,4,2,2,2,3,2,2,3 },
		{ 2,2,2,3,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,3 },
		{ 2,4,2,2,2,2,5,2,2 },
		{ 2,2,2,2,2,2,2,2,4 },
		{ 3,4,3,2,1,2,2,3,3 },
	};

	int stage_2[9][9] = {
		{ 2,4,5,3,0,2,2,3,4 },
		{ 2,2,2,2,2,3,2,2,2 },
		{ 2,5,2,2,2,2,2,2,2 },
		{ 2,2,3,2,2,3,2,2,2 },
		{ 3,2,2,2,2,2,2,2,2 },
		{ 2,2,5,2,2,2,2,2,3 },
		{ 2,2,2,2,2,2,4,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,3,2,2,1,2,5,3,2 },
	};

	int stage_3[9][9] = {
		{ 4,2,2,2,0,2,2,2,2 },
		{ 2,2,2,2,2,2,2,4,2 },
		{ 2,2,2,2,2,2,5,2,2 },
		{ 2,2,4,2,2,2,2,2,2 },
		{ 2,2,2,2,3,2,2,2,2 },
		{ 2,3,2,2,2,2,2,5,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,4,2,3 },
		{ 2,2,2,2,1,2,2,2,5 },
	};

	int stage_4[9][9] = {
		{ 4,2,2,2,0,3,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2 },
		{ 2,2,3,2,2,2,3,5,2 },
		{ 2,2,2,2,2,2,4,2,2 },
		{ 3,2,2,2,2,2,2,2,2 },
		{ 2,2,5,2,2,2,3,2,2 },
		{ 2,2,2,2,2,2,2,2,3 },
		{ 2,2,2,3,2,2,2,5,2 },
		{ 3,4,2,2,1,4,2,2,2 },
	};

	// �f�o�b�O�p
	//stageState = 4;

	stageState = rand() % 5;				// 0�`4�Ń����_���Ȓl��Ԃ�
	num->Rundum_StageNum = stageState;		// Num�ɂǂ̃X�e�[�W�𐶐�������������

	//�X�e�[�W���
	switch (stageState) {
	case 0:
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				stage[j][i] = stage_0[j][i];
			}
		}
		break;
	case 1:

		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				stage[j][i] = stage_1[j][i];
			}
		}

		break;
	case 2:
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				stage[j][i] = stage_2[j][i];
			}
		}

		break;
	case 3:

		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				stage[j][i] = stage_3[j][i];
			}
		}

		break;
	case 4:

		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				stage[j][i] = stage_4[j][i];
			}
		}

		break;
	 default:
		break;
	}

	// �e�N�X�`����ݒ�
	switch (texState) {
	case 1:
		// ����
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				modelRender[(i * 9) + j].SetRaytracingWorld(false);
				
				if (stage[i][j] == 0 || stage[i][j] == 1) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/start_goal.tkm");	// �X�^�[�g �S�[��
					//boxCollider.Create({ 20.0f,5.0f,20.0f });
					//boxCollider.GetBody();
				}
				else if (stage[i][j] == 2) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/grass.tkm");		// ����
				}
				else if (stage[i][j] == 3) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/grass_reef.tkm");	// �����i���j
					stageFlag[i][j] = 1;
				}
				else if (stage[i][j] == 4) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/grass_reef_b.tkm");	// �����i���A�j
					stageFlag[i][j] = 1;
				}
				else if (stage[i][j] == 5) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/grass_rock.tkm");	// �����i��j
					stageFlag[i][j] = 1;
				}
			}
		}
		break;
	case 2:
		// ���A
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {

				modelRender[(i * 9) + j].SetRaytracingWorld(false);
				
				if (stage[i][j] == 0 || stage[i][j] == 1) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/start_goal.tkm");	// �X�^�[�g �S�[��
				}
				else if (stage[i][j] == 2) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/cave.tkm");			// ���A
				}
				else if (stage[i][j] == 3) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/cave_rock.tkm");	// ���A�i��j
					stageFlag[i][j] = 1;
				}
				else if (stage[i][j] == 4) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/cave_rock_a.tkm");	// ���A�i��A�j
					stageFlag[i][j] = 1;
				}
				else if (stage[i][j] == 5) {
					modelRender[(i * 9) + j].Init("Assets/modelData/model/stage/cave_water.tkm");	// ���A�i����)
					stageFlag[i][j] = 1;
				}
			}
		}
		break;
	}
}

void Stage2::SetUp()
{
	// ���W�̐ݒ�
	Vector3 pos = Vector3::Zero;
	int num = 0;

	Stage();

	// �����̊�_
	Vector3 DefPos = { 0.0f,0.0f,400.0f };

	// 9�~9
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {

			pos = DefPos;

			pos.x += i * 50.0f;
			pos.y = 0.0f;
			pos.z -= j * 50.0f;

			position = pos;
			modelRender[num].SetPosition(pos);
			num++;
		}
	}

	// �X�e�[�W���������_���ɕԂ�
	stageState = rand() % 5;
}

Stage2::~Stage2()
{
}

bool Stage2::Start()
{
	// �v���C���[�̃C���X�^���X��T��
	player = FindGO<Player>("player");
	return true;
}

void Stage2::Update()
{
	// �S�[���ɂ��ǂ蒅�����Ƃ�
	if (clearPosition2D.y == player->position2D.y && clearPosition2D.x == player->position2D.x) {
		player->stageClear = true;
		clearFlag = true;
	}

	// 9�~9
	for (int i = 0; i < 81; i++) {
		modelRender[i].Update();
	}
}

void Stage2::Render(RenderContext& rc)
{
	// 9�~9
	for (int i = 0; i < 81; i++) {
		modelRender[i].Draw(rc);
	}
}
