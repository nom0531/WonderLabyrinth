#include "k2EnginePreCompile.h"
#include "FontRender.h"
#include "RenderingEngine.h"

namespace nsK2Engine {
	void FontRender::Draw(RenderContext& rc)
	{
		if (m_text == nullptr)
		{
			return;
		}
		g_renderingEngine->AddRenderObject(this);
	}

	bool FontRender::TextOkuriUpdate(const float addTime) 
	{
		// メッセージ送りフラグがtrueなら更新処理を行う
		if (m_okuriFlag == true) {

			m_textOkuri_Timer += addTime;
			if (m_textOkuri_Interval <= m_textOkuri_Timer) {

				// レッツ更新！
				m_textOkuri_NowLen++;

				// 移植
				for (int n = 0; n < m_textOkuri_NowLen + 1; n++) {
					m_text[n] = m_text_stock[n];
				}

				// 効果音再生（ここで再生するのは本当は好ましくないけど）
				if (m_textOkuriSE) {

					if (se[seNum] != nullptr) {
						DeleteGO(se[seNum]);
					}

					se[seNum] = NewGO<SoundSource>(0);
					se[seNum]->Init(TEXT_SE_NUMBER);
					se[seNum]->SetVolume(1.5f);
					se[seNum]->Play(false);

					seNum++;
					if (seNum > SE_MAX) {
						seNum = 0;
					}
				}		

				// 後始末
				m_textOkuri_Timer = 0.0f;
				if (m_textOkuri_NowLen >= m_textOkuri_Len) {
					m_okuriFlag = false;		// 終了
				}

				return true;
			}

			return false;
		}

	}

	void FontRender::SetTextOkuri(const wchar_t* text, const float& Interval, const bool& TextOkuriSE_Flag) 
	{
		m_textOkuri_Len = (int)wcslen(text);	// 文字数を取得
		for (int n = 0; n < m_textOkuri_Len + 1; n++) {
			m_text_stock[n] = text[n];
		}

		// 設定
		m_textOkuri_Interval = Interval;
		m_textOkuri_Timer = 0;
		m_okuriFlag = true;
		m_textOkuri_NowLen = -1;
		m_textOkuriSE = TextOkuriSE_Flag;

		// テキスト送り音の登録
		if (m_textOkuriSE) {
			g_soundEngine->ResistWaveFileBank(TEXT_SE_NUMBER, "Assets/sound/CV_aru.wav");
		}
	}
}