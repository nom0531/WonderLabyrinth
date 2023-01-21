#include "stdafx.h"
#include "Chat.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Num.h"
#include "Sum.h"
#include "UI.h"

Chat::Chat()
{
	// ���ʉ�
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(25, "Assets/sound/Aru_ChatEnd.wav");

	// �C���X�^���X��T��
	num = FindGO<Num>("num");

	sum = FindGO<Sum>("sum");

	// �L�����N�^�[
	spriteRender_npc.Init("Assets/sprite/aru.DDS", 411.0f, 407.0f);
	spriteRender_npc.SetPosition({ 380.0f,10.0f,0.0f });
	spriteRender_npc.SetScale({ 1.2f, 1.2f, 0.0f });

	// �e�L�X�g�{�b�N�X
	spriteRender_textbox.Init("Assets/sprite/UI/textBox.DDS", 1300.0f, 400.0f);
	spriteRender_textbox.SetPosition({ 0.0f,-250.0f,0.0f });
	spriteRender_textbox.SetScale({0.8f, 0.8f, 0.0f});
	spriteRender_textbox.SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	// ��
	spriteRender_button.Init("Assets/sprite/UI/button_white.DDS", 66.0f, 55.0f);
	spriteRender_button.SetPosition({ 450.0f,-350.0f,0.0f });
	spriteRender_button.SetScale({ 0.8f, 0.8f, 0.0f });

	// ���O
	fontRender_name.SetText(L"�A��");
	fontRender_name.SetPosition(-440.0f, -95.0f, 0.0f);
}

Chat::~Chat()
{
}

void Chat::Name() 
{
	// �C�x���g��
	if (eventFlag == true) {
		EventChat();
	}
	// �����_���`���b�g
	else if (rundumChatStart==true) {
		// �����_���Ȓl���󂯂Ƃ�
		rundumState = getRundumNum();
		RundumChat();
	}
}

void Chat::RundumChat()
{
	// ���Z�b�g
	if (fontRender != nullptr) {
		delete fontRender;
	}
	fontRender = new FontRender;
	fontRender->SetPosition(-470.0f, -200.0f, 0.0f);

	switch (rundumState) {
	case 1:
		fontRender->SetTextOkuri(L"�X���C���͓G�ΓI����Ȃ��̃J�i\n��킸�ɐ؂蔲�����邩��?", chatSpeed, playToSeFlag);
		break;
	case 2:
		fontRender->SetTextOkuri(L"�L�m�R�͒ǂ������Ă���݂������l\n�Ȃɂ�����������̂��ȁE�E�E?", chatSpeed, playToSeFlag);
		break;
	case 3:
		fontRender->SetTextOkuri(L"���������@�Q�[�W��0�ɂȂ����Ⴄ��\n�s���ł��Ȃ��Ȃ邩�璍�Ӄ_���B", chatSpeed, playToSeFlag);
		break;
	case 4:
		fontRender->SetTextOkuri(L"�s���s�\�ɂȂ�����?\n�E�E�E���[��@�{�N���Ȃ�Ƃ����郈!", chatSpeed, playToSeFlag);
		break;
	case 5:
		fontRender->SetTextOkuri(L"�`���Y�ꂿ����Ă��P�h\n�G��|���Ă��A�C�e���𗎂Ƃ���!", chatSpeed, playToSeFlag);
		break;
	case 6:
		fontRender->SetTextOkuri(L"�Q�[�W��ۂ��Ƃ͑厖������\n������HP����؂ɂ��ăl!", chatSpeed, playToSeFlag);
		break;
	case 7:
		fontRender->SetTextOkuri(L"�u�������Ƃ���START�{�^��!�v\n�o���Ă����Ă����Ɗ������i!", chatSpeed, playToSeFlag);
		break;
	case 8:
		fontRender->SetTextOkuri(L"�J�����̏㉺�ړ���X�{�^����\n�؂�ւ����郈�@�����Ă݂Ă�!", chatSpeed, playToSeFlag);
		break;
	case 9:
		fontRender->SetTextOkuri(L"�U�������Ƃ��ɂ��G��������!\n����@���܂��g���Ȃ��J�i�E�E�E�B", chatSpeed, playToSeFlag);
		break;
	case 10:
		fontRender->SetTextOkuri(L"�E�E�E�Ƃ����\n�����[�Ƃڂ���E�E�E���ĉ�?", chatSpeed, playToSeFlag);
		break;
	}
}

void Chat::EventChat()
{
	// ���Z�b�g
	if (fontRender != nullptr) {
		delete fontRender;
	}
	fontRender = new FontRender;
	fontRender->SetPosition(-470.0f, -200.0f, 0.0f);
	
	// ��b���e
	// ���݂̊Ԋu�ł�17�����̎��_��\n
	switch (chatState) {
	case 0:
		// ���[�h���ɕ\�������Ă���̂�SE�͖���
		fontRender->SetTextOkuri(L"�悤����!�`���[�g���A����!", chatSpeed, false);
		break;
	case 1:
		fontRender->SetTextOkuri(L"�{�N�̓A���@��낵����!", chatSpeed, playToSeFlag);
		break;
	case 2:
		fontRender->SetTextOkuri(L"�܂��́E�E�E�ړ�����ׂ�\n��{����������炢!", chatSpeed, playToSeFlag);
		break;
	case 3:
		fontRender->SetTextOkuri(L"�u�ړ��͏\���L�[�v����!\n���ꂶ��@���������Ă݂悤!", chatSpeed, playToSeFlag);
		break;
	case 4:
		break;
	case 5:
		fontRender->SetTextOkuri(L"���񂤂�@�΂�����_�l!", chatSpeed, playToSeFlag);
		break;
	case 6:
		fontRender->SetTextOkuri(L"�Ƃ���f�E�E�E����̐��Q�[�W��\n�������������R�g�ɋC���t����?", chatSpeed, playToSeFlag);
		break;
	case 7:
		fontRender->SetTextOkuri(L"���̃Q�[�W�́@�s���ł���c�莞�ԁB\n���{�ɂ���Ԃǂ�ǂ񌸂��Ă����񂾁B", chatSpeed, playToSeFlag);
		break;
	case 8:
		fontRender->SetTextOkuri(L"�񕜂�����@�́@�Q�[�W�̐F�Ɠ���\n�u���N���X�^�����E���v�R�g!", chatSpeed, playToSeFlag);
		break;
	case 9:
		fontRender->SetTextOkuri(L"���傤�ǋ߂���\n�����Ă���݂��������ǁE�E�E�B", chatSpeed, playToSeFlag);
		break;
	case 10:
		fontRender->SetTextOkuri(L"�G������݂����_�l�E�E�E\n���ꂶ��A�U�����@�������炢!", chatSpeed, playToSeFlag);
		break;
	case 11:
		fontRender->SetTextOkuri(L"�u�U������ɂ�A�{�^���v!\n���܂��g���ĕ����Ă݂悤!", chatSpeed, playToSeFlag);
		break;
	case 12:
		break;
	case 13:
		fontRender->SetTextOkuri(L"�����!�@�����ɃQ�b�g�ł�����!", chatSpeed, playToSeFlag);
		break;
	case 14:
		fontRender->SetTextOkuri(L"�Q�b�g�����Ƃ��ɃQ�[�W��\n�񕜂����̂��킩��������?", chatSpeed, playToSeFlag);
		break;
	case 15:
		fontRender->SetTextOkuri(L"���{���ł̓N���X�^����\n��R�W�߂Đi��ł������Ƃ��J�M!", chatSpeed, playToSeFlag);
		break;
	case 16:
		fontRender->SetTextOkuri(L"������ӂ܂���\n�S�[���܂ŕ����Ă݂悤!", chatSpeed, playToSeFlag);
		break;
	case 17:
		break;
	case 18:
		fontRender->SetTextOkuri(L"�S�[�����߂łƂ�!\n�`���[�g���A���͂���ł����܂�!", chatSpeed, playToSeFlag);
		break;
	case 19:
		fontRender->SetTextOkuri(L"��{�͂΂����肩��?\n���ꂶ��@�������Ƃ���\nSTART�{�^���ŌĂ�ł�!", chatSpeed, playToSeFlag);
		break;
	}
}


void Chat::Update()
{	
	// �C�x���g���̏���
	if (eventFlag == true) {
		EventUpdate();
	}
	// �����_���e�L�X�g�̏���
	else {
		RundumUpdate();
	}

	if (fontRender != nullptr) {
		// ������\�����I�������ǂ������ׂ�
		drawChatFlag = fontRender->GetMessageOkuriFlag();

		fontRender->TextOkuriUpdate(g_gameTime->GetFrameDeltaTime());	// �t�H���g�̍X�V
	}

	// �\�����I����Ă���Ƃ�
	//if (drawChatFlag == false) {

	//	sumPos = -350.0f - movePos;			// ���̍��W + ���Z�l

	//	switch (moveState) {
	//	case 0:
	//		// �������Ɉړ����Ă���Ƃ�
	//		if (sumPos == -360.0f) {
	//			movePos *= -1.0f;
	//			moveState = 1;					// ������Ɉړ�
	//		}
	//		break;
	//	case 1:
	//		// ������Ɉړ����Ă���Ƃ�
	//		if (sumPos == -350.0f) {
	//			movePos *= -1.0f;
	//			moveState = 0;					// �������Ɉړ�
	//		}
	//		break;
	//	} 

	//	spriteRender_button.SetPosition({ 450.0f,sumPos,0.0f });
	//}

	// �X�v���C�g���X�V����
	spriteRender_npc.Update();
	spriteRender_button.Update();
	spriteRender_textbox.Update();
}

void Chat::EventUpdate()
{
	// ������\�����Ă���Ƃ�
	if (StopDrawFlag == false) {
		// ������\�����I����Ă���Ƃ�
		if (drawChatFlag == false) {
			// ����B�{�^�����������Ƃ�
			if (g_pad[0]->IsTrigger(enButtonB)) {

				// ���ʉ����Đ�
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);				// B�{�^��
				se->Play(false);			// ���[�v���Ȃ�
				se->SetVolume(3.5f);		// ���ʂ̐ݒ������

				chatState++;				// ���̕�����\������
				EventChat();
			}
		}
	}

	// �������Ői�ނƂ��e�L�X�g����U��������
	if (chatState == 4 || chatState == 12 || chatState == 17) {
		NextchatFlag = false;				// �e�L�X�g���ꎞ�I�ɔ�\���ɂ���
	}
	else {
		NextchatFlag = true;				// �e�L�X�g�����̂܂ܕ\������
	}

	// ���̕�����\������
	if (NextchatFlag == true) {

		num->stopFlag = true;	// �����Ȃ��悤�ɂ���
		StopDrawFlag = false;	// ��\��������

		// �����X�e�[�g�����
		if (chatState == chatState_end) {
			eveneStartFlag = false;	// �C�x���g���I�������̂�false�ɂ���
		}
	}
	// ���̕�����\�����Ȃ� (��葀�삪�K�v�Ȏ�)
	else if(NextchatFlag == false) {

		num->stopFlag = false;		// ������悤�ɂ���
		StopDrawFlag = true;		// ��\���ɂ���

		// player���������Ƃ�
		if (num->movePlayer == true && clearState == 0) {
			
			eveneStartFlag = true;	// �C�x���g���ĊJ
			num->stopFlag = true;	// �����Ȃ��悤�ɂ���

			chatState = 5;			// �e�L�X�g���w�肷��
			clearState = 1;			// �B���X�e�[�g��؂�ւ���

			EventChat();
		}
		// �A�C�e�����l�������Ƃ�
		if (num->getItem == true && clearState == 1) {

			// �^�C�}�[��0�̂Ƃ�
			waitTimer -= g_gameTime->GetFrameDeltaTime();
			if (waitTimer <= 0.0f) {

				eveneStartFlag = true;	// �C�x���g���ĊJ
				num->stopFlag = true;	// �����Ȃ��悤�ɂ���

				chatState = 13;			// �e�L�X�g���w�肷��
				clearState = 2;			// �B���X�e�[�g��؂�ւ���

				EventChat();
			}
		}
		// �S�[���ɓ��������Ƃ�
		if (num->clearFlag == true && clearState == 2) {

			eveneStartFlag = true;	// �C�x���g���ĊJ
			num->stopFlag = true;	// �����Ȃ��悤�ɂ���

			chatState = 18;			// �e�L�X�g���w�肷��
			clearState = 3;			// �B���X�e�[�g��؂�ւ���

			EventChat();
		}
		else if (num->clearFlag == true && clearState == 1) {
			eveneStartFlag = true;	// �C�x���g���ĊJ
			num->stopFlag = true;	// �����Ȃ��悤�ɂ���

			chatState = 18;			// �e�L�X�g���w�肷��
			clearState = 3;			// �B���X�e�[�g��؂�ւ���

			EventChat();
		}
	}
}

void Chat::RundumUpdate()
{
	// �\�����I����Ă���Ƃ�
	if (drawChatFlag == false) {
		// B�{�^�����������Ƃ�
		if (g_pad[0]->IsTrigger(enButtonB)) {

			// ���ʉ����Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(25);
			se->Play(false);				// ���[�v���Ȃ�
			se->SetVolume(3.5f);			// ���ʂ̐ݒ������

			eveneStartFlag = false;			// �C�x���g���I�������̂�false�ɂ���
			rundumChatStart = false;		// �����_���`���b�g���I������
			num->stopFlag = false;			// ������悤�ɂ���
			num->drawChatFlag = false;		// ���̕`�悪�ł���悤�ɕ`��ς݃t���O���~�낷
			DeleteGO(this);					// ���g���폜����
		}

	}
}

void Chat::Button_SinMove()
{

}


void Chat::Render(RenderContext& rc)
{
	if (StopDrawFlag == false) {
		spriteRender_npc.Draw(rc);
		spriteRender_textbox.Draw(rc);

		fontRender_name.Draw(rc);

		if (fontRender != nullptr) {
			fontRender->Draw(rc);
		}

		// �\�����I�����Ƃ��`�悷��
		if (drawChatFlag == false) {
			spriteRender_button.Draw(rc);
		}
	}
}