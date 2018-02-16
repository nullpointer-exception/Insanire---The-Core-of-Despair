#pragma once
#include <string>
#include "Macros.h"

#define HANDLE_ERROR(CHECK)						\
if(CHECK)										\
{												\
	std::cout << SDL_GetError() << std::endl;	\
	return false;								\
}												\

// get parent directory
std::string GetParentDirectory(std::string _path, int _depth = 1);

// get complete asset path
std::string GetAssetPath(const char* _path, int _depth = 1);