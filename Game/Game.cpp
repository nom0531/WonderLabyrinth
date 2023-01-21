#include "stdafx.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Stage2.h"
#include "UI.h"
#include "Item.h"
#include "Enemy.h"		// slimerabbit
#include "Enemy2.h"		// mushroom
#include "GameClear.h"
#include "NowLoading.h"
#include "Help.h"
#include "Sum.h"		// 計算用クラス
#include "Num.h"		// 状態格納用
#include "Chat.h"
#include "BGM.h"

#define CHANGETOSTAGE 5	// スキン・BGMを変更する階層数の値

Game::Game()
{
	// 効果音
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/X_Button.wav");
	g_soundEngine->ResistWaveFileBank(24, "Assets/sound/Aru_ChatStart.wav");

	skyCube = NewGO<SkyCube>(0);

	g_renderingEngine->DisableTonemap();

	num = FindGO<Num>("num");
	if (num == nullptr) {
		num = NewGO<Num>(0, "num");
	}
	num->stopFlag = false;						// 念のためフラグをリセットしておく
	num->turn = 1;								// playerのターンから開始
	num->enemyNum = 0;
	num->clearFlag = false;

	// スキン変更
	ui = FindGO<UI>("ui");
	if (ui != nullptr) {
		// 一定の階層数でスキンを変更する
		if (ui->UI_stageNum % CHANGETOSTAGE == 0) {
			// 現在のステージのスキンが 1 の時
			if (num->stageState == 1) {
				num->stageState = 2;	// スキンを 2 に変更

				bgm = FindGO<BGM>("bgm");
				bgm->ChangeBGMFlag = true;
				bgm->BGMState = 4;
			}
			// 現在のステージのスキンが 2 の時
			else if (num->stageState == 2) {
				num->stageState = 1;	// スキンを 1 に変更

				bgm = FindGO<BGM>("bgm");
				bgm->ChangeBGMFlag = true;
				bgm->BGMState = 3;
			}
		}
	}

	// stage
	switch (num->stageState) {
	case 0:
		// チュートリアル
		stage = NewGO<Stage>(0, "stage");
		num->stageNum = 5;

		// BGM
		bgm = FindGO<BGM>("bgm");
		// 生成されていないとき生成する
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 2;
			bgm->SetPlayBGM();
		}

		break;
	case 1:
		// それ以外
		stage2 = NewGO<Stage2>(0, "stage2");
		stage2->texState = 1;					// テクスチャを指定する
		stage2->clearFlag = false;
		stage2->SetUp();
		num->stageNum = 9;						// ステージのマス数を渡す

		// BGM
		bgm = FindGO<BGM>("bgm");
		// 生成されていないとき生成する
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 3;
			bgm->SetPlayBGM();
		}

		break;
	case 2:
		// それ以外
		stage2 = NewGO<Stage2>(0, "stage2");
		stage2->texState = 2;					// テクスチャを指定する
		stage2->clearFlag = false;
		stage2->SetUp();
		num->stageNum = 9;						// ステージのマス数を渡す

		// BGM
		bgm = FindGO<BGM>("bgm");
		// 生成されていないとき生成する
		if (bgm == nullptr) {
			bgm = NewGO<BGM>(0, "bgm");
			bgm->ChangeBGMFlag = true;
			bgm->BGMState = 4;
			bgm->SetPlayBGM();
		}

		break;
	}

	// player
	player = FindGO<Player>("player");
	// プレイヤーが未生成の時
	if (player == nullptr) {
		player = NewGO<Player>(0, "player");
		player->p_stageState = num->stageState;
		player->Playermodel(false);					// playerのモデルを更新
	}
	// ステージクリアのフラグが立っているとき
	if (player->stageClear == true) {
		// 階層が変更されるのでいろいろリセットする
		// 座標の再設定
		player->position = { 200.0f,11.0f,2.0f };
		player->position_stage2[8][4] = 1;
		player->position2D = { 4.0f,8.0f };

		player->modelRender.SetPosition(player->position);
		player->p_stageState = num->stageState;

		player->animState = 0;
		player->Playermodel(true);			// playerのモデルを更新

		// フラグを初期化
		player->moveFlag = false;			// 移動できるかどうか
		player->posFlag = false;			// 移動できるオブジェクトかどうか
		player->AttackFlag = false;			// 攻撃したかどうか
	}

	// playerに値を渡す
	player_position = player->position;

	// camera
	gameCamera = FindGO<GameCamera>("gameCamera");
	if (gameCamera == nullptr) {
		gameCamera = NewGO<GameCamera>(0, "gameCamera");
	}
	gameCamera->c_stageState = num->stageState;

	// sistem
	if (ui == nullptr) {
		ui = NewGO<UI>(0, "ui");
	}

	// ゲージの減少を停止しているとき
	if (ui->stopFlag = true) {
		// 解除する
		ui->stopFlag = false;
	}

	ui->UI_stageState = num->stageState;
	
	// stage
	backGround = NewGO<BackGround>(0);

	sum = NewGO<Sum>(0, "sum");
	sum->clearFlag = false;

	// プレイヤー等のポインタ初期化
	if (player->stageClear == true) {
		player->stage = stage;
		player->stage2 = stage2;

		player->num = num;
		player->sum = sum;
		
		ui->num = num;
		ui->stage = stage;
		ui->stage2 = stage2;

		gameCamera->num = num;

		player->stageClear = false;			// ステージをクリアしたかどうか
	}

	switch (num->stageState) {
	case 0:
		skyCube->SetType(enSkyCubeType_DayToon);
		skyCube->SetLuminance(1.0f);
		skyCube->SetScale(300.0f);

		s_Light();	// スポットライト
		StageZero();// 配置

		// ディレクションライト(平行光源)
		g_renderingEngine->SetDirectionLight(
			0,					// ライトの番号
			{ 0.2f,-1.0f,0.5f },			// 方向(X Y Z)
			{ 0.8f,0.8f,0.8f }			// ライトのカラー(R G B)
		);
		// 環境光
		g_renderingEngine->SetAmbient({ 0.7f,0.7f,0.7f });
		break;
	case 1:
		skyCube->SetType(enSkyCubeType_DayToon);
		skyCube->SetLuminance(1.0f);
		skyCube->SetScale(300.0f);

		StageOne();	// 配置

		// ディレクションライト(平行光源)
		g_renderingEngine->SetDirectionLight(
			0,					// ライトの番号
			{ 0.2f,-1.0f,0.5f },			// 方向(X Y Z)
			{ 0.8f,0.8f,0.8f }			// ライトのカラー(R G B)
		);
		// 環境光
		g_renderingEngine->SetAmbient({ 0.7f,0.7f,0.7f });
		break;
	case 2:
		skyCube->SetType(enSkyCubeType_NightToon);
		skyCube->SetLuminance(0.2f);
		skyCube->SetScale(300.0f);

		p_Light();	// ポイントライト
		StageTwo();	// 配置

		// ディレクションライト(平行光源)
		g_renderingEngine->SetDirectionLight(
			0,					// ライトの番号
			{ 0.2f,-1.0f,0.5f },			// 方向(X Y Z)
			{ 0.2f,0.2f,0.2f }		// ライトのカラー(R G B)
		);
		// 環境光
		g_renderingEngine->SetAmbient({ 0.2f,0.2f,0.2f });
		break;
	}
}

void Game::s_Light()
{
	// スポットライト
	spotLight.Init();
	// ライトの影響距離を設定。
	spotLight.SetRange(1200.0f);
	// ライトの影響角度を設定。(大きさ)
	spotLight.SetAngle(Math::DegToRad(3.5f));
	// ライトの距離減衰率を設定。
	spotLight.SetRangeAffectPowParam(1.0f);
	// ライトの角度減衰率を設定。(ぼかし？）
	spotLight.SetAngleAffectPowParam(0.2f);
	// ライトの色を設定。
	spotLight.SetColor(5.0f, 5.0f, 4.5f);
	// ライトの方向を設定。
	spotLight.SetDirection({ 0.0f,-10.0f,0.0f });
}

void Game::p_Light()
{
	// ポイントライト
	pointLight.Init();
	// 位置
	pointLight.SetPosition(100.0f, 10.0f, 8.0f);
	// カラー
	pointLight.SetColor(Vector3(3.0f, 3.0f, 2.5f));
	// 影響率の累乗（？）
	pointLight.SetAffectPowParam(0.1f);
	// 範囲
	pointLight.SetRange(p_scale);
}

void Game::StageZero()
{	
	// 使用するエネミーを作成
	Enemy* slime = NewGO<Enemy>(0, "slime");
	slime->s_position = { 50.0f,2.0f,150.0f };
	slime->s_position_stage[1][1] = 1;
	slime->s_position2D = { 1.0f,1.0f };

	// アイテムはチュートリアルのみ使用する
	Item* item = NewGO<Item>(0, "item");
	item->position = { 100.0f,20.0f,100.0f };
}

void Game::StageOne()
{
	// 使用するエネミーを作成
	Enemy* slime = NewGO<Enemy>(0, "slime");
	Enemy* slime2 = NewGO<Enemy>(0, "slime");
	Enemy* slime3 = NewGO<Enemy>(0, "slime");

	Enemy2* mush = NewGO<Enemy2>(0, "mush");
	Enemy2* mush2 = NewGO<Enemy2>(0, "mush");
	Enemy2* mush3 = NewGO<Enemy2>(0, "mush");

	// ステージに応じて敵の配置を変更する
	switch (num->Rundum_StageNum) {
	case 0:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);
		DeleteGO(mush3);

		// 座標を設定
		slime->s_position = { 200.0f,2.0f,200.0f };
		slime->s_position_stage2[4][4] = 1;
		slime->s_position2D = { 4.0f,4.0f };

		slime2->s_position = { 0.0f,2.0f,350.0f };
		slime2->s_position_stage2[1][0] = 1;
		slime2->s_position2D = { 0.0f,1.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		break;
	case 1:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);

		// 座標を設定
		slime->s_position = { 0.0f,2.0f,300.0f };
		slime->s_position_stage2[2][0] = 1;
		slime->s_position2D = { 0.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,150.0f };
		slime2->s_position_stage2[5][5] = 1;
		slime2->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 200.0f,2.0f,200.0f };
		mush->m_position_stage[4][4] = 1;
		mush->m_position2D = { 4.0f,4.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		mush3->m_position = { 50.0f,2.0f,50.0f };
		mush3->m_position_stage[7][1] = 1;
		mush3->m_position2D = { 1.0f,7.0f };

		break;
	case 2:

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,200.0f };
		slime->s_position_stage2[4][1] = 1;
		slime->s_position2D = { 1.0f,4.0f };

		slime2->s_position = { 200.0f,2.0f,300.0f };
		slime2->s_position_stage2[2][4] = 1;
		slime2->s_position2D = { 4.0f,2.0f };
		
		slime3->s_position = { 250.0f,2.0f,150.0f };
		slime3->s_position_stage2[5][5] = 1;
		slime3->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 400.0f,2.0f,350.0f };
		mush->m_position_stage[1][8] = 1;
		mush->m_position2D = { 8.0f,1.0f };

		mush2->m_position = { 50.0f,2.0f,50.0f };
		mush2->m_position_stage[7][1] = 1;
		mush2->m_position2D = { 1.0f,7.0f };

		mush3->m_position = { 50.0f,2.0f,350.0f };
		mush3->m_position_stage[1][1] = 1;
		mush3->m_position2D = { 1.0f,1.0f };

		break;
	case 3:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);
		DeleteGO(mush3);

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,300.0f };
		slime->s_position_stage2[2][1] = 1;
		slime->s_position2D = { 1.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,100.0f };
		slime2->s_position_stage2[6][5] = 1;
		slime2->s_position2D = { 5.0f,6.0f };

		mush->m_position = { 0.0f,2.0f,50.0f };
		mush->m_position_stage[7][0] = 1;
		mush->m_position2D = { 0.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };

		break;
	case 4:
		// 使用しないエネミーは削除する
		DeleteGO(mush3);
		DeleteGO(slime3);

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,350.0f };
		slime->s_position_stage2[1][1] = 1;
		slime->s_position2D = { 1.0f,1.0f };

		slime2->s_position = { 250.0f,2.0f,200.0f };
		slime2->s_position_stage2[4][5] = 1;
		slime2->s_position2D = { 5.0f,4.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };
		break;
	}
}

void Game::StageTwo()
{
	// 使用するエネミーを作成
	Enemy* slime = NewGO<Enemy>(0, "slime");
	Enemy* slime2 = NewGO<Enemy>(0, "slime");
	Enemy* slime3 = NewGO<Enemy>(0, "slime");

	Enemy2* mush = NewGO<Enemy2>(0, "mush");
	Enemy2* mush2 = NewGO<Enemy2>(0, "mush");
	Enemy2* mush3 = NewGO<Enemy2>(0, "mush");

	// ステージに応じて敵の配置を変更する
	switch (num->Rundum_StageNum) {
	case 0:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);
		DeleteGO(mush3);

		// 座標を設定
		slime->s_position = { 200.0f,2.0f,200.0f };
		slime->s_position_stage2[4][4] = 1;
		slime->s_position2D = { 4.0f,4.0f };

		slime2->s_position = { 0.0f,2.0f,350.0f };
		slime2->s_position_stage2[1][0] = 1;
		slime2->s_position2D = { 0.0f,1.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		break;
	case 1:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);

		// 座標を設定
		slime->s_position = { 0.0f,2.0f,300.0f };
		slime->s_position_stage2[2][0] = 1;
		slime->s_position2D = { 0.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,150.0f };
		slime2->s_position_stage2[5][5] = 1;
		slime2->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 200.0f,2.0f,200.0f };
		mush->m_position_stage[4][4] = 1;
		mush->m_position2D = { 4.0f,4.0f };

		mush2->m_position = { 350.0f,2.0f,300.0f };
		mush2->m_position_stage[2][7] = 1;
		mush2->m_position2D = { 7.0f,2.0f };

		mush3->m_position = { 50.0f,2.0f,50.0f };
		mush3->m_position_stage[7][1] = 1;
		mush3->m_position2D = { 1.0f,7.0f };

		break;
	case 2:

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,200.0f };
		slime->s_position_stage2[4][1] = 1;
		slime->s_position2D = { 1.0f,4.0f };

		slime2->s_position = { 200.0f,2.0f,300.0f };
		slime2->s_position_stage2[2][4] = 1;
		slime2->s_position2D = { 4.0f,2.0f };

		slime3->s_position = { 250.0f,2.0f,150.0f };
		slime3->s_position_stage2[5][5] = 1;
		slime3->s_position2D = { 5.0f,5.0f };

		mush->m_position = { 400.0f,2.0f,350.0f };
		mush->m_position_stage[1][8] = 1;
		mush->m_position2D = { 8.0f,1.0f };

		mush2->m_position = { 50.0f,2.0f,50.0f };
		mush2->m_position_stage[7][1] = 1;
		mush2->m_position2D = { 1.0f,7.0f };

		mush3->m_position = { 50.0f,2.0f,350.0f };
		mush3->m_position_stage[1][1] = 1;
		mush3->m_position2D = { 1.0f,1.0f };

		break;
	case 3:

		// 使用しないエネミーは削除する
		DeleteGO(slime3);
		DeleteGO(mush3);

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,300.0f };
		slime->s_position_stage2[2][1] = 1;
		slime->s_position2D = { 1.0f,2.0f };

		slime2->s_position = { 250.0f,2.0f,100.0f };
		slime2->s_position_stage2[6][5] = 1;
		slime2->s_position2D = { 5.0f,6.0f };

		mush->m_position = { 0.0f,2.0f,50.0f };
		mush->m_position_stage[7][0] = 1;
		mush->m_position2D = { 0.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };

		break;
	case 4:
		// 使用しないエネミーは削除する
		DeleteGO(mush3);
		DeleteGO(slime3);

		// 座標を設定
		slime->s_position = { 50.0f,2.0f,350.0f };
		slime->s_position_stage2[1][1] = 1;
		slime->s_position2D = { 1.0f,1.0f };

		slime2->s_position = { 250.0f,2.0f,200.0f };
		slime2->s_position_stage2[4][5] = 1;
		slime2->s_position2D = { 5.0f,4.0f };

		mush->m_position = { 50.0f,2.0f,50.0f };
		mush->m_position_stage[7][1] = 1;
		mush->m_position2D = { 1.0f,7.0f };

		mush2->m_position = { 400.0f,2.0f,250.0f };
		mush2->m_position_stage[3][8] = 1;
		mush2->m_position2D = { 8.0f,3.0f };
		break;
	}
}

Game::~Game()
{
	// sistem
	DeleteGO(help);
	DeleteGO(gameClear);
	DeleteGO(num);
	DeleteGO(sum);
	DeleteGO(gameBGM);
	// game
	DeleteGO(chat);
	DeleteGO(stage);
	DeleteGO(stage2);
	DeleteGO(backGround);
	DeleteGO(skyCube);
}

void Game::GameEnd() {
	DeleteGO(ui);
	DeleteGO(bgm);
	DeleteGO(player);
	DeleteGO(gameCamera);
	sum->clearFlag = true;
}

bool Game::Start()
{	
	return true;
}

void Game::Update()
{
	// スポットライト
	if (num->stageState == 0) {
		Vector3 spot_position = player->position;
		spot_position.y = 500.0f;
		spotLight.SetPosition(spot_position);	// スポットライトの座標
		spotLight.Update();						// 座標を教える
	}

	// ポイントライト
	if (num->stageState == 2) {
		Vector3 point_position = player->position;
		point_position.y = 45.0;				// playerの体の位置に持ってくる
		pointLight.SetPosition(point_position);	// ポイントライトの座標
		pointLight.Update();					// 座標を教える
	}

	if (num->turn == 2) {

		bool end = true;	// エネミーのターンが終了したかどうか

		// エネミー
		QueryGOs<Enemy>("slime", [&](Enemy* slime) {
			// 1体でも終了していないとき
			if (slime->nowTurnEnd == false) {
				end = false;
			}
			// 終了しているときはtrueを返す
			return true;
			});
		QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
			// 1体でも終了していないとき
			if (mush->nowTurnEnd == false) {
				end = false;
			}
			// 終了しているときはtrueを返す
			return true;
			});

		// 終了しているとき
		if (end == true) {
			num->turn = 1;	// playerのターンに

			// フラグを戻す
			QueryGOs<Enemy>("slime", [&](Enemy* slime) {
				slime->nowTurnEnd = false;
				return true;
				});
			QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
				mush->nowTurnEnd = false;
				return true;
				});
		}
	}

	// エネミーがいない　かつ　エネミーのターンの時
	if (num->enemyNum == 0 && num->turn == 2) {
		num->turn = 1;	// playerのターンに変更する
	}

	// 描画フラグがfalseの時
	if (drawFlag == false) {
		// チュートリアルの時
		if (num->stageState == 0) {
			// 一定条件を満たしたとき
			if (num->NewGoFlag == false && num->movePlayer == false && num->getItem == false) {

				num->stopFlag = true;
				// イベントを再生
				chat = NewGO<Chat>(0, "chat");
				chat->eventFlag = true;					// イベントフラグをtrueにする
				chat->eveneStartFlag = true;			// 会話を開始
				chat->Name();

				num->drawChatFlag = true;				// 画像を描画したのでtrueにする
			}
			num->NewGoFlag = true;						// 初回以降このフラグは無効なのでtrueにする
		}
		else {
			// 会話未表示 かつ スタートボタンを押したとき
			if (num->drawChatFlag == false && g_pad[0]->IsTrigger(enButtonStart)) {

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(24);
				se->Play(false);				// ループしない
				se->SetVolume(3.5f);			// 音量の設定をする

				num->stopFlag = true;
				// ランダムチャットを再生
				chat = NewGO<Chat>(0, "chat");
				chat->rundumChatStart = true;			// ランダムチャットを開始
				chat->eveneStartFlag = true;			// 会話を開始
				chat->Name();

				num->drawChatFlag = true;				// 画像を描画したのでtrueにする
			}
		}
	}

	Crear();											// クリア処理

	// ゲージ量が0以下　または　HPが0の時終了
	if (sum->nowGage == sum->minGage ||
		player->HP == 0) {
		num->clearFlag = true;
	}

	// ヘルプを表示しているときは止める
	if (num->stopFlag == true) {
		sum->nowGage = sum->nowGage;
	}

	// チュートリアル以外　かつ　描画し終わった時
	if (num->stageState != 0 && num->drawChatFlag == false) {
		// 再度描画できるようにする
		drawFlag = false;
	}

	// ステージをクリアした時、行動できないようにする
	if (player->animState == 5) {
		num->stopFlag = true;
		num->turn = 0;					// どちらも動かないようにする
		num->drawChatFlag = true;		// ヘルプを描画できないようにする
	}
}

void Game::TurnCount()
{
	// プレイヤーが動いたとき
	if (player_position.x != player->position.x && player_position.z != player_position.z) {
		player->position = player_position;
		num->turn = 2;
		player->moveFlag = false;
	}
	// そうでないとき
	else {
		num->turn = 1;
		player->moveFlag = true;
	}
}

void Game::Crear()
{
	//ステージクリア
	{
		// 勝利モーションの再生後に実行する
		if (player->modelRender.IsPlayingAnimation() == false && player->animState == 5) {

			player->stageClear = true;

			// ステージクリア
			// 次のステージを生成する
			if (stage2->clearFlag == true) {

				// 再度ゲームを生成する処理
				if (nowLoadingMake == false) {
					nowLoading = NewGO<NowLoading>(5, "nowLoading");
					nowLoading->loadState = 1;					// ゲームをロード
					nowLoading->stageState = num->stageState;	// ステージの情報を渡す

					// 一定の階層数のとき
					if (ui->UI_stageNum % CHANGETOSTAGE == 0) {
						// 変更しないフラグをfalseにする
						nowLoading->NOTchangeBGMFlag = false;
					}
					// 一定の階層数でないとき
					else {
						// 変更しないフラグをtrueにする
						nowLoading->NOTchangeBGMFlag = true;
					}

					nowLoadingMake = true;						// 何度も生成しないようにする
				}
			}
		}
	}

	// ゲームクリアでないときはタイマーを加算する
	Timer += g_gameTime->GetFrameDeltaTime();

	// ゲームクリア
	{
		// クリアフラグがtrueの時
		if (num->clearFlag == true) {
			sum->clearFlag = true;	// クリアしたのでtrueを渡す

			num->turn = 0;			// 動けないようにする
			num->stopFlag = true;

			if (num->stageState == 0) {
				// 会話が終了したとき
				if (chat->eveneStartFlag == false) {
					DeleteFlag = true;
				}
			}
			else if (num->stageState != 0) {
				if (ResultNewGO == false) {
					// リザルト
					nowLoading = NewGO<NowLoading>(5, "nowLoading");
					nowLoading->loadState = 5;				// リザルトを生成

					ResultNewGO = true;						// 何度も生成しないようにする	
				}

				// リザルト用の値を渡す
				nowLoading->Stagenum = ui->UI_stageNum;		// 通過した階層数
				nowLoading->Itemnum = player->itemCount;	// 獲得アイテム数
				nowLoading->HPnum = player->HP;				// 残りHP
				nowLoading->Cleartime = Timer;				// クリアタイム

				animTimer -= g_gameTime->GetFrameDeltaTime();
				if (animTimer <= 0.0f) {

					// エネミーを削除する
					QueryGOs<Enemy>("slime", [&](Enemy* slime) {
						DeleteGO(slime);
						return true;
						});
					// エネミーを削除する
					QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
						DeleteGO(mush);
						return true;
						});

					// 自身を削除する
					GameEnd();
					DeleteGO(this);
				}
			}
		}

		// チュートリアル時の自分を削除する処理
		if (DeleteFlag == true) {

			// タイトルを生成していないとき
			if (TitleNewGO == false) {
				nowLoading = NewGO<NowLoading>(5, "nowLoading");
				nowLoading->loadState = 3;		// タイトルを生成

				TitleNewGO = true;				// タイトルを何度も生成しないようにする
			}

			// タイマーを減少させる
			animTimer -= g_gameTime->GetFrameDeltaTime();
			// 0になったとき
			if (animTimer <= 0.0f) {

				// エネミーを削除する
				QueryGOs<Enemy>("slime", [&](Enemy* slime) {
					DeleteGO(slime);
					return true;
					});
				// エネミーを削除する
				QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
					DeleteGO(mush);
					return true;
					});

				// 自身を削除する
				GameEnd();
				DeleteGO(this);
			}
		}
	}
}

// 本編での階層の移動用
void Game::GameDelete() {

	// 一度もカウントしていないとき
	if (CountFlag == false) {

		ui->stopFlag = true;	// ゲージの減少を停止

		ui->UI_stageNum++;		// カウントする
		ui->TurnCount();		// 階層を教える

		CountFlag = true;		// 複数回カウントしないようにする
	}

	// 削除する
	QueryGOs<Enemy>("slime", [&](Enemy* slime) {
		DeleteGO(slime);
		return true;
		});
	QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
		DeleteGO(mush);
		return true;
		});

	DeleteGO(this);			// 自身を削除
}

void Game::Render(RenderContext& rc)
{
	// 描画
	fontRender.Draw(rc);
}