#include "Player.h"
#include "Input.h"
#include "Rect.h"
#include "Physics.h"
#include "Scene.h"
#include "RangedWeapon.h"
#include "MeleeWeapon.h"
#include "Helper.h"
#include "Texture.h"
#include "Ranged.h"
#include "Melee.h"

Player::Player(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, 
	const char* _pFileHealthBar, const char* _pRunBar)
	: Actor(_pRenderer, _pFileName, _pRect)
{
	// create bullet texture
	m_pBulletTexture = new Texture(GetAssetPath("Texture/Bullet/T_Bullet.png", 5).c_str(),
		_pRenderer);

	// create health bar textured entity
	m_pHealthBar = new TexturedEntity(_pRenderer, _pFileHealthBar, new Rect(64, 8));

	// create run bar textured entity
	m_pRunBar = new TexturedEntity(_pRenderer, _pRunBar, new Rect(64, 8));

	// set tag
	m_pTag = "Player";
}

Player::~Player()
{
	delete m_pBulletTexture;
	delete m_pHealthBar;
	delete m_pRunBar;
}

void Player::Update(float _deltaTime)
{
	// reset hits
	m_playerHits = false;

	// if not moveable return
	if (!m_isMoveable)
		return;

	// rotate player to 0
	if (Input::GetKey(SDL_SCANCODE_D))
		m_xMovement += 1;


	// rotate player to 180
	if (Input::GetKey(SDL_SCANCODE_A))
		m_xMovement -= 1;


	if (Input::GetKeyDown(SDL_SCANCODE_SPACE)
		&&(!m_yMovement == 1))
		m_yMovement = -70;


	

	// if shift is pressed increase movement and decrease run time
	if (Input::GetKey(SDL_SCANCODE_F))
	{
		m_xrun -= 10 * _deltaTime;

		if (m_xrun > 0)
		{
			m_speed = 200;
		}
	}
	else
	{
		// increase run time
		m_xrun += 10 * _deltaTime;
		if (m_xrun > 100.0f)
			m_xrun = 100.0f;

		m_speed = 100;
	}

	// update rect
	Actor::Update(_deltaTime);

	// x direction
	int x = 0;

	// y direction
	int y = 0;

	// set x direction
	if (m_angle == 0 || m_angle == 45 || m_angle == 315)
		x = 1;
	else if (m_angle == 135 || m_angle == 180 || m_angle == 225)
		x = -1;

	// set y direction
	if (m_angle == 45 || m_angle == 90 || m_angle == 135)
		y = 1;
	else if (m_angle == 225 || m_angle == 270 || m_angle == 315)
		y = -1;

	// if space is pressed down spawn bullet
	if (Input::GetKeyDown(SDL_SCANCODE_E))
	{
		/* first create bullet than add to list
		Bullet* bullet = new Bullet(_pRenderer,
		GetAssetPath("Texture/Character/T_Character_Idle.png", 5).c_str(),
		new Rect(m_pRect->x + x * PLAYER_WIDTH_HEIGHT,
		m_pRect->y + y * PLAYER_WIDTH_HEIGHT, 16, 16), x, y);

		m_pScene->AddBulletEntity(bullet);*/

		// create bullet
		/*Bullet* bullet = new Bullet(nullptr, nullptr,
			new Rect(m_pRect->x + x * PLAYER_WIDTH_HEIGHT + (x * 2),
				m_pRect->y + y * PLAYER_WIDTH_HEIGHT + (y * 2), 16, 16), x, y);*/

		// add to list
		//m_pScene->AddMoveEntity(bullet);

		// set texture of bullet
		//bullet->GetTexture()->SetSDLTexture(m_pBulletTexture->GetSDLTexture());

		// set hits to true
		m_playerHits = true;
	}

	// get rect health bar
	Rect rect = *m_pHealthBar->GetRect();

	// set width
	rect.h = 64 * (m_health / 100.0f);

	// set rect x and y
	rect.x = m_pRect->x;
	rect.y = m_pRect->y - 8;

	// set rect of health bar
	m_pHealthBar->SetRect(&rect);

	// get rect health bar
	Rect rectRun = *m_pRunBar->GetRect();

	// set width
	rectRun.h = 64 * (m_xrun / 100.0f);

	// set rect x and y
	rectRun.x = m_pRect->x;
	rectRun.y = m_pRect->y - 20;

	// set rect of health bar
	m_pRunBar->SetRect(&rectRun);
}

void Player::Render(Renderer * _pRenderer)
{
	// x direction
	int x = 0;

	// y direction
	int y = 0;

	// set x direction
	if (m_angle == 0 || m_angle == 45 || m_angle == 315)
		x = 1;
	else if (m_angle == 135 || m_angle == 180 || m_angle == 225)
		x = -1;

	// set y direction
	if (m_angle == 45 || m_angle == 90 || m_angle == 135)
		y = 1;
	else if (m_angle == 225 || m_angle == 270 || m_angle == 315)
		y = -1;

	Actor::Render(_pRenderer);

	// render health bar
	m_pHealthBar->Render(_pRenderer);

	// render run bar
	m_pRunBar->Render(_pRenderer);
}

void Player::CheckMoveable(std::list<TexturedEntity*> _pEntities, float _deltaTime)
{
	// rect after movement frame
	Rect* nextRect = new Rect(m_pRect->x, m_pRect->y,
		m_pRect->w, m_pRect->h);

	// save input
	int x = 0;
	int y = 0;

	// rotate player to 0
	if (Input::GetKey(SDL_SCANCODE_D))
		x = 1;

	// rotate player to 90
	//if (Input::GetKey(SDL_SCANCODE_S))
	//	y = 1;

	// rotate player to 180
	if (Input::GetKey(SDL_SCANCODE_A))
		x = -1;

	// rotate player to 270
	//if (Input::GetKey(SDL_SCANCODE_W))
	//	y = -1;

	// increase rect x and y
	nextRect->x += x * m_speed * _deltaTime;
	nextRect->y += y;


	// rect for hits
	Rect rect;
	rect.h = 64;
	rect.w = 64;

	// reset x and y
	x = 0;
	y = 0;

	// set x direction
	if (m_angle == 0 || m_angle == 45 || m_angle == 315)
		x = 1;
	else if (m_angle == 135 || m_angle == 180 || m_angle == 225)
		x = -1;

	// set y direction
	if (m_angle == 45 || m_angle == 90 || m_angle == 135)
		y = 1;
	else if (m_angle == 225 || m_angle == 270 || m_angle == 315)
		y = -1;

	// set hit rect position
	rect.x = m_pRect->x + x * 64;
	rect.y = m_pRect->y + y * 64;

	// check entities
	for each (Entity* entity in _pEntities)
	{
		// check player moveable
		if
			(Physics::RectRectCollision(nextRect, entity->GetRect())
				&& (entity->GetColType() == ECollisionType::MOVE
					|| entity->GetColType() == ECollisionType::WALL))
			m_isMoveable = false;

		if (Physics::RectRectCollision(nextRect, entity->GetRect())
			&& (entity->GetColType() == ECollisionType::GROUND))
		{
			m_yMovement = 1;
			//m_Walkabel = false;
		}
	

		

		// if player hits
		if (m_playerHits)
		{
			if (entity->GetTag() != "Ranged" || entity->GetTag() != "Melee")
				continue;

			// if hit rect collides with entity
			if (Physics::RectRectCollision(&rect, entity->GetRect()))
			{
				((Ranged*)entity)->TakeDamage(25);
				((Melee*)entity)->TakeDamage(25);
			}
		}
	}
	
	
}