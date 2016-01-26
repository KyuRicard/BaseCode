#pragma once
#include <iostream>
#include "Tileset.h"
#include "Vector2D.h"
#include <vector>
#include "Layer.h"

class TileLayer : public Layer
{
private:	
	Vector2D position;	
	bool hasCollision = false;
	std::vector<std::vector<int>> tileIDs;
	void Draw(std::string id, Tileset * tileset, int x, int y, int frame, int row);
public:
	TileLayer(int width, int height, int tilewidth, int tileheight, std::vector<Tileset>);
	int width, height;
	int tileWidth;
	int tileHeight;
	virtual ~TileLayer();
	virtual void Update();
	virtual void Render();
	void SetTileIDs(const std::vector<std::vector<int>>&);	
	bool IsCollidable();
	void SetCollision(bool);
	std::vector<std::vector<int>> GetTiles();
};