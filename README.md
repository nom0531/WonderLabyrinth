# WonderLabyrinth
<lead>
河原学園電子ビジネス専門学校 <br>
ゲームクリエイター科 1年 野村華生
</lead>

## 1.作品概要
◆◇ **1.1 作品紹介** ◇◆<br>

 [【作品紹介】Wonder Labyrinth](https://youtu.be/NlRZ1-RVJbg "https://youtu.be/NlRZ1-RVJbg")<br>
 
&emsp; 三人称視点の1人用ターン制アクションゲームです。<br>
&emsp; 時間制限内に体力を保ちつつ、敵を倒しながらステージを進んでいきます。<br>

&emsp; プレイヤーは名もなき冒険家となり、危険な迷宮に挑む最中に出会った妖精、<br>
&emsp; 「アル」を相棒として、ともに迷宮の深部を目指します。<br>

◆◇ **1.2 内部構成** ◇◆<br>

[使用ゲームエンジン]<br>
&emsp;学校内製エンジンを使用 <br>
&emsp;※一部改造箇所あり。[3.技術説明]の "**3.1 会話するNPC**" にて詳しく触れています。

[使用ツール] <br>
&emsp;Visual Studio 2022 <br>
&emsp;3ds Max 2022 <br>
&emsp;Adobe Photoshop 2022 <br>
&emsp;FireAlpaca64 <br>

[使用言語] <br>
&emsp;C++ <br>

[開発環境] <br>
&emsp;Windows11 <br>

[制作人数] <br>
&emsp;1人 <br>

[開発期間] <br>
&emsp;2022/08～2022/12 <br>

## 2.操作説明

◆◇ **2.1 基本操作** ◇◆<br>

![図2.1.1](https://user-images.githubusercontent.com/122655553/213868336-da84f4b4-c8a9-49e5-82e5-40c7954bb47d.png "操作説明") <br>

[ゲーム内操作（ゲームプレイ時の主な操作）] <br>
&emsp;十字キー　 　 …　キャラクターの移動 <br>
&emsp;Lスティック　…　カメラの移動 <br>
&emsp;Xボタン　　　…　カメラの上下切り替え <br>
&emsp;Aボタン　　　…　次のテキストを表示(会話時のみ有効) <br>
&emsp;Bボタン　　　…　攻撃 <br>
&emsp;STARTボタン　…　ヒントを聞く <br>

[システム操作 (タイトル、操作説明など)] <br>
&emsp;十字キー　 　 …　ページ、選択項目の切り替え <br>
&emsp;Aボタン　　　…　決定 <br>
&emsp;Bボタン　　　…　キャンセル <br>

## 3.技術説明

◆◇ **3.1 会話するNPC** ◇◆<br>

![図3.1.1](https://user-images.githubusercontent.com/122655553/214467041-15f1530a-3ec1-4871-8b7a-d134bcdc41a6.png "テキストの出力途中のスクリーンショット")
![図3.1.2](https://user-images.githubusercontent.com/122655553/214469059-aac2ed1f-52b1-431d-8d04-03bc04e39518.png "最終的な出力状態") <br>

&emsp;本作品ではエンジンを改造し、テキストが出力される仕様を作成しています。 <br>
&emsp;出力は1文字ずつ出力され、出力が終わったかどうかを判定して次のテキストを表示します。 <br>

&emsp;エンジン内のFontRender.cpp 及び FontRender.hを改造して作成しました。 <br>
&emsp;※サンプルコード内の関数、及び処理の流れとは多少異なります。 <br>

&emsp;テキストを出力する流れとしては以下の通りです。 <br>
&emsp;1.&nbsp;表示したいテキストを関数（関数名等はサンプルコードにて）で指定。 <br>
&emsp;2.&nbsp;for文を回してテキストを予備の配列に格納。 <br>
&emsp;3.&nbsp;テキストを表示する関数を呼び出し、出力できるようにする。 <br>
&emsp;4.&nbsp;指定した表示間隔とタイマーの現在値を比較して、文字を１文字ずつ出力する。 <br>

<details>
	<summary>3.1 サンプルコード</summary><div>	
	
		wchar_t m_text_stock[256] = L"";	// 予備テキスト
		float m_sendText_Interval = 0;		// テキスト送りのインターバルフレーム(間隔)
		float m_sendText_Timer = 0;		// テキスト送りタイマー
		bool m_sendFlag = false;		// メッセージ送り処理のフラグ
		int m_sendText_Len = 0;			// 予備テキストの文字数
		int m_sendText_NowLen = 0;		// 現在の文字数
		
	
		// 1. 表示するテキストを指定する。
		void FontRender::SetSendText(const wchar_t* text, const float& Interval) 
		{
			// 2. 予備テキストの文字数に設定したテキストの文字数を格納。
			m_sendText_Len = (int)wcslen(text);	// 文字数を取得
			// 文字数分for文を回す。
			for (int n = 0; n < m_sendText_Len + 1; n++) {
				// 予備テキスト内に指定したテキストの中身を代入する。
				m_text_stock[n] = text[n];
			}

			// 設定
			// クラス内の変数に引数の Interval を代入する。
			m_sendText_Interval = Interval;
			// タイマーをリセット
			m_sendText_Timer = 0;
			// メッセージ送りフラグを true にして出力できるようにする。
			m_sendFlag = true;
			// 0 の時点で中身を出力してしまうので -1 で出力しないようにする。
			m_sendText_NowLen = -1;
		}
		
		// 3. 指定したテキストを表示する。
		bool FontRender::SendTextUpdate(const float addTime) 
		{
			// メッセージ送りフラグが true なら更新処理を行う。
			if (m_sendText == true) {
				// 4. 指定した表示間隔とタイマーの現在値を比較して、文字を１文字ずつ出力する。
				// fpsをタイマーに加算する
				m_sendText_Timer += addTime;
				// テキストを表示する間隔がタイマーの数値以下のとき
				if (m_sendText_Interval <= m_sendText_Timer) {
	
					// NowLenの値を +1 し、次の文字を表示する。
					m_sendText_NowLen++;

					// 移植
					// 現在のNowLen +1 回分for文を回す。
					for (int n = 0; n < m_textSend_NowLen + 1; n++) {
						// 予備テキストを代入
						m_text[n] = m_text_stock[n];
					}	

					// 後始末
					// タイマーをリセット。
					m_sendText_Timer = 0.0f;
					// 現在の文字数が予備テキストの文字数以上の時
					if (m_sendText_NowLen >= m_sendText_Len) {
						m_sendFlag = false;		// 終了
					}
	
					// true を返す。
					return true;
				}

				// テキストを表示する間隔がタイマーの数値以上のとき
				// false を返す。
				return false;
			}
		}
		
</div></details>

◆◇ **3.2 移動、当たり判定の処理** ◇◆<br>

![図3.2.1](https://user-images.githubusercontent.com/122655553/214481415-3d17fbd6-6223-49a2-8259-47cd7706783a.png "チュートリアルの盤面を上から見たスクリーンショット")

&emsp;本作品の移動処理、当たり判定の処理は配列を用いて <br>
&emsp;プレイヤーキャラクター、エネミー問わず同じ処理を行っています。 <br>

&emsp;それぞれがステージのマス数分の二次元配列を有しており、 <br>
&emsp;そのステージ上での自身の現在の位置（1）を情報として持っています。 <br>

&emsp;例えば上記の画像とき、プレイヤーキャラクター（中央下）は、 <br>

|行/列|0|1|2|3|4|
|---|---|---|---|---|---|
|0|0|0|0|0|0|0|
|1|0|0|0|0|0|0|
|2|0|0|0|0|0|0|
|3|0|0|0|0|0|0|
|4|0|0|1|0|0|0|

&emsp;という情報を持っていることになります。 <br>
&emsp;この配列を基にして、移動した後の座標を決定し、当たり判定を作成しています。 <br>

&emsp;配列の情報を切り替える処理としては以下の流れになります。 <br>
&emsp;1.&nbsp;オブジェクトが移動。 <br>
&emsp;2.&nbsp;移動した方向に配列の中身に 1 を代入する。 <br>
&emsp;3.&nbsp;移動したので元々入っていた配列の中身を0にする。 <br>

<details>
	<summary>3.2 サンプルコード</summary><div>	
	
		float moveSpeed = 50.0f;	// 移動速度

		// 1. オブジェクトが移動。
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			// 現在の2D座標（二次元配列）を代入する
			Vector2 move = position2D;
			// move を移動した後の値にする。
			move.y -= 1.0f;			

			// 動こうとした方向（今回は上方向）に動けるとき。
			if (IsMove(move) == true) {
				// 
				position.z += moveSpeed;
				// ステージのマス数分for文を回す。
				for (int i = 0; i < num->stageNum; i++) {
					for (int j = 0; j < num->stageNum; j++) {
						// 2. 移動した方向の配列の中身に 1 を代入する。
						// 現在の座標を見つけたとき
						if (position_stage[i][j] == 1) {

							// 3. 移動したので元々入っていた配列の中身を0にする。
							position_stage[i][j] = 0;
							// 移動する方向に 1 を代入する。
							position_stage[i - 1][j] = 1;
							// 2D座標（二次元配列）の値を移動後の値にする。
							position2D.y -= 1.0f;

							return;
						}
					}
				}
			}
		}
			
	
</div></details>

◆◇ **3.3 ステージのランダム生成** ◇◆<br>

![図3.3.1](https://user-images.githubusercontent.com/122655553/213916571-711b4e4a-fc53-4196-a1e8-3bcf3321fce4.png "一層目のステージ") <br>
![図3.3.2](https://user-images.githubusercontent.com/122655553/213916575-b57d40c3-cce9-426e-afe2-b2bc35a053a9.png "2層目のステージ") <br>

&emsp;本作品のステージは、一部を除き、9×9のマスで構成されています。 <br><br>
&emsp;マスと前述しました通り、ステージのモデルは一つに見えますが、 <br>
&emsp;内部的には全く別のオブジェクトで構成されています。 <br><br>
&emsp;[8][8]の二次元配列としてステージの情報を渡し、その情報を元にして、 <br>
&emsp;対応するモデルを読み込むことでステージを組み立てています。 <br><br>
![図3.3.3](https://user-images.githubusercontent.com/122655553/213916588-924eff1b-a985-4ad6-9d30-c6653c6fba5d.png "実際に使用したステージのモデル") <br>
&emsp;そのようにしてステージを作成しているため、 <br>

&emsp;1.&nbsp;あらかじめいくつかのステージを作成。 <br>
&emsp;2.&nbsp;プログラムコード内で乱数を出し、Switch文で振り分ける。 <br>
&emsp;3.&nbsp;対応するステージの情報に差し替えて出力する。 <br>
&emsp;・・・という形でランダム生成を行っています。
<details>
	<summary>3.3 サンプルコード</summary><div>	
	
			int stageNum = 2;			// 2次元配列の行と列の値。

			// 1. あらかじめいくつかのステージを作成。
			// 元々のステージのデータ。
			// 本作では配列内に格納している値でテクスチャを指定しています。
			int stage[2][2] = {
			{ 0,0 },
			{ 0,0 },
			};

			// 帰ってきた値が 0 の時このデータを代入する。
			int stage_0[2][2] = {
			{ 0,1 },
			{ 1,0 },
			};

			// 帰ってきた値が 1 の時このデータを代入する。
			int stage_1[2][2] = {
			{ 1,1 },
			{ 1,1 },
			};

			int stageState = rand() % 2;		// 0~1 でランダムな値を返す。			

			// 2. プログラムコード内で乱数を出し、Switch文で振り分けるnい
			// ステージ情報を代入する。
			switch (stageState) {
			case 0:
				// 3. 対応するステージの情報に差し替えて出力する。
				for (int j = 0; j < stageNum; j++) {
					for (int i = 0; i < stageNum; i++) {
						stage[j][i] = stage_0[j][i];
					}
				}
				break;
			case 1:
				// 3. 対応するステージの情報に差し替えて出力する。
				for (int j = 0; j < stageNum; j++) {
					for (int i = 0; i < stageNum; i++) {
						stage[j][i] = stage_1[j][i];
					}
				}

				break;
			}
	
</div></details>

&emsp;この後は格納されている値を見て、テクスチャを決定する処理を行っています。 <br><br>
&emsp;ゲーム内ではステージのランダム生成の仕様に合わせ、場合に応じたテクスチャとBGMを適応させています。 <br>
&emsp;詳しくは [4.こだわりポイント]の "**4.2 ステージのテクスチャ**" にて詳しく触れています。 <br>

## 4.こだわりポイント

◆◇ **4.1 誰にでも伝わるようなUI** ◇◆<br>

![図4.1.1](https://user-images.githubusercontent.com/122655553/213916423-6576f885-0525-4e8d-9da6-fdbf708e1026.png "ゲーム内で使用したUI一覧") <br>

&emsp;似通った色、フォントを使用することで、全体で統一感を持たせました。 <br><br>
&emsp;また、作品を通して柔らかなイメージを持たせるために、 <br>
&emsp;殆どのUIを丸みのあるデザインにしています。 <br><br>
&emsp;ゲーム本編にて画面に表示されているアイコンは、 <br>
&emsp;できる限り文字を使用せず、直感的に伝わるデザインを施しました。 <br>

![図4.1.2](https://user-images.githubusercontent.com/122655553/213916498-632df5ec-2178-495d-ab86-fc4e8d457401.png "ゲーム内で使用したアイテムのゲージ")
![図4.1.3](https://user-images.githubusercontent.com/122655553/213916501-5eb41197-cb4c-4b68-b0d7-60199b983daa.png "ゲーム内で登場するアイテム") <br>

&emsp;それ以外にも、関連性を紐づけしやすくなるよう同じ色を使用する、<br>
&emsp;体力は赤、アイテムは青…など、イメージしやすい色を使用する、などの工夫も行いました。<br>

◆◇ **4.2 ステージのテクスチャ** ◇◆

![図4.2.1](https://user-images.githubusercontent.com/122655553/213963486-bad5e8da-445b-4671-9359-ae5cc04ddacb.png "1層目のスクリーンショット")
![図4.3.2](https://user-images.githubusercontent.com/122655553/213963495-45c104d4-72b3-4769-885f-b0bd7c0a3ad4.png "10層目のスクリーンショット") <br>

&emsp;本作品ではゴールする（奥の赤いマスにたどり着く）度に、右上の階層数が1つずつ加算されていきます。 <br>
&emsp;より階層を進んでいるように感じられるよう、階層数が「5層」増えるごとにステージのテクスチャが変更されるようにしています。 <br>

![図4.2.3](https://user-images.githubusercontent.com/122655553/213963507-7cb18f85-abfc-4faa-87f7-a48615e09cbb.png "学校内製エンジンを使用したテクスチャ①")
![図4.2.4](https://user-images.githubusercontent.com/122655553/213963512-e9ebb04e-fdd8-4fad-94da-82bc02298760.png "学校内製エンジンを使用したテクスチャ②") <br>

&emsp;ステージそのもののテクスチャの他にも、背景や環境光なども変更しています。 <br><br>
&emsp;特に後者のスクリーンショット（テクスチャ②）ではステージのイメージが「洞窟」ということで、 <br>
&emsp;" 探索している "というイメージを損なわないために、 <br>
&emsp;また、プレイヤーが操作キャラクターを見失わないようにポイントライトを使用しています。 <br>

[1.作品概要]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#1%E4%BD%9C%E5%93%81%E6%A6%82%E8%A6%81
[2.操作説明]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#2%E6%93%8D%E4%BD%9C%E8%AA%AC%E6%98%8E
[3.技術説明]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#3%E6%8A%80%E8%A1%93%E8%AA%AC%E6%98%8E
[4.こだわりポイント]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#4%E3%81%93%E3%81%A0%E3%82%8F%E3%82%8A%E3%83%9D%E3%82%A4%E3%83%B3%E3%83%88
