#pragma once
#include "Scene.h"

class Player;
class World;
class Background;

class MainScene : public Scene
{
public:
	// constructor
	MainScene(Engine* _pEngine);

	// destructor
	virtual ~MainScene();

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// update every frame
	virtual void Update(float _deltaTime) override;

	// load images
	virtual void Load(Renderer* _pRenderer) override;

	// unload images
	virtual void Unload() override;

private:
	// player
	Player* m_pPlayer;

	// fps text
	Text* m_pFPS;

	// world
	World* m_pWorld;

	// background
	Background* m_pBackground;

	// collision and delete of entities
	void CheckCollision(float _deltaTime);
};