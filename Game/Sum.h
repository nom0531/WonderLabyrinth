#pragma once

class Game;
class Player;
class UI;
class GameClear;
class Num;
class GameStop;

// 計算用クラス
class Sum:public IGameObject
{
public:
	Sum();
	~Sum();

	void Update();
	void ItemGage();										// アイテムゲージ
	int CrearScore(int item,int stage,int hp);				// クリアスコア
	//void MoveSprite();									// 画像を上下に動かす　使用しない

	// メンバ変数
	Player* player;
	UI* ui;
	GameClear* gameClear;
	Num* num;
	GameStop* gameStop;

	// <summary>
	// 正弦波を利用して画像を上下に動かす
	// </summary>
	// <param name="int">何秒で一周するかを指定する (60カウント/秒) </param>
	// <param name="float">移動値の幅を指定する</param>
	//void setMoveFromSin(int a ,float b) {
	//	syuuki = a;
	//	moveMin_Max = b;
	//}
	// 正弦波を利用した計算後の値を獲得する
	//float getMoveAfterFromSin() {
	//	return AfterPos;
	//}

	bool clearFlag = false;			// クリアしているかどうか

	// アイテムゲージ用
	int nowGage = 800;				// 現在のゲージ量(デフォルト 600)
	const int maxGage = 800;		// 最大値
	const int minGage = 0;			// 最小値
	const int addGage = 200;		// 回復量
	float Scale_x = 0.0f;			// スケールの値

	// スコア用
	const int addPoint_stage = 10;	// 加算スコア
	const int addPoint_item = 100;
	const int addPoint_hp = 1000;

	//int itemNum = 0;				// 獲得アイテム数
	//int stageNum = 0;				// ステージクリア数
	//int HPNum = 0;				// 残りHP

//private:
//
//	float AfterPos = 0.0f;			// 計算後の座標
//
//	float PI = 3.141592654f;		// 円周率
//	float Count = 0;				// 一秒間にカウントするカウンタ
//	int syuuki = 0;					// 周期
//	float moveMin_Max = 0.0f;		// 移動幅
};

