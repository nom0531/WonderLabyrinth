#include "stdafx.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "Num.h"
#include "Stage.h"
#include "Stage2.h"
#include "Sum.h"
#include <iostream>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start() 
{
	// レイトレースを切る
	s_modelRender.SetRaytracingWorld(false);

	// インスタンスを探す
	player = FindGO<Player>("player");
	num = FindGO<Num>("num");
	sum = FindGO<Sum>("sum");

	// ステージの状態
	if (num->stageState == 0) {
		stage = FindGO<Stage>("stage");
	}
	else {
		stage2 = FindGO<Stage2>("stage2");
	}

	// slimeRabbit
	s_animationClips[slime_AnimationClip_Idle].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Idle.tka");		// 待機
	s_animationClips[slime_AnimationClip_Idle].SetLoopFlag(true);													// ループあり
	s_animationClips[slime_AnimationClip_Walk].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Move.tka");		// 歩く
	s_animationClips[slime_AnimationClip_Walk].SetLoopFlag(true);													// ループあり
	s_animationClips[slime_AnimationClip_Damage].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Damage.tka");		// やられ
	s_animationClips[slime_AnimationClip_Damage].SetLoopFlag(false);
	s_animationClips[slime_AnimationClip_Dead].Load("Assets/animData/SlimeRabbitAnim/SlimeRabbit_Death.tka");		// やられ
	s_animationClips[slime_AnimationClip_Dead].SetLoopFlag(false);
	// モデルの読み込み
	s_modelRender.Init("Assets/modelData/model/enemy/SlimeRabbit/SlimeRabbit.tkm", s_animationClips, slime_AnimationClip_Num, enModelUpAxisZ);
	s_modelRender.SetScale(2.0f, 2.0f, 2.0f);

	num->enemyNum++;	// エネミーの数を増やす

	return true;
}

void Enemy::Update()
{
	m_Slime();
	PlayAnimation();

	// 死亡処理が終了したらdeleteGO
	if (s_modelRender.IsPlayingAnimation() == false && s_State == 2) {
		num->enemyNum--;	// 倒れたので数を減らす
		s_ItemNewGO();		// アイテムを生成
		DeleteGO(this);
	}

	s_modelRender.SetPosition(s_position);
	s_modelRender.Update();
}

bool Enemy::s_IsMove(Vector2 movePos)
{
	// 移動先の座標がplayerと重なっているかどうか計算する
	bool isMove = true;	// 移動できる

	// プレイヤーの次の座標
	// 移動できる？		
	// 移動先が同じ時falseを返す
	if (player->position2D.x == movePos.x && player->position2D.y == movePos.y) {
		isMove = false;
	}

	// エネミー
	//QueryGOs<Enemy>("slime", [&](Enemy* slime) {
	//	// 移動できる？
	//	Vector2 enemyNextPos = slime->s_position2D;
	//	// 移動先がエネミーと同じ
	//	if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
	//		isMove = false;
	//	}

	//	enemyNextPos.x += slime->s_NextMove[slime->s_moveCount].x;
	//	enemyNextPos.y += slime->s_NextMove[slime->s_moveCount].y;
	//	// 移動先がエネミーの移動先と同じ
	//	if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
	//		isMove = false;
	//	}

	//	return true;
	//	});

	QueryGOs<Enemy2>("mush", [&](Enemy2* mush) {
		// 移動できる？
		Vector2 enemyNextPos = mush->m_position2D;
		// 移動先がエネミーと同じ
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		//enemyNextPos.x += mush->m_NextMove[mush->m_moveCount].x;
		//enemyNextPos.y += mush->m_NextMove[mush->m_moveCount].y;
		// 移動先がエネミーの移動先と同じ
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		return true;
		});

	// 地形判定
	// 範囲外だったら false を返す
	if (movePos.x < 0.0f) {
		isMove = false;
	}
	if (movePos.x > num->stageNum - 1) {
		isMove = false;
	}
	if (movePos.y < 0.0f) {
		isMove = false;
	}
	if (movePos.y > num->stageNum - 1) {
		isMove = false;
	}


	switch (num->stageState) {
	case 0:
		// 地形
		if (stage->stageFlag[(int)movePos.y][(int)movePos.x] == 1) {
			isMove = false;
		}
		break;
	case 1:
	case 2:
		// 地形
		if (stage2->stageFlag[(int)movePos.y][(int)movePos.x] == 1) {
			isMove = false;
		}
		break;
	}

	return isMove;
}

void Enemy::s_ItemNewGO()
{
	// 自身と同じ位置にアイテムを生成する
	item = NewGO<Item>(0, "item");
	item->position = s_position;
	item->position.y = 20.0f;
}

void Enemy::m_Slime()
{
	// 被弾アニメーション中はこれより下は実行しない
	if (s_modelRender.IsPlayingAnimation() == true && s_State == 3) {
		return;
	}
	// 死亡アニメーション中は何もしない
	if (s_State == 2) {
		return;
	}
	if (nowTurnEnd == true) {
		return;
	}

	// 自分のターンの時以外は動かないようにする
	if (num->turn == 2) {
		moveFlag = true;
	}
	else {
		moveFlag = false;
	}

	float moveSpeed = 50.0f;	// 移動速度
	float forward[8] = { 90.0f,90.0f, 180.0f,180.0f, -90.0f,-90.0f, 0.0f,0.0f };	// 回転

	// 自分のターンの時
	if (moveFlag == true) {

		// 移動予定地の計算
		Vector2 move = s_position2D;
		move.x += s_NextMove[s_moveCount].x;
		move.y += s_NextMove[s_moveCount].y;

		// 移動先にplayerがいたら中断する
		if (s_IsMove(move) == false) {
			nowTurnEnd = true;	// 自分のターンが終了したことを知らせる
			return;
		}

		s_State = 1;

		//座標の移動
		s_position.x += s_NextMove[s_moveCount].x * moveSpeed;
		s_position.z += s_NextMove[s_moveCount].y * -moveSpeed;	// モデルでは奥行きが+のためマイナスを乗算する
		// 向きの指定
		s_rotation.SetRotationDegY(forward[s_moveCount]);
		s_forward.Set(s_NextMove[s_moveCount].x, s_NextMove[s_moveCount].y);	// 正面
			
		// 上
		if (s_NextMove[s_moveCount].y < 0.0f) {
			s_MoveState = 1;
		}
		// 右
		if (s_NextMove[s_moveCount].x > 0.0f) {
			s_MoveState = 2;
		}
		// 左
		if (s_NextMove[s_moveCount].x < 0.0f) {
			s_MoveState = 3;
		}
		// 下
		if (s_NextMove[s_moveCount].y > 0.0f) {
			s_MoveState = 4;
		}

		NowPosition();	// 現在位置の更新

		nowTurnEnd = true;
	}
	else {
		s_State = 0;
	}

	// 移動処理
	if (moveFlag == true) {
		// カウントを増やす
		s_moveCount++;
		// カウントをリセット
		if (s_moveCount >= ((int)sizeof(s_NextMove) / (int)sizeof(Vector2)))
		{
			s_moveCount = 0;
		}
	}

	s_modelRender.SetRotation(s_rotation);	// 回転を教える
	s_modelRender.SetPosition(s_position);	// 座標を教える
}

void Enemy::s_Damege() 
{
	s_HP -= player->player_Attack;
	s_State = 3;

	if (s_HP <= 0) {
		s_State = 2;
	}
}

void Enemy::NowPosition()
{
	// 座標の更新
	switch (s_MoveState) {
	case 1:
		// 上
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j - 1] = 1;
				}
				// チュートリアル以外
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j - 1] = 1;
				}

				s_position2D.y -= 1.0f;
				s_MoveState = 0;
				return;
			}
		}
		break;
	case 2:
		// 右
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j + 1] = 1;
				}
				// チュートリアル以外
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j + 1] = 1;
				}

				s_position2D.x += 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	case 3:
		// 左
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i][j - 1] = 1;
				}
				// チュートリアル以外
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i][j - 1] = 1;
				}

				s_position2D.x -= 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	case 4:
		// 下
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (s_position_stage[i][j] == 1) {

					s_position_stage[i][j] = 0;
					s_position_stage[i + 1][j] = 1;
				}
				// チュートリアル以外
				else if (s_position_stage2[i][j] == 1) {

					s_position_stage2[i][j] = 0;
					s_position_stage2[i + 1][j] = 1;
				}

				s_position2D.y += 1.0f;
				s_MoveState = 0;

				return;
			}
		}
		break;
	default:
		// 上記以外の時は何もしない
		break;
	}
}

void Enemy::PlayAnimation()
{
	switch (s_State) {
	case 0:
		s_modelRender.PlayAnimation(slime_AnimationClip_Idle);		// 待機
		break;
	case 1:
		s_modelRender.PlayAnimation(slime_AnimationClip_Walk);		// 歩く
		break;
	case 2:
		s_modelRender.PlayAnimation(slime_AnimationClip_Dead);		// 死亡
		break;
	case 3:
		s_modelRender.PlayAnimation(slime_AnimationClip_Damage);	// やられ
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	// 描画
	s_modelRender.Draw(rc);
}