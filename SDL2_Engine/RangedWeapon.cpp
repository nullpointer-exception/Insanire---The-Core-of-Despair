#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, int _xDirection, int _yDirection)
	: Actor(_pRenderer, _pFileName, _pRect)
{
	// set directions
	m_xDirection = _xDirection;
	m_yDirection = _yDirection;

	// set speed
	m_speed = 500;

	// set collision Type
	m_colType = ECollisionType::BULLET;

	// calculate angle
	CalculateAngle();
}

void RangedWeapon::Update(float _deltaTime)
{
	// update movement
	m_xMovement = m_xDirection;
	m_yMovement = m_yDirection;

	// update parent class
	Actor::Update(_deltaTime);
}

void RangedWeapon::Render(Renderer * _pRenderer)
{
	// render parent class
	Actor::Render(_pRenderer);
}