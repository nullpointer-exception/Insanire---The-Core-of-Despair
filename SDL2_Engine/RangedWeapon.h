#pragma once
#include "Actor.h"

class RangedWeapon : public Actor
{
public:
	// constructor
	RangedWeapon(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect,
		int _xDirection, int _yDirection);

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

private:
	// direction x
	int m_xDirection;

	// direction y
	int m_yDirection;
};