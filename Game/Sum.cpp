#include "stdafx.h"
#include "Sum.h"
#include "Game.h"
#include "Player.h"
#include "UI.h"
#include "GameClear.h"
#include "Num.h"
#include "GameStop.h"

#include "Math.h"

Sum::Sum()
{
	// �C���X�^���X��T��
	ui = FindGO<UI>("ui");
	player = FindGO<Player>("player");
	num = FindGO<Num>("num");

	gameStop = FindGO<GameStop>("gameStop");
}

Sum::~Sum()
{
}

void Sum::Update()
{
	if (clearFlag)
	{
		return;
	}
	// num �����݂��Ȃ��Ƃ��͎��s���Ȃ�
	if(num != nullptr && ui != nullptr){
		ItemGage();
	}
}

void Sum::ItemGage()
{	
	// �e�L�X�g�Ȃǂ�\�����Ă��Ȃ��Ƃ�
	if (num->stopFlag == false) {
		// �`���[�g���A���ł͈��l�ȉ��ɂȂ�Ȃ��悤�ɂ���
		if (num->stageState == 0 && nowGage <= 150) {
			nowGage = 150;
		}

		// ����s�\�łȂ��Ƃ�
		if (gameStop->StopFlag == false || num->stopFlag == false) {
			// �Q�[�W�����炷
			nowGage -= g_gameTime->GetFrameDeltaTime();
		}

		// �X�P�[���̒l���v�Z����
		Scale_x = (float)nowGage / (float)maxGage;

		// �A�C�e����������Ƃ�
		if (player->itemCount != ui->itemSum) {
			ui->itemSum = player->itemCount;	// �A�C�e���������L����
			// �񕜂���
			if (nowGage >= maxGage) {
				nowGage = maxGage;				// 100�ȏ�ɂȂ�Ȃ��悤�ɂ���
			}
			else if (nowGage <= minGage) {
				nowGage = minGage;				// 0�ȉ��ɂȂ�Ȃ��悤�ɂ���
			}
			else {
				nowGage += addGage;
			}
		}

		// �Q�[�W���傫���l�ɂ͂Ȃ�Ȃ��悤�ɂ���
		if (Scale_x >= 1.0f) {
			Scale_x = 1.0f;
		}

		// �l��n��
		ui->SetNowX(Scale_x);
	}
}

int  Sum::CrearScore(int item, int stage, int hp)
{
	// �X�R�A���v�Z
	// �萔����Z���ăX�R�A�Ƃ���
	int sum = 0;

	sum += item * addPoint_item;
	sum += stage * addPoint_stage;
	sum += hp * addPoint_hp;

	// �v�Z�����l��߂�l�Ƃ���
	return sum;
}