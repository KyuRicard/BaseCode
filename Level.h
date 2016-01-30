#pragma once
#include <vector>
#include "Tileset.h"
#include "Layer.h"
#include "TileLayer.h"

class Level
{
private:
	friend class LevelParser;	
	std::vector<Tileset> tilesets;
	std::vector<Layer *> layers;
public:
	Level(std::vector<Tileset>, std::vector<Layer *>);
	~Level();
	void Update();
	void Render();

	std::vector<Tileset> * getTilesets();
	std::vector<Layer *> * getLayers();
	std::vector<TileLayer *> * getCollidableTileLayers();
};