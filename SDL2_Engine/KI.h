#pragma once
#include "Actor.h"
#include "Player.h"
#include "Scene.h"
#include <list>

class KI : public Actor
{
public:
	// constructor
	KI(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect,
		const char* _phealthBarFileName);

	// destructor
	~KI();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;
};