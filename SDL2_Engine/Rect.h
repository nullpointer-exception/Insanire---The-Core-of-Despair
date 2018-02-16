#pragma once
#include "SDL_rect.h"

class Rect : public SDL_Rect
{
public:
	// construtor
	Rect();

	// constructor with with and height
	Rect(int _w, int _h);

	// constructor with with, height, x and y pos
	Rect(int _x, int _y, int _w, int _h);
};