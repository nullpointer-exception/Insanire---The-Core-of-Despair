/*
	Beatrice Römer
	Oliver Aiberspach
*/

#include "Ranged.h"
#include "Helper.h"
#include "Rect.h"
#include "Physics.h"
#include "RangedWeapon.h"
#include "Texture.h"
#include "Animation.h"
#include "Vector2.h"
#include "Renderer.h"
#include <cstdlib>

Ranged::Ranged(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, const char * _phealthBarFileName)
	: Actor(_pRenderer, _pFileName, _pRect)
{
	m_pHealthBar = new TexturedEntity(_pRenderer, _phealthBarFileName, new Rect(64, 8));

	// set tag
	m_pTag = "Ranged";

	// create distance check rect
	m_pDistanceRect = new Rect(704, 704);

	// create new idle animation
	m_pIdle = new Animation(0, 0, 253, 216, 20);

	// set idle animation speed
	m_pIdle->SetAnimationSpeed(1.0f);

	// create new walk animation
	m_pWalk = new Animation(0, 216, 258, 220, 20);

	// set walk animation speed
	m_pWalk->SetAnimationSpeed(1.0f);

	// create new attack animation
	m_pAttack = new Animation(0, 436, 255, 215, 3);

	// set attack animation speed
	m_pAttack->SetAnimationSpeed(0.3f);

	// create sound
	//m_pShotSound = new Sound(nullptr);
}

Ranged::~Ranged()
{
	delete m_pHealthBar;

	// delete animations
	delete m_pIdle;
	delete m_pWalk;
	delete m_pAttack;
}	

void Ranged::Update(float _deltaTime)
{
	// decrease time
	m_timeState -= _deltaTime;

	// switch states
	switch (m_state)
	{

		// idle
	case ERangedState::IDLE:
		if (m_timeState < 0)
			ChangeState();
		break;

		// walk
	case ERangedState::WALK:
		m_xMovement = m_directionX;
		m_yMovement = m_directionY;
		if (m_timeState < 0)
			ChangeState();
		break;

		// attack
	case ERangedState::ATTACK:
		m_xMovement = m_directionX;
		m_yMovement = m_directionY;

		// if attack animation is over set idle
		if (m_pCurrentAnimation && m_pCurrentAnimation == m_pAttack)
		{
			if (m_pCurrentAnimation->GetAnimationPercentage() >= 100.0f)
				m_pCurrentAnimation = m_pIdle;
		}

		if (m_timeState <= 0)
		{
			// set current state to attack
			m_pCurrentAnimation = m_pAttack;

			// set time time
			m_timeState = 0.5f;

			// create new bullet with no texture!!!
			RangedWeapon* bullet = new RangedWeapon(nullptr, nullptr,
				new Rect(m_pRect->x + m_directionX * 70, m_pRect->y + m_directionY * 70,
					16, 16), m_directionX, m_directionY);

			// set bullet texture
			bullet->GetTexture()->SetSDLTexture(m_pPlayer->GetBulletTexture()->GetSDLTexture());

			// add bullet to move entities list
			m_pPlayer->GetCurrentScene()->AddMoveEntity(bullet);

			// play shot sound
			//m_pShotSound->Play();
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

	// update current animation
	if (m_pCurrentAnimation)
		m_pCurrentAnimation->Update(_deltaTime);
}

void Ranged::Render(Renderer * _pRenderer)
{
	// render health bar
	m_pHealthBar->Render(_pRenderer);

	// render with source rect
	if (m_pCurrentAnimation)
	{
		_pRenderer->RenderTexture(m_pTexture, m_pRect, &Rect(
			m_pCurrentAnimation->GetCurrentTexture().m_X,
			m_pCurrentAnimation->GetCurrentTexture().m_Y,
			m_pCurrentAnimation->GetWidth(), m_pCurrentAnimation->GetHeight()),
			m_angle, true);
	}

	// if no animation render parent
	else
	{
		Actor::Render(_pRenderer);
	}
}

void Ranged::CheckCollision(std::list<TexturedEntity*> _pEntities, float _deltaTime)
{
	// if not walking return
	if (m_state != ERangedState::WALK)
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

void Ranged::ChangeState()
{
	// set new time state
	m_timeState = 3.0f;

	// if idle set walk and random direction
	if (m_state == ERangedState::IDLE)
	{
		// set walk state
		m_state = ERangedState::WALK;
		m_directionX = rand() % 3 - 1;
		m_directionY = rand() % 3 - 1;

		// set current animation to walk
		m_pCurrentAnimation = m_pWalk;
	}

	// if walk set idle
	else
	{
		// set idle state
		m_state = ERangedState::IDLE;

		// set current animation to idle
		m_pCurrentAnimation = m_pIdle;
	}
}

void Ranged::CheckDistance()
{
	// set x and y of distance rect
	m_pDistanceRect->x = m_pRect->x - 320;
	m_pDistanceRect->y = m_pRect->y - 320;

	// if distance rect collides with player
	if (Physics::RectRectCollision(m_pDistanceRect, m_pPlayer->GetRect()))
	{
		// set state to attack
		m_state = ERangedState::ATTACK;

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
	else if (m_state == ERangedState::ATTACK)
	{
		// change state
		ChangeState();

		// set speed
		m_speed = 100;
	}
}