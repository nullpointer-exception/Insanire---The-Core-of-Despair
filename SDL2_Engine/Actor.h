#pragma once
#include "TexturedEntity.h"

class Actor :
	public TexturedEntity
{
public:
	// constructor
	Actor(Renderer* _pRenderer, const char* _pFileName, 
		Rect* _pRect);

	// destructor
	~Actor();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// get speed
	inline int GetSpeed() { return m_speed; };

	// set speed
	inline void SetSpeed(int _speed) { m_speed = _speed; };

	// add movement
	void AddMovement(int _x, int _y);

protected:
	// movement x
	int m_xMovement;

	// movement y
	int m_yMovement;

	// speed
	int m_speed;

	// calculate angle
	void CalculateAngle();
};