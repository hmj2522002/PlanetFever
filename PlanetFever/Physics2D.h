#pragma once
#include "Math.h"
#include "Screen.h"
#include <list>
#include <unordered_map>
#include <unordered_set>

class Actor2D;

// Actor2D同士の衝突判定
class Physics2D
{
private:
	static constexpr float Gravity = 0.1f;
	static constexpr float LimitSpeedFall = 2.0f;
	static constexpr float LimitHorizontalSpeed = 3.0f;
	static constexpr int LimitDistance =
		((std::max)(Screen::Width, Screen::Height) / 2) *
		((std::max)(Screen::Width, Screen::Height) / 2);

	struct Pair
	{
		Actor2D* actor1;
		Actor2D* actor2;

		Pair(Actor2D* actor1, Actor2D* actor2) :
			actor1(actor1),
			actor2(actor2) { }
	};

	Vector2 m_gravityPoint;		// 重力点
	bool m_isActive;			// 稼働フラグ

	std::list<Actor2D*> m_actorList;	// 衝突判定をするActorのリスト
	std::unordered_map<Actor2D*, std::unordered_set<Actor2D*>>
		m_prevCallbackList;	// 前回の衝突判定で衝突していた組み合わせ

	Physics2D() :
		m_gravityPoint(Screen::Center),
		m_isActive(false)
	{}

public:
	static Physics2D* GetInstance()
	{
		static Physics2D instance;
		return &instance;
	}

	// 物理演算を稼働
	void Active() { m_isActive = true; }

	// 物理演算を停止
	void Deactive() { m_isActive = false; }

	// Actor2Dを登録
	void Register(Actor2D* actor) { m_actorList.push_back(actor); }

	// Actor2Dを除外
	void Remove(Actor2D* actor) { m_actorList.remove(actor); }

	void Update();

	void SetGravityPoint(Vector2& point) { m_gravityPoint = point; }

	Vector2 GetGravityPoint() const { return m_gravityPoint; }
};
