#pragma once
#include "Actor2D.h"

class Player : public Actor2D
{
private:
	static constexpr Vector2 GlidSize = Vector2(40, 40);
	static constexpr float MaxJetPackSpeed = 6;
	static constexpr float JetPackBoost = 0.2f;
	
	struct HitBox
	{
		static constexpr float Radius = 15;
		static constexpr Vector2 Offset = Vector2(0, 0);
	};

	bool m_isGrounded;
	Vector2 m_mouseWorldPoint;
	float m_jetPackSpeed;

protected:
	virtual void Load();
	virtual void Release();
	virtual void Update();
	virtual void Draw();

public:
	Player();

	virtual void OnCollisionEnter(const Actor2D* other) override;
//	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;

};
