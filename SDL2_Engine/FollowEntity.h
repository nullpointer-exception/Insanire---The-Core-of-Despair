#pragma once
#include "Actor.h"

enum EDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class FollowEntity :
	public Actor
{
public:
	// constructor
	FollowEntity(Renderer* _pRenderer, 
		const char* _pFileName, Rect* _pRect);

	// set target reference
	inline void SetTargetActor(Actor* _pActor)
	{
		m_pTarget = _pActor;
	};

	// set offset
	inline void SetOffset(int _x, int _y)
	{
		m_xOffset = _x;
		m_yOffset = _y;

		if (_x >= -64 && _y == -64)
			m_dir = EAST;
		else if (_x == 64 && _y == -64)
			m_dir = SOUTH;
		else if (_x == 64 && _y == 64)
			m_dir = WEST;
		else
			m_dir = NORTH;
	}

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render frame frame
	virtual void Render(Renderer* _pRenderer) override;

private:
	// offset x
	int m_xOffset;

	// offset y
	int m_yOffset;

	// frames count
	int m_frames;

	// direction
	int m_dir = 0;

	// speed
	int m_speed = 8;

	// followed actor
	Actor* m_pTarget;
};