#pragma once
#include "DxLib.h"
#include "Vector2.h"
#include "Actor2D.h"
#include "Scroll.h"

class Transform2D;

class Animation2D
{
private:
	const char* m_handle;
	float m_animeTime;	// アニメーション経過時間
	int m_id;			// リソース
	int m_animeNum;		// アニメーションコマ数
	int m_animeType;	// リソース内のどれを再生するか->こんな感じ	〇〇○○
	//																△△△△△△ <-これを再生したかったら1を代入
	//																□□
	int m_prevAnimeType;// 直前のアニメーションのタイプ
	int m_tiles;		// アニメーションのコマ数
	int m_speed;		// アニメーション速度
	int m_timeFrame;	// 経過時間（フレーム単位）
	int m_brightness;	// 明るさ（255がデフォ、0が黒）
	Vector2 m_glidSize;	// 一コマの大きさ
	bool m_loopFlag;	// ループするか	
	bool m_isFlipX;		// 画像を反転させるか
	bool m_isLooped;	// ループしたか
	bool m_isDraw;		// 描画するか

	void MainDraw(const Transform2D& transform, Layer layer);

protected:

public:
	 void Load();
	 void Release();
	 void Update();
	 void Draw(const Transform2D& transform, Layer layer);
	 void LateDraw(const Transform2D& transform, Layer layer);

	Animation2D(
		const char* handle,
		int tiles = 1,
		int speed = 0,
		bool loopFlag = true);

	void SetAnimeType(int type)
	{
		m_animeType = type;
	}

	int GetAnimeType() const
	{
		return m_animeType;
	}

	void SetGlidSize(Vector2 glidSize)
	{
		m_glidSize = glidSize;
	}

	void SetBrightness(int brightness = 255)
	{
		m_brightness = brightness;
	}

	int GetSpeed() const
	{
		return m_speed;
	}

	void SetSpeed(int speed)
	{
		m_speed = speed;
	}

	int GetTiles() const
	{
		return m_tiles;
	}

	void SetTiles(int tiles)
	{
		m_tiles = tiles;
	}

	void SwitchLoop(bool loop)
	{
		m_loopFlag = loop;
	}

	void SwitchFlipX(bool flip)
	{
		m_isFlipX = flip;
	}

	bool GetIsLooped() const
	{
		return m_isLooped;
	}

	void SwitchDraw(bool draw)
	{
		m_isDraw = draw;
	}
};
