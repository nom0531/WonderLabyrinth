#include "stdafx.h"
#include "Chat.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Num.h"
#include "Sum.h"
#include "UI.h"

Chat::Chat()
{
	// 効果音
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/B_Button.wav");
	g_soundEngine->ResistWaveFileBank(25, "Assets/sound/Aru_ChatEnd.wav");

	// インスタンスを探す
	num = FindGO<Num>("num");

	sum = FindGO<Sum>("sum");

	// キャラクター
	spriteRender_npc.Init("Assets/sprite/aru.DDS", 411.0f, 407.0f);
	spriteRender_npc.SetPosition({ 380.0f,10.0f,0.0f });
	spriteRender_npc.SetScale({ 1.2f, 1.2f, 0.0f });

	// テキストボックス
	spriteRender_textbox.Init("Assets/sprite/UI/textBox.DDS", 1300.0f, 400.0f);
	spriteRender_textbox.SetPosition({ 0.0f,-250.0f,0.0f });
	spriteRender_textbox.SetScale({0.8f, 0.8f, 0.0f});
	spriteRender_textbox.SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	// ▼
	spriteRender_button.Init("Assets/sprite/UI/button_white.DDS", 66.0f, 55.0f);
	spriteRender_button.SetPosition({ 450.0f,-350.0f,0.0f });
	spriteRender_button.SetScale({ 0.8f, 0.8f, 0.0f });

	// 名前
	fontRender_name.SetText(L"アル");
	fontRender_name.SetPosition(-440.0f, -95.0f, 0.0f);
}

Chat::~Chat()
{
}

void Chat::Name() 
{
	// イベント時
	if (eventFlag == true) {
		EventChat();
	}
	// ランダムチャット
	else if (rundumChatStart==true) {
		// ランダムな値を受けとる
		rundumState = getRundumNum();
		RundumChat();
	}
}

void Chat::RundumChat()
{
	// リセット
	if (fontRender != nullptr) {
		delete fontRender;
	}
	fontRender = new FontRender;
	fontRender->SetPosition(-470.0f, -200.0f, 0.0f);

	switch (rundumState) {
	case 1:
		fontRender->SetTextOkuri(L"スライムは敵対的じゃないのカナ\n戦わずに切り抜けられるかも?", chatSpeed, playToSeFlag);
		break;
	case 2:
		fontRender->SetTextOkuri(L"キノコは追いかけてくるみたいだネ\nなにか条件があるのかな・・・?", chatSpeed, playToSeFlag);
		break;
	case 3:
		fontRender->SetTextOkuri(L"そうそう　ゲージが0になっちゃうと\n行動できなくなるから注意ダヨ。", chatSpeed, playToSeFlag);
		break;
	case 4:
		fontRender->SetTextOkuri(L"行動不能になったら?\n・・・うーん　ボクがなんとかするヨ!", chatSpeed, playToSeFlag);
		break;
	case 5:
		fontRender->SetTextOkuri(L"伝え忘れちゃってたケド\n敵を倒してもアイテムを落とすよ!", chatSpeed, playToSeFlag);
		break;
	case 6:
		fontRender->SetTextOkuri(L"ゲージを保つことは大事だけど\n自分のHPも大切にしてネ!", chatSpeed, playToSeFlag);
		break;
	case 7:
		fontRender->SetTextOkuri(L"「困ったときはSTARTボタン!」\n覚えておいてくれると嬉しいナ!", chatSpeed, playToSeFlag);
		break;
	case 8:
		fontRender->SetTextOkuri(L"カメラの上下移動はXボタンで\n切り替えられるヨ　試してみてね!", chatSpeed, playToSeFlag);
		break;
	case 9:
		fontRender->SetTextOkuri(L"攻撃したときにも敵が動いた!\nこれ　うまく使えないカナ・・・。", chatSpeed, playToSeFlag);
		break;
	case 10:
		fontRender->SetTextOkuri(L"・・・ところで\nすたーとぼたん・・・って何?", chatSpeed, playToSeFlag);
		break;
	}
}

void Chat::EventChat()
{
	// リセット
	if (fontRender != nullptr) {
		delete fontRender;
	}
	fontRender = new FontRender;
	fontRender->SetPosition(-470.0f, -200.0f, 0.0f);
	
	// 会話内容
	// 現在の間隔では17文字の時点で\n
	switch (chatState) {
	case 0:
		// ロード中に表示させているのでSEは無し
		fontRender->SetTextOkuri(L"ようこそ!チュートリアルへ!", chatSpeed, false);
		break;
	case 1:
		fontRender->SetTextOkuri(L"ボクはアル　よろしくね!", chatSpeed, playToSeFlag);
		break;
	case 2:
		fontRender->SetTextOkuri(L"まずは・・・移動する為の\n基本操作をおさらい!", chatSpeed, playToSeFlag);
		break;
	case 3:
		fontRender->SetTextOkuri(L"「移動は十字キー」だよ!\nそれじゃ　早速動いてみよう!", chatSpeed, playToSeFlag);
		break;
	case 4:
		break;
	case 5:
		fontRender->SetTextOkuri(L"うんうん　ばっちりダネ!", chatSpeed, playToSeFlag);
		break;
	case 6:
		fontRender->SetTextOkuri(L"ところデ・・・左上の青いゲージが\nすこし減ったコトに気が付いた?", chatSpeed, playToSeFlag);
		break;
	case 7:
		fontRender->SetTextOkuri(L"このゲージは　行動できる残り時間。\n迷宮にいる間どんどん減っていくんだ。", chatSpeed, playToSeFlag);
		break;
	case 8:
		fontRender->SetTextOkuri(L"回復する方法は　ゲージの色と同じ\n「青いクリスタルを拾う」コト!", chatSpeed, playToSeFlag);
		break;
	case 9:
		fontRender->SetTextOkuri(L"ちょうど近くに\n落ちているみたいだけど・・・。", chatSpeed, playToSeFlag);
		break;
	case 10:
		fontRender->SetTextOkuri(L"敵もいるみたいダネ・・・\nそれじゃ、攻撃方法をおさらい!", chatSpeed, playToSeFlag);
		break;
	case 11:
		fontRender->SetTextOkuri(L"「攻撃するにはAボタン」!\nうまく使って歩いてみよう!", chatSpeed, playToSeFlag);
		break;
	case 12:
		break;
	case 13:
		fontRender->SetTextOkuri(L"やった!　無事にゲットできたね!", chatSpeed, playToSeFlag);
		break;
	case 14:
		fontRender->SetTextOkuri(L"ゲットしたときにゲージが\n回復したのがわかったかな?", chatSpeed, playToSeFlag);
		break;
	case 15:
		fontRender->SetTextOkuri(L"迷宮内ではクリスタルを\n沢山集めて進んでいくことがカギ!", chatSpeed, playToSeFlag);
		break;
	case 16:
		fontRender->SetTextOkuri(L"それをふまえて\nゴールまで歩いてみよう!", chatSpeed, playToSeFlag);
		break;
	case 17:
		break;
	case 18:
		fontRender->SetTextOkuri(L"ゴールおめでとう!\nチュートリアルはこれでおしまい!", chatSpeed, playToSeFlag);
		break;
	case 19:
		fontRender->SetTextOkuri(L"基本はばっちりかな?\nそれじゃ　困ったときは\nSTARTボタンで呼んでね!", chatSpeed, playToSeFlag);
		break;
	}
}


void Chat::Update()
{	
	// イベント時の処理
	if (eventFlag == true) {
		EventUpdate();
	}
	// ランダムテキストの処理
	else {
		RundumUpdate();
	}

	if (fontRender != nullptr) {
		// 文字を表示し終えたかどうか調べる
		drawChatFlag = fontRender->GetMessageOkuriFlag();

		fontRender->TextOkuriUpdate(g_gameTime->GetFrameDeltaTime());	// フォントの更新
	}

	// 表示し終わっているとき
	//if (drawChatFlag == false) {

	//	sumPos = -350.0f - movePos;			// 元の座標 + 加算値

	//	switch (moveState) {
	//	case 0:
	//		// 下向きに移動しているとき
	//		if (sumPos == -360.0f) {
	//			movePos *= -1.0f;
	//			moveState = 1;					// 上向きに移動
	//		}
	//		break;
	//	case 1:
	//		// 上向きに移動しているとき
	//		if (sumPos == -350.0f) {
	//			movePos *= -1.0f;
	//			moveState = 0;					// 下向きに移動
	//		}
	//		break;
	//	} 

	//	spriteRender_button.SetPosition({ 450.0f,sumPos,0.0f });
	//}

	// スプライトを更新する
	spriteRender_npc.Update();
	spriteRender_button.Update();
	spriteRender_textbox.Update();
}

void Chat::EventUpdate()
{
	// 文字を表示しているとき
	if (StopDrawFlag == false) {
		// 文字を表示し終わっているとき
		if (drawChatFlag == false) {
			// かつBボタンを押したとき
			if (g_pad[0]->IsTrigger(enButtonB)) {

				// 効果音を再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(10);				// Bボタン
				se->Play(false);			// ループしない
				se->SetVolume(3.5f);		// 音量の設定をする

				chatState++;				// 次の文字を表示する
				EventChat();
			}
		}
	}

	// 一定条件で進むときテキストを一旦消去する
	if (chatState == 4 || chatState == 12 || chatState == 17) {
		NextchatFlag = false;				// テキストを一時的に非表示にする
	}
	else {
		NextchatFlag = true;				// テキストをそのまま表示する
	}

	// 次の文字を表示する
	if (NextchatFlag == true) {

		num->stopFlag = true;	// 動けないようにする
		StopDrawFlag = false;	// 非表示を解除

		// 文字ステートが一定
		if (chatState == chatState_end) {
			eveneStartFlag = false;	// イベントが終了したのでfalseにする
		}
	}
	// 次の文字を表示しない (一定操作が必要な時)
	else if(NextchatFlag == false) {

		num->stopFlag = false;		// 動けるようにする
		StopDrawFlag = true;		// 非表示にする

		// playerが動いたとき
		if (num->movePlayer == true && clearState == 0) {
			
			eveneStartFlag = true;	// イベントを再開
			num->stopFlag = true;	// 動けないようにする

			chatState = 5;			// テキストを指定する
			clearState = 1;			// 達成ステートを切り替える

			EventChat();
		}
		// アイテムを獲得したとき
		if (num->getItem == true && clearState == 1) {

			// タイマーが0のとき
			waitTimer -= g_gameTime->GetFrameDeltaTime();
			if (waitTimer <= 0.0f) {

				eveneStartFlag = true;	// イベントを再開
				num->stopFlag = true;	// 動けないようにする

				chatState = 13;			// テキストを指定する
				clearState = 2;			// 達成ステートを切り替える

				EventChat();
			}
		}
		// ゴールに到着したとき
		if (num->clearFlag == true && clearState == 2) {

			eveneStartFlag = true;	// イベントを再開
			num->stopFlag = true;	// 動けないようにする

			chatState = 18;			// テキストを指定する
			clearState = 3;			// 達成ステートを切り替える

			EventChat();
		}
		else if (num->clearFlag == true && clearState == 1) {
			eveneStartFlag = true;	// イベントを再開
			num->stopFlag = true;	// 動けないようにする

			chatState = 18;			// テキストを指定する
			clearState = 3;			// 達成ステートを切り替える

			EventChat();
		}
	}
}

void Chat::RundumUpdate()
{
	// 表示し終わっているとき
	if (drawChatFlag == false) {
		// Bボタンを押したとき
		if (g_pad[0]->IsTrigger(enButtonB)) {

			// 効果音を再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(25);
			se->Play(false);				// ループしない
			se->SetVolume(3.5f);			// 音量の設定をする

			eveneStartFlag = false;			// イベントが終了したのでfalseにする
			rundumChatStart = false;		// ランダムチャットを終了する
			num->stopFlag = false;			// 動けるようにする
			num->drawChatFlag = false;		// 次の描画ができるように描画済みフラグを降ろす
			DeleteGO(this);					// 自身を削除する
		}

	}
}

void Chat::Button_SinMove()
{

}


void Chat::Render(RenderContext& rc)
{
	if (StopDrawFlag == false) {
		spriteRender_npc.Draw(rc);
		spriteRender_textbox.Draw(rc);

		fontRender_name.Draw(rc);

		if (fontRender != nullptr) {
			fontRender->Draw(rc);
		}

		// 表示し終えたとき描画する
		if (drawChatFlag == false) {
			spriteRender_button.Draw(rc);
		}
	}
}