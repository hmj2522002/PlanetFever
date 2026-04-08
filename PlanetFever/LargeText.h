#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Screen.h"

class LargeText : public Node
{
public:
	enum class Text
	{
		ClickToStart,	// クリックしてください
		ClickThePlanet,	// 惑星をクリックしてスタート
		ClickToBack,	// クリックしてステージ選択画面に戻る
		DragToScroll,	// 画面をドラッグしてスクロールできます
		Result,			// リザルト
		Ready,			// よーい
		Start,			// スタート！
		Finish			// じかんぎれ！
	};

private:
	static constexpr float BlinkingSpeed = 1.0f;
	static constexpr Vector2 GlidSize = Vector2(866, 60);

	Text m_text;		// 描画テキスト
	Vector2 m_position;	// 描画位置
	bool m_isBlinking;	// 点滅するか
	int m_handle;		// 画像ID

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;

public:
	LargeText(Text text, Vector2 position = Screen::Center, bool blinking = false);

	void UIDraw();

	void ChangeText(Text text)
	{
		m_text = text;
	}
};
