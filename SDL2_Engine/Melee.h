/*
Beatrice Römer
Oliver Aiberspach
*/


#pragma once
#include "Actor.h"
#include "Player.h"
#include "Scene.h"
//#include "Sound.h"
#include <list>

class Animation;

// Melee state
enum class EMeleeState
{
	IDLE,
	WALK,
	ATTACK
};

class Melee : public Actor
{
public:
	// constructor
	Melee(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect,
		const char* _phealthBarFileName);

	// destructor
	~Melee();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// set player reference
	inline void SetPlayer(Player* _pPlayer)
	{
		// set player
		m_pPlayer = _pPlayer;

		// set sound
		//m_pShotSound->SetSound(m_pPlayer->GetShotSound()->GetSound());
	};

	// get health
	inline int GetHealth() { return m_health; };

	// take damage
	inline void TakeDamage(int _damage)
	{
		m_health -= _damage;
		if (m_health <= 0)
			m_pPlayer->GetCurrentScene()->AddRemoveEntity((Entity*)this);
	};

	// increase health
	inline void IncreaseHealth(int _health)
	{
		m_health += _health;
		if (m_health > 100)
			m_health = 100;
	}

	// check collision
	void CheckCollision(std::list<TexturedEntity*> _pEntities, float _deltaTime);

private:
	// state
	EMeleeState m_state;

	// health
	int m_health = 100;

	// move direction x
	int m_directionX;

	// move direction y
	int m_directionY;

	// time in state
	float m_timeState;

	// player reference
	Player* m_pPlayer;

	// healthbar texture
	TexturedEntity* m_pHealthBar;

	// distance rect
	Rect* m_pDistanceRect;

	// current animation
	Animation* m_pCurrentAnimation;

	// idle animation
	Animation* m_pIdle;

	// walk animation
	Animation* m_pWalk;

	// attack animation
	Animation* m_pAttack;

	// shot sound
	//Sound* m_pShotSound;

	// change state
	void ChangeState();

	// check distance to player
	void CheckDistance();
};