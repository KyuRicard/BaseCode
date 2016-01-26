#include "TileLayer.h"
#include "Tools.h"
#include "Loaders.h"
#include "Game.h"
#include "GameStates.h"
#include "Camera.h"

TileLayer::TileLayer(int width, int height, int tileWidth, int tileHeight, std::vector<Tileset> tileSets) : Layer(tileSets)
{
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;	
}

TileLayer::~TileLayer()
{
}

void TileLayer::Update()
{
	position.X = TheCam->GetPosition()->X;
	position.Y = 0;
}

void TileLayer::Render()
{
	Vector2D scr((float)Tools::GetWidth(), (float)Tools::GetHeight());
	int firstRow = (int)TheCam->GetPosition()->X / tileWidth;
	int lastRow = (int)(TheCam->GetPosition()->X + Tools::GetWidth()) / tileWidth;
	int firstCell = Tools::ToCell((int)TheCam->GetPosition()->Y, this);
	int lastCell = Tools::ToCell((int)(TheCam->GetPosition()->Y + Tools::GetHeight()), this);
	lastRow++;
	for (int row = firstRow; row < lastRow; row++) 
	{
		for (int tile = firstCell; tile < lastCell; tile++)
		{		
			if ((unsigned int)row >= tileIDs[tile].size())
				continue;
			int current = tileIDs[tile][row];
			if (current == 0)
				continue;
			
			int x1 = (row * tileWidth);
			int x2 = x1 + tileWidth;
			int y1 = Tools::GetHeight() - (height - tile) * tileHeight;
			int y2 = y1 + tileHeight;

			if (y1 < 0 && y2 < 0)
				continue;
						
			Tileset * ts = GetTileset(current);
			current--;
			Draw(ts->name, ts, (int)(x1 - position.X), (int)(y1 - position.Y),
				(current - (ts->firstGridID - 1)) / ts->numColumns,
				(current - (ts->firstGridID - 1)) % ts->numColumns);
		}
	}
}

void TileLayer::SetTileIDs(const std::vector<std::vector<int>>& tileIDs)
{
	this->tileIDs = tileIDs;
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

bool TileLayer::IsCollidable() {
	return this->hasCollision;
}

void TileLayer::SetCollision(bool collidable) {
	this->hasCollision = collidable;
}

vector<vector<int>> TileLayer::GetTiles() {
	return tileIDs;
}