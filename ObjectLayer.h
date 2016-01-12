#pragma once
#include <vector>
#include "Layer.h"
#include "Entity.h"
#include "Tileset.h"

class ObjectLayer : public Layer
{
private:
	std::vector<Entity *> entities;
	std::vector<Tileset> tilesets;
public:
	ObjectLayer(std::vector<Tileset> tilesets)
	{
		this->tilesets = tilesets;
	}

	virtual void render();
	virtual void update();

	std::vector<Entity *> * getEntities() 
	{
		return &entities;
	}
};