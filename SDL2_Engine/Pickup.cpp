#include "Pickup.h"

Pickup::Pickup(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect)
	: TexturedEntity(_pRenderer, _pFileName, _pRect)
{
	// set tag
	m_pTag = "Pickup";
}