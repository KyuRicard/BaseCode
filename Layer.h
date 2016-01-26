#pragma once

#include <vector>
#include "Tileset.h"

class Layer 
{
protected:
	std::vector<Tileset> tilesets;
public:
	Layer(std::vector<Tileset>);
	virtual void Render() = 0;
	virtual void Update() = 0;
	Tileset * GetTileset(int);
	std::vector<Tileset> GetTilesets()
	{
		return tilesets;
	}
};