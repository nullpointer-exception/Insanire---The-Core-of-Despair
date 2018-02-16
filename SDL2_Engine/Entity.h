#pragma once

class Rect;
class Renderer;

enum ECollisionType
{
	NONE,
	MOVE,
	WALL,
	BULLET,
	GROUND
	
};

class Entity
{
public:
	// get rect
	virtual Rect* GetRect() = 0;

	// set rect
	virtual void SetRect(Rect* _pRect) = 0;

	// update every frame
	virtual void Update(float _deltaTime) = 0;

	// render every frame
	virtual void Render(Renderer* _pRenderer) = 0;

	// get collision type
	inline ECollisionType GetColType() { return m_colType; };

	// set collision type
	inline void SetColType(ECollisionType _type)
		{ m_colType = _type; };

	// get tag
	inline char* GetTag() { return m_pTag; };

	// set tag
	inline void SetTag(char* _pTag) { m_pTag = _pTag; };

protected:
	// collision type
	ECollisionType m_colType;

	// tag of entity
	char* m_pTag;
};