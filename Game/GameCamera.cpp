#include "stdafx.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Num.h"

GameCamera::GameCamera()
{
	// near,farの設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// 注視点から視点までのベクトル
	cameraPos.Set(0.0f, 125.0f, -250.0f);
	
	num = FindGO<Num>("num");		// インスタンスを探す
	c_stageState = num->stageState;	// ステージの情報
	return true;
}

void GameCamera::Update()
{
	// 操作不能でないとき
	if (num->stopFlag == false) {
		// カメラ切り替え
		switch (cameraState) {
		//ノーマル回転
		case 0:Normal();
			break;
		// リバース回転
		case 1:Reverse();
			break;
		}
	}
	// 或いはカメラの調節をするように指示されているとき
	else if (num->CameraAdjustmentFlag == true) {
		// カメラ切り替え
		switch (cameraState) {
			//ノーマル回転
		case 0:Normal();
			break;
			// リバース回転
		case 1:Reverse();
			break;
		}
	}

	// ボタンを押したとき
	if (g_pad[0]->IsTrigger(enButtonX)) {
		// リバースへ切り替え
		if (cameraState == 0) {
			cameraState = 1;
		}
		// ノーマルへ切り替え
		else if (cameraState == 1) {
			cameraState = 0;
		}
	}
}

void GameCamera::Normal()
{
	// 注視点
	Vector3 c_position;				// カメラの位置
	switch (c_stageState) {
	case 0:
		// チュートリアル
		c_position = {100.0f, 10.0f, 2.0f};

		break;
	case 1:
	case 2:
		// それ以外
		c_position = {200.0f, 10.0f, 2.0f};
		num->CameraAdjustmentFlag == false;
		break;
	}
	
	// 注視点
	Vector3 target = c_position;
	//Vector3 target = Vector3::Zero;
	target.y += 50.0;
	target.z += 80.0;

	Vector3 cameraPosOld = cameraPos;

	// パッド入力でカメラを回す
	float x = g_pad[0]->GetLStickXF();
	float y = g_pad[0]->GetLStickYF();
	// Y軸
	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, 0.1 * x);
	rot.Apply(cameraPos);
	// X軸(Normal)
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, cameraPos);
	axisX.Normalize();
	rot.SetRotationDeg(axisX, -1.5f * y);
	rot.Apply(cameraPos);
	// カメラの回転の上限をチェックする。
	// 注視点から視点までのベクトルを正規化する。
	// 正規化すると、ベクトルの大きさが１になる。
	// 大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = cameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		// カメラが上向きすぎ。
		cameraPos = cameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		// カメラが下向きすぎ。
		cameraPos = cameraPosOld;
	}

	// 視点を計算する。
	Vector3 pos = target + cameraPos;
	// メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	// カメラの更新。
	g_camera3D->Update();

	//target = Vector3::Zero;		// デバッグ用
	//pos = { 0.0f,80.0f,-150.0f };	// デバッグ用
}

void GameCamera::Reverse()
{
	// 注視点
	Vector3 c_position;				// カメラの位置
	switch (c_stageState) {
	case 0:
		c_position = { 100.0f, 10.0f, 2.0f };
		break;
	case 1:
	case 2:
		c_position = { 200.0f, 10.0f, 2.0f };
		num->CameraAdjustmentFlag == false;
		break;
	}

	Vector3 target = c_position; // 注視点
	// Vector3 target = Vector3::Zero;
	target.y += 50.0;
	target.z += 80.0;

	Vector3 cameraPosOld = cameraPos;
	// パッド入力でカメラを回す
	float x = g_pad[0]->GetLStickXF();
	float y = g_pad[0]->GetLStickYF();
	// Y軸
	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, 0.1 * x);
	rot.Apply(cameraPos);
	// X軸(Reverse)
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, cameraPos);
	axisX.Normalize();
	rot.SetRotationDeg(axisX, 1.5f * y);
	rot.Apply(cameraPos);

	// カメラの回転の上限をチェックする。
	// 注視点から視点までのベクトルを正規化する。
	// 正規化すると、ベクトルの大きさが１になる。
	// 大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = cameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		// カメラが上向きすぎ。
		cameraPos = cameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		// カメラが下向きすぎ。
		cameraPos = cameraPosOld;
	}

	// 視点を計算する。
	Vector3 pos = target + cameraPos;
	// メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	// カメラの更新。
	g_camera3D->Update();
}