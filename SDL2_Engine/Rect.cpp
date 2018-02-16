#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(int _w, int _h)
{
	x = 0;
	y = 0;
	w = _w;
	h = _h;
}

Rect::Rect(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}