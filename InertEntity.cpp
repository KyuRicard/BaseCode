#include "InertEntity.h"
#include "Game.h"
#include "TextureManager.h"

InertEntity::InertEntity()
{

}

InertEntity::~InertEntity()
{

}

void InertEntity::Load(EntityParams * params)
{
	this->params = params;
	texture = params->GetId();
}

void InertEntity::Draw()
{
	SDL_Rect img, draw;
	img.x = 0;
	img.y = 0;
	img.w = params->GetWidth();
	img.h = params->GetHeight();

	draw.x = (int)params->GetXPos();
	draw.y = (int)params->GetYPos();
	draw.h = params->GetHeight();
	draw.w = params->GetWidth();

	SDL_RendererFlip flip = params->IsFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Texture * textura = TextureManager::GetInstance()->GetArray()[texture];
	SDL_RenderCopyEx(TheGame->GetRenderer(), textura, &img, &draw, 0, NULL, flip);
}

void InertEntity::DrawFrame() { Draw(); }

void InertEntity::Update()
{

}

void InertEntity::Clear()
{

}