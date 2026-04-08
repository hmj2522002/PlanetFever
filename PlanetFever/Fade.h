#pragma once

class Fade
{
private:
	static constexpr int Black = (0x000000);
	static constexpr int DurationTimeFrame = 30;	// 必要フェード時間（フレーム単位）

	bool m_isFade;				// フェード中か
	int m_height;
	int m_elapsedTimeFrame;		// 経過時間Ｆ
	int m_durationTimeFrame;	// フェード時間Ｆ
	int m_beginHeight;			// 開始時の縦幅
	int m_endHeight;			// 終了時の縦幅
	int m_fadeColor;

	Fade();

public:
	// シングルトン
	static Fade* GetInstance()
	{
		static Fade instance;
		return &instance;
	}

	void Update();

	// フェードイン
	void StartFadeIn(int color = Black);

	// フェードアウト
	void StartFadeOut(int color = Black);

	// フェード中か
	bool IsFade() const { return m_isFade; }
};
