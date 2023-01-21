#pragma once

// ステート格納クラス
class Num:public IGameObject
{
public:
	bool CameraAdjustmentFlag = false;		// カメラの位置を調節するフラグ

	bool clearFlag = false;			// ゲームのクリア判定
	bool stopFlag = false;			// true :ゲーム内の操作などなどをすべて停止する
	bool NewGoFlag = false;			// イベント用フラグ (初回)
	bool movePlayer = false;		// イベント用移動フラグ
	bool getItem = false;			// イベント用アイテム獲得フラグ

	int turn = 1;					// 1:プレイヤー　2:MOB
	int stageState = 0;				// 0:チュートリアル　1:草原　2:洞窟
	int stageNum = 0;				// ステージのマス数

	int enemyNum = 0;				// エネミーの数

	int Rundum_StageNum = 0;		// ステージのランダム生成の値

	bool drawChatFlag = false;		// チャットを描画したかどうか
};

