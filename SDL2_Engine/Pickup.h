#pragma once
#include "TexturedEntity.h"

class Pickup : public TexturedEntity
{
public:
	// constructor
	Pickup(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect);
};