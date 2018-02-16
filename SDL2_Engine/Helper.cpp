#include "Helper.h"
#include <SDL.h>

std::string GetParentDirectory(std::string _path, int _depth)
{
	// get parent directory recursive
	if (_depth > 1)
	{
		_path = GetParentDirectory(_path, _depth - 1);
	}

	//position of last sub
	size_t pos = _path.find_last_of("\\/");

	//return parent
	// if() else -> if() ? :
	return (std::string::npos == pos)
		? ""
		: _path.substr(0, pos);
}

std::string GetAssetPath(const char* _path, int _depth)
{
	// get parent directory
	std::string path = GetParentDirectory(SDL_GetBasePath(), _depth);

	// append sub path
	path.append("/Build/Assets/").append(_path);

	return path;
}