#pragma once
#include "Actor2D.h"

class Planet : public Actor2D
{
private:
	static constexpr Vector2 GlidSize = Vector2(250, 250);

	float m_radius;
	bool m_isHit;

protected:
	virtual void Load();
	virtual void Release();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;

public:
	Planet();
};
