#pragma once

#include <tinyxml2.h>
#include "Tileset.h"
#include "Layer.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Level.h"
#include <iostream>
#include <vector>
#include <zlib.h>
#include <base64.h>

class LevelParser
{
private:	
	static void ParseTilesets(tinyxml2::XMLElement *, vector<Tileset> *);
	static void ParseTileLayer(tinyxml2::XMLElement *, std::vector<Layer *> *, std::vector<Tileset> *, int, int);
	static void ParseObjectLayer(tinyxml2::XMLElement *, std::vector<Layer *> *, std::vector<Tileset> *, int, int);
public:	
	static Level * ParseLevel(std::string);
	static bool CheckLevel(std::string);
};