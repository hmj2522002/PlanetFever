#pragma once
#include "Actor2D.h"

class Bullet : public Actor2D
{
private:
	static constexpr int LifeTimeFrame = 90;	// 消滅するまでのコマ数
	static constexpr float Radius = 2.0f;
	static constexpr float Speed = 6.0f;
	static constexpr Vector2 GlidSize = Vector2(8, 8);

	int m_lifeTimeFrame;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;

public:
	enum class BulletType
	{
		Normal,	// 通常弾
		Charge	// チャージ弾
	};

	Bullet(Transform2D& transform, BulletType bulletType = BulletType::Normal);

};
