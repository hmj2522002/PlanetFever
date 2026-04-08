#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Screen.h"

class SmallText : public Node
{
public:
	enum class Text
	{
		Amount,			// あつめた数
		Ore,			// おたから
		Total,			// 合計
		FinalResult,	// 総合スコア
		Score,			// スコア
		NoOres,			// 何も回収しなかった
		NeedScore,		// 必要スコア
		New				// NEW!!
	};

private:
	static constexpr Vector2 GlidSize = Vector2(308, 32);

	Text m_text;		// 描画テキスト
	Vector2 m_position;	// 描画位置
	int m_handle;		// 画像ID

public:
	SmallText(Text text);

	void Release();
	void Draw(Vector2 position, float scale = 1.0f) const;

	void ChangeText(Text text)
	{
		m_text = text;
	}
};
