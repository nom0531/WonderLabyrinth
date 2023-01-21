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
	// 効果音
	g_soundEngine->ResistWaveFileBank(23, "Assets/sound/Get_Item.wav");

	modelRender.Init("Assets/modelData/model/stage/item.tkm");
	modelRender.SetScale(1.0f, 1.3f, 1.0f);

	// インスタンスを探す
	player = FindGO<Player>("player");
	sum = FindGO<Sum>("sum");
	num = FindGO<Num>("num");

	// ステージの状態
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
	Rot();		// 回転処理
	Get();		// アイテムの獲得処理

	// 本編の時
	if (num->stageState == 2) {
		// ステージをクリアしたら
		if (stage2->clearFlag == true) {
			DeleteGO(this);
		}
	}

	// ゲームをクリアしたとき
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
	// プレイヤーとアイテムの座標の差を求める
	Vector3 itemGet = player->position - position;
	// 距離が20.0f以下
	if (itemGet.Length() <= 10.0f) {
		// SE

		player->itemCount++;	// カウント

		if (num->stageState == 0) {
			num->getItem = true;	// イベント用フラグ
		}

		// 効果音を再生
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(23);					// get_item
		se->Play(false);				// ループしない
		se->SetVolume(3.5f);			// 音量の設定をする

		DeleteGO(this);
	}
}

void Item::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}