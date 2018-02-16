#include "TexturedEntity.h"
#include "Texture.h"
#include "Renderer.h"
#include "Rect.h"

TexturedEntity::TexturedEntity(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect)
{
	// create texture
	m_pTexture = new Texture(_pFileName, _pRenderer);

	// set rect
	m_pRect = _pRect;
}

TexturedEntity::~TexturedEntity()
{
	// important to delete pointer
	if(m_colType != ECollisionType::BULLET)
		delete m_pTexture;

	delete m_pRect;
}

void TexturedEntity::Update(float _deltaTime)
{
}

void TexturedEntity::Render(Renderer * _pRenderer)
{
	// render texture
	_pRenderer->RenderTexture(m_pTexture, m_pRect, nullptr, m_angle, true);
}

Rect * TexturedEntity::GetRect()
{
	return m_pRect;
}

void TexturedEntity::SetRect(Rect * _pRect)
{
	m_pRect->x = _pRect->x;
	m_pRect->y = _pRect->y;
	m_pRect->w = _pRect->w;
	m_pRect->h = _pRect->h;
}