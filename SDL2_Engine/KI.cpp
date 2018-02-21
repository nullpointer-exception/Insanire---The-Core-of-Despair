#include "KI.h"
#include "Helper.h"
#include "Rect.h"
#include "Physics.h"
#include "Bullet.h"
#include "Texture.h"
#include <cstdlib>

KI::KI(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, const char * _phealthBarFileName)
	: Actor(_pRenderer, _pFileName, _pRect)
{
	m_pHealthBar = new TexturedEntity(_pRenderer, _phealthBarFileName, new Rect(64, 8));

	// set tag
	m_pTag = "KI";

	// create distance check rect
	m_pDistanceRect = new Rect(704, 704);
}

KI::~KI()
{
	delete m_pHealthBar;
}

void KI::Update(float _deltaTime)
{
	// decrease time
	m_timeState -= _deltaTime;

	// switch states
	switch (m_state)
	{
	// attack
	case EKIState::ATTACK:
		m_xMovement = m_directionX;
		m_yMovement = m_directionY;

		if (m_timeState <= 0)
		{
			// set time time
			m_timeState = 0.5f;

			// create new bullet with no texture!!!
			Bullet* bullet = new Bullet(nullptr, nullptr,
				new Rect(m_pRect->x + m_directionX * 70, m_pRect->y + m_directionY * 70,
					16, 16), m_directionX, m_directionY);

			// set bullet texture
			bullet->GetTexture()->SetSDLTexture(m_pPlayer->GetBulletTexture()->GetSDLTexture());

			// add bullet to move entities list
			m_pPlayer->GetCurrentScene()->AddMoveEntity(bullet); 
		}
		break;
	default:
		break;
	}

	// update parent
	Actor::Update(_deltaTime);

	// get health bar rect
	Rect rect = *m_pHealthBar->GetRect();

	// set width rect
	rect.w = 64 * m_health / 100;

	// set x and y of rect
	rect.x = m_pRect->x;
	rect.y = m_pRect->y;

	// set rect of health bar
	m_pHealthBar->SetRect(&rect);

	// check distance to player
	CheckDistance();
}

void KI::Render(Renderer * _pRenderer)
{
	// render health bar
	m_pHealthBar->Render(_pRenderer);

	// render parent
	Actor::Render(_pRenderer);
}

void KI::CheckCollision(std::list<TexturedEntity*> _pEntities, float _deltaTime)
{
	// if not walking return
	if (m_state != EKIState::WALK)
		return;

	// next rect
	Rect nextRect = Rect(m_pRect->x, m_pRect->y, m_pRect->w, m_pRect->h);

	// increase location
	nextRect.x += m_directionX * m_speed * _deltaTime;
	nextRect.y += m_directionY * m_speed * _deltaTime;

	// if collision change state
	for each (TexturedEntity* entity in _pEntities)
	{
		if (entity == this)
			continue;

		if ((entity->GetColType() == ECollisionType::WALL ||
			entity->GetColType() == ECollisionType::MOVE) &&
			Physics::RectRectCollision(&nextRect, entity->GetRect()))
		{
			ChangeState();
		}
	}
}

void KI::ChangeState()
{
	// set new time state
	m_timeState = 3.0f;

	// if idle set walk and random direction
	if (m_state == EKIState::IDLE)
	{
		// set walk state
		m_state = EKIState::WALK;
		m_directionX = rand() % 3 - 1;
		m_directionY = rand() % 3 - 1;
	}

	// if walk set idle
	else
	{
		// set idle state
		m_state = EKIState::IDLE;
	}
}

void KI::CheckDistance()
{
	// set x and y of distance rect
	m_pDistanceRect->x = m_pRect->x - 320;
	m_pDistanceRect->y = m_pRect->y - 320;

	// if distance rect collides with player
	if (Physics::RectRectCollision(m_pDistanceRect, m_pPlayer->GetRect()))
	{
		// set state to attack
		m_state = EKIState::ATTACK;

		// set x direction
		if (m_pPlayer->GetRect()->x < m_pRect->x)
			m_directionX = -1;
		else if (m_pPlayer->GetRect()->x > m_pRect->x + 64)
			m_directionX = 1;
		else
			m_directionX = 0;

		// set y direction
		if (m_pPlayer->GetRect()->y < m_pRect->y)
			m_directionY = -1;
		else if (m_pPlayer->GetRect()->y > m_pRect->y + 64)
			m_directionY = 1;
		else
			m_directionY = 0;

		// set speed to 0
		m_speed = 0;
	}

	// if no collision and attack state is active
	else if (m_state == EKIState::ATTACK)
	{
		// change state
		ChangeState();

		// set speed
		m_speed = 100;
	}
}