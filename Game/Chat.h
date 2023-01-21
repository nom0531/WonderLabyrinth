#pragma once

class Num;
class Sum;
class UI;

// 会話用クラス
class Chat:public IGameObject
{
public:
	Chat();
	~Chat();

	void Update();
	void Name();						// 表示名の判別
	void RundumChat();					// ランダムチャット
	void RundumUpdate();				// ランダムチャット用の処理
	void Button_SinMove();		// スプライトを上下させる
	void EventChat();					// チュートリアル用会話
	void EventUpdate();					// チュートリアル用の処理
	void Render(RenderContext& rc);

	// ランダムな値を渡す
	int getRundumNum() {
		// 1～10の値をランダムに返す
		return rand() % 10 + 1;
	}

	// メンバ変数
	SpriteRender spriteRender_npc;		// キャラクター
	SpriteRender spriteRender_textbox;	// テキストボックス
	SpriteRender spriteRender_button;	// ボタン

	FontRender fontRender_name;			// キャラクター名格納用
	FontRender* fontRender = nullptr;	// 会話内容

	Num* num;							// 値格納用
	Sum* sum;							// 計算用

	UI* ui;

	// 文字
	float waitTimer = 1.0f;				// 表示するまでの待ち時間
	float chatSpeed = 0.02;				// 文字の表示速度

	bool StopDrawFlag = false;			// 文字を一時的に非表示にする
	bool drawChatFlag = false;			// 文字を表示し終えたかどうか
	bool NextchatFlag = false;			// 次の文字を表示するかどうか
	bool playToSeFlag = true;			// キャラクターの音声を再生するかどうか

	bool eventFlag = false;				// イベントかランダムかの判別　trueでイベント中
	bool rundumChatStart = false;		// ランダムチャットを開始する
	bool eveneStartFlag = false;		// true:ランダム会話・イベントを開始する

	// 会話処理用
	int chatState = 0;					// チュートリアルの内容の指定
	int chatState_end = 20;				// 会話終了時の値

	int rundumState = 0;				// ランダムテキストの内容の指定
	int clearState = 0;					// 条件達成ステート 1:動いた 2:アイテムの獲得 3:ゲームクリア 4:ゲーム終了

	// ▼の移動処理用
	float movePos = 1.0f;				// 加算する移動値 (y軸)
	float sumPos = 0.0f;
	int moveState = 0;					// 0:下向きに移動　1:上向きに移動
};

