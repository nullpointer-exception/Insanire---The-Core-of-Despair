#pragma once
#include <list>

class Engine;
class Entity;
class TexturedEntity;
class Renderer;
class Text;

class Scene
{
public:
	// constructor
	Scene(Engine* _pEngine);

	// destructor
	virtual ~Scene();

	// render every frame
	virtual void Render(Renderer* _pRenderer) = 0;

	// update every frame
	virtual void Update(float _deltaTime) = 0;

	// load images
	virtual void Load(Renderer* _pRenderer) = 0;

	// unload images
	virtual void Unload();

	// add move entity to list
	inline void AddMoveEntity(TexturedEntity* _pEntity) 
	{
		m_pMoveEntities.push_back(_pEntity);
	}

	// add entity to remove list
	inline void AddRemoveEntity(Entity* _pEntity)
	{
		m_pEntitiesToRemove.push_back(_pEntity);
	}

	// get engine
	inline Engine* GetEngine() { return m_pEngine; };

protected:
	// engine
	Engine* m_pEngine;

	// list of all move entities
	std::list<TexturedEntity*> m_pMoveEntities;

	// list of all texts
	std::list<Text*> m_pTexts;

	// list of entities to remove
	std::list<Entity*> m_pEntitiesToRemove;
};