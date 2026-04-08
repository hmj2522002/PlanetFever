#include "Button.h"
#include "Vector2.h"
#include "Input.h"

Button::Button(Actor2D* target, float rad, int mouse) :
	m_target(target),
	m_pressMouse(mouse),
	m_radius(rad),
	m_mouseDist(0),
	m_isHolding(false)
{
	m_transform = m_target->GetTransform();
}

void Button::Update()
{
	// ƒ}ƒEƒX‚Æ‚Ì‹——£‚ğæ“¾
	m_mouseDist = (m_transform.position - Mouse::GetPoint()).Magnitude();
}

bool Button::IsCursorIn()
{
	return m_mouseDist < m_radius * m_transform.scale;
}

bool Button::IsDown()
{
	m_isHolding = IsCursorIn() && Mouse::IsDown(m_pressMouse);

	return m_isHolding;
}

bool Button::IsPress()
{
	if (!IsCursorIn()) m_isHolding = false;

	return IsCursorIn() && Mouse::IsPress(m_pressMouse);
}

bool Button::IsUp()
{
	return IsCursorIn() && Mouse::IsUp(m_pressMouse);
}

bool Button::IsDownToUp()
{
	return m_isHolding;
}
