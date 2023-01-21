#pragma once

#include "Graphics/IRenderer.h"

namespace nsK2Engine {
	/// <summary>
	/// フォントレンダ―。
	/// </summary>
	class FontRender : public IRenderer
	{
	public:
		static const int MAX_TEXT_SIZE = 256;
		~FontRender()
		{

		}
		/// <summary>
		/// 表示する文字を設定。
		/// </summary>
		/// <param name="text">表示する文字。</param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}
		/// <summary>
		/// 表示する文字を取得。
		/// </summary>
		/// <returns>表示する文字。</returns>
		const wchar_t* GetText() const
		{
			return m_text;
		}
		/// <summary>
		/// 座標を設定。zは0.0fで。
		/// </summary>
		/// <param name="position">座標。</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// 大きさを設定。zは0.0fで。
		/// </summary>
		/// <param name="position">座標。</param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// 座標を取得。
		/// </summary>
		/// <returns>座標。</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// 大きさを設定。
		/// </summary>
		/// <param name="scale">大きさ。</param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// 大きさを取得。
		/// </summary>
		/// <returns>大きさ。</returns>
		const float GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// 色を設定。
		/// </summary>
		/// <param name="color">色。</param>
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r, g, b, a });
		}
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// 色を取得。
		/// </summary>
		/// <returns>色。</returns>
		const Vector4& GetColor() const
		{
			return m_color;
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rotation">回転。</param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// 回転を取得。
		/// </summary>
		/// <returns>回転。</returns>
		const float GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// ピボットを設定。
		/// </summary>
		/// <remark>
		/// <param name="pivot">
		/// ピボット。
		/// x = 0.5, y = 0.5で画像の中心が基点。
		/// x = 0.0, y = 0.0で画像の左下。
		/// x = 1.0, y = 1.0で画像の右上。
		/// UnityのuGUIに準拠。
		/// </param>
		/// </remark>
		/// <param name="x">ピボットのx座標</param>
		/// <param name="y">ピボットのy座標</param>
		void SetPivot(float x, float y)
		{
			SetPivot({ x, y });
		}
		/// <summary>
		/// ピボットを設定。
		/// </summary>
		/// <param name="pivot">
		/// ピボット。
		/// x = 0.5, y = 0.5で画像の中心が基点。
		/// x = 0.0, y = 0.0で画像の左下。
		/// x = 1.0, y = 1.0で画像の右上。
		/// UnityのuGUIに準拠。
		/// </param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// ピボットを取得。
		/// </summary>
		/// <returns>ピボット。</returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}
		/// <summary>
		/// 描画処理。
		/// </summary>
		/// <param name="rc">レンダ―コンテキスト。</param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// 影のパラメータを設定。
		/// </summary>
		/// <param name="isDrawShadow">影を描画する？</param>
		/// <param name="shadowOffset">影を描画するときのピクセルのオフセット量。</param>
		/// <param name="shadowColor">影の色。</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}

		/// <summary>
		/// テキスト送り演出
		/// SetTextの代わりに呼んでください
		/// </summary>
		/// <param name="text">表示するテキスト</param>
		/// <param name="Interval">1文字ごとのインターバル</param>
		/// <param name="TextOkuriSE_Flag">文字送りの効果音を再生するかどうか</param>
		void SetTextOkuri(const wchar_t* text, const float& Interval, const bool& TextOkuriSE_Flag = true);
		/// <summary>
		/// テキスト送りをする場合Updateから呼んでね☆
		/// 
		/// あえて呼び出しを止めることで一時的にメッセージ送りを止めることも可能
		/// </summary>
		/// <param name="addTime"> g_gameTime->GetFrameDeltaTime()を入れてください！ </param>
		/// <returns>このフレームで文字更新したかどうか trueなら更新した</returns>
		bool TextOkuriUpdate(const float addTime);

		/// <summary>
		/// メッセージ送り中ならtrueを返す
		/// </summary>
		const bool GetMessageOkuriFlag() {
			return m_okuriFlag;
		}
		/// <summary>
		/// 現在何文字目まで表示しているかを返す
		/// </summary>
		const int GetNowLen() {
			return m_textOkuri_NowLen;
		}
		
	private:
		/// <summary>
		/// 2D描画パスから呼ばれる処理。
		/// </summary>
		/// <param name="rc"></param>
		void OnRender2D(RenderContext& rc) override
		{

			m_font.Begin(rc);
			m_font.Draw(m_text, Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
			m_font.End(rc);
		}
	private:
		Vector3							m_position = Vector3::Zero;			//座標。	
		float							m_scale = 1.0f;						//文字の大きさ。
		Vector4							m_color = g_vec4White;				//文字の色、デフォルトで白。
		float							m_rotation = 0.0f;					//回転。
		Vector2							m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット。
		wchar_t							m_text[MAX_TEXT_SIZE];				//文字。
		Font							m_font;								//フォント。

		//だんだん表示システム
		wchar_t m_text_stock[256] = L"";			// 予備テキスト
		float m_textOkuri_Interval = 0;				// テキスト送りのインターバルフレーム
		float m_textOkuri_Timer = 0;				// テキスト送りタイマー
		bool m_okuriFlag = false;					// メッセージ送り処理のフラグ
		int m_textOkuri_Len = 0;					// 予備テキストの文字数
		int m_textOkuri_NowLen = 0;					// 現在の文字数

		bool m_textOkuriSE = false;					// テキスト送り中にSEを鳴らす？
		const int TEXT_SE_NUMBER = 26;				// テキスト送り音の登録番号

		SoundSource* se[10];
		int seNum = 0;
		const int SE_MAX = 9;
	};
}
