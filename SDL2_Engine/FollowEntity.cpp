#include "FollowEntity.h"
#include "Rect.h"
#include <cstdlib>

FollowEntity::FollowEntity(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect)
	: Actor(_pRenderer, _pFileName, _pRect)
{

}

void FollowEntity::Update(float _deltaTime)
{
	// return here for better visual
	if (!m_pTarget)
		return;

	switch (m_dir)
	{
	case NORTH:
		m_yOffset -= m_speed;
		if (m_yOffset <= -64)
		{
			m_yOffset = -64;
			m_dir = EAST;
		}
		break;
	case EAST:
		m_xOffset += m_speed;
		if (m_xOffset >= 64)
		{
			m_xOffset = 64;
			m_dir = SOUTH;
		}
		break;
	case WEST:
		m_xOffset -= m_speed;
		if (m_xOffset <= -64)
		{
			m_xOffset = -64;
			m_dir = NORTH;
		}
		break;
	case SOUTH:
		m_yOffset += m_speed;
		if (m_yOffset >= 64)
		{
			m_yOffset = 64;
			m_dir = WEST;
		}
		break;
	}

	// set rect x and y from target rect + offset
	m_pRect->x = m_pTarget->GetRect()->x + m_xOffset;
	m_pRect->y = m_pTarget->GetRect()->y + m_yOffset;

	// increase frames
	/*m_frames++;

	if (m_frames < 30)
		return;

	m_frames = 0;

	// random value from 0 to 9
	//m_pRect->x += rand() % 10;

	// random value from -4 to 5
	m_pRect->x += rand() % 10 - 5;*/
}

void FollowEntity::Render(Renderer * _pRenderer)
{
	Actor::Render(_pRenderer);
}