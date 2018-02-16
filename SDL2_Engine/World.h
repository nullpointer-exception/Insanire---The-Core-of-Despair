#pragma once
#include "TexturedEntity.h"
#include <list>

class World : public TexturedEntity
{
public:
	// constructor
	World(Renderer* _pRenderer, const char* _pFile, Rect* _pRect);

	// destructor
	~World();

	// get world entities
	inline std::list<TexturedEntity*> GetEntities()
		{ return m_pEntities; };

	// load world
	void LoadWorld(Renderer* _pRenderer);

	// renderer entities
	void RenderEntities(Renderer* _pRenderer, int _playerPosX,
		int _playerPosY);

private:
	// world entities
	std::list<TexturedEntity*> m_pEntities;

	// world 2d array
	int m_world[50][25];
};