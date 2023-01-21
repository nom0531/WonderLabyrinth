#include "stdafx.h"
#include "Enemy2.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "Num.h"
#include "Stage.h"
#include "Stage2.h"
#include "Sum.h"

Enemy2::Enemy2()
{

}

Enemy2::~Enemy2()
{

}

bool Enemy2::Start() {
	// レイトレースを切る
	m_modelRender.SetRaytracingWorld(false);

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

	// mushroomMan
	m_animationClips[mush_AnimationClip_Idle].Load("Assets/animData/MushroomManAnim/MushroomMonster_Idle.tka");		// 待機
	m_animationClips[mush_AnimationClip_Idle].SetLoopFlag(true);													// ループあり
	m_animationClips[mush_AnimationClip_Walk].Load("Assets/animData/MushroomManAnim/MushroomMonster_Walk.tka");		// 歩く
	m_animationClips[mush_AnimationClip_Walk].SetLoopFlag(true);													// ループあり
	m_animationClips[mush_AnimationClip_Attack].Load("Assets/animData/MushroomManAnim/MushroomMonster_Attack.tka");	// 攻撃
	m_animationClips[mush_AnimationClip_Attack].SetLoopFlag(false);													// ループなし
	m_animationClips[mush_AnimationClip_Damege].Load("Assets/animData/MushroomManAnim/MushroomMonster_Damage.tka");	// やられ
	m_animationClips[mush_AnimationClip_Damege].SetLoopFlag(false);
	m_animationClips[mush_AnimationClip_Dead].Load("Assets/animData/MushroomManAnim/MushroomMonster_Death.tka");	// やられ
	m_animationClips[mush_AnimationClip_Dead].SetLoopFlag(false);
	// モデルの読み込み
	m_modelRender.Init("Assets/modelData/model/enemy/MushroomMan/MushroomMan.tkm", m_animationClips, mush_AnimationClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(0.4f, 0.4f, 0.4f);

	num->enemyNum++;	// エネミーの数を増やす

	return true;
}

void Enemy2::Update()
{
	m_Mush();
	PlayAnimation();						// アニメーション

	// 攻撃アニメーションが終了したとき
	if (m_modelRender.IsPlayingAnimation() == false && m_State == 2) {
		num->turn = 1;	// playerのターンにする
		m_State = 0;	// 待機モーションに戻す
	}

	// 死亡処理が終了したらdeletego
	if (m_modelRender.IsPlayingAnimation() == false && m_State == 3) {
		num->enemyNum--;	// 倒れたので数を減らす
		m_ItemNewGO();		// アイテムを生成
		DeleteGO(this);
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy2::PlayAnimation()
{
	switch (m_State) {
	case 0:
		m_modelRender.PlayAnimation(mush_AnimationClip_Idle);		// 待機
		break;
	case 1:
		m_modelRender.PlayAnimation(mush_AnimationClip_Walk);		// 歩く
		break;
	case 2:
		m_modelRender.PlayAnimation(mush_AnimationClip_Attack);		// 攻撃
		break;
	case 3:
		m_modelRender.PlayAnimation(mush_AnimationClip_Dead);		// 倒れた
		break;
	case 4:
		m_modelRender.PlayAnimation(mush_AnimationClip_Damege);		// 被弾
		break;
	}
}

bool Enemy2::Search()
{
	bool flag = false;

	// プレイヤーが自身の向きと同じ列にいるとき
	switch (m_ForwardState) {
	case 1:
		// 上方向
		if (player->position2D.x == m_position2D.x &&
			player->position2D.y <= m_position2D.y &&
			player->position2D.y >= m_position2D.y - 3.0f) {
			flag = true;
		}
		break;
	case 2:
		// 右方向
		if (player->position2D.y == m_position2D.y &&
			player->position2D.x >= m_position2D.x &&
			player->position2D.x <= m_position2D.x + 3.0f) {
			flag = true;
		}
		break;
	case 3:
		// 左方向
		if (player->position2D.y == m_position2D.y &&
			player->position2D.x <= m_position2D.x &&
			player->position2D.x >= m_position2D.x - 3.0f) {
			flag = true;
		}
		break;
	case 4:
		// 下方向
		if (player->position2D.x == m_position2D.x &&
			player->position2D.y >= m_position2D.y &&
			player->position2D.y <= m_position2D.y + 3.0f) {
			flag = true;
		}
		break;
	}

	return flag;
}

void Enemy2::m_ItemNewGO()
{
	// 自身と同じ位置にアイテムを生成する
	item = NewGO<Item>(0, "item");
	item->position = m_position;
	item->position.y = 20.0f;
}

void Enemy2::m_Mush()
{
	// 操作等を停止するようにしているときは以下の処理は行わない
	if (num->stopFlag == true) {
		return;
	}

	// 被弾アニメーション中はこれより下は実行しない
	if (m_modelRender.IsPlayingAnimation() == true && m_State == 4) {
		return;
	}
	// 死亡アニメーション中は何もしない
	if (m_State == 3) {
		return;
	}
	// 自身のターンが終了しているとき何もしない
	if (nowTurnEnd == true) {
		return;
	}

	if (num->turn == 2) {
		moveFlag = true;
	}
	else {
		moveFlag = false;
	}

	float moveSpeed = 50.0f;		// 移動速度

	// 自分のターンの時
	if (moveFlag == true) {
		m_moveCount++;

		
		// 通常パターン
		if (searchFlag == false) {
			m_State = 0;
			m_MoveState = 0;
			// その場で2ターンごとに回転する
			if (m_moveCount >= 0 && m_moveCount <= 2) {
				// 右回転
				m_RotState = 2;
			}
			else if (m_moveCount >= 3 && m_moveCount <= 5) {
				// 下回転
				m_RotState = 4;
			}
			else if (m_moveCount >= 6 && m_moveCount <= 8) {
				// 左回転
				m_RotState = 3;
			}
			else if (m_moveCount >= 9 && m_moveCount <= 11) {
				// 上回転
				m_RotState = 1;

				if (m_moveCount == 10) {
					// カウントをリセット
					m_moveCount = 0;
				}
			}

			// 索敵
			if (Search() == true) {
				searchFlag = true;
			}
		}
		// プレイヤーを見つけた時
		if (searchFlag == true) {
			m_State = 1;

			// 隣接しているとき
			if (m_IsJoin() == true) {
				if (attackWaitFlag == true) {
					attackWaitFlag = false;
				}
				else {
					m_Attack();		// 攻撃する
				}
			}
			else {

				Chase(moveSpeed);

			}
		}

		m_Rot();					// 回転の計算を実行する
		NowPosition();							// 二次元配列上の座標
		nowTurnEnd = true;
	}
	else {
		m_State = 0;
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
}

void Enemy2::Chase(float moveSpeed) {

	// playerを追いかける
	Vector3 toPlayer = player->position - m_position;

	// 絶対値で大小を計算する
	// xが近いとき
	if (abs(toPlayer.x) > abs(toPlayer.z)) {
		// 左右どっちか
		if (toPlayer.x > 0.0f) {
			// 右
			Vector2 movePos = m_position2D;
			movePos.x += 1.0f;

			if (m_IsMove(movePos) == true) {
				m_position.x += moveSpeed;
				m_MoveState = 2;

				m_RotState = 2;		// 回転方向を教える

				return;
			}
		}
		else {
			// 左
			Vector2 movePos = m_position2D;
			movePos.x -= 1.0f;

			if (m_IsMove(movePos) == true) {
				m_position.x -= moveSpeed;
				m_MoveState = 3;

				m_RotState = 3;		// 回転方向を教える

				return;
			}
		}
	}

	// zが近いとき
	// 上下どっちか
	if (toPlayer.z > 0.0f) {
		// 前
		Vector2 movePos = m_position2D;
		movePos.y -= 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.z += moveSpeed;
			m_MoveState = 1;

			m_RotState = 1;		// 回転方向を教える

			return;
		}

	}
	else if (toPlayer.z < 0.0f) {
		// 後
		Vector2 movePos = m_position2D;
		movePos.y += 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.z -= moveSpeed;
			m_MoveState = 4;

			m_RotState = 4;		// 回転方向を教える

			return;
		}
	}

	// 左右どっちか
	if (toPlayer.x > 0.0f) {
		// 右
		Vector2 movePos = m_position2D;
		movePos.x += 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.x += moveSpeed;
			m_MoveState = 2;

			m_RotState = 2;		// 回転方向を教える

			return;
		}
	}
	else if (toPlayer.x < 0.0f) {
		// 左
		Vector2 movePos = m_position2D;
		movePos.x -= 1.0f;

		if (m_IsMove(movePos) == true) {
			m_position.x -= moveSpeed;
			m_MoveState = 3;

			m_RotState = 3;		// 回転方向を教える

			return;
		}
	}

}

void Enemy2::m_Rot()
{
	switch (m_RotState) {
	case 1:
		// 上回転
		m_rotation.SetRotationDegY(0.0f);
		m_forward.Set(0, -1);		// 正面を設定
		m_ForwardState = 1;			// 正面のステートを設定
		break;
	case 2:
		// 右回転
		m_rotation.SetRotationDegY(90.0f);
		m_forward.Set(1, 0);		// 正面を設定
		m_ForwardState = 2;			// 正面のステートを設定
		break;
	case 3:
		// 左回転
		m_rotation.SetRotationDegY(-90.0f);
		m_forward.Set(-1, 0);		// 正面を設定
		m_ForwardState = 3;			// 正面のステートを設定
		break;
	case 4:
		// 下回転
		m_rotation.SetRotationDegY(-180.0f);
		m_forward.Set(0, 1);		// 正面を設定
		m_ForwardState = 4;			// 正面のステートを設定
		break;
	}
}

void Enemy2::m_Attack()
{
	// 攻撃する
	m_State = 2;

	player->Damege(m_enemy_Attack);



	// 攻撃場所を計算
	Vector2 attackPos = m_position2D;		// エネミーの前方を計算する
	attackPos.x += m_forward.x;
	attackPos.y += m_forward.y;
}

bool Enemy2 :: m_IsJoin()
{
	bool flag = false;

	//隣接してたらtrue
	// 右方向
	if (m_position2D.x + 1.0f == player->position2D.x &&
		m_position2D.y == player->position2D.y) {
		m_RotState = 2;		// 回転方向を教える
		flag = true;
	}
	// 左方向
	if (m_position2D.x - 1.0f == player->position2D.x &&
		m_position2D.y == player->position2D.y) {
		m_RotState = 3;		// 回転方向を教える
		flag = true;
	}
	// 前方向 (奥)
	if (m_position2D.y + 1.0f == player->position2D.y &&
		m_position2D.x == player->position2D.x) {
		m_RotState = 4;		// 回転方向を教える
		flag = true;
	}
	// 下方向 (手前)
	if (m_position2D.y - 1.0f == player->position2D.y &&
		m_position2D.x == player->position2D.x) {
		m_RotState = 1;		// 回転方向を教える
		flag = true;
	}

	return flag;
}

bool Enemy2::m_IsMove(Vector2 movePos)
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
	QueryGOs<Enemy>("slime", [&](Enemy* slime) {
		// 移動できる？
		Vector2 enemyNextPos = slime->s_position2D;
		// 移動先がエネミーと同じ
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		enemyNextPos.x += slime->s_NextMove[slime->s_moveCount].x;
		enemyNextPos.y += slime->s_NextMove[slime->s_moveCount].y;
		// 移動先がエネミーの移動先と同じ
		if (enemyNextPos.x == movePos.x && enemyNextPos.y == movePos.y) {
			isMove = false;
		}

		return true;
		});

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


void Enemy2 :: m_Damege()
{
	// playerに攻撃された時被弾
	m_HP -= player->player_Attack;
	m_State = 4;

	if (searchFlag == false) {
		searchFlag = true;
		attackWaitFlag = true;
	}

	if (m_HP <= 0) {
		m_State = 3;
	}
}

void Enemy2::NowPosition()
{
	// 座標の更新
	switch (m_MoveState) {
	case 1:
		// 上
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i - 1][j] = 1;

					m_position2D.y -= 1.0f;
					m_MoveState = 0;		// どの方向に移動したか指定する変数をリセットする

					return;
				}
			}
		}
		break;
	case 2:
		// 右
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i][j + 1] = 1;

					m_position2D.x += 1.0f;
					m_MoveState = 0;		// どの方向に移動したか指定する変数をリセットする

					return;
				}
			}
		}
		break;
	case 3:
		// 左
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i][j - 1] = 1;

					m_position2D.x -= 1.0f;
					m_MoveState = 0;		// どの方向に移動したか指定する変数をリセットする

					return;
				}
			}
		}
		break;
	case 4:
		// 下
		for (int i = 0; i < num->stageNum; i++) {
			for (int j = 0; j < num->stageNum; j++) {
				if (m_position_stage[i][j] == 1) {

					m_position_stage[i][j] = 0;
					m_position_stage[i + 1][j] = 1;

					m_position2D.y += 1.0f;
					m_MoveState = 0;		// どの方向に移動したか指定する変数をリセットする

					return;
				}
			}
		}
		break;
	default:
		// 上記以外の時は何もしない
		break;
	}
}

void Enemy2::Render(RenderContext& rc)
{
	// 描画
	m_modelRender.Draw(rc);
}