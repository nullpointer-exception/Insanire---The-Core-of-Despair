#pragma once

#include <SDL.h>
#include <stdio.h>
#include "Engine.h"

//class Renderer;
//class Color;

class GUI
{
public:
	// constructor
	GUI();

	// load image
	bool Load();
	
	// clear
	void Clear();

	void Render();

	//// load images
	//void Load(const char* _pFileName);
	//
	//// load animated images
	//void Load(const char* _pFileName, int _with, int _heigth);

private:
	// if program is running
	bool m_isRunning;

	// current scene
	Scene* m_pScene;

	// sdl window
	SDL_Window* m_pWindow;

	// sdl surface
	SDL_Surface* m_pSurface;

	// renderer
	Renderer* m_pRenderer;

	// time
	Time* m_pTime;

	// render every frame
	void Render();

	// update every frame
	void Update();
}; };

