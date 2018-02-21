#include "MainScene.h"
#include "Renderer.h"
#include "TexturedEntity.h"
#include "Rect.h"
#include "Helper.h"
#include "Player.h"
#include "Ranged.h"
#include "Melee.h"
#include "Text.h"
#include "Font.h"
#include "Color.h"
#include "Physics.h"
#include "FollowEntity.h"
#include "World.h"
#include "Time.h"
#include "MenuScene.h"
#include "Pickup.h"
#include "Background.h"

MainScene::MainScene(Engine * _pEngine)
	: Scene(_pEngine)
{
}

MainScene::~MainScene()
{
}

void MainScene::Render(Renderer * _pRenderer)
{
	// set camera position before rendering anything
	_pRenderer->m_CameraX = m_pPlayer->GetRect()->x + m_pPlayer->GetRect()->w / 2;
	_pRenderer->m_CameraY = m_pPlayer->GetRect()->y + m_pPlayer->GetRect()->h / 2;

	// render background
	m_pBackground->Render(_pRenderer);

	// render world entities
	m_pWorld->RenderEntities(_pRenderer, m_pPlayer->GetRect()->x, m_pPlayer->GetRect()->y);

	// render player
	m_pPlayer->Render(_pRenderer);

	// render every move entity
	for each(TexturedEntity* entity in m_pMoveEntities)
		entity->Render(_pRenderer);

	// render every move entity
	for each(Entity* entity in m_pMoveEntities)
		entity->Render(_pRenderer);

	// render every text
	// important text after entities
	for each (Text* text in m_pTexts)
		text->Render(_pRenderer);

	// set string
	std::string fpsText = "FPS: ";
	fpsText.append(std::to_string(Time::GetFPS()));

	// set text of fpsText
	m_pFPS->SetText(fpsText.c_str());

	// load text
	m_pFPS->Load(_pRenderer);

	// render fps text
	m_pFPS->Render(_pRenderer);
}

void MainScene::Update(float _deltaTime)
{
	// update every move entity
	for each(TexturedEntity* entity in m_pMoveEntities)
		entity->Update(_deltaTime);

	// update player
	m_pPlayer->Update(_deltaTime);

	// set player moveable
	m_pPlayer->SetMoveable(true);

	// check player collision
	m_pPlayer->CheckMoveable(m_pWorld->GetEntities(), _deltaTime);

	// check player collision with move entities
	m_pPlayer->CheckMoveable(m_pMoveEntities, _deltaTime);

	// check collision for all entities
	for each(TexturedEntity* entity in m_pMoveEntities)
	{
		// if entity is ranged
		if (entity->GetTag() == "Ranged")
		{
			((Ranged*)entity)->CheckCollision(m_pMoveEntities, _deltaTime);
			((Ranged*)entity)->CheckCollision(m_pWorld->GetEntities(), _deltaTime);
		}

		// if entity is melee
		if (entity->GetTag() == "Melee")
		{
			((Melee*)entity)->CheckCollision(m_pMoveEntities, _deltaTime);
			((Melee*)entity)->CheckCollision(m_pWorld->GetEntities(), _deltaTime);
		}
	}

	// check collision
	CheckCollision(_deltaTime);
}

void MainScene::Load(Renderer * _pRenderer)
{
	// create background
	m_pBackground = new Background(_pRenderer,
		GetAssetPath("Texture/World/Background_Wald2.png", 5).c_str(),
		new Rect(0, 0, 1280, 720));

	// create player
	m_pPlayer = new Player(_pRenderer, 
		GetAssetPath("Texture/Character/T_Character_Idle.png", 5).c_str(), 
		new Rect(66, 192, 64, 64), GetAssetPath("Texture/HealthBar/HP_Full.png", 5).c_str(),
		GetAssetPath("Texture/HealthBar/Ausdauer_Leiste.png", 5).c_str());

	// set speed
	m_pPlayer->SetSpeed(750);

	// set current scene of player
	m_pPlayer->SetCurrentScene(this);

	// create text
	m_pFPS = new Text(new Rect(100, 50), "FPS:",
		new Font(GetAssetPath("Texture/Font/T_Arial.ttf", 5).c_str(), 24),
		new Color());

	// load text
	m_pFPS->Load(_pRenderer);

	// create new world
	m_pWorld = new World(_pRenderer, GetAssetPath("Texture/World/T_World.png", 5).c_str(),
		new Rect());

	// load world
	m_pWorld->LoadWorld(_pRenderer);

	// create ranged
	Ranged* ranged = new Ranged(_pRenderer, GetAssetPath("Texture/Character/T_Enemy_Idle.png", 5).c_str(),
	new Rect(768, 192, 64, 64), GetAssetPath("Texture/Character/T_HealthBar.png", 5).c_str());
	
	//for (int i = 0; i < 5; i++)
	//{
	//	if (ranged <= i)
	//	{
			// set collision type
			ranged->SetColType(ECollisionType::MOVE);

			// set player reference
			ranged->SetPlayer(m_pPlayer);

			// add enemy to list
			m_pMoveEntities.push_back(ranged);
	//	}
	//}

	// create melee
	Melee* melee = new Melee(_pRenderer, GetAssetPath("Texture/Character/T_Enemy_Idle.png", 5).c_str(),
		new Rect(768, 192, 64, 64), GetAssetPath("Texture/Character/T_HealthBar.png", 5).c_str());

	// set collision type
	melee->SetColType(ECollisionType::MOVE);

	// set player reference
	melee->SetPlayer(m_pPlayer);

	// add enemy to list
	m_pMoveEntities.push_back(melee);

	// create new pickup
	Pickup* pickup = new Pickup(_pRenderer, GetAssetPath("Texture/Items/T_Flag.png", 5).c_str(),
		new Rect(100, 460, 32, 32));

	// set collision type
	pickup->SetColType(ECollisionType::BULLET);

	// add pickup to list
	m_pMoveEntities.push_back(pickup);
}

void MainScene::Unload()
{
	// delete all entities to remove
	while (m_pEntitiesToRemove.size() > 0)
	{
		// get first entity
		Entity* entity = m_pEntitiesToRemove.front();

		// remove entity from entites to remove
		m_pEntitiesToRemove.remove(entity);

		// remove entity from move entites
		m_pMoveEntities.remove((TexturedEntity*)entity);

		// delete entity
		delete entity;
	}

	while (m_pTexts.size() > 0)
	{
		// get first text
		Text* text = m_pTexts.front();

		// remove text from text list
		m_pTexts.remove(text);

		// delete text
		delete text;
	}

	while (m_pMoveEntities.size() > 0)
	{
		// get first entity
		TexturedEntity* entity = m_pMoveEntities.front();

		// remove entity from entity list
		m_pMoveEntities.remove(entity);

		// delete entity
		delete entity;
	}

	// delete background
	delete m_pBackground;

	// delete world
	delete m_pWorld;

	// delete fps text
	delete m_pFPS;

	// delete player
	delete m_pPlayer;

	// unload parent
	Scene::Unload();
}

void MainScene::CheckCollision(float _deltaTime)
{
	// bool if player dead
	bool playerDead = false;

	// check all move entities
	for each (TexturedEntity* entity in m_pMoveEntities)
	{
		// if bullet
		if (entity->GetColType() == ECollisionType::BULLET)
		{
			// check all move entities
			for each (TexturedEntity* moveEntity in m_pMoveEntities)
			{
				// if bullet is pickup and move entity is ranged
				if (entity->GetTag() == "Pickup" &&
					moveEntity->GetTag() == RANGED)
				{
					// check collision
					if (Physics::RectRectCollision(entity->GetRect(), moveEntity->GetRect()))
					{
						// increase health and add pickup to remove list
						((Ranged*)moveEntity)->IncreaseHealth(25);
						m_pEntitiesToRemove.push_back(entity);
					}
				}

				// if bullet is pickup and move entity is ranged
				if (entity->GetTag() == "Pickup" &&
					moveEntity->GetTag() == MELEE)
				{
					// check collision
					if (Physics::RectRectCollision(entity->GetRect(), moveEntity->GetRect()))
					{
						// increase health and add pickup to remove list
						((Melee*)moveEntity)->IncreaseHealth(25);
						m_pEntitiesToRemove.push_back(entity);
					}
				}

				// if collision type none or bullet ignore entity
				if (moveEntity->GetColType() == ECollisionType::NONE ||
					moveEntity->GetColType() == ECollisionType::BULLET)
					continue;

				// check collision
				if (Physics::RectRectCollision(entity->GetRect(), moveEntity->GetRect()))
				{
					m_pEntitiesToRemove.push_back(entity);

					// if hitted move entity is enemy
					if (moveEntity->GetTag() == RANGED)
					{
						// take damage
						((Ranged*)moveEntity)->TakeDamage(25);
					}

					// if hitted move entity is enemy
					if (moveEntity->GetTag() == MELEE)
					{
						// take damage
						((Melee*)moveEntity)->TakeDamage(25);
					}
				}
			}

			// check all move entities
			for each (TexturedEntity* moveEntity in m_pWorld->GetEntities())
			{
				// if collision type none or bullet ignore entity
				if (moveEntity->GetColType() == ECollisionType::NONE ||
					moveEntity->GetColType() == ECollisionType::BULLET)
					continue;

				// check collision
				if (Physics::RectRectCollision(entity->GetRect(), moveEntity->GetRect()))
				{
					m_pEntitiesToRemove.push_back(entity);
				}
			}

			// if bullet hits player
			if (Physics::RectRectCollision(entity->GetRect(), m_pPlayer->GetRect()))
			{
				// if bullet type is pickup
				if (entity->GetTag() == "Pickup")
				{
					// check collision
					if (Physics::RectRectCollision(entity->GetRect(), m_pPlayer->GetRect()))
					{
						// increase player health and add pickup to remove list
						//m_pPlayer->IncreaseHealth(25);
						playerDead = true;
						m_pEntitiesToRemove.push_back(entity);
					}
				}

				// if normal bullet
				else
				{
					// add to remove list and take damage on player
					m_pEntitiesToRemove.push_back(entity);
					m_pPlayer->TakeDamage(5);
				}

				// if player health under 0 set bool
				if (m_pPlayer->GetHealth() <= 0)
					playerDead = true;
			}
		}
}	

	// as long as there is a entity to remove
	// NO FOR EACH !!!
	while (m_pEntitiesToRemove.size() > 0)
	{
		// get first entity
		Entity* entity = m_pEntitiesToRemove.front();

		// remove entity from entites to remove
		m_pEntitiesToRemove.remove(entity);

		// remove entity from move entites
		m_pMoveEntities.remove((TexturedEntity*)entity);
	
		// delete entity
		delete entity;
		}

		// if player dead change scene
		if (playerDead)
		{
			MenuScene* menuScene = new MenuScene(m_pEngine);
			m_pEngine->ChangeScene(menuScene);
		}
	}