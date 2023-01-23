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
&emsp;十字キー	   …	キャラクターの移動 <br>
&emsp;Lスティック	…	カメラの移動 <br>
&emsp;Xボタン		   …	カメラの上下切り替え <br>
&emsp;Aボタン		   …	次のテキストを表示(会話時のみ有効) <br>
&emsp;Bボタン	   	…	攻撃 <br>
&emsp;STARTボタン	…	ヒントを聞く <br>

[システム操作 (タイトル、操作説明など)] <br>
&emsp;十字キー	   …	ページ、選択項目の切り替え <br>
&emsp;Aボタン	   	…	決定 <br>
&emsp;Bボタン	   	…	キャンセル <br>

## 3.技術説明

◆◇ **3.1 会話するNPC** ◇◆<br>

◆◇ **3.2 エネミーの移動処理** ◇◆<br>

◆◇ **3.2 ステージのランダム生成** ◇◆<br>

![図3.2.1](https://user-images.githubusercontent.com/122655553/213916571-711b4e4a-fc53-4196-a1e8-3bcf3321fce4.png "一層目のステージ") <br>
![図3.2.2](https://user-images.githubusercontent.com/122655553/213916575-b57d40c3-cce9-426e-afe2-b2bc35a053a9.png "2層目のステージ") <br>
&emsp;本作品のステージは、一部を除き、9×9のマスで構成されています。 <br><br>
&emsp;マスと前述しました通り、ステージのモデルは一つに見えますが、 <br>
&emsp;内部的には全く別のオブジェクトで構成されています。 <br><br>
&emsp;[8][8]の二次元配列としてステージの情報を渡し、その情報を元にして、 <br>
&emsp;対応するモデルを読み込むことでステージを組み立てています。 <br><br>
![図3.2.3](https://user-images.githubusercontent.com/122655553/213916588-924eff1b-a985-4ad6-9d30-c6653c6fba5d.png "実際に使用したステージのモデル") <br>
&emsp;そのようにしてステージを作成しているため、 <br>

&emsp;1.&nbsp;あらかじめいくつかのステージを作成。 <br>
&emsp;2.&nbsp;プログラムコード内で乱数を出し、Switch文で振り分ける。 <br>
&emsp;3.&nbsp;対応するステージの情報に差し替えて出力する。 <br>
&emsp;・・・という形でランダム生成を行っています。
<details>
	<summary>サンプルコード</summary><div>	
	
	
		```
			int stageNum = 2;			// 2次元配列の行と列の値。

			// 1.あらかじめいくつかのステージを作成。
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

			// 2.プログラムコード内で乱数を出し、Switch文で振り分ける。
			// ステージ情報を代入する。
			switch (stageState) {
			case 0:
				// 3.対応するステージの情報に差し替えて出力する。
				for (int j = 0; j < stageNum; j++) {
					for (int i = 0; i < stageNum; i++) {
						stage[j][i] = stage_0[j][i];
					}
				}
				break;
			case 1:
				// 3.対応するステージの情報に差し替えて出力する。
				for (int j = 0; j < stageNum; j++) {
					for (int i = 0; i < stageNum; i++) {
						stage[j][i] = stage_1[j][i];
					}
				}

				break;
			}
	
		```
	
</div></details>

&emsp;この後は格納されている値を見て、テクスチャを決定する処理を行っています。 <br><br>
&emsp;ゲーム内ではステージのランダム生成の仕様に合わせ、場合に応じたテクスチャとBGMを適応させています。 <br>
&emsp;詳しくは [4.こだわりポイント]の "**4.3 ステージのテクスチャ**" にて詳しく触れています。 <br>

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

◆◇ **4.3 ステージのテクスチャ** ◇◆
![図4.3.1](https://user-images.githubusercontent.com/122655553/213963486-bad5e8da-445b-4671-9359-ae5cc04ddacb.png "1層目のスクリーンショット")
![図4.3.2](https://user-images.githubusercontent.com/122655553/213963495-45c104d4-72b3-4769-885f-b0bd7c0a3ad4.png "10層目のスクリーンショット") <br><br>
&emsp;本作品ではゴールする（奥の赤いマスにたどり着く）度に、右上の階層数が1つずつ加算されていきます。 <br>
&emsp;より階層を進んでいるように感じられるよう、階層数が「5層」増えるごとにステージのテクスチャが変更されるようにしています。 <br>
![図4.3.3](https://user-images.githubusercontent.com/122655553/213963507-7cb18f85-abfc-4faa-87f7-a48615e09cbb.png "学校内製エンジンを使用したテクスチャ①")
![図4.3.4](https://user-images.githubusercontent.com/122655553/213963512-e9ebb04e-fdd8-4fad-94da-82bc02298760.png "学校内製エンジンを使用したテクスチャ②") <br><br>
&emsp;ステージそのもののテクスチャの他にも、背景や環境光なども変更しています。 <br><br>
&emsp;特にテクスチャ②ではステージのイメージが「洞窟」ということで、" 探索している "というイメージを損なわないために、 <br>
&emsp;また、プレイヤーが操作キャラクターを見失わないようにポイントライトを使用しています。 <br>

[1.作品概要]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#1%E4%BD%9C%E5%93%81%E6%A6%82%E8%A6%81
[2.操作説明]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#2%E6%93%8D%E4%BD%9C%E8%AA%AC%E6%98%8E
[3.技術説明]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#3%E6%8A%80%E8%A1%93%E8%AA%AC%E6%98%8E
[4.こだわりポイント]:https://github.com/nom0531/WonderLabyrinth/blob/main/README.md#4%E3%81%93%E3%81%A0%E3%82%8F%E3%82%8A%E3%83%9D%E3%82%A4%E3%83%B3%E3%83%88
