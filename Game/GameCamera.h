#pragma once

class Num;
// ゲームカメラ
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();
	void Normal();	// 見回し(ノーマル設定)
	void Reverse();	// 見回し(リバース設定)

	// メンバ変数
	SpriteRender spriteRender;
	Vector3 cameraPos;		// 注視点から視点へのベクトル

	Num* num;

	int cameraState = 0;	// 回転切り替え
	int c_stageState = 0;	// カメラの位置切り替え
};

