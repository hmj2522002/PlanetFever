#include "Button.h"
#include "Vector2.h"
#include "Input.h"

Button::Button(Actor2D* target, float rad, int mouse) :
	m_target(target),
	m_pressMouse(mouse),
	m_radius(rad),
	m_mouseDist(0),
	m_isPress(false),
	m_prevPress(false),
	m_isHolding(false),
	m_prevHold(false)
{

}

void Button::Update()
{
	// ƒ}ƒEƒX‚Æ‚Ì‹——£‚ðŽæ“¾
	m_transform = m_target->GetTransform();
	m_mouseDist = (m_transform.position - Mouse::GetPoint()).Magnitude();

	m_prevPress = m_isPress;
	m_isPress = IsCursorIn() && Mouse::IsPress(m_pressMouse);

	m_prevHold = m_isHolding;
	if (IsDown()) m_isHolding = true;
	if (IsUp()) m_isHolding = false;
}

bool Button::IsCursorIn()
{
	return m_mouseDist < m_radius * m_transform.scale;
}

bool Button::IsDown()
{
	return m_isPress && !m_prevPress;
}

bool Button::IsPress()
{
	return m_isPress && m_prevPress;
}

bool Button::IsUp()
{
	return !m_isPress && m_prevPress;
}

bool Button::IsDownToUp()
{
	return m_prevHold && IsUp();
}
