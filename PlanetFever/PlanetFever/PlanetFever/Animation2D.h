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
	int m_id;			// リソース
	int m_animeNum;		// アニメーションコマ数
	int m_animeType;	// リソース内のどれを再生するか->こんな感じ	〇〇○○
	//											△△△△△△ <-これを再生したかったら1を代入
	//											□□
	int m_prevAnimeType;// 直前のアニメーションのタイプ
	int m_tiles;		// アニメーションのコマ数
	int m_speed;		// アニメーション速度
	int m_timeFrame;	// 経過時間（フレーム単位）
	Vector2 m_glidSize;	// 一コマの大きさ
	bool m_loopFlag;	// ループするか	

protected:

public:
	 void Load();
	 void Release();
	 void Update();
	 void Draw(const Transform2D& transform, Layer layer) const;
	 void LateDraw(const Transform2D& transform, Layer layer) const;

	Animation2D(
		const char* handle,
		int tiles = 1,
		int speed = 0,
		bool loopFlag = true);

	//Animation2D(
	//	const char* handle
	//);

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

};
