/*
Beatrice Römer
*/

#pragma once
#include "Entity.h"

class Texture;
class Rect;

class Background : public Entity
{
public:
	// constructor
	Background(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect);

	// destructor
	~Background();

	// update every Frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// get rect
	virtual Rect* GetRect() override;

	// set rect
	virtual void SetRect(Rect* _pRect) override;

	// get texture
	inline Texture* GetTexture() { return m_pTexture; };

	// get angle
	inline float GetAngle() { return m_angle; };

	// set angle
	inline void SetAngle(float _angle) { m_angle = _angle; };

protected:
	// angle
	float m_angle;

	// texture
	Texture* m_pTexture;

	// rect
	Rect* m_pRect;
};