#pragma once
#include <tinyxml2.h>
#include <vector>
#include "Tileset.h"
#include "Layer.h"
#include "Level.h"

class LevelParser
{
private:
	static void parseTilesets(tinyxml2::XMLElement * root, std::vector<Tileset> * tilesets);
	static void parseTileLayer(tinyxml2::XMLElement * tileElement, std::vector<Layer *> * layers,
		std::vector<Tileset> * tilesets, int tileWidth, int tileHeight);
	static void parserObjectLayer(tinyxml2::XMLElement * objElement, std::vector<Layer *> * layers,
		std::vector<Tileset> * tilesets);
public:
	static Level * parseLevel(const std::string file);
};