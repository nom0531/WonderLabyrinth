#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Num.h"

Stage::Stage()
{
}

void Stage::StageZero()
{
	//レイトレースを切る
	//modelRender.SetRaytracingWorld(false);

	//ステージ情報
	int stage[][5] = {
		{ 2,5,0,2,2 },
		{ 2,2,2,2,2 },
		{ 2,2,2,2,2 },
		{ 3,2,2,2,4 },
		{ 2,2,1,2,2 }
	};
	//チュートリアル
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			modelRender[(i * 5) + j].SetRaytracingWorld(false);

			if (stage[i][j] == 0 || stage[i][j] == 1) {
				modelRender[(i * 5) + j].Init("Assets/modelData/model/stage/start_goal.tkm");	//スタート ゴール
				//boxCollider.Create({ 20.0f,5.0f,20.0f });
				//boxCollider.GetBody();
			}
			else if (stage[i][j] == 2) {
				modelRender[(i * 5) + j].Init("Assets/modelData/model/stage/grass.tkm");		//平原
			}
			else if (stage[i][j] == 3) {
				modelRender[(i * 5) + j].Init("Assets/modelData/model/stage/grass_rock.tkm");	//平原（岩）
				stageFlag[i][j] = 1;
			}
			else if (stage[i][j] == 4) {
				modelRender[(i * 5) + j].Init("Assets/modelData/model/stage/grass_reef.tkm");	//平原（草）
				stageFlag[i][j] = 1;
			}
			else if (stage[i][j] == 5) {
				modelRender[(i * 5) + j].Init("Assets/modelData/model/stage/grass_reef_b.tkm");	//平原（草②）
				stageFlag[i][j] = 1;
			}
		}
	}
}

Stage::~Stage()
{
}

bool Stage::Start()
{
	// インスタンスを探す
	num = FindGO<Num>("num");
	player = FindGO<Player>("player");

	SetUp();

	return true;
}

void Stage::SetUp()
{
	//座標の設定
	Vector3 pos = Vector3::Zero;
	int num = 0;

	StageZero();

	// ステージの基点
	Vector3 DefPos{ 0.0f,0.0f,200.0f };

	//5×5
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {

			pos = DefPos;

			pos.x += i * 50.0f;
			pos.y = 0.0f;
			pos.z -= j * 50.0f;

			position = pos;
			modelRender[num].SetPosition(pos);
			num++;
		}
	}
}

void Stage::Update()
{
	// ゴールにたどり着いたとき
	if (clearPosition2D.y == player->position2D.y && clearPosition2D.x == player->position2D.x) {
		num->clearFlag = true;
	}

	// 5×5
	for (int i = 0; i < 25; i++) {
		modelRender[i].Update();
	}
}

void Stage::Render(RenderContext& rc)
{
	// 5×5
	for (int i = 0; i < 25; i++) {
		modelRender[i].Draw(rc);
	}
}