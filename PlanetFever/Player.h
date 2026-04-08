#pragma once
#include "Actor2D.h"

class Player : public Actor2D
{
private:
	static constexpr Vector2 GlidSize = Vector2(40, 40);
	static constexpr float MaxJetPackSpeed = 6;
	static constexpr float JetPackBoost = 0.2f;
	static constexpr float StartWalkSpeed = 0.1f;	// 歩きアニメーションに切り替えるのに必要な速度
	static constexpr float DamageKnockBackPower = 15;
	static constexpr float MinEffectPower = 1.2f;
	static constexpr float MaxEffectPower = 2.8f;

	struct HitBox
	{
		static constexpr float Radius = 15;
		static constexpr Vector2 Offset = Vector2(0, 0);
	};

	// プレイヤーアニメーション
	enum class Anime
	{
		Stand,	// 直立
		Walk,	// 歩行
		Fly,	// 飛行
		Fall,	// 落下

		Length
	};

	class AnimeInfo
	{
	public:
		int tiles;
		int speed;
		bool loop;

		AnimeInfo(int _tiles = 1, int _speed = 0 , bool _loop = false) :
			tiles(_tiles),
			speed(_speed),
			loop(_loop)
		{}
	};

	const AnimeInfo AnimeGlid[static_cast<int>(Anime::Length)]
	{
		AnimeInfo(2, 2, true),
		AnimeInfo(4, 4, true),
		AnimeInfo(),
		AnimeInfo()
	};

	Vector2 m_mouseWorldPoint;
	float m_jetPackSpeed;
	float m_horizontalSpeed;
	int m_prevAnimType;
	int m_seFire;
	int m_seDamage;
	int m_seJet;
	bool m_isGrounded;
	bool m_prevGrounded;
	bool m_isJet;
	bool m_prevJet;

	void SetAnimeType(Anime type);

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;

public:
	Player(Vector2 pos);

};
