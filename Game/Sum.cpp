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
	// インスタンスを探す
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
	// num が存在しないときは実行しない
	if(num != nullptr && ui != nullptr){
		ItemGage();
	}
}

void Sum::ItemGage()
{	
	// テキストなどを表示していないとき
	if (num->stopFlag == false) {
		// チュートリアルでは一定値以下にならないようにする
		if (num->stageState == 0 && nowGage <= 150) {
			nowGage = 150;
		}

		// 操作不能でないとき
		if (gameStop->StopFlag == false || num->stopFlag == false) {
			// ゲージを減らす
			nowGage -= g_gameTime->GetFrameDeltaTime();
		}

		// スケールの値を計算する
		Scale_x = (float)nowGage / (float)maxGage;

		// アイテムを取ったとき
		if (player->itemCount != ui->itemSum) {
			ui->itemSum = player->itemCount;	// アイテム数を共有する
			// 回復する
			if (nowGage >= maxGage) {
				nowGage = maxGage;				// 100以上にならないようにする
			}
			else if (nowGage <= minGage) {
				nowGage = minGage;				// 0以下にならないようにする
			}
			else {
				nowGage += addGage;
			}
		}

		// ゲージより大きい値にはならないようにする
		if (Scale_x >= 1.0f) {
			Scale_x = 1.0f;
		}

		// 値を渡す
		ui->SetNowX(Scale_x);
	}
}

int  Sum::CrearScore(int item, int stage, int hp)
{
	// スコアを計算
	// 定数を乗算してスコアとする
	int sum = 0;

	sum += item * addPoint_item;
	sum += stage * addPoint_stage;
	sum += hp * addPoint_hp;

	// 計算した値を戻り値とする
	return sum;
}