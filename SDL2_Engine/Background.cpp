/*
Beatrice Römer
*/

#include "Background.h"
#include "Texture.h"
#include "Renderer.h"
#include "Rect.h"

Background::Background(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect)
{
	// create Texture
	m_pTexture = new Texture(_pFileName, _pRenderer);

	// set rect
	m_pRect = _pRect;
}

Background::~Background()
{
}

void Background::Update(float _deltaTime)
{
}

void Background::Render(Renderer * _pRenderer)
{
	// render texture
	_pRenderer->RenderTexture(m_pTexture, m_pRect, nullptr, m_angle, true);
}

Rect * Background::GetRect()
{
	return m_pRect;
}

void Background::SetRect(Rect * _pRect)
{
	m_pRect->x = _pRect->x;
	m_pRect->y = _pRect->y;
	m_pRect->w = _pRect->w;
	m_pRect->h = _pRect->h;
}
