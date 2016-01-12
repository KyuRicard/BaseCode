#include "TileLayer.h"
#include "Tools.h"
#include "Loaders.h"
#include "Game.h"

TileLayer::TileLayer(int width, int height, int tileWidth, int tileHeight, std::vector<Tileset> tileSets)
{
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tilesets = tileSets;
}

TileLayer::~TileLayer()
{
}

void TileLayer::Update(Player * player)
{
	position.X = 0;
	position.Y = 0;
}

void TileLayer::Render()
{
	Vector2D scr((float)Tools::GetWidth(), (float)Tools::GetHeight());
	for (int row = 0; row < width; row++) 
	{
		for (int tile = 0; tile < height; tile++)
		{		
			int current = tileIDs[tile][row];
			if (current == 1 || current == 0)
				continue;

			
			int x1 = (row * tileWidth) - (position.X / tileWidth);
			int x2 = x1 + tileWidth;
			int y1 = Tools::GetHeight() - (90 - tile) * tileHeight;
			int y2 = y1 + tileHeight;

			// si tile = height, y2 = Tools::GetHeight(), x tant:
			// si tile = 0, y2 = Tools::GetHeight() - 90 * tileHeight
			// x tant, y2 = Tools::GetHeight() - (90 - tile) * tileHeight


			if (y1 < 0 && y2 < 0)
				continue;
			if (x1 < 0 && x2 < 0 || x1 > Tools::GetWidth() && x1 > Tools::GetWidth())
				continue;
			
			Tileset * ts = GetTileset(current);
			current--;
			Draw(ts->name, ts, x1 - position.X, y1 - position.Y, 
				(current - (ts->firstGridID - 1)) / ts->numColumns,
				(current - (ts->firstGridID - 1)) % ts->numColumns);
		}
	}
}

void TileLayer::SetTileIDs(const std::vector<std::vector<int>>& tileIDs)
{
	this->tileIDs = tileIDs;
}

Tileset * TileLayer::GetTileset(int ts)
{
	int f = 0;
	for (unsigned int i = 0; i < tilesets.size(); i++)
	{
		if (tilesets.at(i).firstGridID <= ts)
			f = i;
		else
			break;
	}
	return &tilesets.at(f);
}

void TileLayer::Draw(string id, Tileset * ts, int x, int y, int row, int frame)
{
	//source = IMATGE; draw = PANTALLA;
	SDL_Rect source, draw;
	
	source.x = ts->margin + (ts->spacing + ts->tileWidth) * (frame);
	source.y = ts->margin + (ts->spacing + ts->tileHeight) * row;
	source.w = ts->tileWidth;
	source.h = ts->tileHeight;

	draw.w = tileWidth;
	draw.h = tileHeight;
	draw.x = x;
	draw.y = y;

	SDL_Texture * textura = TextureManager::GetInstance()->GetArray()[id];
	SDL_RenderCopy(TheGame->GetRenderer(), textura, &source, &draw);
}