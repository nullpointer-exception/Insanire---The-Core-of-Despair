#include "World.h"
#include "Rect.h"
#include "Renderer.h"
#include <string>

World::World(Renderer * _pRenderer, const char * _pFile, Rect * _pRect)
	: TexturedEntity(_pRenderer, _pFile, _pRect)
{
}

World::~World()
{
	// save counter of entities
	int count = m_pEntities.size();

	// delete all entities
	for (int i = 0; i < count; i++)
		m_pEntities.pop_front();
}

void World::LoadWorld(Renderer * _pRenderer)
{
	// string to identify world
	std::string s;

	// fill string
	// W = water
	// 0 = way
	// S = street
	// X = house

	s += "X0WWWWWWWWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "X0WWWWWWWWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "X0WWWWWWWWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "X000WWW0000000WWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSS00000SSSSS0WWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XXXSSSSSXXXXX000WWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "X0WWWWWWSSSSSSS0WWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "X000WWWWWWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSS000WWWWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSXSS000WWWWWWWWWWW0XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSXSS0000000000000XSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSXSSSSSSSSSSSSSXSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XXXXXXXXXXXXXXXXXXXXXSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";
	s += "XSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSX";

	// go through all char
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			// switch chars
			// S = 0 x on atlas map
			// 0 = 64
			// W = 128
			// X = 192
			switch (s[y * 50 + x])
			{
			case 'S':
				m_world[x][y] = 0;
				break;
			case '0':
				m_world[x][y] = 64;
				break;
			case 'W':
				m_world[x][y] = 128;
				break;
			case 'X':
				m_world[x][y] = 192;
				break;
			default:
				break;
			}
		}
	}

	// create new textured entities
	// screen resolution 1280x720
	// 1 block 64x64
	// 20 x 12 blocks
	for (int i = 0; i < 22 * 14; i++)
	{
		m_pEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(64, 64)));
	}
	
}

void World::RenderEntities(Renderer * _pRenderer, int _playerPosX, int _playerPosY)
{
	// player position in x, y coordinates
	int posX = (_playerPosX - 640) / 64 - 1;
	int posY = (_playerPosY - 360) / 64 - 1;

	// destination and source rect
	Rect destination;
	Rect source;

	// go through all entities
	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 22; x++)
		{
			// save position x, y and tile id
			int realX = posX + x;
			int realY = posY + y;
			int tile = 0;

			// get entity at index
			std::list<TexturedEntity*>::iterator entity = std::next(
				m_pEntities.begin(), y * 21 + x);

			// if position out of world set tile to water
			if (realX < 0 || realX > 49 || realY < 0 || realY > 24)
			{
				//tile = 128;
				(*entity)->SetColType(ECollisionType::WALL);
			}

			// if position in world set tile and collision
			else
			{
				// set tile
				tile = m_world[realX][realY];

				// set collision
				if (tile == 192)
					(*entity)->SetColType(ECollisionType::WALL);
				else if (tile == 128)
				{
					//((TexturedEntity*)(*entity))->m_Walkabel = false;
					(*entity)->SetColType(ECollisionType::GROUND);
				}
				else
					(*entity)->SetColType(ECollisionType::NONE);
					//((TexturedEntity*)(*entity))->m_Walkabel = true;
			}

			// set destination rect
			destination.x = realX * 64;
			destination.y = (posY + y) * 64;
			destination.h = 64;
			destination.w = 64;

			// set rect of entity
			(*entity)->SetRect(&destination);

			// set source rect
			source.x = tile;
			source.y = 0;
			source.h = 64;
			source.w = 64;

			// render rect
			_pRenderer->RenderTexture(m_pTexture, &destination, &source, 0, true);
		}
	}
}