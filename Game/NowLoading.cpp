#include "stdafx.h"
#include "NowLoading.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"
#include "GameClear.h"
#include "Sum.h"
#include "Num.h"
#include "Help.h"
#include "BGM.h"
#include "GameStop.h"

NowLoading::NowLoading()
{
	// 画像
	spriteRender_back.Init("Assets/sprite/UI/black.DDS", 1920, 1080);
	spriteRender_back.SetMulColor({ 1,1,1,0 });		// 半透明のテクスチャ
}

bool NowLoading::Start()
{
	// インスタンスを探す
	bgm = FindGO<BGM>("bgm");

	gameStop = FindGO<GameStop>("gameStop");
	gameStop->StopFlag = true;					// 生成された瞬間に操作不能にする

	return true;
}

NowLoading::~NowLoading()
{
}

void NowLoading::Update()
{
	spriteRender_back.SetMulColor({ 1.0f,1.0f,1.0f,alpha });	// 半透明のテクスチャ

	// アニメーションタイマーを減少させる
	animTimer -= g_gameTime->GetFrameDeltaTime();
	// 0の時
	if (animTimer <= 0.0f) {

		alpha -= g_gameTime->GetFrameDeltaTime();

		// 透明度が0.0f以下のとき自身を削除する
		if (alpha <= 0.0f) {
			gameStop->StopFlag = false;	// 削除するのでフラグを降ろす
			DeleteGO(this);
		}
	}
	else {
		alpha += g_gameTime->GetFrameDeltaTime();
	}
	
	// 指定したシーンを生成していない かつ 透明度が1.0f以上の時
	if (makeFlag == false && alpha >= 1.0f) {
		NewScene();			// シーンの生成
		makeFlag = true;	// 生成したのでフラグを降ろす
	}

	// 待機フラグが立っている
	if (waitFlag)
	{
		waitFlame--;

		// 待機フレームが 0 になったとき
		if (waitFlame < 0) {
			// numとgameを生成する
			num = NewGO<Num>(0, "num");
			num->stageState = stageState;		// どのステージを出力するか渡す
			num->CameraAdjustmentFlag = true;	// カメラの調節を行う

			// BGMを差し替える処理
			switch (num->stageState) {
			case 0:
				bgm->ChangeBGMFlag = true;		// 音量を変更する
				bgm->BGMState = 2;				// チュートリアル
				break;
			case 1:
				// 変更しないフラグがfalseの時
				if (NOTchangeBGMFlag == false) {
					bgm->ChangeBGMFlag = true;		// 音量を変更する
					bgm->BGMState = 3;				// 本編(草原)
				}
				break;
			case 2:
				// 変更しないフラグがfalseの時
				if (NOTchangeBGMFlag == true) {
					bgm->ChangeBGMFlag = true;		// 音量を変更する
					bgm->BGMState = 4;				// 本編(洞窟)
				}
				break;
			}

			game = NewGO<Game>(0, "game");		// gameを生成する
			waitFlag = false;
		}
	}

	spriteRender_back.Update();
}

void NowLoading::NewScene() 
{
	// 判別式
	switch (loadState) {
	// ゲームを出力
	case 1:
		// インスタンスを探す
		game = FindGO<Game>("game");

		// ゲームが生成されているとき
		if (game != nullptr) {
			game->GameDelete();
		}

		waitFlag = true;					// 待機フラグを立てる
		break;
	// タイトル
	case 2:
		title = NewGO<Title>(0, "title");

		// 操作説明以外からタイトルに戻るとき
		if (migrationToTitleFlag == true) {
			// BGMを差し替える処理
			bgm->ChangeBGMFlag = true;		// 音量を変更する
			bgm->BGMState = 0;				// タイトル
		}

		break;
	// ステージ選択
	case 3:
		stageselect = NewGO<StageSelect>(0, "stageselect");

		// BGMを差し替える処理
		bgm->ChangeBGMFlag = true;		// 音量を変更する
		bgm->BGMState = 1;				// ステージ選択

		break;
	// 説明書
	case 4:
		help = NewGO<Help>(0, "help");
		break;
	// リザルト画面
	case 5:
		gameClear = NewGO<GameClear>(0, "gameClear");
		// 値を渡す
		gameClear->setClearNum(
			Cleartime,					// クリアタイム
			Stagenum,					// 通過ステージ数
			Itemnum,					// 獲得アイテム数
			HPnum						// 残りHP
		);

		// BGMを差し替える処理
		bgm->ChangeBGMFlag = true;		// 音量を変更する
		bgm->BGMState = 5;				// リザルト

		break;
	}

	return;
}

void NowLoading::Render(RenderContext& rc)
{
	spriteRender_back.Draw(rc);
}