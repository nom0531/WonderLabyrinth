#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "Stage.h"
#include "Stage2.h"
#include "Player.h"
#include "GameCamera.h"
#include "NowLoading.h"
#include "Num.h"
#include "Sum.h"

UI::UI()
{
	// インスタンスを探す
	num = FindGO<Num>("num");
	player = FindGO<Player>("player");					
	gameCamera = FindGO<GameCamera>("gameCamera");
	stage = FindGO<Stage>("stage");
	stage2 = FindGO<Stage2>("stage2");

	itemSum = player->itemCount;		// アイテム数を格納する

	// 8:5でサイズ指定
	// HPバー
	spriteRender_HP.Init("Assets/sprite/UI/HP_full.DDS", 1600, 1000);
	spriteRender_HP.SetPosition({ -580.0f, 450.0f, 0.0f });
	spriteRender_HP.Update();

	// 深度の表示 (デフォルトは01)
	spriteRender_turn.Init("Assets/sprite/UI/turncount.DDS", 800, 500);
	spriteRender_turn.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_turn.Update();
	// 1の位
	spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_1.DDS", 800, 500);
	spriteRender_countOne.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countOne.Update();
	// 10の位
	spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_00.DDS", 800, 500);
	spriteRender_countTen.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countTen.Update();

	// ヘルプアイコン (スタートボタン)
	spriteRender_help.Init("Assets/sprite/UI/aicon_help.DDS", 400, 250);
	spriteRender_help.SetPosition({ 870.0f,200.0f,0.0f });
	spriteRender_help.Update();

	// カメラ切り替え（X）
	spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_a.DDS", 400, 250);
	spriteRender_camera.SetPosition({ 870.0f,85.0f,0.0f });
	spriteRender_camera.Update();

	// アイテムゲージ
	spriteRender_itemgage.Init("Assets/sprite/UI/item_gage.DDS", 800, 500);
	spriteRender_itemgage.SetPosition({ -600.0f, 310.0f, 0.0f });
	spriteRender_itemgage.Update();
	// 背景
	spriteRender_itemback.Init("Assets/sprite/UI/item_back.DDS", 220, 50);
	spriteRender_itemback.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_itemback.SetPivot({ 0.0f,0.5f });	// 画像の中心点
	spriteRender_itemback.Update();
	// ゲージ部分
	spriteRender_item.Init("Assets/sprite/UI/item.DDS", 220, 50);
	spriteRender_item.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_item.SetPivot({ 0.0f,0.5f });		// 画像の中心点
	spriteRender_item.Update();

	// 説明用キャラクター
	spriteRender_chat.Init("Asettes/sprite/chara.DDS", 400, 800);	// 画像の読み込み
	spriteRender_chat.SetPosition({ 0.0f, 0.0f, 0.0f });
	spriteRender_chat.Update();
}

UI::~UI()
{
}

void UI::Update()
{
	Camera();		// カメラ
	Crear();		// クリア処理
	PlayerHP();		// HP

	// numが存在する時に実行する
	if (num != nullptr) {
		ItemGage();		// アイテムゲージ
	}

	// playerが被弾したとき
	if (player->animState == 3) {
		UI_playerHP = player->HP;	// HPを参照
	}
}

void UI::ItemGage()
{
	// 停止したときゲージ量を減らさないようにする
	if (stopFlag == true) {
		nowGage = nowGage;
	}

	// アイテムゲージのUI処理
	spriteRender_item.SetPivot({ 0.0f,0.5f });	// 画像の中心点

	// スケールと位置を設定する
	spriteRender_item.SetScale({ nowGage, 1.0f, 1.0f });
	spriteRender_item.SetPosition({ -668.0f, 289.1f, 0.0f });
	spriteRender_item.Update();
}

void UI::TurnCount()
{
	// 値が9以下の時
	if (UI_stageNum >= 0 && UI_stageNum <= 9) {
		if (UI_stageNum == 0) {
			turn_one = 0;
		}
		// そのまま渡す
		turn_one = UI_stageNum;
	}
	// 10以上19以下の時
	else if (UI_stageNum >= 10 && UI_stageNum <= 19) {
		if (UI_stageNum == 10) {
			turn_one = 0;
		}
		else {
			// 10を引いて1の位を渡す
			turn_one = UI_stageNum - 10;
		}
		// 10の位は1の位を引いて渡す
		turn_ten = 1;
	}
	// 20以上29以下の時
	else if (UI_stageNum >= 20 && UI_stageNum <= 29) {
		if (UI_stageNum == 20) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 20;
		}
		turn_ten = 2;
	}
	// 30以上39以下の時
	else if (UI_stageNum >= 30 && UI_stageNum <= 39) {
		if (UI_stageNum == 30) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 30;
		}
		turn_ten = 3;
	}
	// 40以上49以下の時
	else if (UI_stageNum >= 40 && UI_stageNum <= 49) {
		if (UI_stageNum == 40) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 40;
		}
		turn_ten = 4;
	}
	// 50以上59以下の時
	else if (UI_stageNum >= 50 && UI_stageNum <= 59) {
		if (UI_stageNum == 50) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 50;
		}
		turn_ten = 5;
	}
	// 60以上69以下の時
	else if (UI_stageNum >= 60 && UI_stageNum <= 69) {
		if (UI_stageNum == 60) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 60;
		}
		turn_ten = 6;
	}
	// 70以上79以下の時
	else if (UI_stageNum >= 70 && UI_stageNum <= 79) {
		if (UI_stageNum == 70) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 70;
		}
		turn_ten = 7;
	}
	// 80以上89以下の時
	else if (UI_stageNum >= 80 && UI_stageNum <= 89) {
		if (UI_stageNum == 80) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 80;
		}
		turn_ten = 8;
	}
	// 90以上99以下の時
	else if (UI_stageNum >= 90 && UI_stageNum <= 99) {
		if (UI_stageNum == 90) {
			turn_one = 0;
		}
		else {
			turn_one = UI_stageNum - 90;
		}
		turn_ten = 9;
	}
	else {
		turn_one = 0;
		turn_ten = 0;
	}

	// ステージをクリアしたときに呼び出す
	if (player->stageClear == true) {
		// 階層の表示
		TurnOne();
		TurnTen();
	}

	// ターン数のカウント
	//wchar_t Turntext[256];
	// 桁数の指定
	//swprintf_s(Turntext, 256, L"%2d手目", (int)UI_turn);
}

void UI::TurnOne()
{
	// 1の位
	switch (turn_one) {
	case 0:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_0.DDS", 800, 500);
		break;
	case 1:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_1.DDS", 800, 500);
		break;
	case 2:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_2.DDS", 800, 500);
		break;
	case 3:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_3.DDS", 800, 500);
		break;
	case 4:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_4.DDS", 800, 500);
		break;
	case 5:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_5.DDS", 800, 500);
		break;
	case 6:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_6.DDS", 800, 500);
		break;
	case 7:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_7.DDS", 800, 500);
		break;
	case 8:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_8.DDS", 800, 500);
		break;
	case 9:
		spriteRender_countOne.Init("Assets/sprite/UI/turn_one/turncount_9.DDS", 800, 500);
		break;
	}

	spriteRender_countOne.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countOne.Update();
}

void UI::TurnTen()
{
	// 10の位
	switch (turn_ten) {
	case 0:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_00.DDS", 800, 500);
		break;
	case 1:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_10.DDS", 800, 500);
		break;
	case 2:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_20.DDS", 800, 500);
		break;
	case 3:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_30.DDS", 800, 500);
		break;
	case 4:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_40.DDS", 800, 500);
		break;
	case 5:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_50.DDS", 800, 500);
		break;
	case 6:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_60.DDS", 800, 500);
		break;
	case 7:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_70.DDS", 800, 500);
		break;
	case 8:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_80.DDS", 800, 500);
		break;
	case 9:
		spriteRender_countTen.Init("Assets/sprite/UI/turn_ten/turncount_90.DDS", 800, 500);
		break;
	}

	spriteRender_countTen.SetPosition({ 760.0f,400.0f,0.0f });
	spriteRender_countTen.Update();
}

void UI::PlayerHP()
{
	// 値を参照
	UI_playerHP = player->HP;

	// HPの処理
	switch (UI_playerHP) {
	case 0:
		// 残りHP:0
		spriteRender_HP.Init("Assets/sprite/UI/HP_3damege.DDS", 1600, 1000);
		num->clearFlag = true;
		break;
	case 1:
		// 残りHP:1
		spriteRender_HP.Init("Assets/sprite/UI/HP_2damege.DDS", 1600, 1000);
		break;
	case 2:
		// 残りHP:2
		spriteRender_HP.Init("Assets/sprite/UI/HP_1damege.DDS", 1600, 1000);
		break;
	}
	spriteRender_HP.SetPosition({ -580.0f, 450, 0.0f });
	spriteRender_HP.Update();
}

void UI::Camera()
{
	// 値を参照
	UI_cameraState = gameCamera->cameraState;

	if (num->stopFlag == false) {
		// アイコンの切り替え
		switch (UI_cameraState) {
		case 0:
			if (g_pad[0]->IsTrigger(enButtonX)) {
				spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_a.DDS", 400, 250);
			}
			break;
		case 1:
			if (g_pad[0]->IsTrigger(enButtonX)) {
				spriteRender_camera.Init("Assets/sprite/UI/aicon_camera_b.DDS", 400, 250);
			}
			break;
		}
	}
	spriteRender_camera.SetPosition({ 870.0f,85.0f,0.0f });
	spriteRender_camera.Update();
}

void UI::Crear()
{
	//spriteRender.Init("Assets/")
}

void UI::Render(RenderContext& rc)
{
	// 描画
	spriteRender_HP.Draw(rc);
	spriteRender_help.Draw(rc);		// ヘルプアイコン
	spriteRender_camera.Draw(rc);	// カメラアイコン

	spriteRender_turn.Draw(rc);		// ターン数
	spriteRender_countOne.Draw(rc);
	spriteRender_countTen.Draw(rc);

	spriteRender_itemgage.Draw(rc);	// アイテムゲージ
	spriteRender_itemback.Draw(rc);
	spriteRender_item.Draw(rc);

	spriteRender_chat.Draw(rc);		// キャラクターの表示
}