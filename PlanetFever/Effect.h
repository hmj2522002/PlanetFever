#pragma once
#include "Actor2D.h"

class Effect : public Actor2D
{
public:
	// エフェクトアニメーション
	enum class Anime
	{
		Air,	// 空気
		Glow,	// 光
		Meteor,	// 隕石の欠片

		Length
	};

private:
	static constexpr Vector2 GlidSize = Vector2(16, 16);
	static constexpr int LifeTimeFrame = 120;
	static constexpr int Radius = 10;

	int m_lifeTimeFrame;

	Anime m_effectType;

	class AnimeInfo
	{
	public:
		int tiles;
		int speed;
		bool loop;

		AnimeInfo(int _tiles = 1, int _speed = 0, bool _loop = false) :
			tiles(_tiles),
			speed(_speed),
			loop(_loop)
		{
		}
	};

	const AnimeInfo AnimeGlid[static_cast<int>(Anime::Length)]
	{
		AnimeInfo(5, 4),
		AnimeInfo(5, 4),
		AnimeInfo()
	};

protected:
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;


public:
	Effect(Transform2D transform, Anime anime, Vector2 dir = Vector2(), float power = 1.0f);
};
