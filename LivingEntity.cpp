#include "LivingEntity.h"
#include <SDL.h>
#include "TextureManager.h"
#include "Game.h"
#include <cmath>
#include "Camera.h"

using namespace std;

LivingEntity::LivingEntity() : Entity()
{
	callback = nullptr;
}


LivingEntity::~LivingEntity()
{
	
}

void LivingEntity::Move(float xPos, float yPos)
{	
	if (xPos < 0 && !params->IsFlipped() || xPos > 0 && params->IsFlipped())
		params->Flip();
	if (SDL_GetTicks() % 100 / (int)Game::GetInstance()->delta == 0)
		params->AddFrame();
	params->AddXPos(xPos);	
}

void LivingEntity::Accelerate(int aX, int aY)
{
	velocity.X += (aX * acceleration.X);
	velocity.Y += (aY * acceleration.Y);

	if (velocity.X > 0)
		velocity.X = fmin(velocity.X, maxVel.X);
	else if (velocity.X < 0)
		velocity.X = fmax(velocity.X, -maxVel.X);
	if (velocity.Y > 0)
		velocity.Y = fmin(velocity.Y, maxVel.Y);
	else if (velocity.Y < 0)
		velocity.Y = fmax(velocity.Y, -maxVel.Y);

	velocity.X *= (1 - friction.X);

	if (abs(velocity.X) < 0.1)
	{
		velocity.X = 0;
	}

	int oldX = position.X;
	if (params->IsFlipped())
	{
		oldX++;
	}
	else
	{
		oldX--;
	}
	if (!IsCollidingWithTile((int)position.X + (int)velocity.X, (int)position.Y)) {
		position.X += velocity.X;
	}
	else {
		this->onCollide(NULL);
	}
		
	if (!IsCollidingWithTile(oldX, (int)position.Y + (int)velocity.Y)) {
		position.Y += velocity.Y;
		inAir = true;
	}
	else if (inAir) {
		inAir = false;
		position.Y = (float)getYGravity((int)position.X, (int)position.Y);
	}

	bool isFlipped;

	if (aX > 0)
		isFlipped = false;
	else if (aX < 0)
		isFlipped = true;
	else if (aX == 0)
		isFlipped = params->IsFlipped();

	params->SetFlipped(isFlipped);

	if (SDL_GetTicks() % 3 == 0 && aX != 0)
		params->AddFrame();	
}

void LivingEntity::Load(EntityParams * params)
{
	this->params = params;
	position.X = params->GetXPos();
	position.Y = params->GetYPos();
	velocity = Vector2D(0, 0);
	friction = Vector2D(0.25, 0.25);
}

void LivingEntity::Draw()
{
	SDL_Rect img, draw;
	img.x = 0;
	img.y = 0;
	img.w = params->GetWidth();
	img.h = params->GetHeight();

	draw.x = (int)position.X;
	draw.y = (int)position.Y;
	draw.h = params->GetHeight();
	draw.w = params->GetWidth();

	SDL_RendererFlip flip = params->IsFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Texture * textura = TextureManager::GetInstance()->GetArray()[params->GetId()];
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), textura, &img, &draw, 0, NULL, flip);
}

void LivingEntity::DrawFrame()
{
	const Vector2D * camPos = TheCam->GetPosition();

	if (position.X - camPos->X < 0 || position.X - camPos->X > Tools::GetWidth() ||
		position.Y - camPos->Y < 0 || position.Y - camPos->Y > Tools::GetHeight())
		return;
	SDL_Rect img, draw;

	img.x = params->GetWidth() * params->GetFrame();
	img.y = params->GetHeight() * params->GetRow();
	img.w = params->GetWidth();
	img.h = params->GetHeight();

	draw.x = (int)position.X - (int)camPos->X;
	draw.y = (int)position.Y - (int)camPos->Y;
	draw.w = params->GetWidth();
	draw.h = params->GetHeight();

	SDL_RendererFlip flip = params->IsFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Texture * textura = TextureManager::GetInstance()->GetArray()[texture];
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), textura, &img, &draw, 0, NULL, flip);
}

void LivingEntity::Update()
{
	
}

void LivingEntity::Clear()
{
	this->~LivingEntity();
}

bool LivingEntity::IsCollidingWithTile(int x, int y) {
	
	for each (TileLayer * layer in *collisionLayers) {
		vector<vector<int>> tiles = layer->GetTiles();
		int size = layer->GetTileset(0)->tileWidth;
		int yReal = y - Tools::GetHeight() + ((tiles.size() + 1) * size);
		int row = yReal / size;
		int row2 = (yReal + size) / size;
		int cell = x / size;
		int cell2 = (x + size) / size;
		if ((unsigned int)row >= tiles.size())
			return false;
		if ((unsigned int)x + GetWidth() >= tiles.size() * size || x < 0  || yReal < 0)
			return true;
		int x2 = x + size;
		int y2 = y + size;

		if (cell == cell2)
		{
			if (tiles[row][cell] != 0)
			{
				return true;
			}
		}
		else if (row == row2)
		{
			if (tiles[row][cell] != 0)
			{
				return true;
			}
		}
		//Check Horitzonal collision
		else if (x + collisionMargin >= cell * size || x2 - collisionMargin <= (1 + cell) * size)
		{			
			if (tiles[row][cell] != 0 || tiles[row][cell + 1] != 0)
			{
				return true;
			}			
		}
		//Check Vertical collision
		else if (tiles[row][cell] != 0 || tiles[row + 1][cell] != 0)
		{
			return true;
		}
	}
	return false;
}

void LivingEntity::LoadCollisionLayers(vector<TileLayer *> * layers) {
	if (collisionLayers == NULL)
	{
		collisionLayers = new vector<TileLayer *>();
	}
	this->collisionLayers = layers;
}

int LivingEntity::getYGravity(int x, int y)
{
	for each (TileLayer * layer in *collisionLayers) {
		vector<vector<int>> tiles = layer->GetTiles();
		int size = layer->GetTileset(0)->tileWidth;
		int yReal = y - Tools::GetHeight() + ((tiles.size() + 1) * size);
		int row = yReal / size;
		int cell = x / size;
		int newY = (row)* size - ((tiles.size() + 1) * size) + Tools::GetHeight();
		return newY + size - 1;
	}
	return 0;
}

void LivingEntity::Die()
{
	this->position.X = -150;
	this->position.Y = 500;
}